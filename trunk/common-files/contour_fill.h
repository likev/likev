/*
	由一组等值线获取填色区域
	使用方法 
	1.定义 contour_fill 类，初始化时传入等值线集合(可以非闭合)
	2.获取闭合等值线集 contours[4] 分别存储C B A D类闭合等值线 并按填色顺序排好序
	std::vector<contr_set_type> & get_fill_contours(std::vector<contr_set_type> & contours)
	
*/

#include <comn.h>
#include <contr.h>

#ifndef _CONTOUR_FILL_
#define _CONTOUR_FILL_


class contour_fill
{
public:
	typedef contr::pointxy<double> point_type;//点
	typedef std::vector<point_type> line_type;//线
	typedef std::vector<line_type> contr_set_type;//等值线的集合

	contour_fill()
		:Precision(1E-6),MIN_X(0),MIN_Y(0),MAX_X(0),MAX_Y(0)
	{}

	contour_fill(const contr_set_type & lines,
		double min_x,double min_y,double max_x, double max_y)
		:Precision(1E-6),MIN_X(min_x),MIN_Y(min_y),MAX_X(max_x),MAX_Y(max_y)
	{
		classify_edge(lines);
	}

	
	std::vector<contr_set_type> & 
		get_fill_contours(std::vector<contr_set_type> & contours)
	{
		sort_contour_list();

		contours.resize(4,contr_set_type());
		
		generate_fill_contours(leftlines, contours);
		generate_fill_contours(toplines, contours);
		generate_fill_contours(rightlines, contours);
		generate_fill_contours(buttomlines, contours);
		generate_fill_contours(closedlines, contours);

		return contours;
	}

private:
	const double Precision;
	const double MIN_X,MIN_Y,MAX_X,MAX_Y;
	contr_set_type leftlines,toplines,rightlines,buttomlines,closedlines;

	//边类型
	enum edge_type
	{
		Left,Top,Right,Buttom,Closed  //左 上 右 下 内
	};

	//等值线类型
	enum contour_type
	{
		EdgeContour,        //a类等值线
		CornerContour,      //b类
		BridgeContour,      //c类
		ClosedContour      //d类
	};

	//获取边类型
	edge_type get_edge_type(point_type pt)const
	{
		if(beql(pt.x,MIN_X))
		{
			return Left;
		}
		else if(beql(pt.y,MAX_Y))
		{
			return Top;
		}
		else if(beql(pt.x,MAX_X))
		{
			return Right;
		}
		else if(beql(pt.y,MIN_Y))
		{
			return Buttom;
		}
		else
		{
			return Closed;
		}
	}


	//获取等值线类型
	contour_type get_contour_type(const line_type &line)const
	{
		if(beql(abs(line.back().x-line.front().x),MAX_X-MIN_X)
		|| beql(abs(line.back().y-line.front().y),MAX_Y-MIN_Y) )
		{
			return BridgeContour;
		}
		else if(line.back() == line.front())
		{
			return ClosedContour;
		}
		else if(beql(line.back().x, line.front().x)
			||  beql(line.back().y, line.front().y))
		{
			return EdgeContour;
		}
		else
		{
			return CornerContour;
		}

	}

	//按照不同边分类
	void classify_edge(const contr_set_type & lines)
	{
		for(contr_set_type::const_iterator it=lines.begin();
			it != lines.end(); it++)
		{
			switch(get_edge_type(it->front()))
			{
			case Left:
				{
					if(it->size() && beql(it->back().y, MIN_Y))
					{
						buttomlines.push_back(line_type(it->rbegin(),it->rend() ) );
					}
					else
					{
						leftlines.push_back(*it);
					}
					break;
				}
			case Top:      toplines.push_back(*it);break;
			case Right:  rightlines.push_back(*it);break;
			case Buttom:buttomlines.push_back(*it);break;
			case Closed:closedlines.push_back(*it);break;
			default:break;
			}
		}
	}

	//对等值线按照边界和起点排序
	void sort_contour_list()
	{
		using std::sort;

		sort(leftlines.begin(),leftlines.end(),contr::sort_by_axes<double>('y'));
		sort(toplines.begin(),toplines.end(),contr::sort_by_axes<double>('x'));
		sort(rightlines.rbegin(),rightlines.rend(),contr::sort_by_axes<double>('y'));
		sort(buttomlines.rbegin(),buttomlines.rend(),contr::sort_by_axes<double>('x'));
		sort(closedlines.begin(),closedlines.end(),contr::sort_by_axes<double>('x'));
	}

	//对于每一条等值线 如需要时添加一个点(区域顶点)使其成为闭合区域
	//将等值线按CBAD四类添加到向量中
	void generate_fill_contours(contr_set_type & lines, std::vector<contr_set_type> & contours)
	{
		for(contr_set_type::iterator it=lines.begin(); 
			it!=lines.end(); it++)
		{
			size_t length= it->size();

			point_type pt1,pt2;
			switch(get_edge_type(it->front()))
			{
			case Left:
				{
					pt1 = point_type(MAX_X,MAX_Y);
					pt2 = point_type(MIN_X,MAX_Y);
					break;
				}
			case Top: 
				{
					pt1 = point_type(MAX_X,MIN_Y);
					pt2 = point_type(MAX_X,MAX_Y);
					break;
				}
			case Right:
				{
					pt1 = point_type(MIN_X,MIN_Y);
					pt2 = point_type(MAX_X,MIN_Y);
					break;
				}
			case Buttom:
				{
					pt1 = point_type(MIN_X,MAX_Y);
					pt2 = point_type(MIN_X,MIN_Y);
					break;
				}
			default:break;
			}

			switch(get_contour_type(*it) )
			{
			case BridgeContour:       //C类等值线
					it->push_back(pt1);
					it->push_back(pt2);

					contours[0].push_back(*it);
					break;

			case CornerContour:       //B类等值线
				{
					point_type end = it->back();

					it->push_back(pt2);

					contours[1].push_back(*it);
					break;
				}
				
			case EdgeContour:      //A类等值线
				contours[2].push_back(*it);
				break;
				
			case ClosedContour:    //D类等值线
				contours[3].push_back(*it);
				break;
			default:break;
			}
		}
	}
};



//读取数据
contour_fill::contr_set_type readdata();

#endif /* _CONTOUR_FILL_ */

