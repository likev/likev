
//SA SB雷达基数据 数据结构
#ifndef _SADATASTRUCT_
#define _SADATASTRUCT_

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

//DataBase.h
//SA，SB雷达的距离库数
/** /
#define RGates  460				//S BAND 反射率距离库数
#define VGates  920				//S BAND 速度距离库数
#define WGates  920				//S BAND 谱宽距离库数
/ **/

//CB 雷达的距离库数
/*
#define RGates  800				//C BAND 反射率距离库数
#define VGates  1600			//C BAND 速度距离库数
#define WGates  1600			//C BAND 谱宽距离库数
*/

#define MaxCuts		20			//最大仰角层数
#define MaxRads		360			//每层仰角上的方位数,每度保留一个径向

#define CODE_INVALID 0			//编码值中的特殊标记,表示无有效观测数据
#define CODE_RANFOLD 1			//编码值中的特殊标记,表示有距离模糊

#define VALUE_INVALID -999.		//实际值中的特殊标记,表示无有效观测数据
#define VALUE_RANFOLD  999.		//实际值中的特殊标记,表示有距离模糊
#define VALUE_AINVALID -1;

#define RES_POINT_FIVE 2		//速度精度类型,代表的精度为0.5 M/S
#define RES_ONE_POINT  4		//速度精度类型,代表的精度为1.0 M/S

#define RADIAN  3.14159/180.
#define PI 3.14159
//////////////////////////////////////////////////////////////////////
//雷达基数据结构
template <unsigned RGates_VGates_WGates>
struct RadarBaseData
{
	unsigned short		temp1[7];						//保留
	unsigned short		RadarStatus;					//1 - 表示为雷达数据 
	unsigned short		temp2[6];						//保留
	unsigned int		mSeconds;						//径向数据收集时间(毫秒,自00:00开始)
	unsigned short		JulianDate;						//从1970/1/1起的日期
	unsigned short		URange;							//不模糊距离（表示：数值/10.=千米）
	unsigned short		Az;								//方位角度（编码方式：[数值/8.]*[180./4096.]=度）
	unsigned short		RadialNumber;					//径向数据序号
	unsigned short		RadialStatus;					//径向数据状态
	unsigned short		El;								//仰角（编码方式：[数值/8.]*[180./4096.]=度）
	unsigned short		ElNumber;						//体扫内的仰角编号
	short				RangeToFirstGateOfRef;			//第一个反射率数据表示的实际距离(m)
	short				RangeToFirstGateOfDop;			//第一个多普勒数据表示的实际距离(m)
	unsigned short		GateSizeOfReflectivity;			//反射率数据的距离库长(m)
	unsigned short		GateSizeOfDoppler;				//多普勒数据的距离库长(m)
	unsigned short		GatesNumberOfReflectivity;		//反射率数据的距离库数
	unsigned short		GatesNumberOfDoppler;			//多普勒数据的距离库数
	unsigned short		CutSectorNumber; 				//扇区号
	unsigned int		CalibrationConst; 				//标定常数
	unsigned short		PtrOfReflectivity;				//反射率数据指针
	unsigned short		PtrOfVelocity;					//速度数据指针
	unsigned short		PtrOfSpectrumWidth;				//谱宽数据指针
	unsigned short		ResolutionOfVelocity;			//多普勒速度分辨率:2=0.5m/s;4=1.0m/s
	unsigned short		VcpNumber;						//体扫模式 11： 降水模式，16层仰角 21：降水模式，14层仰角 31：晴空模式，8层仰角 32：晴空模式，7层仰角
	unsigned short		temp4[4];						//保留
	unsigned short		PtrOfArcReflectivity;			//反射率数据指针
	unsigned short		PtrOfArcVelocity;				//速度数据指针
	unsigned short		PtrOfArcWidth;					//谱宽数据指针
	unsigned short		Nyquist;						//不模糊速度（表示：数值/100. = 米/秒）
	unsigned short      temp46;                         //保留
	unsigned short      temp47;                         //保留
	unsigned short      temp48;                         //保留
	unsigned short      CircleTotal;					//仰角数
	unsigned char		temp5[30];						//保留
	unsigned char		Echodata[RGates_VGates_WGates];	//129－2428 共2300字节 (460字节反射率数据+920字节速度数据+920字节谱宽数据)
	unsigned char		temp[4];						//保留

};

