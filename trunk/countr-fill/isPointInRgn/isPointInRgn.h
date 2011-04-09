/*
	�ж�ĳһ��/һ������ �Ƿ����� ��һ����
	2011 3 29 
*/

#ifndef IS_POINT_IN_RGN
#define IS_POINT_IN_RGN

#include <cmath>
#include <vector>

template <typename T>
struct mVector //����һ��������һ�������
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

	//�������
	mVector<T> add(const mVector<T> &right)const
	{
		return mVector<T>(x+right.x, y+right.y);
	}

	//�������
	mVector<T> minus(const mVector<T> &right)const
	{
		return mVector<T>(x-right.x, y-right.y);
	}

	//�������
	T multipy(const mVector<T> &right)const
	{
		return x*right.x + y*right.y;
	}

	//�ж����������Ƿ�ƽ�� 0--��ƽ�� 1--ƽ���ҷ�����ͬ 2--ƽ���ҷ����෴
	int isParallel(const mVector<T> &right)const
	{
		if(x*right.y == y*right.x) //ƽ��
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

	//�ж����������Ƿ��ཻ
	bool isIntersect(const mVector<T> &right)const
	{
		return ! isParallel(right);
	}

	//�ж����������Ƿ�ֱ
	bool isPerpendicular(const mVector<T> &right)const
	{
		return !(this->multipy(right));
	}

	//��ȡ�����ĳ���
	double getLength()const
	{
		return std::sqrt(double(x*x + y*y));
	}
};

//��ȡһ����е���һ����
template <typename T>
T getNextPoint(const std::vector<T > &rgn, size_t index)
{
	if(index == rgn.size()-1 ) return rgn.at(0);
	else return rgn.at(index+1);
}

//��ȡһ����е���һ����
template <typename T>
T getPrevPoint(const std::vector<T > &rgn, size_t index)
{
	if(0 == index) return rgn.at(rgn.size()-1);
	else return rgn.at(index-1);
}

//��ȡ�����Ĵ�ֱ���� -1--���� 1--���� 0--ˮƽ
template <typename T>
int getVectorDirect(const mVector<T> &vec)
{
	if(vec.y > 0) return -1;
	else if(vec.y <0) return 1;
	else return 0;
}

//�жϵ�point�Ƿ�������rgn�ڲ� 1--�ڲ� -1--�߽� 0--�ⲿ
template <typename T>
int isPointInRgn(const mVector<T> &point, const std::vector<mVector<T> > &rgn)
{
	int num1=0, num2=0;
	for(std::vector<mVector<T> >::size_type index=0; index != rgn.size(); index++ )
	{
		mVector<T> nextPoint = getNextPoint(rgn,index);

		if(rgn[index].x<point.x && nextPoint.x<point.x) {continue;} //���ҷ���������
		else if(nextPoint.minus(point).isParallel( point.minus(rgn[index]) ) == 1)
		{
			return -1;//���ڱ߽�
		}
		else if(point.y == rgn[index].y) //���߾����߽��
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
		else {}//���߲������߽��߶�
	}

	if((num1 + num2/2)%2) return 1;//����
	else return 0;
}

//�ж�����B�Ƿ�������A�ڲ�
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