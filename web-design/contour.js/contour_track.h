#pragma once

/*
	����һ�������׷�ٵ�ֵ��
	ʹ�÷���
	1.����contr::contour_track ����
	2.����׷�� contr::contour_track::begin_track()
	3.��ȡ���е�ֵ�� contr::contour_track::get_all_iso_line();
*/

#include "contr.h"

namespace contr{

	//��ֵ����Ϣ
	struct iso_point
	{
		int row;          //����������ǰ������ߣ�ע�����ߣ������
		int col;         //��������е����ֵҪ��rows colsС1

		pointxy<double> xy;

		bool is_horizon;     //��ֵ���Ƿ���X���ϣ�ˮƽ���ϣ�   true--X   false--Y

		iso_point(int r=0,int c=0,bool h=true,double x=0,double y=0)
			:row(r),col(c),is_horizon(h),xy(x,y)
		{}
	};

	//ÿ�����ϵ���Ϣ�����޵�ֵ�㣬��ʱ���ںδ���_rate��
	struct edge_info         
	{
		bool have_iso_point;   //�ڴ˱����Ƿ��е�ֵ��
		double rate;		
	};

	struct iso_line     //��ֵ�ߵ���Ϣ
	{
		std::vector<iso_point> line;
		double value;     //ָʾ��ǰ��ֵ�ߵ�ֵ
	};

	class contour_track
	{
	public:
		typedef std::vector<std::vector<edge_info> > edge_side_type;
		typedef std::vector<iso_line> iso_line_array;
	private:
		int n_level; //��ֵ����
		std::vector<double> contour_level;
		bool is_set_default_level;  //�Ƿ����ó�ΪĬ�ϵĵ�ֵ�ߵȼ���Ĭ��Ϊ10�ȷ�


		std::string pre_filename;      //��ǰ���ļ������������Ƿ��ٴζ�ȡ����
		access_contour acc_contr;
		int grid_rows,grid_cols;
		double delt_x,delt_y;//x y ������ֵ

		const double Excursion;     //����ֵ

		edge_side_type x_side, y_side;

		double cur_follow_value;       //��ǰ����׷�ٵĵ�ֵ��ֵ
		iso_point pre_iso_point, cur_iso_point, next_iso_point;

		iso_line now_iso_line;    //��ǰ��ֵ��
		iso_line_array all_iso_line;     //���е�ֵ��
		
	public:

		contour_track(std::string filename="")
			:Excursion(0.001)
		{
			n_level = 10;
			is_set_default_level = true;
			pre_filename = filename;
		}

		void begin_track()
		{
			acc_contr.get_grid_data(pre_filename);

			grid_rows = acc_contr.gd_info().rows;
			grid_cols = acc_contr.gd_info().cols;

			x_side.assign(grid_rows,std::vector<edge_info> (grid_cols-1));
			y_side.assign(grid_rows-1,std::vector<edge_info> (grid_cols));

			if (is_set_default_level)
                set_default_level();
            else
                SetContourLevel();      //�û��Զ����ֵ�� ĿǰΪ�պ���

			delt_x = (acc_contr.gd_info().xmax-acc_contr.gd_info().xmin)/(grid_cols-1);
			delt_y = (acc_contr.gd_info().ymax-acc_contr.gd_info().ymin)/(grid_rows-1);

			for (int i = 0; i < n_level; i++)
            {
                cur_follow_value = contour_level[i];

                interpolate_tracing_value(); //ɨ�貢�����ݡ�����ϵ�ֵ������

                tracing_non_closed_contour();  //׷�ٿ���ֵ��

                tracing_closed_contour();    //׷�ٷ�յ�ֵ��
            }


		}

		iso_line_array get_all_iso_line()
		{
			return all_iso_line;
		}

	private:

