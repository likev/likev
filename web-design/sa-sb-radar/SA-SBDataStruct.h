
//SA SB�״������ ���ݽṹ
#ifndef _SADATASTRUCT_
#define _SADATASTRUCT_

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

//DataBase.h
//SA��SB�״�ľ������
/** /
#define RGates  460				//S BAND �����ʾ������
#define VGates  920				//S BAND �ٶȾ������
#define WGates  920				//S BAND �׿�������
/ **/

//CB �״�ľ������
/*
#define RGates  800				//C BAND �����ʾ������
#define VGates  1600			//C BAND �ٶȾ������
#define WGates  1600			//C BAND �׿�������
*/

#define MaxCuts		20			//������ǲ���
#define MaxRads		360			//ÿ�������ϵķ�λ��,ÿ�ȱ���һ������

#define CODE_INVALID 0			//����ֵ�е�������,��ʾ����Ч�۲�����
#define CODE_RANFOLD 1			//����ֵ�е�������,��ʾ�о���ģ��

#define VALUE_INVALID -999.		//ʵ��ֵ�е�������,��ʾ����Ч�۲�����
#define VALUE_RANFOLD  999.		//ʵ��ֵ�е�������,��ʾ�о���ģ��
#define VALUE_AINVALID -1;

#define RES_POINT_FIVE 2		//�ٶȾ�������,����ľ���Ϊ0.5 M/S
#define RES_ONE_POINT  4		//�ٶȾ�������,����ľ���Ϊ1.0 M/S

#define RADIAN  3.14159/180.
#define PI 3.14159
//////////////////////////////////////////////////////////////////////
//�״�����ݽṹ
template <unsigned RGates_VGates_WGates>
struct RadarBaseData
{
	unsigned short		temp1[7];						//����
	unsigned short		RadarStatus;					//1 - ��ʾΪ�״����� 
	unsigned short		temp2[6];						//����
	unsigned int		mSeconds;						//���������ռ�ʱ��(����,��00:00��ʼ)
	unsigned short		JulianDate;						//��1970/1/1�������
	unsigned short		URange;							//��ģ�����루��ʾ����ֵ/10.=ǧ�ף�
	unsigned short		Az;								//��λ�Ƕȣ����뷽ʽ��[��ֵ/8.]*[180./4096.]=�ȣ�
	unsigned short		RadialNumber;					//�����������
	unsigned short		RadialStatus;					//��������״̬
	unsigned short		El;								//���ǣ����뷽ʽ��[��ֵ/8.]*[180./4096.]=�ȣ�
	unsigned short		ElNumber;						//��ɨ�ڵ����Ǳ��
	short				RangeToFirstGateOfRef;			//��һ�����������ݱ�ʾ��ʵ�ʾ���(m)
	short				RangeToFirstGateOfDop;			//��һ�����������ݱ�ʾ��ʵ�ʾ���(m)
	unsigned short		GateSizeOfReflectivity;			//���������ݵľ���ⳤ(m)
	unsigned short		GateSizeOfDoppler;				//���������ݵľ���ⳤ(m)
	unsigned short		GatesNumberOfReflectivity;		//���������ݵľ������
	unsigned short		GatesNumberOfDoppler;			//���������ݵľ������
	unsigned short		CutSectorNumber; 				//������
	unsigned int		CalibrationConst; 				//�궨����
	unsigned short		PtrOfReflectivity;				//����������ָ��
	unsigned short		PtrOfVelocity;					//�ٶ�����ָ��
	unsigned short		PtrOfSpectrumWidth;				//�׿�����ָ��
	unsigned short		ResolutionOfVelocity;			//�������ٶȷֱ���:2=0.5m/s;4=1.0m/s
	unsigned short		VcpNumber;						//��ɨģʽ 11�� ��ˮģʽ��16������ 21����ˮģʽ��14������ 31�����ģʽ��8������ 32�����ģʽ��7������
	unsigned short		temp4[4];						//����
	unsigned short		PtrOfArcReflectivity;			//����������ָ��
	unsigned short		PtrOfArcVelocity;				//�ٶ�����ָ��
	unsigned short		PtrOfArcWidth;					//�׿�����ָ��
	unsigned short		Nyquist;						//��ģ���ٶȣ���ʾ����ֵ/100. = ��/�룩
	unsigned short      temp46;                         //����
	unsigned short      temp47;                         //����
	unsigned short      temp48;                         //����
	unsigned short      CircleTotal;					//������
	unsigned char		temp5[30];						//����
	unsigned char		Echodata[RGates_VGates_WGates];	//129��2428 ��2300�ֽ� (460�ֽڷ���������+920�ֽ��ٶ�����+920�ֽ��׿�����)
	unsigned char		temp[4];						//����

};

class SA_SB_Info
{
public:
	typedef RadarBaseData<2300> SA_Base,SB_Base;
	enum RADIAL_STATUS {
		VOL_BEG=3,   //��ɨ��ʼ״̬��־
		VOL_END=4,	 //��ɨ����״̬��־
		ELV_BEG=0,	 //���ǿ�ʼ״̬��־
		ELV_END=2,   //���ǽ���״̬��־
		ELV_NORMAL=1
	};

	enum VOL_MODEL {
		RAIN16 = 11,  //��ˮģʽ��16������
		RAIN14 = 21,  //��ˮģʽ��14������
		SUN8 = 31,  // ���ģʽ��8������
		SUN7 = 32 //   ���ģʽ��7������
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
			std::cout<<"���ļ�"<<filename<<"ʧ�ܣ�"<<std::endl;
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
			"��1970/1/1������� "
			"��������ʱ��  "
			"��ɨģʽ "
			"��ģ������  "
			"��� "
			"״̬  "
			"���Ǳ��    "
			"����    "
			"��λ��  "
			"��һ�����������ݱ�ʾ��ʵ�ʾ���(m) "
			"��һ�����������ݱ�ʾ��ʵ�ʾ���(m) "
			"���������ݵľ���ⳤ(m)  "
			"���������ݵľ���ⳤ(m)  "
			"���������ݵľ������   "
			"���������ݵľ������   "
			"����������ָ��  "
			"�ٶ�����ָ��   "
			"�׿�����ָ��   "
			"�������ٶȷֱ���  "
			"����������ָ��2  "
			"�ٶ�����ָ��2   "
			"�׿�����ָ��2   "
			"��ģ���ٶ�  "
			"������  "

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