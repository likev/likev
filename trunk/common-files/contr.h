//
#pragma once
#ifndef _CONTRH_
#define _CONTRH_

/*
	定义等值线绘制中使用到的基本数据类型
	读取网格点信息 contr::access_contour
*/

#include "comn.h"
#include "string-trans.h"

namespace contr{

	template <typename T>
	class pointxy //点
	{
	public:
		T x;
		T y;

		pointxy()
			:x(0),y(0)
		{}

		pointxy(T a,T b)
		{
			set(a,b);
		}

		void set(T a,T b)
		{
			x=a;
			y=b;
		}

		bool operator ==(const pointxy & right)const
		{
			if(beql(right.x,this->x) && beql(right.y,this->y))
			{
				return true;
			}
			return false;
		}

		bool operator !=(const pointxy & right)const
		{
			if(*this == right)
				return false;

			return true;
		}

		//for CPoint Class
		operator CPoint()const
		{
			return CPoint(int(x+0.5),int(y+0.5));
		}
	};

	template <typename T>
	std::istream & operator >>(std::istream & in,pointxy<T> &pt)
	{
		in>>pt.x>>pt.y;

		return in;
	}

	template <typename T>
	std::ostream & operator <<(std::ostream & out,const pointxy<T> &pt)
	{
		out<<pt.x<<" "<<pt.y;

		return out;
	}

	//仿函数
	//按照坐标轴排序
	template <typename T>
	class sort_by_axes
	{
	public:
		typedef pointxy<T> point_type;
		typedef std::vector<point_type> line_type;
	private:
		char c;
	public:
		sort_by_axes(char m):c(m){}

		//比较两个点
		bool operator ()(const point_type &left,const point_type &right)const
		{
			switch(c)
			{
			case 'x':
				if(left.x < right.x)
				{
					return true;
				}
				break;
			case 'y':
				if(left.y < right.y)
				{
					return true;
				}
				break;
			default:
				break;
			}

			return false;
		}

		//重载  比较两条线的起点
		bool operator ()(const line_type &left,const line_type &right)const
		{
			return this->operator () (left[0],right[0]);
		}
	};

	//网格点数据结构
	struct grid_point
	{
		pointxy<double> xy;

		double value;
	};

	class grid_point_sort
	{
	public:
		grid_point_sort(char m):c(m){}

		bool operator ()(const grid_point & left, const grid_point &right)const
		{
			switch(c)
			{
			case 'x':
				if(left.xy.x < right.xy.x)
				{
					return true;
				}
				break;
			case 'y':
				if(left.xy.y < right.xy.y)
				{
					return true;
				}
				break;
			case 'v':
				if(left.value < right.value)
				{
					return true;
				}
			default:
				break;
			}

			return false;
		}

	private:
		char c;
	};

	

	//网格的一些基本信息
	//网格的行数，列数，X，Y, Z轴的最大最小值
	struct grid_info
	{
		int rows,cols;

		double xmin,xmax;
		double ymin,ymax;
		double zmin,zmax;

		grid_info()
		{
			xmin = xmax = 0;
			ymin = ymax = 0;
			zmin = zmax = 0;
		}
	};

	class access_contour
	{
	private:
		grid_info gridinfo; //网格信息
		std::vector<grid_point> gridpoints;

	public:
		access_contour()
		{
			
		}

		void get_grid_data(std::string filename)
		{
			std::string text_content;
			std::vector<std::string> text_lines; 
			filetostr(filename,text_content);

			str_split(str_trim(text_content),"\n",text_lines,true);

			double x0=0,x1=0;
			string_to(text_lines[0],x0);
			string_to(text_lines[1],x1);

			if(beql(x0,x1))//行优先
			{
				get_col_first(text_lines);
			}
			else
			{
				get_row_first(text_lines);
			}

		}

		const grid_info& gd_info()const
		{
			return gridinfo;
		}

		const std::vector<grid_point>& gdpts()const
		{
			return gridpoints;
		}

	private:

		void get_row_first(std::vector<std::string> &text_lines)
		{
			gridpoints.resize(text_lines.size());

			for(size_t it=0;
				it != text_lines.size(); it++)
			{
				std::vector<std::string> aline;
				str_split(text_lines[it]," ",aline);

				if(aline.size()<3) continue;

				string_to(aline[0],gridpoints[it].xy.x);
				string_to(aline[1],gridpoints[it].xy.y);
				string_to(aline[2],gridpoints[it].value);
			}

			set_grid_info();
		}
		void get_col_first(std::vector<std::string> &text_lines)
		{
		}

		void set_grid_info()
		{
			std::vector<grid_point>::iterator it;
			it = std::min_element(gridpoints.begin(), gridpoints.end(), grid_point_sort('x'));
			gridinfo.xmin = it->xy.x;
			it = std::max_element(gridpoints.begin(), gridpoints.end(), grid_point_sort('x'));
			gridinfo.xmax = it->xy.x;
			it = std::min_element(gridpoints.begin(), gridpoints.end(), grid_point_sort('y'));
			gridinfo.ymin = it->xy.y;
			it = std::max_element(gridpoints.begin(), gridpoints.end(), grid_point_sort('y'));
			gridinfo.ymax = it->xy.y;
			it = std::min_element(gridpoints.begin(), gridpoints.end(), grid_point_sort('v'));
			gridinfo.zmin = it->value;
			it = std::max_element(gridpoints.begin(), gridpoints.end(), grid_point_sort('v'));
			gridinfo.zmax = it->value;

			gridinfo.cols = int((gridinfo.xmax - gridinfo.xmin)/(gridpoints[1].xy.x - gridpoints[0].xy.x)+1.5);
		
			gridinfo.rows = (gridpoints.size()/gridinfo.cols);
		}

	};
}

#endif /* _CONTRH_ END */