class SA_SB_Info
{
public:
	typedef RadarBaseData<2300> SA_Base,SB_Base;
	enum RADIAL_STATUS {
		VOL_BEG=3,   //体扫开始状态标志
		VOL_END=4,	 //体扫结束状态标志
		ELV_BEG=0,	 //仰角开始状态标志
		ELV_END=2,   //仰角结束状态标志
		ELV_NORMAL=1
	};

	enum VOL_MODEL {
		RAIN16 = 11,  //降水模式，16层仰角
		RAIN14 = 21,  //降水模式，14层仰角
		SUN8 = 31,  // 晴空模式，8层仰角
		SUN7 = 32 //   晴空模式，7层仰角
	};

public:
	std::vector<SB_Base> alldata;//RGates+VGates+WGates
public:
	bool read_base_data(const std::string& filename)
	{
		//"Z_RADR_I_Z9398_20120717041200_O_DOR_SB_CAP.bin"
		std::ifstream fin(filename.c_str(), std::ios_base::in|std::ios_base::binary);

		if(!fin.is_open())
		{
			std::cout<<"打开文件"<<filename<<"失败！"<<std::endl;
		}

		SB_Base oneline;
		alldata.clear();

		while(fin)
		{
			fin.read( (char *)(&oneline), sizeof(SB_Base));
			alldata.push_back(oneline);
		}

		fin.close();

		return true;
	}

	void out_info(std::ostream &out)
	{
		out<<
			"从1970/1/1起的日期 "
			"径向数据时间  "
			"体扫模式 "
			"不模糊距离  "
			"序号 "
			"状态  "
			"仰角编号    "
			"仰角    "
			"方位角  "
			"第一个反射率数据表示的实际距离(m) "
			"第一个多普勒数据表示的实际距离(m) "
			"反射率数据的距离库长(m)  "
			"多普勒数据的距离库长(m)  "
			"反射率数据的距离库数   "
			"多普勒数据的距离库数   "
			"反射率数据指针  "
			"速度数据指针   "
			"谱宽数据指针   "
			"多普勒速度分辨率  "
			"反射率数据指针2  "
			"速度数据指针2   "
			"谱宽数据指针2   "
			"不模糊速度  "
			"仰角数  "

			"\n"<<std::endl;
		for(unsigned i=0; i!=alldata.size(); i++)
		{
			SB_Base &cur = alldata[i];
			out<<cur.JulianDate<<"  "
				<<cur.mSeconds<<"   "
				<<get_vol_model(cur.VcpNumber)<<"  "
				<<cur.URange<<"  "
				<<cur.RadialNumber<<"  "
				<<get_radial_status(cur.RadialStatus)<<"   "
				<<cur.ElNumber<<"  "
				<<cur.El<<"  "
				<<cur.Az<<"  "
				<<cur.RangeToFirstGateOfRef<<"   "			//
				<<cur.RangeToFirstGateOfDop<<"   "
				<<cur.GateSizeOfReflectivity<<"   "
				<<cur.GateSizeOfDoppler<<"   "
				<<cur.GatesNumberOfReflectivity<<"   "
				<<cur.GatesNumberOfDoppler<<"  "
				<<cur.PtrOfReflectivity<<"  "
				<<cur.PtrOfVelocity<<"   "
				<<cur.PtrOfSpectrumWidth<<"  "
				<<cur.ResolutionOfVelocity<<"  "
				<<cur.PtrOfArcReflectivity<<"  "
				<<cur.PtrOfArcVelocity<<"   "
				<<cur.PtrOfArcWidth<<"  "
				<<cur.Nyquist<<"  "
				<<cur.CircleTotal<<"  "
				<<std::endl;
		}
	}

private:
	std::string get_radial_status(unsigned short RadialStatus)
	{
		std::string status;

		switch(RadialStatus)
		{
		case VOL_BEG:
			status = "VOL_BEG"; break;
		case VOL_END:
			status = "VOL_END"; break;
		case ELV_BEG:
			status = "ELV_BEG"; break;
		case ELV_END:
			status = "ELV_END"; break;
		case ELV_NORMAL:
			status = "Normal"; break;
		default:
			status = "UNKNOW";
		}

		return status;
	}

	std::string get_vol_model(unsigned short VcpNumber)
	{
		std::string status;

		switch(VcpNumber)
		{
		case RAIN16:
			status = "RAIN16"; break;
		case RAIN14:
			status = "RAIN14"; break;
		case SUN8:
			status = "SUN8"; break;
		case SUN7:
			status = "SUN7"; break;
		default:
			status = "UNKNOW";
		}

		return status;
	}
};

#endif