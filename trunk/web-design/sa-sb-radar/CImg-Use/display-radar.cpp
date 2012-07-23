#include "SA-SBDataStruct.h"

#define M_PI 3.14159265358979323846

#define cimg_use_png
#include "CImg.h"

using namespace cimg_library;


//填充一个区域 像素x坐标属于[x1, x2) 像素y坐标属于[y1, y2)
void fill_rect(CImg<unsigned char> &img, 
	unsigned x1,unsigned y1, unsigned x2,unsigned y2, 
	const std::vector<unsigned char> &color)
{
	if(x1 > x2) std::swap(x1, x2);
	if(y1 > y2) std::swap(y1, y2);

	for(unsigned i=x1; i<x2; i++)
	{
		for(unsigned j=y1; j<y2; j++)
		{
			for(std::size_t v=0; v<color.size() && v<4; v++)
			{
				img.atXY(i, j, 0, v) = color[v];//越界将忽略
			}
		}
	}
}

//获取雷达发射率对应的RGBA值
void get_reflectivity_color(double ref, std::vector<unsigned char> &color)
{
	
	unsigned char r=0, g=0, b=0, alpha=255;
	if(ref < -5)
	{
		alpha=0;
	}
	else if(ref < 0)
	{
		r = 0, g=172, b=164;
	}
	else if(ref < 5)
	{
		r = 192, g=192, b=254;
	}
	else if(ref < 10)
	{
		r = 112, g=114, b=238;
	}
	else if(ref < 15)
	{
		r = 30, g=38, b=208;
	}
	else if(ref < 20)
	{
		r = 166, g=252, b=168;
	}
	else if(ref < 25)
	{
		r = 0, g=234, b=0;
	}
	else if(ref < 30)
	{
		r = 16, g=146, b=26;
	}
	else if(ref < 35)
	{
		r = 252, g=244, b=100;
	}
	else if(ref < 40)
	{
		r = 200, g=200, b=2;
	}
	else if(ref < 45)
	{
		r = 140, g=140, b=0;
	}
	else if(ref < 50)
	{
		r = 254, g=172, b=172;
	}
	else if(ref < 55)
	{
		r = 254, g=100, b=92;
	}
	else if(ref < 60)
	{
		r = 238, g=2, b=48;
	}
	else if(ref < 65)
	{
		r = 212, g=142, b=254;
	}
	else if(ref < 900)
	{
		r = 170, g=36, b=250;
	}
	else
	{
		alpha=0;
	}

	color.resize(4, 0);
	color[0] = r;
	color[1] = g;
	color[2] = b;
	color[3] = alpha;

	return;
}

//将一个仰角层保存为图片
bool save_png(const RadarElevation &el, const std::string &filename)
{
	const double RADIAN = M_PI/180.0;

	CImg<unsigned char> img(el.r_gate_count*2,el.r_gate_count*2,1,4,0);
	std::vector<unsigned char> color;

	for(std::size_t i=0; i<el.r.size(); i++)//方位角
	{
		double sini = sin(i*RADIAN),  cosi = cos(i*RADIAN);
		for(std::size_t j=0; j<el.r[i].size(); j++)//第j个库
		{
			double r = el.r_gate_length*j/1000.0 ;//将库长转换为地面上对应的长度(Km)
			int x = int( r*sini + 0.5) + el.r_gate_count, 
				y = int(-r*cosi + 0.5) + el.r_gate_count;

			get_reflectivity_color(el.r[i][j], color);
			fill_rect(img, x, y, (x+1), (y+1), color);
		}
	}

	img.save(filename.c_str());

	return true;
}

int main()
{
	std::string filename = "Z_RADR_I_Z9398_20120717041200_O_DOR_SB_CAP.bin";

	SA_SB_Info radar(filename);

	for(SA_SB_Info::r_it it = radar.elevations.begin();
		it != radar.elevations.end(); it++)
	{
		if(it->second.r_valid)
		{
			save_png(it->second, it->first + ".png");
		}
	}

	return 0;
}

int main2()
{
	CImg<unsigned char> img(920,920,1,4,100);
	 
	img.atXY(1000,1000,0,0,10) = 3;
	img.atXY(100,100,0,0,10) = 255;
	img.save("a.png");

	return 0;
}