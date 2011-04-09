/*
	判断某一点/一个区域 是否属于 另一区域
	2011 3 29 
*/

#ifndef IS_POINT_IN_RGN
#define IS_POINT_IN_RGN

#include <cmath>
#include <vector>

template <typename T>
struct mVector //代表一个向量或一个坐标点
{
public:
	T x,y;

	mVector()
		:x(0),y(0)
	{}

	mVector(T a,T b)
	{
		set(a,b);
	}

	void set(T a,T b)
	{
		x=a;
		y=b;
	}

	//向量相加
	mVector<T> add(const mVector<T> &right)const
	{
		return mVector<T>(x+right.x, y+right.y);
	}

	//向量相减
	mVector<T> minus(const mVector<T> &right)const
	{
		return mVector<T>(x-right.x, y-right.y);
	}

	//向量点乘
	T multipy(const mVector<T> &right)const
	{
		return x*right.x + y*right.y;
	}

	//判断两个向量是否平行 0--不平行 1--平行且方向相同 2--平行且方向相反
	int isParallel(const mVector<T> &right)const
	{
		if(x*right.y == y*right.x) //平行
		{
			if(x) //x!=0
			{
				if(right.x/x >= 0) return 1;
				else return -1;
			}
			else //x==0
			{
				if(y)
				{
					if(right.y/y >= 0) return 1;
					else return -1;
				}
				else {return 1;}
			}
		}

		return 0;
	}

	//判断两个向量是否相交
	bool isIntersect(const mVector<T> &right)const
	{
		return ! isParallel(right);
	}

	//判断两个向量是否垂直
	bool isPerpendicular(const mVector<T> &right)const
	{
		return !(this->multipy(right));
	}

	//获取向量的长度
	double getLength()const
	{
		return std::sqrt(double(x*x + y*y));
	}
};

//获取一组点中的下一个点
template <typename T>
T getNextPoint(const std::vector<T > &rgn, size_t index)
{
	if(index == rgn.size()-1 ) return rgn.at(0);
	else return rgn.at(index+1);
}

//获取一组点中的上一个点
template <typename T>
T getPrevPoint(const std::vector<T > &rgn, size_t index)
{
	if(0 == index) return rgn.at(rgn.size()-1);
	else return rgn.at(index-1);
}

//获取向量的垂直方向 -1--向上 1--向下 0--水平
template <typename T>
int getVectorDirect(const mVector<T> &vec)
{
	if(vec.y > 0) return -1;
	else if(vec.y <0) return 1;
	else return 0;
}

//判断点point是否在区域rgn内部 1--内部 -1--边界 0--外部
template <typename T>
int isPointInRgn(const mVector<T> &point, const std::vector<mVector<T> > &rgn)
{
	int num1=0, num2=0;
	for(std::vector<mVector<T> >::size_type index=0; index != rgn.size(); index++ )
	{
		mVector<T> nextPoint = getNextPoint(rgn,index);

		if(rgn[index].x<point.x && nextPoint.x<point.x) {continue;} //向右方向作射线
		else if(nextPoint.minus(point).isParallel( point.minus(rgn[index]) ) == 1)
		{
			return -1;//点在边界
		}
		else if(point.y == rgn[index].y) //射线经过边界点
		{	
			mVector<T> prevVector = rgn[index].minus(getPrevPoint(rgn,index)), 
					   nextVector = getNextPoint(rgn,index).minus(rgn[index]);

			num2 += getVectorDirect(prevVector) + getVectorDirect(nextVector);
			
			
		}
		else if( (point.y > rgn[index].y && point.y < nextPoint.y)
			|| (point.y > nextPoint.y && point.y < rgn[index].y) )
		{
			++num1;
		}
		else {}//射线不经过边界线段
	}

	if((num1 + num2/2)%2) return 1;//奇数
	else return 0;
}

//判断区域B是否在区域A内部
template <typename T>
bool isRgnInRgn(const std::vector<mVector<T> > &rgnB, const std::vector<mVector<T> > &rgnA)
{
	for(std::vector<mVector<T> >::size_type index = 0;
		index != rgnB.size(); index++)
	{
		if(! isPointInRgn(rgnB[index], rgnA) ) return false;
	}

	return true;
}

#endif //IS_POINT_IN_RGN