		void interpolate_xy(std::vector<std::vector<edge_info> > &edge, bool is_horizon)
		{
			/*      ������ʶ����:
        
            (i+1,j)��--------��(i+1,j+1)
                    |        |
                    |        |
                    ��       |
	                |        |
	         (i,j) ��--------��(i,j+1)

              i:��ʾ�к�(��������)
			  j:��ʾ�к�(��������)
			  ��ʶһ�����񽻵�ʱ���к���ǰ���к����ң��磺(i,j)
            */

            /*
             * ���ж�ˮƽ����h0--(i, j)   h1--(i, j+1)  _xSide, _ySide�е�_rateΪ(value-h0)/(h1-h0)
             */

			double h0, h1;       //��¼һ�����ϵ�����ֵ

			std::vector<grid_point> gridPoints = acc_contr.gdpts();

			//ɨ��ÿһ����
			for (size_t i = 0; i < edge.size(); i++)
			{
				for (size_t j = 0; j < edge[i].size(); j++)
				{
					h0 = gridPoints[i * grid_cols + j].value;
					if(is_horizon)
					{
						//x�ߵĶ˵�
						h1 = gridPoints[i * grid_cols + j + 1].value;
					}
					else
					{
						h1 = gridPoints[(i + 1) * grid_cols + j].value;
					}

					if (beql(h0, h1))
					{
						edge[i][j].rate = -2.0;
						edge[i][j].have_iso_point = false;
					}
					else
					{
						double flag = (cur_follow_value - h0) * (cur_follow_value - h1);

						if (flag > 0) //ͬʱ���ڻ�С�����˵�
						{
							edge[i][j].rate = -2.0;
							edge[i][j].have_iso_point = false;
						}
						else if (flag < 0) //������֮��
						{
							edge[i][j].rate = (cur_follow_value - h0) / (h1 - h0);
							edge[i][j].have_iso_point = true;
						}
						else //������һ�����
						{
							//����
							if (beql(cur_follow_value, h0))
								h0 += Excursion;
							else
								h1 += Excursion;

							edge[i][j].rate = (cur_follow_value - h0) / (h1 - h0);

							if (edge[i][j].rate < 0 || edge[i][j].rate > 1)
								edge[i][j].have_iso_point = false;
							else
								edge[i][j].have_iso_point = true;
						}
					}
				}
			}
		}


		//ɨ�貢����ᡢ�ݱ��ϵ�ֵ���������õ�_xSide, _ySide��ֵ��
		void interpolate_tracing_value()
		{
			interpolate_xy(x_side,true);
			interpolate_xy(y_side,false);
		}

		void tracing_non_closed_contour()
		{
			//׷����߿�
            for (int i = 0; i < grid_rows-1; i++)
            {
				if (y_side[i][0].have_iso_point)
                {
                    pre_iso_point = iso_point(i,-1,false);
                    cur_iso_point = iso_point(i, 0,false);

                    tracing_one_non_closed_contour();
                }
            }
			//׷���ϱ߿�
            for (int j = 0; j < grid_cols-1; j++)
            {
				if (x_side[grid_rows-1][j].have_iso_point)
                {
                    pre_iso_point = iso_point(grid_rows-1,j,true);
                    cur_iso_point = iso_point(grid_rows-1,j,true);

                    tracing_one_non_closed_contour();
                }
            }
			//׷���ұ߿�
            for (int i = 0; i < grid_rows-1; i++)
            {
				if (y_side[i][grid_cols-1].have_iso_point)
                {
                    pre_iso_point = iso_point(i,grid_cols-1,false);
                    cur_iso_point = iso_point(i,grid_cols-1,false);

                    tracing_one_non_closed_contour();
                }
            }
			//׷���±߿�
            for (int j = 0; j < grid_cols-1; j++)
            {
				if (x_side[0][j].have_iso_point)
                {
                    pre_iso_point = iso_point(-1,j,true);
                    cur_iso_point = iso_point(0, j,true);

                    tracing_one_non_closed_contour();
                }
            }
		}

		void tracing_one_non_closed_contour()
		{
			now_iso_line.line.clear();
			now_iso_line.value = cur_follow_value;

			int row = cur_iso_point.row, col = cur_iso_point.col;
			bool is_h = cur_iso_point.is_horizon;
			calc_coord(row,col,is_h);

			if(is_h)
			{
				x_side[row][col].have_iso_point = false;
			}
			else
			{
				y_side[row][col].have_iso_point = false;
			}

			bool over = false;

			while(!over)
			{
				trace_next_point();

				pre_iso_point = cur_iso_point;
				cur_iso_point = next_iso_point;

				over = (!cur_iso_point.row && cur_iso_point.is_horizon)
					|| (!cur_iso_point.col && !cur_iso_point.is_horizon)
					|| (cur_iso_point.row == grid_rows-1)
					|| (cur_iso_point.col == grid_cols-1);
			}

			all_iso_line.push_back(now_iso_line);
			
		}

		//�жϷ���
		void determine_direction(iso_point &left,iso_point &right,iso_point &oppsite,iso_point &leftoppsite)
		{
			//�жϴ������ı߽���
            if (cur_iso_point.row > pre_iso_point.row) //��������
            {
				left = cur_iso_point; 
				left.is_horizon = false;

				right = left; 
				right.col += 1;

				oppsite = cur_iso_point; 
				oppsite.row += 1;

				leftoppsite = left; 
				leftoppsite.row += 1;
                //TracingFromBottom2Top();
                return;
            }
            else if (cur_iso_point.col > pre_iso_point.col)  //��������
            {
				right = cur_iso_point; 
				right.is_horizon = true;
				
				left = right;
				left.row += 1;

				oppsite = cur_iso_point;
				oppsite.col += 1;

				leftoppsite = left;
				leftoppsite.col += 1;
                //TracingFromLeft2Right();
                return;
            }
			else if (cur_iso_point.is_horizon)  //��������
            {
				right = cur_iso_point; 
				right.row -= 1;
				right.is_horizon = false;
				
				left = right;
				left.col += 1;

				oppsite = cur_iso_point; 
				oppsite.row -= 1;

				leftoppsite = left; 
				leftoppsite.row -= 1;
                //TracingFromTop2Bottom();
                return;
            }
            else                               //��������
            {
				left = cur_iso_point;
				left.col -= 1;
				left.is_horizon = true;

				right = left; 
				right.row += 1;

				oppsite = cur_iso_point; 
				oppsite.col -= 1;

				leftoppsite = left; 
				leftoppsite.col -= 1;
                //TracingFromRight2Left();
                return;
            }
		}

