#pragma once
//Message Header Block
//  [8/8/2007 fdx]
//Message Header Block ,18Bytes :[0,17]Byte
#pragma pack(push)
#pragma pack(1)
struct HEADER
{  unsigned short int MessageCode; //0~1 16～109表示产品
        unsigned short int MessageDate; //2~3 传输日期，1/1/1970以来的Julian日期
      unsigned char    TimeofMessage[4]; //4~6传输时间，GMT时间，0~86399秒
        unsigned long  int MessageLength; //7~11 数据长度（字节数）
        unsigned short int SourceID;    //12~13 RDA的ID号
        unsigned short int DestinationID;  //14~15 数据接受ID号
       unsigned short int BlocksNumber; //16~17 数据块个数
};//数据头（共有)
struct DESCRIPTION
{         short int BlockDivider; //18~19 数据块分隔符，为-1
                 long  int RadarLatitude; //20~23 雷达站经度，单位：0.001度
                 long  int RadarLongtitude; //24~27雷达站纬度，单位：0.001度
                 short int RadarHeight;   //28~29 海拔高度，单位：英尺
                 short int ProductCode;   //30~31 产品代号
                 short int OperationalMode; //32~33 运行模式，
                                            // 0=Maintenance 
                                            // 1=Clear Air 
                                            // 2=Precipitation/Server Weather 
                 short int VolumeCoveragePattern; //34~35 VCP方式
        unsigned short int SequenceNumber;     //36~37 产品生成序列号
        unsigned short int VolumeScanNumber;  //38~39 体扫计数，1~80之间循环
        unsigned short int VolumeScanDate;    //40~41 体扫日期(Julian-1/1/70) 
       unsigned long int VolumeScanTime;    //42~45 体扫时间(GMT)
        unsigned short int ProductGenerationDate;//46~47产品生成日期 
        unsigned  char TimeofMessage2[4];  //48~51 产品生成GMT时间
                 short int P1;    //52~53 
                 short int P2;    //54~55
                 short int ElevationNumber; //56~57 表示体扫中的第几个仰角层(1~20) 
                 short int P3;    //58~59
                 short int DataLevelThreshold[16]; //60~91 数据分级门限值
                 short int P4;    //92~93
                 short int P5;    //94~95
                 short int P6;    //96~97
                 short int P7;    //98~99
                 short int P8;    //100~101
                 short int P9;    //102~103
                 short int P10;   //104~105
                 short int NumberOfMaps; //106~107 底图数据中的块数； 
                         // Version;   高字节表示 产品的版本号，原始产品为0；
// StopBlank;  低字节1=Stop ON, 2=Stop OFF
        unsigned long  int OffsetToSymbology;    //108~111
        unsigned long  int OffsetToGraphic;      //112~115
        unsigned long  int OffsetToTabular;      //116~119
         

}; 
////以上是固定都要有的文件头
struct SYMBOLOGY
{ short  BlockDivider; //数据块分隔符=-1
  short  nBlockId; // 产品数据标识=1
};//区分1、2、3
/////1类产品
 struct onetow
        { unsigned char    LengthOfBlock[4];            //块的长度
            short            NumberOfLayers;//层的个数
              
        };
/////////////1类产品
///举例径向数据
struct ifon1
{  short    LayerDivider;///分割符=-1
   unsigned char    cch[4];  //层的长度
};
struct tagLVPacket
{
short int PacketCode;           //6      Packet Type 6
short int LengthOfDataBlock;    //Number of bytes in block not including self or packet code
//Data Block
};
struct jingxiangtow
{ //short   nflag;///分割符=-1    
//short int  IndexofFirstRangeBin;        //0-460
    short int NumberofRangeBins;        //1-460
    short int ICenterofSweep;            //
    short  JCenterofSweep;            //
    short  ScaleFactor;                //0.001-8.000
    short  NumberofRadials;  
};//格式文档第48页
struct jingxiang
{
unsigned short Number;          //1-230
unsigned short RadialStartAngle;
unsigned short RadialAngelDelta;
};
///径向数据举例

struct cr                        
{ 
 unsigned short nFlag2;//00C0
 short nIStart;//起始i坐标
 short nJStart;//起始j坐标
 unsigned short nXScale;//x分辨率
 unsigned short nXFraction;
 unsigned short nYScale;//y分辨率
 unsigned short nYFraction;
 unsigned short nRowNum;//行数
 unsigned short nPackFormat;//包的格式
};
struct mye
{ short int PageNumber; //数据页号
   short int LengthOfPage;  //页数据长度（字节数）
};
///2类产品
struct zbf
{          unsigned char    LengthOfBlock[4];  //数据长度（字节数）
HEADER BLOCK1;
DESCRIPTION BLOCK2;
                 short int BlockDivider; //数据块分隔符=-1
                 short int NumberOfPages; //数据总页面数
                // short int NumberOfCharacters; //页内字符数
               // short int EndOfPageFlag; //数据结束标志=-1



};
///3类产品
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
    };//格式文档第48页

struct bb2
{ 
    short int ICenterofSweep;            //
    short  JCenterofSweep;  
    };//格式文档第48页

