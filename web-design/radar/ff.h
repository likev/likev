#pragma once
//Message Header Block
//  [8/8/2007 fdx]
//Message Header Block ,18Bytes :[0,17]Byte
#pragma pack(push)
#pragma pack(1)
struct HEADER
{  unsigned short int MessageCode; //0~1 16��109��ʾ��Ʒ
        unsigned short int MessageDate; //2~3 �������ڣ�1/1/1970������Julian����
      unsigned char    TimeofMessage[4]; //4~6����ʱ�䣬GMTʱ�䣬0~86399��
        unsigned long  int MessageLength; //7~11 ���ݳ��ȣ��ֽ�����
        unsigned short int SourceID;    //12~13 RDA��ID��
        unsigned short int DestinationID;  //14~15 ���ݽ���ID��
       unsigned short int BlocksNumber; //16~17 ���ݿ����
};//����ͷ������)
struct DESCRIPTION
{         short int BlockDivider; //18~19 ���ݿ�ָ�����Ϊ-1
                 long  int RadarLatitude; //20~23 �״�վ���ȣ���λ��0.001��
                 long  int RadarLongtitude; //24~27�״�վγ�ȣ���λ��0.001��
                 short int RadarHeight;   //28~29 ���θ߶ȣ���λ��Ӣ��
                 short int ProductCode;   //30~31 ��Ʒ����
                 short int OperationalMode; //32~33 ����ģʽ��
                                            // 0=Maintenance 
                                            // 1=Clear Air 
                                            // 2=Precipitation/Server Weather 
                 short int VolumeCoveragePattern; //34~35 VCP��ʽ
        unsigned short int SequenceNumber;     //36~37 ��Ʒ�������к�
        unsigned short int VolumeScanNumber;  //38~39 ��ɨ������1~80֮��ѭ��
        unsigned short int VolumeScanDate;    //40~41 ��ɨ����(Julian-1/1/70) 
       unsigned long int VolumeScanTime;    //42~45 ��ɨʱ��(GMT)
        unsigned short int ProductGenerationDate;//46~47��Ʒ�������� 
        unsigned  char TimeofMessage2[4];  //48~51 ��Ʒ����GMTʱ��
                 short int P1;    //52~53 
                 short int P2;    //54~55
                 short int ElevationNumber; //56~57 ��ʾ��ɨ�еĵڼ������ǲ�(1~20) 
                 short int P3;    //58~59
                 short int DataLevelThreshold[16]; //60~91 ���ݷּ�����ֵ
                 short int P4;    //92~93
                 short int P5;    //94~95
                 short int P6;    //96~97
                 short int P7;    //98~99
                 short int P8;    //100~101
                 short int P9;    //102~103
                 short int P10;   //104~105
                 short int NumberOfMaps; //106~107 ��ͼ�����еĿ����� 
                         // Version;   ���ֽڱ�ʾ ��Ʒ�İ汾�ţ�ԭʼ��ƷΪ0��
// StopBlank;  ���ֽ�1=Stop ON, 2=Stop OFF
        unsigned long  int OffsetToSymbology;    //108~111
        unsigned long  int OffsetToGraphic;      //112~115
        unsigned long  int OffsetToTabular;      //116~119
         

}; 
////�����ǹ̶���Ҫ�е��ļ�ͷ
struct SYMBOLOGY
{ short  BlockDivider; //���ݿ�ָ���=-1
  short  nBlockId; // ��Ʒ���ݱ�ʶ=1
};//����1��2��3
/////1���Ʒ
 struct onetow
        { unsigned char    LengthOfBlock[4];            //��ĳ���
            short            NumberOfLayers;//��ĸ���
              
        };
/////////////1���Ʒ
///������������
struct ifon1
{  short    LayerDivider;///�ָ��=-1
   unsigned char    cch[4];  //��ĳ���
};
struct tagLVPacket
{
short int PacketCode;           //6      Packet Type 6
short int LengthOfDataBlock;    //Number of bytes in block not including self or packet code
//Data Block
};
struct jingxiangtow
{ //short   nflag;///�ָ��=-1    
//short int  IndexofFirstRangeBin;        //0-460
    short int NumberofRangeBins;        //1-460
    short int ICenterofSweep;            //
    short  JCenterofSweep;            //
    short  ScaleFactor;                //0.001-8.000
    short  NumberofRadials;  
};//��ʽ�ĵ���48ҳ
struct jingxiang
{
unsigned short Number;          //1-230
unsigned short RadialStartAngle;
unsigned short RadialAngelDelta;
};
///�������ݾ���

struct cr                        
{ 
 unsigned short nFlag2;//00C0
 short nIStart;//��ʼi����
 short nJStart;//��ʼj����
 unsigned short nXScale;//x�ֱ���
 unsigned short nXFraction;
 unsigned short nYScale;//y�ֱ���
 unsigned short nYFraction;
 unsigned short nRowNum;//����
 unsigned short nPackFormat;//���ĸ�ʽ
};
struct mye
{ short int PageNumber; //����ҳ��
   short int LengthOfPage;  //ҳ���ݳ��ȣ��ֽ�����
};
///2���Ʒ
struct zbf
{          unsigned char    LengthOfBlock[4];  //���ݳ��ȣ��ֽ�����
HEADER BLOCK1;
DESCRIPTION BLOCK2;
                 short int BlockDivider; //���ݿ�ָ���=-1
                 short int NumberOfPages; //������ҳ����
                // short int NumberOfCharacters; //ҳ���ַ���
               // short int EndOfPageFlag; //���ݽ�����־=-1



};
///3���Ʒ
  struct bar
{
	short int value;
	short int x;
	short int y;
	short int direction;
	short int speed;
};
struct fxf
{ 
    short int ICenterofSweep;            //
    short  JCenterofSweep;  
 short  bj;           //
    };//��ʽ�ĵ���48ҳ

struct bb2
{ 
    short int ICenterofSweep;            //
    short  JCenterofSweep;  
    };//��ʽ�ĵ���48ҳ