		//׷����һ��
        void trace_next_point()
        {
			iso_point left,right,oppsite,leftoppsite;

			determine_direction(left,right,oppsite,leftoppsite);
            
			std::vector<std::vector<edge_info> > edge1 = y_side,edge2 = x_side;
			if(left.is_horizon)
			{
				edge1 = x_side;
				edge2 = y_side;
			}

			edge_info left_edge  = edge1[left.row][left.col],
				right_edge = edge1[right.row][right.col],
				oppsite_edge = edge2[oppsite.row][oppsite.col],leftoppsite_edge;

			//�迼�Ǳ߽�����
			if(leftoppsite.row>=0 && leftoppsite.row < grid_rows-1 && leftoppsite.col>=0 && leftoppsite.col < grid_cols-1)
				leftoppsite_edge = edge1[leftoppsite.row][leftoppsite.col];
			else
				leftoppsite_edge.rate = -2.0; //�����߽�


			if(left_edge.have_iso_point)//���뷽����ߵı����Ƿ��е�ֵ��
			{
				if(oppsite_edge.have_iso_point)
				{

					if(left_edge.rate < right_edge.rate)
					{
						deal_next_point(left);
					}
					else if(left_edge.rate > right_edge.rate)
					{
						deal_next_point(right);
					}
					else
					{
						if(leftoppsite_edge.rate < 0.5)
						{
							deal_next_point(left);
						}
						else
						{
							deal_next_point(right);
						}
					}
				}
				else
				{
					deal_next_point(left);
				}
			}
			else if(oppsite_edge.have_iso_point)
			{
				deal_next_point(oppsite);
			}
			else
			{
				deal_next_point(right);
			}

        }

		void deal_next_point(iso_point point)
		{
			int row = point.row, col = point.col;
			bool is_h = point.is_horizon;
 			calc_coord(row,col,is_h);

			if(is_h)
			{
				x_side[row][col].have_iso_point = false;
			}
			else
			{
				y_side[row][col].have_iso_point = false;
			}

			next_iso_point = point;

		}

		void tracing_closed_contour()
		{
			for(int j=0;j<grid_cols-1;j++)
			{
				for(int i=0;i<grid_rows-1;i++)
				{
					if(y_side[i][j].have_iso_point)
					{
						pre_iso_point = iso_point(i,0,false);
						cur_iso_point = iso_point(i,j,false);

						tracing_one_closed_contour();

					}
				}
			}
		}

		void tracing_one_closed_contour()
		{
			now_iso_line.line.clear();
			now_iso_line.value = cur_follow_value;

			int start_r = cur_iso_point.row, start_c = cur_iso_point.col;
			
			
			calc_coord(start_r,start_c,false);

			bool over = false;

			while(!over)
			{
				trace_next_point();

				pre_iso_point = cur_iso_point;
				cur_iso_point = next_iso_point;

				over = (cur_iso_point.row==start_r) && (cur_iso_point.col == start_c)
					&& (!cur_iso_point.is_horizon);
			}

			all_iso_line.push_back(now_iso_line);
		}



		//Ĭ�ϵĵ�ֵ�ߣ�10�ȷ֣�
        void set_default_level()
		{
			contour_level.clear();
			grid_info grdf = acc_contr.gd_info();

            for (int i = 0; i < n_level; i++)
            {
				contour_level.push_back((grdf.zmax-grdf.zmin)*i/(n_level-1)+grdf.zmin );
            }
        }

		void SetContourLevel()
		{}

		//�������겢���˵���뵱ǰ��ֵ����
		void calc_coord(int row,int col,bool is_h)
		{
			double x= acc_contr.gd_info().xmin + col*delt_x,
				   y= acc_contr.gd_info().ymin + row*delt_y;
			if(is_h)
			{
				x += x_side[row][col].rate * delt_x;
			}
			else
			{
				y += y_side[row][col].rate * delt_y;
			}

			now_iso_line.line.push_back(iso_point(row,col,is_h,x,y));

		}

	};

}
