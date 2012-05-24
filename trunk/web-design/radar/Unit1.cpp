//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <windows.h>
#include<math.h>
#include <iomanip.h>
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>
#include <fstream.h>
#include <stdio.h>
#include <dir.h>
#include <time.h>
#include "math.h"
#include   <tlhelp32.h>
#include   <sys/types.h>
  #include   <sys/stat.h>
#include   <algorith.h>
#include "whihr_radproj.h"
#include "DateUtils.hpp"
#include <stdio.h>
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
FILE *fp60,*fplj;
TDateTime tt,tq,tv,tvil,tet,t60;
typedef struct {
    short bfType;
    long  bfSize;
    short bf1;
    short bf2;
    long bfOffbits;
}BMP_fileh; //14 bytes

typedef struct {
    long biSize;
    long biWidth;
    long biHeight;
    short biPlanes;//1
    short biBitcount;// 1 4 8 24
    long biComp;//0 1 2
    long biSizeimage;
    long biX;
    long biY;
    long biClrused;
    long biClrimp;
}BMP_infoh; //40 bytes

typedef struct {
    unsigned char rB;
    unsigned char rG;
    unsigned char rR;
    unsigned char rX;
}BMP_rgb;//4 bytes

BMP_rgb zfpal[256];
int GMS_W=1000,GMS_H=1000;
unsigned char data[1001][1001],qdata[1001][1001],etdata[1001][1001],data1[1001][1001],vildata[1001][1001],vdata[1001][1001];
double radlat, radlon, radh;
float  xj,yj,xyl[1000][1000];
double ele, az,L,dh,ds,lon,lat,yjs,yjh;
int sz[460][460],bzf=0;
String  flj,f60,sxr,rdz,lljj,sds,sd,ss,l,ss3,yt,yth,mlljj,ss4,ss5,ss6,ss7,ss8,ss9,ltp,yn,ssd,sj1,sd1,sd2,sd3,sd60;
TDateTime time1,time2,time3,time4,time5,time6,time7,time8,time9,time10,time11,time12,time13,time14;
FILE *fp11;
float high0[30]={
		15.2,13.7,12.2,10.7,9.1,8.5,7.9,7.6,7.3,6.7,
        6.1,5.8,5.5,5.2,4.9,4.6,4.3,4.0,3.7,3.4,3.0,
		2.7,2.4,2.1,1.8,1.5,1.2,0.9,0.6,0.3};
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
      short  kgl;
      short  qkgl;
       short  ygl;
    };//格式文档第48页

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
  void     ActToPro(float&lon,float&lat,float posx, float posy, float lon0, float lat0,

float m_centX, float m_centY, float m_Resolute)
        {
           // float lon, lat;//经纬度
            float p, c;//直角坐标
            //lon0, lat0;//合肥中心位置经纬度
            // float r = 6370;//地球半径
            lon0 = (float)(lon0 * PI / 180);
            lat0 = (float)(lat0 * PI / 180);
            posx = (float)((posx - m_centX) * m_Resolute / 6370.0);
            posy = (float)((m_centY - posy) * m_Resolute / 6370.0);
            //lon = (float)(float)(Longitude * Math.PI / 180);
            //lat = (float)(float)(Latitude * Math.PI / 180);
            p = (float)sqrt(pow(posx, 2) + pow(posy,2));            c = (float)atan(p);

            lon = lon0 + (float)atan(posx * sin(c) / (p *cos(lat0) * cos(c) - posy * sin(lat0) * sin(c)));            lat = (float)asin(cos(c) * sin(lat0) + posy* sin(c) * cos(lat0) / p);            lat = (float)(lat * 180 / PI);
            lon = (float)(lon * 180 / PI);

        }
  void PointF(float& Xact,float& Yact,float Longitude, float Latitude, float lon0, float lat0, float m_centX, float m_centY, float m_Resolute)
        {
            float lon, lat;//经纬度
            float x, y;//直角坐标
            //float lon0,lat0;//合肥中心位置经纬度
              float r = 6370,pi=3.1415926;//地球半径
            //PointF pz;//浮点点变量
            lon0 = (float)(lon0 * pi / 180);
            lat0 = (float)(lat0 * pi / 180);

            lon = (float)(float)(Longitude * pi / 180);
            lat = (float)(float)(Latitude * pi / 180);

            x = (float)(r * cos(lat) * sin(lon - lon0) / (sin(lat) *sin(lat0) + cos(lat) * cos(lat0) * cos(lon - lon0)));
            y = (float)(-r * (sin(lat) *cos(lat0) -cos(lat) * sin(lat0) *cos(lon - lon0)) / (sin(lat) *sin(lat0) + cos(lat) *cos(lat0) * cos(lon - lon0)));
            Xact = m_centX + x / m_Resolute;
             Yact = m_centY + y / m_Resolute;

        }

   unsigned short ChangeWord(unsigned short nValue)
        {
            byte hibyte, lobyte;
            hibyte = (byte)(nValue / 256);
            lobyte = (byte)(nValue % 256);
            return (unsigned short)(lobyte * 256 + hibyte);
        }
      unsigned int ChangeDWord(unsigned int nValue)
        {
            unsigned short hiword, loword;
            hiword = ChangeWord((unsigned short)(nValue / 65536));
            loword = ChangeWord((unsigned short)(nValue % 65536));
            return (unsigned int)(loword * 65536 + hiword);

        }

          unsigned long ChangeWord1(unsigned long nValue)
        {
           int high = nValue>>32;
int low = nValue;
return (low<<32+high);

        } 





        void GetRadialDate(unsigned short JulianDate, int& year, int& month, int& day)
{
	int JLDAYN = JulianDate+2440587;
	int L   = JLDAYN + 68569 ;
	int N   = 4 * L / 146097 ;
		L  = L - (146097 * N + 3) / 4 ;
	int I   = 4000 * (L + 1) / 1461001 ;
		L   = L - 1461 * I / 4 + 31 ;
	int J   = 80 * L / 2447 ;
		day  = L - 2447 * J / 80 ;
		L  = J / 11 ;
		month  = J + 2 - 12 * L ;
		year  = 100 * (N - 49) + I + L ;
}
void GetRadialTime(unsigned long liMilliSeconds, int& hour, int& minute, int& seconds)
{
   	int Seconds=liMilliSeconds;///1000;
	hour = Seconds/3600000;
	minute= (Seconds-hour*3600000)/60000 ;
	seconds = Seconds -(60*hour+minute)*60 ;
}
//////////////




void __fastcall TForm1::Button1Click(TObject *Sender)
{
// int x[17]={255,0,0,192,122,30,166,0,16,252,200,140,254,254,238,212,170},y[17]={255,0,172,192,114,38,252,234,146,244,200,140,172,100,2,142,36},z[17]={255,0,164,254,238,208,168,0,26,100,2,0,172,92,48,254,250};

////

 int x[16]={255,0,198,123,24,165,0,16,255,206,140,255,255,239,214,173},
 y[16]={255,174,195,113,36,255,235,146,247,203,142,173,101,0,142,36},
z[16]={255,165,255,239,214,173,0,24,99,0,0,173,101,0,255,255};

////

 for(int i=0;i<16;i++)
 {

         zfpal[i].rB=z[i];
        zfpal[i].rG=y[i];
        zfpal[i].rR=x[i];
        zfpal[i].rX=0;
    }


  FILE *fp;
    char xs[80];


  for(int k=0;k<1;k++)
     {
     for(int i=0;i<=GMS_H;i++)
     {for(int j=0;j<=GMS_W;j++)
     {// if(data[i][j]>=15)
    //ShowMessage(data[i][j]);
     // if(data[i][j]>=3)
      qdata[i][j]=int((qdata[i][j]+qdata[i][j+1]+qdata[i][j-1]+qdata[i+1][j]+qdata[i-1][j])/5.);

     //if(data[i][j]>=8)
   // data[i][j]=(data[i][j+1]+data[i][j-1]+data[i+1][j]+data[i-1][j])/4;

     }
     }
     }

 Button2->Click() ;


}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button2Click(TObject *Sender)
{
BMP_fileh BMPh1;
    BMP_infoh BMPh2;
  BMPh1.bfType=19778;
    BMPh1.bfSize=(long)(14+40+256*4+GMS_W*GMS_H);
    BMPh1.bf1=0;
    BMPh1.bf2=0;
    BMPh1.bfOffbits=(long)(40+256*4);

    BMPh2.biSize=40L;
    BMPh2.biWidth=(long)GMS_W;
    BMPh2.biHeight=(long)GMS_H;
    BMPh2.biPlanes=1;//1
    BMPh2.biBitcount=8;// 1(2) 4(16) 8(256) 24(true color)
    BMPh2.biComp=0L;//0 1 2
    BMPh2.biSizeimage=((long)GMS_W*(long)GMS_H);
    BMPh2.biX=(long)GMS_W;
    BMPh2.biY=(long)GMS_H;
    BMPh2.biClrused=0L;
    BMPh2.biClrimp=0L;
    FILE *fp;
    if (ss3.SubString(1,1)!="1")
    {
    ss3=ltp+"QREF\\0.5\\"+ss3+".bmp";
    fp=fopen(ss3.c_str() ,"wb");
     //1文件头            long
    fwrite(&BMPh1.bfType,2,1,fp);
    fwrite(&BMPh1.bfSize,4,1,fp);
    fwrite(&BMPh1.bf1,2,1,fp);
    fwrite(&BMPh1.bf2,2,1,fp);
    fwrite(&BMPh1.bfOffbits,4,1,fp);

    //2位图信息头
    fwrite(&BMPh2.biSize,4,1,fp);
    fwrite(&BMPh2.biWidth,4,1,fp);
    fwrite(&BMPh2.biHeight,4,1,fp);
    fwrite(&BMPh2.biPlanes,2,1,fp);
    fwrite(&BMPh2.biBitcount,2,1,fp);
    fwrite(&BMPh2.biComp,4,1,fp);
    fwrite(&BMPh2.biSizeimage,4,1,fp);
    fwrite(&BMPh2.biX,4,1,fp);
    fwrite(&BMPh2.biY,4,1,fp);
    fwrite(&BMPh2.biClrused,4,1,fp);
    fwrite(&BMPh2.biClrimp,4,1,fp);

    //3颜色信息
       for(int i=0;i<256;i++){
        fwrite(&zfpal[i],sizeof(BMP_rgb),1,fp);
    }
    int xx=0;//偏移量
    for(int i=GMS_H;i>0;i--){
        for(int j=xx;j<GMS_W;j++){
           if(i<6)
           qdata[i][j]=0;
            if(qdata[i][j]<5)
            qdata[i][j]=0;
            fwrite(&qdata[i][j],1,1,fp);
        }
        for(int j=0;j<xx;j++){
           // if(data[i][j]<6)
            //data[i][j]=0;
          fwrite(&qdata[i][j],1,1,fp);
        }
    }
    fclose(fp);

bzf=0;
 Image1->Picture->LoadFromFile(ss3.c_str());
 ///
 ////

/*AnsiString flsd;
flsd="c:\\q00.txt";

fp=fopen(flsd.c_str(),"w");

 ///
float lon4,lat4,dbzp;
for(int i=(GMS_H-10);i>0;i=i-10){
        for(int j=0;j<=(GMS_W-10);j=j+10){
        for(int ii=i+10;ii>i;ii--)
        {for(int jj=j;jj<j+10;jj++)
        {dbzp=dbzp+qdata[ii][jj];

        }
        }
       dbzp=dbzp/100.0;


        if (dbzp>10)
        { ActToPro(lon4,lat4,j+5,i-5, 114,34.0,500, 500, 1);

         fprintf(fp,"%f %f 1\n",lon4,lat4);
          //ShowMessage(FloatToStr(lon4));
          //ShowMessage(FloatToStr(lat4));
                 // Image1->Transparent=true;
         //Image1->Canvas->Font->Size=20;
        //Image1->Canvas->TextOutA(i,j,"+");
        }
        //>Draw(50,50,"+");
       dbzp=0;
        }
        }
      fclose(fp);*/
 ///
  Image1->Picture->SaveToFile(ss3.c_str());
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
FILE *fpr;

    unsigned char ss,xs[200];
    char str[80];
    int i,j;

    fpr=fopen("10080918.000","rb");

    fread(xs,128,1,fpr);//跳过前128个字节的文件头
    for(i=0;i<GMS_H;i++){
        for(j=0;j<GMS_W;j++){
            fread(&ss,1,1,fpr);//读象素值
            if(ss>14)
            data[i][j]=14;
            else
            data[i][j]=ss;
         //ShowMessage(ss);
        }
    }
    fclose(fpr);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
FILE *fp1;
String f;
int a,b;
float  lon,lat,xx,yy;
 f=l+"河南省地区边界数据.txt";
         fp1=fopen(f.c_str(),"r");

  while(!feof(fp1))
 {  fscanf(fp1, "%d%d%d%d%d%d%d",&a,&a,&a,&a,&a,&a,&b);
  for(int i=0;i<b;i++)
   {
    fscanf(fp1, "%f%f",&lon,&lat);
     PointF(xx,yy,lon,lat, 114,34,500,500,1);
      data[int(yy+0.5)][int(xx+0.5)]=14;
    }


 }
 fclose(fp1);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{

FILE *fp;


int nian,yue,ri,xiaoshi,fenzhong,miao;
 long tt;

////
int low,high,jxs,sjs,h=0,zz,a[360][230],db,yjh;
for(int i=0;i<360;i++)
{
        for(int j=0;j<230;j++)
        {
          a[i][j]=0;

           }
           }

char hb;
HEADER  hed;
        DESCRIPTION  nn;
         SYMBOLOGY n3;
        onetow n4;
               ifon1 n5;
        tagLVPacket n6;
AnsiString ff;
ff=lljj+sd;

fp = fopen(ff.c_str(),"rb");
fread(&hed,sizeof(hed),1,fp);
fread(&nn,sizeof(nn),1,fp);
 radlat=(int)ChangeDWord((unsigned int)(nn.RadarLatitude))*0.001;
           radlon=(int)ChangeDWord((unsigned int)(nn.RadarLongtitude))*0.001;
           radh = (short)ChangeWord((unsigned short)(nn.RadarHeight))*0.3048;
          
           PointF(xj,yj,radlon,radlat,  114,34.0,500,500,1);

           yjh = ChangeWord((unsigned short)(nn.ElevationNumber));
           if(yjh==1)
           ele=0.5;
           if(yjh==2)
           ele=1.5;
           if(yjh==3)
           ele=2.4;
          CRadEPrj *p = new CRadEPrj(radlon,radlat,radh);
p->Initialized(40.0, 0, 0, 1000);

              fread(&n3,sizeof(n3),1,fp);
n3.nBlockId=(short)ChangeWord((unsigned short)(n3.nBlockId)) ;

//long nTimeofMessage=nn.TimeofMessage2[0]<<24|nn.TimeofMessage2[1]<<16|
                                nn.TimeofMessage2[2]<<8|nn.TimeofMessage2[3];

//GetRadialTime(nTimeofMessage*1000,xiaoshi,fenzhong,miao);
////////
if(n3.nBlockId==1)
{ fread(&n4,sizeof(n4),1,fp);
n4.NumberOfLayers=(short)ChangeWord((unsigned short)(n4.NumberOfLayers));

 fread(&n5,sizeof(n5),1,fp);
 fread(&n6,sizeof(n6),1,fp);
n5. LayerDivider=(short)ChangeWord((unsigned short)(n5. LayerDivider)) ;


               jingxiangtow  mm;
                       fread(&mm,sizeof(mm),1,fp);

            jxs = (short)ChangeWord((unsigned short)(mm.NumberofRadials));


                          jingxiang  jx;
             for(int i=0;i<jxs;i++)
             {fread(&jx,sizeof(jx),1,fp);
              sjs = ChangeWord((unsigned short)(jx.Number))*2;
              yjs=ChangeWord((unsigned short)(jx.RadialStartAngle))*0.1;

              if(int(yjs)>=360)
              zz=int(yjs)-360;
              else
              zz=int(yjs);
             for(int j=0;j<sjs;j++)
              {fread(&hb,sizeof(char),1,fp);
               high=(hb>>4)&0xf;
               low=hb&15;

                             for(int ii=0;ii<high;ii++)
               {
               a[zz][ii+h]=low+1;


               }
               h=h+high;
              }
              h=0;
             }
             fclose(fp);


           for(int i=-230;i<230;i++)
             {
for(int j=-230;j<230;j++)
{  if(j!=0||i!=0)
{
  p->tilt_of_gps(0.5,  i, j,  lon, lat,dh,ds) ;
  p->gps_to_tilt(lon,lat,0.5, az,L,dh);

  if(L<230&&az<360)
{  //if(a[int(az)][int(L)]>5)
           //   { ShowMessage(a[int(az)][int(L)]);
             //  ShowMessage(az);
             //   ShowMessage(L);
              //  }
 //if(a[int(az)][int(L)]>data[int(j+yj)][int(i+xj)]&&(data1[int(j+yj)][int(i+xj)]>190||xyl[int(j+yj)][int(i+xj)]>0.5||bzf==2))
 if(a[int(az)][int(L)]>qdata[int(j+yj)][int(i+xj)])
 {
 qdata[int(j+yj)][int(i+xj)]=a[int(az)][int(L)];
 /*if(data[int(j+yj)][int(i+xj)]>10)
 {
 ShowMessage(FloatToStr(lon));
          ShowMessage(FloatToStr(lat));
          } */

// ShowMessage(data1[int(j+yj)][int(i+xj)]);
 }
// else
 // data[int(j+yj)][int(i+xj)]=0;



}
  }
}
}

delete p;
}

}
//---------------------------------------------------------------------------



void __fastcall TForm1::FormCreate(TObject *Sender)
{

FILE *fp1;
String  pzlj,fff;
l=GetCurrentDir()+"\\";
char lj0[500],lj1[500];
pzlj=l+"配置文件.ini";
fp1=fopen(pzlj.c_str(),"r");
 fscanf(fp1, "%s%s",&lj0,&lj1);
 lljj=AnsiString(lj0);
 // fscanf(fp1, "%s%s",&lj0,&lj1);
  //mlljj=AnsiString(lj0);
   //fscanf(fp1, "%s%s",&lj0,&lj1);
   // yt=AnsiString(lj0);
    fscanf(fp1, "%s%s",&lj0,&lj1);
    ltp=AnsiString(lj0);
   fscanf(fp1, "%s%s",&lj0,&lj1);
    rdz=AnsiString(lj0);
     fclose(fp1);
     
     // Button19->Click() ;
      //Button20->Click();
    // fff=l+"\\风暴追踪.exe";
  //WinExec(fff.c_str(),SW_HIDE);
  /*Button6->Click() ;
  Button17->Click();
  Button21->Click();
      Button26->Click();
         //Button31->Click();
         //Button36->Click() ;
         //Button40->Click() ;
         //Button46->Click() ;
         Button51->Click() ;
       Button56->Click() ;
         //Button61->Click() ;
         //Button45->Click() ;
         // Button38->Click() ;  */
        Button70->Click() ; 
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{

TSearchRec sr;
TDateTime time,t;
      String path=lljj+"*R_10_230_5.*",sj;
      if (FindFirst(path,faAnyFile,sr)==0)
   {
  do
  { sd=sr.Name;
   sj=sd.SubString(16,4)+"-"+sd.SubString(20,2)+"-"+sd.SubString(22,2)+" "+sd.SubString(24,2)+":"+sd.SubString(26,2)+":"+sd.SubString(28,2);
    time=StrToDateTime(sj);
    if(time>time1)
    {time1=time;
                 }
  }


   while(FindNext(sr)==0);
     FindClose(sr);
   }
    t=time1+8/24.;
    tq=t;
    tt=t;
    String nian,yue,ri,shi,fen;
   Word Year,Month,Day,Hour,Me,Mee,Meee;
   DecodeDate(t,Year,Month,Day);
   DecodeTime(t,Hour,Me,Mee,Meee);
   nian=IntToStr(Year);
if(Month<10)
yue="0"+IntToStr(Month);
else
yue=IntToStr(Month);
if(Day<10)
ri="0"+IntToStr(Day);
else
ri=IntToStr(Day);
if(Hour<10)
shi="0"+IntToStr(Hour);
else
shi=IntToStr(Hour);
if(Me<10)
fen="0"+IntToStr(Me);
else
fen=IntToStr(Me);
ss3=nian+yue+ri+shi+fen;
ss4=nian+yue+ri+shi;
sxr=nian+"年"+yue+"月"+ri+"日"+shi+"时"+fen+"分";

yth=nian.SubString(3,2) +yue+ri+shi;
String f2=yt+yth+".000";
///
 if(!FileExists(f2))
 {
  t=time1+7/24.;
     DecodeDate(t,Year,Month,Day);
   DecodeTime(t,Hour,Me,Mee,Meee);
   nian=IntToStr(Year);
if(Month<10)
yue="0"+IntToStr(Month);
else
yue=IntToStr(Month);
if(Day<10)
ri="0"+IntToStr(Day);
else
ri=IntToStr(Day);
if(Hour<10)
shi="0"+IntToStr(Hour);
else
shi=IntToStr(Hour);
yth=nian.SubString(3,2) +yue+ri+shi;
}
//
//Button9->Click() ;
//Button12->Click() ;
 Button7->Click() ;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
 for(int i=GMS_H;i>0;i--)
{
        for(int j=0;j<GMS_W;j++)
        {
                    qdata[i][j]=0;
           }
           }
TSearchRec sr;
    int countMin;
TDateTime time;
      String path=lljj+"*R_10_230_5.*",sj;
      if (FindFirst(path,faAnyFile,sr)==0)
   {
  do
  { sd=sr.Name;
   sj=sd.SubString(16,4)+"-"+sd.SubString(20,2)+"-"+sd.SubString(22,2)+" "+sd.SubString(24,2)+":"+sd.SubString(26,2)+":"+sd.SubString(28,2);
    time=StrToDateTime(sj);
   countMin=MinutesBetween(time,time1);
   if(time<=time1&&countMin<6)
   {

        Button5->Click();

   }
  }

   while(FindNext(sr)==0);
     FindClose(sr);
   }



 Button1->Click();




}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{     Button6->Click();
   Button17->Click();
    Button21->Click();
     Button26->Click();
    Button38->Click();
              Button40->Click() ;
        Button46->Click() ;
         Button51->Click() ;
         Button56->Click() ;
         Button61->Click() ;
          Button67->Click() ;
            Button36->Click();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
 FILE *fp;
    char xs[80];
    int xh,cR,cG,cB,ii=0,r,g,b;

    fp=fopen("colormap.ir","r");
    if(fp==NULL){
              return;
    }

    fscanf(fp,"%s%s%s",xs,xs,xs);
   // int i=0;j=0;
    while(!feof(fp)){
        fscanf(fp,"%d%d%d%d",&xh,&cR,&cG,&cB);
        if(!feof(fp)){
        cR=cR/257;
        cG=cG/257;
        cB=cB/257;
        zfpal[xh].rB=cB;
        zfpal[xh].rG=cG;
        zfpal[xh].rR=cR;
        zfpal[xh].rX=0;


    }
    }
    fclose(fp);
   

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button9Click(TObject *Sender)
{
FILE *fpr,*fp1;
    unsigned char ss,xs[200];
    float lon,lat,xx,yy;
    String f,ff,f4;
    char str[80];
    int i,j;
    f="land.dat";
    ff=yt+yth;

    if(!FileExists(ff))
 { bzf++;
    return;
    }
    f4=yn+"20"+yth.SubString(1,8) +".bmp";
     if(FileExists(f4))
 {
    return;
    }

    fp1 = fopen(f.c_str() ,"rb");

    fpr=fopen(ff.c_str() ,"rb");

    fread(xs,128,1,fpr);//跳过前128个字节的文件头
    for(i=0;i<512;i++){
        for(j=0;j<512;j++){
            fread(&ss,1,1,fpr);//读象素值
             fread(&lon,sizeof(lon),1,fp1);
 fread(&lat,sizeof(lat),1,fp1);

 if(lon>108&&lon<120&&lat>30&&lat<38)
 {     PointF(xx,yy,lon,lat, 114,34.0,500,500,1);
  for(int i=(int(yy)-8);i<(int(yy)+8);i++)
 {
 for(int j=(int(xx)-8);j<(int(xx)+8);j++)
 {       // ShowMessage(i);


            data1[i][j]=ss;

            }
            }
            }
         //ShowMessage(ss);
        }
    }
    fclose(fpr);
     fclose(fp1);

  Button15->Click() ;

}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button11Click(TObject *Sender)
{
 BMP_fileh BMPh1;
    BMP_infoh BMPh2;
  BMPh1.bfType=19778;
    BMPh1.bfSize=(long)(14+40+256*4+GMS_W*GMS_H);
    BMPh1.bf1=0;
    BMPh1.bf2=0;
    BMPh1.bfOffbits=(long)(40+256*4);

    BMPh2.biSize=40L;
    BMPh2.biWidth=(long)GMS_W;
    BMPh2.biHeight=(long)GMS_H;
    BMPh2.biPlanes=1;//1
    BMPh2.biBitcount=8;// 1(2) 4(16) 8(256) 24(true color)
    BMPh2.biComp=0L;//0 1 2
    BMPh2.biSizeimage=((long)GMS_W*(long)GMS_H);
    BMPh2.biX=(long)GMS_W;
    BMPh2.biY=(long)GMS_H;
    BMPh2.biClrused=0L;
    BMPh2.biClrimp=0L;
    FILE *fp;
    fp=fopen("e:\\bv.bmp","wb");
     //1文件头            long
    fwrite(&BMPh1.bfType,2,1,fp);
    fwrite(&BMPh1.bfSize,4,1,fp);
    fwrite(&BMPh1.bf1,2,1,fp);
    fwrite(&BMPh1.bf2,2,1,fp);
    fwrite(&BMPh1.bfOffbits,4,1,fp);

    //2位图信息头
    fwrite(&BMPh2.biSize,4,1,fp);
    fwrite(&BMPh2.biWidth,4,1,fp);
    fwrite(&BMPh2.biHeight,4,1,fp);
    fwrite(&BMPh2.biPlanes,2,1,fp);
    fwrite(&BMPh2.biBitcount,2,1,fp);
    fwrite(&BMPh2.biComp,4,1,fp);
    fwrite(&BMPh2.biSizeimage,4,1,fp);
    fwrite(&BMPh2.biX,4,1,fp);
    fwrite(&BMPh2.biY,4,1,fp);
    fwrite(&BMPh2.biClrused,4,1,fp);
    fwrite(&BMPh2.biClrimp,4,1,fp);

    //3颜色信息
       for(int i=0;i<256;i++){
        fwrite(&zfpal[i],sizeof(BMP_rgb),1,fp);
    }
    int xx=0;//偏移量
    for(int i=GMS_H;i>0;i--){
        for(int j=xx;j<GMS_W;j++){
            fwrite(&data1[i][j],1,1,fp);
        }
        for(int j=0;j<xx;j++){
            fwrite(&data1[i][j],1,1,fp);
        }
    }
 
    fclose(fp);

        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button10Click(TObject *Sender)
{
/*
FILE *fp1;
String f;
int a,b;
float  lon,lat,xx,yy;
 f="河南省地区边界数据.txt";
         fp1=fopen(f.c_str(),"r");

  while(!feof(fp1))
 {  fscanf(fp1, "%d%d%d%d%d%d%d",&a,&a,&a,&a,&a,&a,&b);
  for(int i=0;i<b;i++)
   {
    fscanf(fp1, "%f%f",&lon,&lat);
     PointF(xx,yy,lon,lat, 114,34,500,500,1);
      data[int(yy)][int(xx)]=1;
    }


 }
 fclose(fp1);  */
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button12Click(TObject *Sender)
{


FILE *fp1;
String f,sj;
int a,b;
char bb[300],zhan[20];
TDateTime time;
float  lon,lat,gd,yl,xx,yy;
 f="c:\\yl.txt";
       if(!FileExists(f))
       { bzf++;
    return;
    }
         fp1=fopen(f.c_str(),"r");
      fscanf(fp1, "%s",&bb);
      fscanf(fp1, "%s",&bb);
      fscanf(fp1, "%s",&bb);
      sj=AnsiString(bb);
      fscanf(fp1, "%s",&bb);
      sj=sj+" "+AnsiString(bb);
      //ShowMessage(sj);
      //sj=AnsiString(bb).SubString(1,4)+"-"+AnsiString(bb).SubString(7,2)+"-"+AnsiString(bb).SubString(11,2)+" "+AnsiString(bb).SubString(15,2)+":00:00";
     time=StrToDateTime(sj);
    // ShowMessage(time);
    // ShowMessage(tt);
     //ShowMessage(MinutesBetween(time,tt));
  if(MinutesBetween(time,tt)<60)
  {
  while(!feof(fp1))
 { fscanf(fp1, "%s%f%f%f%f",&zhan,&lon,&lat,&yl,&gd);
 if(yl>=0.5)
 PointF(xx,yy,lon,lat, 114,34,500,500,1);
   for(int i=(xx-10);i<(xx+10);i++)
   {  for(int j=(yy-15);j<(yy+15);j++)
    {xyl[i][j]=yl;
  }
    }


 }
 }
 fclose(fp1);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer2Timer(TObject *Sender)
{

TSearchRec sr,sr1;
AnsiString f20;
String sd,f,ff;
  int   iAttributes   =   0;
    SYSTEMTIME   lpSystemTime;
/////////////????
TDateTime t,fan;

   String path;
   for (int i=0;i<8;i++)
   { if (i==0)
   {ff="QREF\\0.5\\" ;
   path=ltp+ff+"*.bmp";

   }
   if (i==1)
   {ff="QREF\\1.5\\";
   path=ltp+ff+"*.bmp";

   }
    if (i==2)
   {ff="QREF\\2.4\\";
   path=ltp+ff+"*.bmp";

   }
    if (i==3)
   {ff="QREF\\3.4\\";
   path=ltp+ff+"*.bmp";

   }
   if (i==4)
   {ff="cref\\";
   path=ltp+ff+"*.bmp";

   }
    if (i==5)
   {ff="ET\\";
   path=ltp+ff+"*.bmp";

   }
    if (i==6)
   {ff="v\\";
   path=ltp+ff+"*.bmp";

   }
    if (i==7)
   {ff="VIL\\";
   path=ltp+ff+"*.bmp";

   }
    if (FindFirst(path,faAnyFile,sr)==0)
   {
  do
  {
   sd=sr.Name;
   f=ltp+ff+sd;
    if   (FindFirst( f,iAttributes,   sr1)   ==   0)
    {
        FileTimeToSystemTime(&sr1.FindData.ftCreationTime,&lpSystemTime);        FindClose(sr1);
    }

    t=SystemTimeToDateTime(lpSystemTime)+StrToInt(Edit1->Text)/12.; 

    if(Now()>t)
  DeleteFile(ltp+ff+sd);

  }
  while(FindNext(sr)==0);
     FindClose(sr);
   }

  }


}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button13Click(TObject *Sender)
{

TSearchRec sr;
AnsiString f20;
String sd;
/////////////????
TDateTime t,fan;

   String path=mlljj+"*.txt";
    if (FindFirst(path,faAnyFile,sr)==0)
   {
  do
  {
   sd=sr.Name;
   f20=sd.SubString(1,4)+"-"+sd.SubString(5,2)+"-"+sd.SubString(7,2)+"  "+sd.SubString(9,2)+":00:00";
    t=StrToDateTime(f20);
    t=t+1/24.;
    if(Now()>t)
  DeleteFile(ltp+sd);

  }
  while(FindNext(sr)==0);
     FindClose(sr);
   }


}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button15Click(TObject *Sender)
{FILE *fp;
String f;
int xh,cR,cG,cB,ii=0,r,g,b;
f=l+"colormap.ir";

 fp=fopen(f.c_str() ,"r");
    if(fp==NULL){
              return;
    }

    while(!feof(fp)){
        fscanf(fp,"%d%d%d%d",&xh,&cR,&cG,&cB);
        if(!feof(fp)){
        if(xh!=0)
        {
        cR=cR/257;
        cG=cG/257;
        cB=cB/257;
        }
        zfpal[xh].rB=cB;
        zfpal[xh].rG=cG;
        zfpal[xh].rR=cR;
        zfpal[xh].rX=0;

      }

    }

    fclose(fp);

  for(int k=0;k<1;k++)
     {
     for(int i=0;i<GMS_H;i++)
     {for(int j=0;j<GMS_W;j++)
     {
      data1[i][j]=int((data1[i][j]+data[i][j+1]+data1[i][j-1]+data1[i+1][j]+data1[i-1][j]+data1[i+1][j+1]+data1[i-1][j-1]+data1[i+1][j-1]+data1[i-1][j+1])/9.);


     }
     }
     }

  Button16->Click() ;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button16Click(TObject *Sender)
{
BMP_fileh BMPh1;
    BMP_infoh BMPh2;
  BMPh1.bfType=19778;
    BMPh1.bfSize=(long)(14+40+256*4+GMS_W*GMS_H);
    BMPh1.bf1=0;
    BMPh1.bf2=0;
    BMPh1.bfOffbits=(long)(40+256*4);

    BMPh2.biSize=40L;
    BMPh2.biWidth=(long)GMS_W;
    BMPh2.biHeight=(long)GMS_H;
    BMPh2.biPlanes=1;//1
    BMPh2.biBitcount=8;// 1(2) 4(16) 8(256) 24(true color)
    BMPh2.biComp=0L;//0 1 2
    BMPh2.biSizeimage=((long)GMS_W*(long)GMS_H);
    BMPh2.biX=(long)GMS_W;
    BMPh2.biY=(long)GMS_H;
    BMPh2.biClrused=0L;
    BMPh2.biClrimp=0L;
    FILE *fp;
    ss3=yn+"20"+yth.SubString(1,8) +".bmp";

    fp=fopen(ss3.c_str() ,"wb");
     //1文件头            long
    fwrite(&BMPh1.bfType,2,1,fp);
    fwrite(&BMPh1.bfSize,4,1,fp);
    fwrite(&BMPh1.bf1,2,1,fp);
    fwrite(&BMPh1.bf2,2,1,fp);
    fwrite(&BMPh1.bfOffbits,4,1,fp);

    //2位图信息头
    fwrite(&BMPh2.biSize,4,1,fp);
    fwrite(&BMPh2.biWidth,4,1,fp);
    fwrite(&BMPh2.biHeight,4,1,fp);
    fwrite(&BMPh2.biPlanes,2,1,fp);
    fwrite(&BMPh2.biBitcount,2,1,fp);
    fwrite(&BMPh2.biComp,4,1,fp);
    fwrite(&BMPh2.biSizeimage,4,1,fp);
    fwrite(&BMPh2.biX,4,1,fp);
    fwrite(&BMPh2.biY,4,1,fp);
    fwrite(&BMPh2.biClrused,4,1,fp);
    fwrite(&BMPh2.biClrimp,4,1,fp);

    //3颜色信息
       for(int i=0;i<256;i++){
        fwrite(&zfpal[i],sizeof(BMP_rgb),1,fp);
    }
    int xx=0;//偏移量
    for(int i=GMS_H;i>0;i--){
        for(int j=xx;j<GMS_W;j++){
        if(j>900||i>900||i<100||j<100)
        data1[i][j]=0;
            fwrite(&data1[i][j],1,1,fp);
        }
        for(int j=0;j<xx;j++){
            fwrite(&data1[i][j],1,1,fp);
        }
    }
    fclose(fp);
    
bzf=0;
Image1->Picture->LoadFromFile(ss3.c_str());
  Image1->Picture->SaveToFile(ss3.c_str());
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button17Click(TObject *Sender)
{
TSearchRec sr;
 int countMin;
TDateTime time,time2,t;
String sdl="c:\\fkx.txt";
fp11=fopen(sdl.c_str(),"w");
      String path=lljj+"*VWP_20*",sj;
      if (FindFirst(path,faAnyFile,sr)==0)
   {
  do
  { sd=sr.Name;
   sj=sd.SubString(16,4)+"-"+sd.SubString(20,2)+"-"+sd.SubString(22,2)+" "+sd.SubString(24,2)+":"+sd.SubString(26,2)+":"+sd.SubString(28,2);
    time=StrToDateTime(sj);
    if(time>time2)
    {sj1=sj;
    time2=time;
                 }
  }


   while(FindNext(sr)==0);
     FindClose(sr);
   }
  ///
   fprintf(fp11,"%s %s\n",sj1,"世界时");
    path=lljj+"*VWP_20*",sj;
      if (FindFirst(path,faAnyFile,sr)==0)
   {
  do
  { sd=sr.Name;
   sj=sd.SubString(16,4)+"-"+sd.SubString(20,2)+"-"+sd.SubString(22,2)+" "+sd.SubString(24,2)+":"+sd.SubString(26,2)+":"+sd.SubString(28,2);
    time=StrToDateTime(sj);
   countMin=MinutesBetween(time,time2);
     if(time<=time2&&countMin<6)
   {
       ssd=sd;
        Button18->Click();
   }
   }
     while(FindNext(sr)==0);
     FindClose(sr);
   }
      fclose(fp11);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button18Click(TObject *Sender)
{

FILE *fp;
zbf n8;
 char hb;
int rb=0,bbf=0;
double ele, az,L,dh;
int nian,yue,ri,xiaoshi,fenzhong,miao;
 long tt;
float x0=0,y0=0,u;
int v;
 unsigned short Number1;
 ////
int low,high,jxs,sjs,h=0,zz,a[360][230],db,yjh;
float yjs,lon,lat;
HEADER  hed;
        DESCRIPTION  nn;
        SYMBOLOGY n3;
         onetow n4;
        ifon1 n5;
        cr  mm;
        tagLVPacket n6;
        bar n7;
AnsiString ff;

//if(OpenDialog1->Execute())
//{ff=OpenDialog1->FileName;
//}
//else
//return;
ff=lljj+ssd;
fp = fopen(ff.c_str(),"rb");
fread(&hed,sizeof(hed),1,fp);
fread(&nn,sizeof(nn),1,fp);
radlat=(int)ChangeDWord((unsigned int)(nn.RadarLatitude))*0.001;
           radlon=(int)ChangeDWord((unsigned int)(nn.RadarLongtitude))*0.001;
                 fread(&n3,sizeof(n3),1,fp);
                       fread(&n4,sizeof(n4),1,fp);
                       fread(&n5,sizeof(n5),1,fp);
                       n4. NumberOfLayers = (short)ChangeWord((unsigned short)(  n4. NumberOfLayers));
                   long chd=n5.cch[0]<<24|n5.cch[1]<<16|
            n5.cch[2]<<8|n5.cch[3];
             u=0;
              v=0;
                        long gg=chd;
                                 do
                              {
               fread(&n6,sizeof(n6),1,fp);
             n6.PacketCode = (short)ChangeWord((unsigned short)(n6. PacketCode));
              n6.LengthOfDataBlock = (short)ChangeWord((unsigned short)(n6.LengthOfDataBlock));

                                    if(n6.PacketCode==4)
             {
              fread(&n7,sizeof(n7),1,fp);
               n7. value = (short)ChangeWord((unsigned short)(  n7. value));
              n7. x = (short)ChangeWord((unsigned short)(  n7. x));
                  n7. speed = (short)ChangeWord((unsigned short)(  n7. speed));
                  n7. y = (short)ChangeWord((unsigned short)(  n7. y));
                  n7. direction = (short)ChangeWord((unsigned short)(  n7.direction));


                  if(n7.x==474)
                   {
                  u=n7.speed;
                  v=n7.direction;
                 for(int i=0;i<30;i++)
                 {if(int((455-n7.y)/15.+0.5)==i)
                   fprintf(fp11,"%f %f %f %d %f\n",high0[i],radlon,radlat,v,u);
                 }

             }
             }

                   if( n6.PacketCode!=4)
                   {
                         for(int i=0;i< n6.LengthOfDataBlock;i++)
             { fread(&hb,sizeof(char),1,fp);
             }
             }

             gg=gg-n6.LengthOfDataBlock-4;
         }
          while(gg>0);
          fclose(fp);



}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button19Click(TObject *Sender)
{
char   cBuf[256];
          TListItem   *pItem;
          AnsiString   ExeFile;
          PROCESSENTRY32   pe32   =   {sizeof(pe32)};
          HANDLE   hSnapShot   =   CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);   
    
          if(hSnapShot   ==   NULL)   
                  return;   
          ListView1->Clear();   
    
          bool   bFlag   =   Process32First(hSnapShot,&pe32);   
          while   (bFlag)   
          {   
                  pItem   =ListView1->Items->Add();   
                  ExeFile   =   AnsiString(pe32.szExeFile);   
                  pItem->Caption   =   String(ListView1->Items->Count);   
                  if(ExeFile.Pos("\\")!=0)   
                          ExeFile   =   ExtractFileName(pe32.szExeFile);   
                  pItem->SubItems->Add(ExeFile);   
                  pItem->SubItems->Add(String(IntToHex(int(pe32.th32ProcessID),8)));   
                  pItem->SubItems->Add(String(IntToHex(int(pe32.th32ParentProcessID),8)));   
                  bFlag   =   Process32Next(hSnapShot,&pe32);   
          }   
          CloseHandle(hSnapShot);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button20Click(TObject *Sender)
{

 int n=ListView1->Items->Count;
String f;
/*if   (ListView1->SelCount   ==   0)
          {
                  MessageBox(Handle,"请选择一个进程先！",Application->Title.c_str()   ,MB_OK|MB_ICONWARNING);
                  return;
          } */
           for(int i=0;i<n;i++)
           {
           ListView1->Items->Item[i]->Selected   =   True ;
           f=ListView1->Items->Item[i]->SubItems->Strings[0];
          // ShowMessage(f);
           if(f=="风暴追踪.EXE")
           {
          int   pPid   =   ("0x"   +   ListView1->Selected->SubItems->Strings[1]).ToInt();


          HANDLE   ps   =   OpenProcess(1,false,pPid);
          ShowWindow(ps,SW_HIDE);//隐藏
          ps&&TerminateProcess(ps,-9);
          TerminateProcess(ps, -9);
          ShowWindow(ps,SW_HIDE);//隐藏
          }
          }           
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button21Click(TObject *Sender)
{
 for(int i=0;i<GMS_H;i++){
        for(int j=0;j<GMS_W;j++){
           etdata[i][j]=0;
           }
        }
TSearchRec sr;
TDateTime time,t;
      String path=lljj+"*ET_40*",sj;
      if (FindFirst(path,faAnyFile,sr)==0)
   {
  do
  { sd=sr.Name;
   sj=sd.SubString(16,4)+"-"+sd.SubString(20,2)+"-"+sd.SubString(22,2)+" "+sd.SubString(24,2)+":"+sd.SubString(26,2)+":"+sd.SubString(28,2);
    time=StrToDateTime(sj);
    if(time>time2)
    {time2=time;
                 }
  }


   while(FindNext(sr)==0);
     FindClose(sr);
   }
    t=time2+8/24.;
    tet=t;
    tt=t;
    String nian,yue,ri,shi,fen;
   Word Year,Month,Day,Hour,Me,Mee,Meee;
   DecodeDate(t,Year,Month,Day);
   DecodeTime(t,Hour,Me,Mee,Meee);
   nian=IntToStr(Year);
if(Month<10)
yue="0"+IntToStr(Month);
else
yue=IntToStr(Month);
if(Day<10)
ri="0"+IntToStr(Day);
else
ri=IntToStr(Day);
if(Hour<10)
shi="0"+IntToStr(Hour);
else
shi=IntToStr(Hour);
if(Me<10)
fen="0"+IntToStr(Me);
else
fen=IntToStr(Me);
ss5=nian+yue+ri+shi+fen;



Button23->Click() ;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button22Click(TObject *Sender)
{
 ///

FILE *fp;
String f;
    float x8,y8;
char hb;
double ele, az,L,dh;
int nian,yue,ri,xiaoshi,fenzhong,miao,pyl,bt[460][460];
 long tt;
float x0=1,y0=1;
 unsigned short Number1;
 for(int i=0;i<460;i++)
{
        for(int j=0;j<460;j++)
        {
          bt[i][j]=0;

           }
           }
////
int low,high,jxs,sjs,h=0,zz,db,yjh;
float yjs,lon,lat;
HEADER  hed;
        DESCRIPTION  nn;
        SYMBOLOGY n3;
         onetow n4;
        ifon1 n5;
        tagLVPacket n6;
        cr  mm;
AnsiString ff;
ff=lljj+sd1;

fp = fopen(ff.c_str(),"rb");
fread(&hed,sizeof(hed),1,fp);
fread(&nn,sizeof(nn),1,fp);
                 fread(&n3,sizeof(n3),1,fp);
                 radlat=(int)ChangeDWord((unsigned int)(nn.RadarLatitude))*0.001;
           radlon=(int)ChangeDWord((unsigned int)(nn.RadarLongtitude))*0.001;
              PointF(xj,yj,radlon,radlat,  114,34.0,500,500,1);

n3.nBlockId=(short)ChangeWord((unsigned short)(n3.nBlockId)) ;

if(n3.nBlockId==1)
{

                       fread(&n4,sizeof(n4),1,fp);
                       n4.NumberOfLayers=(short)ChangeWord((unsigned short)(n4.NumberOfLayers));
                       fread(&n5,sizeof(n5),1,fp);
                         fread(&n6,sizeof(n6),1,fp);
                       fread(&mm,sizeof(mm),1,fp);
                       mm.nJStart= (short)ChangeWord((unsigned short)( mm.nJStart)) ;;
             mm.nRowNum=ChangeWord((unsigned short)(mm.nRowNum)) ;
              mm.nXScale=ChangeWord((unsigned short)(mm.nXScale)) ;
              mm.nYScale=ChangeWord((unsigned short)(mm.nYScale)) ;

              pyl=mm.nRowNum*mm.nYScale/2;
             for(int i=0;i<mm.nRowNum;i++)
             {
               fread(&Number1,sizeof( Number1),1,fp);
                Number1=ChangeWord((unsigned short)(Number1)) ;
                for(int j=0;j<Number1;j++)
                {
                 fread(&hb,sizeof(char),1,fp);
               high=(hb>>4)&0xf;
               low=hb&15;
              for(int x=x0;x<x0+high*mm.nXScale;x=x+1)
               { for(int y=y0;y<y0+mm.nYScale;y=y+1)
               {if(x<460&&y<460)
               bt[x][y]=low;


               }


               }
               x0=x0+high*mm.nXScale;

                }
                y0=y0+mm.nYScale;
                x0=0;

            }



}
 fclose(fp);
 for(int i=-230;i<230;i++)
 {
 for(int j=-230;j<230;j++)
{ if (bt[i+230][j+230]>etdata[int(j+yj)][int(i+xj)])
 etdata[int(j+yj)][int(i+xj)]=bt[i+230][j+230];




  }
  }


}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button23Click(TObject *Sender)
{

TSearchRec sr;
    int countMin;
TDateTime time;
      String path=lljj+"*ET_40*",sj;
      if (FindFirst(path,faAnyFile,sr)==0)
   {
  do
  { sd1=sr.Name;
   sj=sd1.SubString(16,4)+"-"+sd1.SubString(20,2)+"-"+sd1.SubString(22,2)+" "+sd1.SubString(24,2)+":"+sd1.SubString(26,2)+":"+sd1.SubString(28,2);
    time=StrToDateTime(sj);
   countMin=MinutesBetween(time,time2);
   //ShowMessage(sj);
   if(time<=time2&&countMin<6)
   {

        Button22->Click();
   }
  }

   while(FindNext(sr)==0);
     FindClose(sr);
   }
Button24->Click();
 Button25->Click();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button24Click(TObject *Sender)
{
int x[16]={255,0,118,0,0,0,50,0,0,0,254,254,174,254,254,230},
y[16]={255,0,118,224,176,144,0,250,186,238,190,254,0,0,254,0},
z[16]={255,0,118,254,254,204,150,144,0,0,0,0,0,0,254,254};

////

 for(int i=0;i<16;i++)
 {

         zfpal[i].rB=z[i];
        zfpal[i].rG=y[i];
        zfpal[i].rR=x[i];
        zfpal[i].rX=0;
    }

  FILE *fp;
    char xs[80];




                    /* for(int k=0;k<0;k++)
     {
     for(int i=0;i<GMS_H;i++)
     {for(int j=0;j<GMS_W;j++)
     {// if(data[i][j]>=15)
    //ShowMessage(data[i][j]);
      if(data[i][j]>=2)
      data[i][j]=int((data[i][j]+data[i][j+1]+data[i][j-1]+data[i+1][j]+data[i-1][j]+data[i+1][j+1]+data[i-1][j-1]+data[i+1][j-1]+data[i-1][j+1])/9.);

     //if(data[i][j]>=8)
   // data[i][j]=(data[i][j+1]+data[i][j-1]+data[i+1][j]+data[i-1][j])/4;

     }
     }
     } */




}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button25Click(TObject *Sender)
{
 BMP_fileh BMPh1;
    BMP_infoh BMPh2;
  BMPh1.bfType=19778;
    BMPh1.bfSize=(long)(14+40+256*4+GMS_W*GMS_H);
    BMPh1.bf1=0;
    BMPh1.bf2=0;
    BMPh1.bfOffbits=(long)(40+256*4);

    BMPh2.biSize=40L;
    BMPh2.biWidth=(long)GMS_W;
    BMPh2.biHeight=(long)GMS_H;
    BMPh2.biPlanes=1;//1
    BMPh2.biBitcount=8;// 1(2) 4(16) 8(256) 24(true color)
    BMPh2.biComp=0L;//0 1 2
    BMPh2.biSizeimage=((long)GMS_W*(long)GMS_H);
    BMPh2.biX=(long)GMS_W;
    BMPh2.biY=(long)GMS_H;
    BMPh2.biClrused=0L;
    BMPh2.biClrimp=0L;
    FILE *fp,*fp1;
     if (ss5.SubString(1,1)!="1")
    {
    ss5=ltp+"et\\"+ss5+".bmp";
    fp=fopen(ss5.c_str() ,"wb");
     //1文件头            long
    fwrite(&BMPh1.bfType,2,1,fp);
    fwrite(&BMPh1.bfSize,4,1,fp);
    fwrite(&BMPh1.bf1,2,1,fp);
    fwrite(&BMPh1.bf2,2,1,fp);
    fwrite(&BMPh1.bfOffbits,4,1,fp);

    //2位图信息头
    fwrite(&BMPh2.biSize,4,1,fp);
    fwrite(&BMPh2.biWidth,4,1,fp);
    fwrite(&BMPh2.biHeight,4,1,fp);
    fwrite(&BMPh2.biPlanes,2,1,fp);
    fwrite(&BMPh2.biBitcount,2,1,fp);
    fwrite(&BMPh2.biComp,4,1,fp);
    fwrite(&BMPh2.biSizeimage,4,1,fp);
    fwrite(&BMPh2.biX,4,1,fp);
    fwrite(&BMPh2.biY,4,1,fp);
    fwrite(&BMPh2.biClrused,4,1,fp);
    fwrite(&BMPh2.biClrimp,4,1,fp);

    //3颜色信息
       for(int i=0;i<256;i++){
        fwrite(&zfpal[i],sizeof(BMP_rgb),1,fp);
    }
    int xx=0;//偏移量
    for(int i=GMS_H;i>0;i--){
        for(int j=xx;j<GMS_W;j++){
           if(i<6)
           etdata[i][j]=0;
            if(etdata[i][j]<3)
            etdata[i][j]=0;
            fwrite(&etdata[i][j],1,1,fp);
        }
        for(int j=0;j<xx;j++){
           // if(data[i][j]<6)
            //data[i][j]=0;
          fwrite(&etdata[i][j],1,1,fp);
        }
    }
    fclose(fp);

bzf=0;
Image1->Picture->LoadFromFile(ss5.c_str());
AnsiString flsd,f;;
flsd="c:\\冰雹.txt";
f="c:\\雷电.txt";
fp=fopen(flsd.c_str(),"w");
fp1=fopen(f.c_str(),"w");
 ///
 if (MinutesBetween(tq,tet)<12)
 { fprintf(fp,"%s\n",sxr);
 fprintf(fp1,"%s\n",sxr);
float lon4,lat4,det,dq;
for(int i=(GMS_H-10);i>0;i=i-10){
        for(int j=0;j<(GMS_W-10);j=j+10){
        for(int ii=i+10;ii>i;ii--)
        {for(int jj=j;jj<j+10;jj++)
        {dq=dq+qdata[ii][jj];
        det=det+etdata[ii][jj];

        }
        }
       dq=dq/100.0;
       det=det/100.0;


        if (det>6&&dq>10)
        { ActToPro(lon4,lat4,j+5,i-5, 114,34.0,500, 500, 1);

         fprintf(fp,"%f %f 1\n",lon4,lat4);

        }
        if (det>6&&dq>6)
        { ActToPro(lon4,lat4,j+5,i-5, 114,34.0,500, 500, 1);

         fprintf(fp1,"%f %f 1\n",lon4,lat4);

        }

       dq=0;
       det=0;
        }
        }
        }
        else
        {
      fprintf(fp,"缺少足够多的同步计算数据\n");
      fprintf(fp1,"缺少足够多的同步计算数据\n");
      }
      fclose(fp);
      fclose(fp1);
 ///

  Image1->Picture->SaveToFile(ss5.c_str());
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button26Click(TObject *Sender)
{for(int i=GMS_H;i<0;i--){
        for(int j=0;j<(GMS_W+1);j++){

           vildata[i][j]=0;
           }
        }

TSearchRec sr;
TDateTime time,t;
      String path=lljj+"*VIL_40*",sj;
      if (FindFirst(path,faAnyFile,sr)==0)
   {
  do
  { sd=sr.Name;
   sj=sd.SubString(16,4)+"-"+sd.SubString(20,2)+"-"+sd.SubString(22,2)+" "+sd.SubString(24,2)+":"+sd.SubString(26,2)+":"+sd.SubString(28,2);
    time=StrToDateTime(sj);
    if(time>time3)
    {time3=time;
                 }
  }


   while(FindNext(sr)==0);
     FindClose(sr);
   }
    t=time3+8/24.;
    tvil=t;
    tt=t;
    String nian,yue,ri,shi,fen;
   Word Year,Month,Day,Hour,Me,Mee,Meee;
   DecodeDate(t,Year,Month,Day);
   DecodeTime(t,Hour,Me,Mee,Meee);
   nian=IntToStr(Year);
if(Month<10)
yue="0"+IntToStr(Month);
else
yue=IntToStr(Month);
if(Day<10)
ri="0"+IntToStr(Day);
else
ri=IntToStr(Day);
if(Hour<10)
shi="0"+IntToStr(Hour);
else
shi=IntToStr(Hour);
if(Me<10)
fen="0"+IntToStr(Me);
else
fen=IntToStr(Me);
ss6=nian+yue+ri+shi+fen;
Button27->Click() ;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button27Click(TObject *Sender)
{
/*for(int i=GMS_H;i>0;i--)
{
        for(int j=0;j<GMS_W;j++)
        {
                    data[i][j]=0;
           }
           }*/
TSearchRec sr;
    int countMin;
TDateTime time;
      String path=lljj+"*VIL_40*",sj;
      if (FindFirst(path,faAnyFile,sr)==0)
   {
  do
  { sd2=sr.Name;
   sj=sd2.SubString(16,4)+"-"+sd2.SubString(20,2)+"-"+sd2.SubString(22,2)+" "+sd2.SubString(24,2)+":"+sd2.SubString(26,2)+":"+sd2.SubString(28,2);
    time=StrToDateTime(sj);
   countMin=MinutesBetween(time,time3);
  if(time<=time3&&countMin<6)
   {

        Button28->Click();
   }
  }

   while(FindNext(sr)==0);
     FindClose(sr);
   }
Button29->Click();
 Button30->Click();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button28Click(TObject *Sender)
{

FILE *fp;
String f;
    float x8,y8;
char hb;
double ele, az,L,dh;
int nian,yue,ri,xiaoshi,fenzhong,miao,pyl,bt[460][460];
 long tt;
float x0=1,y0=1;
for(int i=0;i<460;i++)
{
        for(int j=0;j<460;j++)
        {
          bt[i][j]=0;

           }
           }
 unsigned short Number1;
////
int low,high,jxs,sjs,h=0,zz,db,yjh;
float yjs,lon,lat;
HEADER  hed;
        DESCRIPTION  nn;
        SYMBOLOGY n3;
         onetow n4;
        ifon1 n5;
        tagLVPacket n6;
        cr  mm;
AnsiString ff;
ff=lljj+sd2;

fp = fopen(ff.c_str(),"rb");
fread(&hed,sizeof(hed),1,fp);
fread(&nn,sizeof(nn),1,fp);
                 fread(&n3,sizeof(n3),1,fp);
                 radlat=(int)ChangeDWord((unsigned int)(nn.RadarLatitude))*0.001;
           radlon=(int)ChangeDWord((unsigned int)(nn.RadarLongtitude))*0.001;
              PointF(xj,yj,radlon,radlat,  114,34.0,500,500,1);

n3.nBlockId=(short)ChangeWord((unsigned short)(n3.nBlockId)) ;

if(n3.nBlockId==1)
{

                       fread(&n4,sizeof(n4),1,fp);
                       n4.NumberOfLayers=(short)ChangeWord((unsigned short)(n4.NumberOfLayers));
                       fread(&n5,sizeof(n5),1,fp);
                         fread(&n6,sizeof(n6),1,fp);
                       fread(&mm,sizeof(mm),1,fp);
                       mm.nJStart= (short)ChangeWord((unsigned short)( mm.nJStart)) ;;
             mm.nRowNum=ChangeWord((unsigned short)(mm.nRowNum)) ;
              mm.nXScale=ChangeWord((unsigned short)(mm.nXScale)) ;
              mm.nYScale=ChangeWord((unsigned short)(mm.nYScale)) ;

              pyl=mm.nRowNum*mm.nYScale/2;
             for(int i=0;i<mm.nRowNum;i++)
             {
               fread(&Number1,sizeof( Number1),1,fp);
                Number1=ChangeWord((unsigned short)(Number1)) ;
                for(int j=0;j<Number1;j++)
                {
                 fread(&hb,sizeof(char),1,fp);
               high=(hb>>4)&0xf;
               low=hb&15;
              for(int x=x0;x<x0+high*mm.nXScale;x=x+1)
               { for(int y=y0;y<y0+mm.nYScale;y=y+1)
               {if(x<460&&y<460)
               bt[x][y]=low;


               }


               }
               x0=x0+high*mm.nXScale;

                }
                y0=y0+mm.nYScale;
                x0=0;

            }



}
 fclose(fp);
 for(int i=-230;i<230;i++)
 {
 for(int j=-230;j<230;j++)
{ if (bt[i+230][j+230]>vildata[int(j+yj)][int(i+xj)])
 vildata[int(j+yj)][int(i+xj)]=bt[i+230][j+230];



  }
  }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button29Click(TObject *Sender)
{
int x[16]={255,156,118,250,238,200,0,0,254,208,254,218,174,0,254,230},
y[16]={255,156,118,170,140,112,250,186,254,208,96,0,0,0,254,0},
z[16]={255,156,118,170,140,112,144,0,112,96,96,0,0,254,254,254};

////

 for(int i=0;i<16;i++)
 {

         zfpal[i].rB=z[i];
        zfpal[i].rG=y[i];
        zfpal[i].rR=x[i];
        zfpal[i].rX=0;
    }

  FILE *fp;
    char xs[80];


/* for(int k=0;k<0;k++)
     {
     for(int i=0;i<GMS_H;i++)
     {for(int j=0;j<GMS_W;j++)
     {// if(data[i][j]>=15)
    //ShowMessage(data[i][j]);
      //if(data[i][j]>=3)
      data[i][j]=int((data[i][j]+data[i][j+1]+data[i][j-1]+data[i+1][j]+data[i-1][j]+data[i+1][j+1]+data[i-1][j-1]+data[i+1][j-1]+data[i-1][j+1])/9.);

     //if(data[i][j]>=8)
   // data[i][j]=(data[i][j+1]+data[i][j-1]+data[i+1][j]+data[i-1][j])/4;

     }
     }
     } */


}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button30Click(TObject *Sender)
{
BMP_fileh BMPh1;
    BMP_infoh BMPh2;
  BMPh1.bfType=19778;
    BMPh1.bfSize=(long)(14+40+256*4+GMS_W*GMS_H);
    BMPh1.bf1=0;
    BMPh1.bf2=0;
    BMPh1.bfOffbits=(long)(40+256*4);

    BMPh2.biSize=40L;
    BMPh2.biWidth=(long)GMS_W;
    BMPh2.biHeight=(long)GMS_H;
    BMPh2.biPlanes=1;//1
    BMPh2.biBitcount=8;// 1(2) 4(16) 8(256) 24(true color)
    BMPh2.biComp=0L;//0 1 2
    BMPh2.biSizeimage=((long)GMS_W*(long)GMS_H);
    BMPh2.biX=(long)GMS_W;
    BMPh2.biY=(long)GMS_H;
    BMPh2.biClrused=0L;
    BMPh2.biClrimp=0L;
    FILE *fp;
     if (ss6.SubString(1,1)!="1")
    {
    ss6=ltp+"\\vil\\"+ss6+".bmp";
    fp=fopen(ss6.c_str() ,"wb");
     //1文件头            long
    fwrite(&BMPh1.bfType,2,1,fp);
    fwrite(&BMPh1.bfSize,4,1,fp);
    fwrite(&BMPh1.bf1,2,1,fp);
    fwrite(&BMPh1.bf2,2,1,fp);
    fwrite(&BMPh1.bfOffbits,4,1,fp);

    //2位图信息头
    fwrite(&BMPh2.biSize,4,1,fp);
    fwrite(&BMPh2.biWidth,4,1,fp);
    fwrite(&BMPh2.biHeight,4,1,fp);
    fwrite(&BMPh2.biPlanes,2,1,fp);
    fwrite(&BMPh2.biBitcount,2,1,fp);
    fwrite(&BMPh2.biComp,4,1,fp);
    fwrite(&BMPh2.biSizeimage,4,1,fp);
    fwrite(&BMPh2.biX,4,1,fp);
    fwrite(&BMPh2.biY,4,1,fp);
    fwrite(&BMPh2.biClrused,4,1,fp);
    fwrite(&BMPh2.biClrimp,4,1,fp);

    //3颜色信息
       for(int i=0;i<256;i++){
        fwrite(&zfpal[i],sizeof(BMP_rgb),1,fp);
    }
    int xx=0;//偏移量
    for(int i=GMS_H;i>0;i--){
        for(int j=xx;j<GMS_W;j++){
           if(i<6)
           vildata[i][j]=0;
          // if (vildata[i][j]>15)
          // vildata[i][j]=0;
            if(vildata[i][j]<0)
            vildata[i][j]=0;
            fwrite(&vildata[i][j],1,1,fp);
        }
        for(int j=0;j<xx;j++){
           // if(data[i][j]<6)
            //data[i][j]=0;
          fwrite(&vildata[i][j],1,1,fp);
        }
    }
    fclose(fp);

bzf=0;
Image1->Picture->LoadFromFile(ss6.c_str());
AnsiString flsd;
flsd="c:\\短历时强降水.txt";

fp=fopen(flsd.c_str(),"w");
if (MinutesBetween(tq,tvil)<12)
{ fprintf(fp,"%s\n",sxr);
 ///
float lon4,lat4,qd,vild;
for(int i=(GMS_H-10);i>0;i=i-10){
        for(int j=0;j<(GMS_W-10);j=j+10){
        for(int ii=i+10;ii>i;ii--)
        {for(int jj=j;jj<j+10;jj++)
        {vild=vild+vildata[ii][jj];
         qd=qd+qdata[ii][jj];
        }
        }
       vild=vild/100.0;
       qd=qd/100.0;


        if (vild>8&&qd>9)
        { ActToPro(lon4,lat4,j+5,i-5, 114,34.0,500, 500, 1);

         fprintf(fp,"%f %f 1\n",lon4,lat4);
          //ShowMessage(FloatToStr(lon4));
          //ShowMessage(FloatToStr(lat4));
                 // Image1->Transparent=true;
         //Image1->Canvas->Font->Size=20;
        //Image1->Canvas->TextOutA(i,j,"+");
        }
        //>Draw(50,50,"+");
       qd=0;
       vild=0;
        }
        }
        }
        else
        fprintf(fp,"缺少足够多的同步计算数据\n");
      fclose(fp);
 ///

  Image1->Picture->SaveToFile(ss6.c_str());
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button31Click(TObject *Sender)
{
for(int i=0;i<GMS_H;i++){
        for(int j=0;j<GMS_W;j++){
           data[i][j]=0;
           }
        }
TSearchRec sr;
TDateTime time,t;
      String path=lljj+"*.78.*",sj;
      if (FindFirst(path,faAnyFile,sr)==0)
   {
  do
  { sd=sr.Name;
   sj=sd.SubString(1,4)+"-"+sd.SubString(5,2)+"-"+sd.SubString(7,2)+" "+sd.SubString(10,2)+":"+sd.SubString(12,2)+":"+sd.SubString(14,2);
    time=StrToDateTime(sj);
    if(time>time4)
    {time4=time;
                 }
  }


   while(FindNext(sr)==0);
     FindClose(sr);
   }
    t=time1+8/24.;
    tt=t;
    String nian,yue,ri,shi,fen;
   Word Year,Month,Day,Hour,Me,Mee,Meee;
   DecodeDate(t,Year,Month,Day);
   DecodeTime(t,Hour,Me,Mee,Meee);
   nian=IntToStr(Year);
if(Month<10)
yue="0"+IntToStr(Month);
else
yue=IntToStr(Month);
if(Day<10)
ri="0"+IntToStr(Day);
else
ri=IntToStr(Day);
if(Hour<10)
shi="0"+IntToStr(Hour);
else
shi=IntToStr(Hour);
if(Me<10)
fen="0"+IntToStr(Me);
else
fen=IntToStr(Me);
ss7=nian+yue+ri+shi+fen;

Button32->Click() ;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button32Click(TObject *Sender)
{

for(int i=GMS_H;i>0;i--)
{
        for(int j=0;j<GMS_W;j++)
        {
                    data[i][j]=0;
           }
           }
TSearchRec sr;
    int countMin;
TDateTime time;
      String path=lljj+"*.78.*",sj;
      if (FindFirst(path,faAnyFile,sr)==0)
   {
  do
  { sd3=sr.Name;
   sj=sd3.SubString(1,4)+"-"+sd3.SubString(5,2)+"-"+sd3.SubString(7,2)+" "+sd3.SubString(10,2)+":"+sd3.SubString(12,2)+":"+sd3.SubString(14,2);
    time=StrToDateTime(sj);
   countMin=MinutesBetween(time,time4);
  if(time<=time4&&countMin<6)
   {

        Button33->Click();
   }
  }

   while(FindNext(sr)==0);
     FindClose(sr);
   }
Button34->Click();
 Button35->Click();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button33Click(TObject *Sender)
{

FILE *fp;


int nian,yue,ri,xiaoshi,fenzhong,miao;
 long tt;

////
int low,high,jxs,sjs,h=0,zz,a[360][230],db,yjh;
for(int i=0;i<360;i++)
{
        for(int j=0;j<230;j++)
        {
          a[i][j]=0;

           }
           }

char hb;
HEADER  hed;
        DESCRIPTION  nn;
         SYMBOLOGY n3;
        onetow n4;
               ifon1 n5;
        tagLVPacket n6;
AnsiString ff;
ff=lljj+sd3;

fp = fopen(ff.c_str(),"rb");
fread(&hed,sizeof(hed),1,fp);
fread(&nn,sizeof(nn),1,fp);
 radlat=(int)ChangeDWord((unsigned int)(nn.RadarLatitude))*0.001;
           radlon=(int)ChangeDWord((unsigned int)(nn.RadarLongtitude))*0.001;
           radh = (short)ChangeWord((unsigned short)(nn.RadarHeight))*0.3048;
           PointF(xj,yj,radlon,radlat,  114,34.0,500,500,1);

           yjh = ChangeWord((unsigned short)(nn.ElevationNumber));
           if(yjh==1)
           ele=0.5;
           if(yjh==2)
           ele=1.5;
           if(yjh==3)
           ele=2.4;
          CRadEPrj *p = new CRadEPrj(radlon,radlat,radh);
p->Initialized(40.0, 0, 0, 1000);

              fread(&n3,sizeof(n3),1,fp);
n3.nBlockId=(short)ChangeWord((unsigned short)(n3.nBlockId)) ;

//long nTimeofMessage=nn.TimeofMessage2[0]<<24|nn.TimeofMessage2[1]<<16|
                                nn.TimeofMessage2[2]<<8|nn.TimeofMessage2[3];

//GetRadialTime(nTimeofMessage*1000,xiaoshi,fenzhong,miao);
////////
if(n3.nBlockId==1)
{ fread(&n4,sizeof(n4),1,fp);
n4.NumberOfLayers=(short)ChangeWord((unsigned short)(n4.NumberOfLayers));

 fread(&n5,sizeof(n5),1,fp);
 fread(&n6,sizeof(n6),1,fp);
n5. LayerDivider=(short)ChangeWord((unsigned short)(n5. LayerDivider)) ;


               jingxiangtow  mm;
                       fread(&mm,sizeof(mm),1,fp);

            jxs = (short)ChangeWord((unsigned short)(mm.NumberofRadials));


                          jingxiang  jx;
             for(int i=0;i<jxs;i++)
             {fread(&jx,sizeof(jx),1,fp);
              sjs = ChangeWord((unsigned short)(jx.Number))*2;
              yjs=ChangeWord((unsigned short)(jx.RadialStartAngle))*0.1;

              if(int(yjs)>=360)
              zz=int(yjs)-360;
              else
              zz=int(yjs);
             for(int j=0;j<sjs;j++)
              {fread(&hb,sizeof(char),1,fp);
               high=(hb>>4)&0xf;
               low=hb&15;

                             for(int ii=0;ii<high;ii++)
               {
               a[zz][ii+h]=low+1;


               }
               h=h+high;
              }
              h=0;
             }
             fclose(fp);


           for(int i=-230;i<230;i++)
             {
for(int j=-230;j<230;j++)
{  if(j!=0||i!=0)
{
  p->tilt_of_gps(0.5,  i, j,  lon, lat,dh,ds) ;
  p->gps_to_tilt(lon,lat,0.5, az,L,dh);

  if(L<230&&az<360)
{  //if(a[int(az)][int(L)]>5)
           //   { ShowMessage(a[int(az)][int(L)]);
             //  ShowMessage(az);
             //   ShowMessage(L);
              //  }
 if(a[int(az)][int(L)]>data[int(j+yj)][int(i+xj)]&&(data1[int(j+yj)][int(i+xj)]>190||xyl[int(j+yj)][int(i+xj)]>0.5||bzf==2))
 {
 data[int(j+yj+0.5)][int(i+xj+0.5)]=a[int(az)][int(L)];
// ShowMessage(data1[int(j+yj)][int(i+xj)]);
 }
 else
  data[int(j+yj)][int(i+xj)]=0;



}
  }
}
}

delete p;
}

        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button34Click(TObject *Sender)
{
int x[17]={255,0,0,192,122,30,166,0,16,252,200,140,254,254,238,212,170},y[17]={255,0,172,192,114,38,252,234,146,244,200,140,172,100,2,142,36},z[17]={255,0,164,254,238,208,168,0,26,100,2,0,172,92,48,254,250};

////

 for(int i=0;i<17;i++)
 {

         zfpal[i].rB=z[i];
        zfpal[i].rG=y[i];
        zfpal[i].rR=x[i];
        zfpal[i].rX=0;
    }

  FILE *fp;
    char xs[80];


  for(int k=0;k<1;k++)
     {
     for(int i=0;i<GMS_H;i++)
     {for(int j=0;j<GMS_W;j++)
     {// if(data[i][j]>=15)
    //ShowMessage(data[i][j]);
      if(data[i][j]>=6)
      data[i][j]=int((data[i][j]+data[i][j+1]+data[i][j-1]+data[i+1][j]+data[i-1][j]+data[i+1][j+1]+data[i-1][j-1]+data[i+1][j-1]+data[i-1][j+1])/9.);
    
     //if(data[i][j]>=8)
   // data[i][j]=(data[i][j+1]+data[i][j-1]+data[i+1][j]+data[i-1][j])/4;

     }
     }
     }

          
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button35Click(TObject *Sender)
{
 BMP_fileh BMPh1;
    BMP_infoh BMPh2;
  BMPh1.bfType=19778;
    BMPh1.bfSize=(long)(14+40+256*4+GMS_W*GMS_H);
    BMPh1.bf1=0;
    BMPh1.bf2=0;
    BMPh1.bfOffbits=(long)(40+256*4);

    BMPh2.biSize=40L;
    BMPh2.biWidth=(long)GMS_W;
    BMPh2.biHeight=(long)GMS_H;
    BMPh2.biPlanes=1;//1
    BMPh2.biBitcount=8;// 1(2) 4(16) 8(256) 24(true color)
    BMPh2.biComp=0L;//0 1 2
    BMPh2.biSizeimage=((long)GMS_W*(long)GMS_H);
    BMPh2.biX=(long)GMS_W;
    BMPh2.biY=(long)GMS_H;
    BMPh2.biClrused=0L;
    BMPh2.biClrimp=0L;
    FILE *fp;
    ss3=ltp+"\\OHP\\"+ss7+".bmp";
    fp=fopen(ss3.c_str() ,"wb");
     //1文件头            long
    fwrite(&BMPh1.bfType,2,1,fp);
    fwrite(&BMPh1.bfSize,4,1,fp);
    fwrite(&BMPh1.bf1,2,1,fp);
    fwrite(&BMPh1.bf2,2,1,fp);
    fwrite(&BMPh1.bfOffbits,4,1,fp);

    //2位图信息头
    fwrite(&BMPh2.biSize,4,1,fp);
    fwrite(&BMPh2.biWidth,4,1,fp);
    fwrite(&BMPh2.biHeight,4,1,fp);
    fwrite(&BMPh2.biPlanes,2,1,fp);
    fwrite(&BMPh2.biBitcount,2,1,fp);
    fwrite(&BMPh2.biComp,4,1,fp);
    fwrite(&BMPh2.biSizeimage,4,1,fp);
    fwrite(&BMPh2.biX,4,1,fp);
    fwrite(&BMPh2.biY,4,1,fp);
    fwrite(&BMPh2.biClrused,4,1,fp);
    fwrite(&BMPh2.biClrimp,4,1,fp);

    //3颜色信息
       for(int i=0;i<256;i++){
        fwrite(&zfpal[i],sizeof(BMP_rgb),1,fp);
    }
    int xx=0;//偏移量
    for(int i=GMS_H;i>0;i--){
        for(int j=xx;j<GMS_W;j++){
           if(i<6)
           data[i][j]=0;
            if(data[i][j]<6)
            data[i][j]=0;
            fwrite(&data[i][j],1,1,fp);
        }
        for(int j=0;j<xx;j++){
           // if(data[i][j]<6)
            //data[i][j]=0;
            fwrite(&data[i][j],1,1,fp);
        }
    }
    fclose(fp);

bzf=0;
Image1->Picture->LoadFromFile(ss3.c_str());
  Image1->Picture->SaveToFile(ss3.c_str());

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button36Click(TObject *Sender)
{
TSearchRec sr;
TDateTime time,t;
      String sd1,path=lljj+"*_M_*."+rdz+".*",sj;

      if (FindFirst(path,faAnyFile,sr)==0)
   {
  do
  { sd1=sr.Name;
   sj=sd1.SubString(16,4)+"-"+sd1.SubString(20,2)+"-"+sd1.SubString(22,2)+" "+sd1.SubString(24,2)+":"+sd1.SubString(26,2)+":"+sd1.SubString(28,2);
    time=StrToDateTime(sj);
    if(time>time5)
    {time5=time;
                     }
  }


   while(FindNext(sr)==0);
     FindClose(sr);
   }
    t=time5+8/24.;
    t60=t;
      String nian,yue,ri,shi,fen;
   Word Year,Month,Day,Hour,Me,Mee,Meee;
   DecodeDate(t,Year,Month,Day);
   DecodeTime(t,Hour,Me,Mee,Meee);
   nian=IntToStr(Year);
if(Month<10)
yue="0"+IntToStr(Month);
else
yue=IntToStr(Month);
if(Day<10)
ri="0"+IntToStr(Day);
else
ri=IntToStr(Day);
if(Hour<10)
shi="0"+IntToStr(Hour);
else
shi=IntToStr(Hour);
if(Me<10)
fen="0"+IntToStr(Me);
else
fen=IntToStr(Me);
ss8=nian+"年"+yue+"月"+ri+"日"+shi+"时"+fen+"分";

if(sd!="")
Button71->Click() ;


}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button37Click(TObject *Sender)
{
  TSearchRec sr;
TDateTime time,t;
   int countMin,ljx,ljy;
FILE *fp;
    float qcc;
double lon,lat;
mye  n7;
zbf n8;
fxf n9;
String pd,f98;
 short int biao;
////
char hb,dfs[2];
int rb=0,pd1=-1;
double ele, az,L,dh;
int nian,yue,ri,xiaoshi,fenzhong,miao;
 long tt;
float x0=0,y0=0;
 unsigned short Number1,mb;
////
int low,high,jxs,sjs,h=0,zz,a[360][230],db,yjh;
float yjs,det,dq;
HEADER  hed;
        DESCRIPTION  nn;
        SYMBOLOGY n3;
         onetow n4;
        ifon1 n5;
        cr  mm;
        tagLVPacket n6;
AnsiString ff,flj;
int dsi;

ff=lljj+sd1;
fp = fopen(ff.c_str(),"rb");
fread(&hed,sizeof(hed),1,fp);
fread(&nn,sizeof(nn),1,fp);
radlat=(int)ChangeDWord((unsigned int)(nn.RadarLatitude))*0.001;
           radlon=(int)ChangeDWord((unsigned int)(nn.RadarLongtitude))*0.001;
            radh = (short)ChangeWord((unsigned short)(nn.RadarHeight))*0.3048;
           //ShowMessage(radlat);
            CRadEPrj *p = new CRadEPrj(radlon,radlat,radh);
p->Initialized(40.0, 0, 0, 1000);
      fread(&n3,sizeof(n3),1,fp);

String f90;
f90=IntToStr(nian)+"-"+IntToStr(yue)+"-"+IntToStr(ri)+" "+IntToStr(xiaoshi)+":"+IntToStr(fenzhong);
      n3.nBlockId=(short)ChangeWord((unsigned short)(n3.nBlockId)) ;

      if(n3.nBlockId==1)
                   {                                 fread(&n4,sizeof(n4),1,fp);
                  n4.NumberOfLayers=(short)ChangeWord((unsigned short)(n4.NumberOfLayers)) ;



                      for(int i=0;i<n4.NumberOfLayers;i++)
                  {   fread(&n5,sizeof(n5),1,fp);

                long chd=n5.cch[0]<<24|n5.cch[1]<<16|
                                n5.cch[2]<<8|n5.cch[3];
                           long gg=chd;

                             do
                              {
               fread(&n6,sizeof(n6),1,fp);
             n6.PacketCode = (short)ChangeWord((unsigned short)(n6. PacketCode));

                        n6.LengthOfDataBlock = (short)ChangeWord((unsigned short)(n6.LengthOfDataBlock));
                      if(n6.PacketCode==3||n6.PacketCode==11)
                      {dsi=n6.LengthOfDataBlock/6;
                      for(int i=0;i<dsi;i++)
                      {
                       fread(&n9,sizeof(n9),1,fp);
            x0=(short)ChangeWord((unsigned short)(n9.ICenterofSweep))/4.;
            y0   = (short)ChangeWord((unsigned short)(n9.JCenterofSweep))/4.;

               p->tilt_of_gps(0,  int(x0),-int(y0),  lon, lat,dh,ds) ;
              qcc    = (short)ChangeWord((unsigned short)( n9.bj))/4.;


             fprintf(fp60,"%f %f %f\n",lon,lat,qcc);
               PointF(ljx,ljy,lon,lat, 114,34,500,500,1);


 ///
 if ((MinutesBetween(tq,t60)<12)&&(MinutesBetween(tet,t60)<12))
 {
  for(int i=(ljx-5);i<=(ljx+5);i++){
        for(int j=(ljy-5);j<=(ljy+5);j++){
        dq=dq+qdata[i][j];
        det=det+etdata[i][j];

        }
        }
       dq=dq/100.0;
       det=det/100.0;


        if (det>6&&dq>10)
        {

         fprintf(fplj,"%f %f 1\n",lon,lat);

        }


       dq=0;
       det=0;
        }


      }
      }
 ///
                   else
                      {
                         for(int i=0;i< n6.LengthOfDataBlock;i++)
             { fread(&hb,sizeof(char),1,fp);

             }
             }
             gg=gg-n6.LengthOfDataBlock-4;
         }
         while(gg>0);

         }



           }
         delete p;

             fclose(fp);





}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button38Click(TObject *Sender)
{
TSearchRec sr;
TDateTime time,t;
      String path=lljj+"*_HI_*",sj,sd;
      if (FindFirst(path,faAnyFile,sr)==0)
   {
  do
  { sd=sr.Name;
   sj=sd.SubString(16,4)+"-"+sd.SubString(20,2)+"-"+sd.SubString(22,2)+" "+sd.SubString(24,2)+":"+sd.SubString(26,2)+":"+sd.SubString(28,2);
    time=StrToDateTime(sj);
    if(time>time6)
    {time6=time;
                 }
  }


   while(FindNext(sr)==0);
     FindClose(sr);
   }
    t=time6+8/24.;
      String nian,yue,ri,shi,fen;
   Word Year,Month,Day,Hour,Me,Mee,Meee;
   DecodeDate(t,Year,Month,Day);
   DecodeTime(t,Hour,Me,Mee,Meee);
   nian=IntToStr(Year);
if(Month<10)
yue="0"+IntToStr(Month);
else
yue=IntToStr(Month);
if(Day<10)
ri="0"+IntToStr(Day);
else
ri=IntToStr(Day);
if(Hour<10)
shi="0"+IntToStr(Hour);
else
shi=IntToStr(Hour);
if(Me<10)
fen="0"+IntToStr(Me);
else
fen=IntToStr(Me);
ss9=nian+"年"+yue+"月"+ri+"日"+shi+"时"+fen+"分";
if(sd!="")
Button39->Click() ;
sd="";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button39Click(TObject *Sender)
{
TSearchRec sr;
TDateTime time,t;
   int countMin;
FILE *fp,*fp1;
    float qcc;
double lon,lat;
mye  n7;
zbf n8;
bb2 n9;
String pd,f98;
 short int biao;
////
char hb,dfs[2];
int rb=0,pd1=-1;
double ele, az,L,dh;
int nian,yue,ri,xiaoshi,fenzhong,miao;
 long tt;
float x0=0,y0=0;
 unsigned short Number1,mb;
////
int low,high,jxs,sjs,h=0,zz,a[360][230],db,yjh;
float yjs;
HEADER  hed;
        DESCRIPTION  nn;
        SYMBOLOGY n3;
         onetow n4;
        ifon1 n5;
        cr  mm;
        tagLVPacket n6;
AnsiString ff;

f98="c:\\59.txt";

fp1=fopen(f98.c_str(),"w");
fprintf(fp1,"%s\n",ss9);
 String path=lljj+"*_HI_*",sj;
      if (FindFirst(path,faAnyFile,sr)==0)
   {
  do
  { sd=sr.Name;
   sj=sd.SubString(16,4)+"-"+sd.SubString(20,2)+"-"+sd.SubString(22,2)+" "+sd.SubString(24,2)+":"+sd.SubString(26,2)+":"+sd.SubString(28,2);
    time=StrToDateTime(sj);
   countMin=MinutesBetween(time,time6);
     if(time<=time6&&countMin<6)
   {
           //
ff=lljj+sd;;

fp = fopen(ff.c_str(),"rb");
fread(&hed,sizeof(hed),1,fp);
fread(&nn,sizeof(nn),1,fp);
radlat=(int)ChangeDWord((unsigned int)(nn.RadarLatitude))*0.001;
           radlon=(int)ChangeDWord((unsigned int)(nn.RadarLongtitude))*0.001;
            radh = (short)ChangeWord((unsigned short)(nn.RadarHeight))*0.3048;
                     CRadEPrj *p = new CRadEPrj(radlon,radlat,radh);
p->Initialized(40.0, 0, 0, 1000);
      fread(&n3,sizeof(n3),1,fp);

String f90;
f90=IntToStr(nian)+"-"+IntToStr(yue)+"-"+IntToStr(ri)+" "+IntToStr(xiaoshi)+":"+IntToStr(fenzhong);
      n3.nBlockId=(short)ChangeWord((unsigned short)(n3.nBlockId)) ;

      if(n3.nBlockId==1)
                   {                                 fread(&n4,sizeof(n4),1,fp);
                  n4.NumberOfLayers=(short)ChangeWord((unsigned short)(n4.NumberOfLayers)) ;



                      for(int i=0;i<n4.NumberOfLayers;i++)
                  { fread(&n5,sizeof(n5),1,fp);
              
                long chd=n5.cch[0]<<24|n5.cch[1]<<16|
                                n5.cch[2]<<8|n5.cch[3];
                           long gg=chd;

                             do
                              {
               fread(&n6,sizeof(n6),1,fp);
             n6.PacketCode = (short)ChangeWord((unsigned short)(n6. PacketCode));

                        n6.LengthOfDataBlock = (short)ChangeWord((unsigned short)(n6.LengthOfDataBlock));
                      if(n6.PacketCode==19)
                      {  fread(&n9,sizeof(n9),1,fp);
            x0=(short)ChangeWord((unsigned short)(n9.ICenterofSweep))/4.;
            y0   = (short)ChangeWord((unsigned short)(n9.JCenterofSweep))/4.;
              n9.kgl=(short)ChangeWord((unsigned short)(n9.kgl));
               p->tilt_of_gps(0,  int(x0),-int(y0),  lon, lat,dh,ds) ;
             if (n9.kgl>50)
             fprintf(fp1,"%f %f %d\n",lon,lat,n9.kgl);

                      }
                      else
                      {
                         for(int i=0;i< n6.LengthOfDataBlock;i++)
             { fread(&hb,sizeof(char),1,fp);

             }
             }
             gg=gg-n6.LengthOfDataBlock-4;
         }
         while(gg>0);

         }

       

           }
         delete p;

             fclose(fp);
   }

   }
     while(FindNext(sr)==0);
     FindClose(sr);
   }
   ////////////
    fclose(fp1);

}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button40Click(TObject *Sender)
{
 for(int i=0;i<=GMS_H;i++){
        for(int j=0;j<=GMS_W;j++){
           vdata[i][j]=0;
           }
        }
TSearchRec sr;
TDateTime time,t;
      String path=lljj+"*V_10_230_5.*",sj;
      if (FindFirst(path,faAnyFile,sr)==0)
   {
  do
  { sd=sr.Name;
   sj=sd.SubString(16,4)+"-"+sd.SubString(20,2)+"-"+sd.SubString(22,2)+" "+sd.SubString(24,2)+":"+sd.SubString(26,2)+":"+sd.SubString(28,2);
    time=StrToDateTime(sj);
    if(time>time7)
    {time7=time;
                 }
  }


   while(FindNext(sr)==0);
     FindClose(sr);
   }
   t=time7+8/24.;
   tv=t;
    tt=t;
    String nian,yue,ri,shi,fen;
   Word Year,Month,Day,Hour,Me,Mee,Meee;
   DecodeDate(t,Year,Month,Day);
   DecodeTime(t,Hour,Me,Mee,Meee);
   nian=IntToStr(Year);
if(Month<10)
yue="0"+IntToStr(Month);
else
yue=IntToStr(Month);
if(Day<10)
ri="0"+IntToStr(Day);
else
ri=IntToStr(Day);
if(Hour<10)
shi="0"+IntToStr(Hour);
else
shi=IntToStr(Hour);
if(Me<10)
fen="0"+IntToStr(Me);
else
fen=IntToStr(Me);
ss3=nian+yue+ri+shi+fen;
ss4=nian+yue+ri+shi;
yth=nian.SubString(3,2) +yue+ri+shi;
String f2=yt+yth+".000";
///
 if(!FileExists(f2))
 {
  t=time1+7/24.;
     DecodeDate(t,Year,Month,Day);
   DecodeTime(t,Hour,Me,Mee,Meee);
   nian=IntToStr(Year);
if(Month<10)
yue="0"+IntToStr(Month);
else
yue=IntToStr(Month);
if(Day<10)
ri="0"+IntToStr(Day);
else
ri=IntToStr(Day);
if(Hour<10)
shi="0"+IntToStr(Hour);
else
shi=IntToStr(Hour);
yth=nian.SubString(3,2) +yue+ri+shi;
}
//
//Button9->Click() ;
//Button12->Click() ;
 Button41->Click() ;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button41Click(TObject *Sender)
{

TSearchRec sr;
    int countMin;
TDateTime time;
      String path=lljj+"*V_10_230_5.*",sj;
      if (FindFirst(path,faAnyFile,sr)==0)
   {
  do
  { sd=sr.Name;
   sj=sd.SubString(16,4)+"-"+sd.SubString(20,2)+"-"+sd.SubString(22,2)+" "+sd.SubString(24,2)+":"+sd.SubString(26,2)+":"+sd.SubString(28,2);
    time=StrToDateTime(sj);
   countMin=MinutesBetween(time,time7);
   if(time<=time7&&countMin<10)
   {

        Button42->Click();
   }
  }

   while(FindNext(sr)==0);
     FindClose(sr);
   }
 Button43->Click();



}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button42Click(TObject *Sender)
{

FILE *fp;


int nian,yue,ri,xiaoshi,fenzhong,miao;
 long tt;

////
int low,high,jxs,sjs,h=0,zz,a[360][230],db,yjh;
for(int i=0;i<360;i++)
{
        for(int j=0;j<230;j++)
        {
          a[i][j]=0;

           }
           }

char hb;
HEADER  hed;
        DESCRIPTION  nn;
         SYMBOLOGY n3;
        onetow n4;
               ifon1 n5;
        tagLVPacket n6;
AnsiString ff;
ff=lljj+sd;

fp = fopen(ff.c_str(),"rb");
fread(&hed,sizeof(hed),1,fp);
fread(&nn,sizeof(nn),1,fp);
 radlat=(int)ChangeDWord((unsigned int)(nn.RadarLatitude))*0.001;
           radlon=(int)ChangeDWord((unsigned int)(nn.RadarLongtitude))*0.001;
           radh = (short)ChangeWord((unsigned short)(nn.RadarHeight))*0.3048;
          // ShowMessage(FloatToStr(radh));
           PointF(xj,yj,radlon,radlat,  114,34.0,500,500,1);

           yjh = ChangeWord((unsigned short)(nn.ElevationNumber));
           if(yjh==1)
           ele=0.5;
           if(yjh==2)
           ele=1.5;
           if(yjh==3)
           ele=2.4;
          CRadEPrj *p = new CRadEPrj(radlon,radlat,radh);
p->Initialized(40.0, 0, 0, 1000);

              fread(&n3,sizeof(n3),1,fp);
n3.nBlockId=(short)ChangeWord((unsigned short)(n3.nBlockId)) ;

//long nTimeofMessage=nn.TimeofMessage2[0]<<24|nn.TimeofMessage2[1]<<16|
                                nn.TimeofMessage2[2]<<8|nn.TimeofMessage2[3];

//GetRadialTime(nTimeofMessage*1000,xiaoshi,fenzhong,miao);
////////
if(n3.nBlockId==1)
{ fread(&n4,sizeof(n4),1,fp);
n4.NumberOfLayers=(short)ChangeWord((unsigned short)(n4.NumberOfLayers));

 fread(&n5,sizeof(n5),1,fp);
 fread(&n6,sizeof(n6),1,fp);
n5. LayerDivider=(short)ChangeWord((unsigned short)(n5. LayerDivider)) ;


               jingxiangtow  mm;
                       fread(&mm,sizeof(mm),1,fp);

            jxs = (short)ChangeWord((unsigned short)(mm.NumberofRadials));


                          jingxiang  jx;
             for(int i=0;i<jxs;i++)
             {fread(&jx,sizeof(jx),1,fp);
              sjs = ChangeWord((unsigned short)(jx.Number))*2;
              yjs=ChangeWord((unsigned short)(jx.RadialStartAngle))*0.1;

              if(int(yjs)>=360)
              zz=int(yjs)-360;
              else
              zz=int(yjs);
             for(int j=0;j<sjs;j++)
              {fread(&hb,sizeof(char),1,fp);
               high=(hb>>4)&0xf;
               low=hb&15;

                             for(int ii=0;ii<high;ii++)
               {
               a[zz][ii+h]=low+1;


               }
               h=h+high;
              }
              h=0;
             }
             fclose(fp);


           for(int i=-230;i<230;i++)
             {
for(int j=-230;j<230;j++)
{  if(j!=0||i!=0)
{
  p->tilt_of_gps(0.5,  i, j,  lon, lat,dh,ds) ;
  p->gps_to_tilt(lon,lat,0.5, az,L,dh);

  if(L<230&&az<360)
{  //if(a[int(az)][int(L)]>5)
           //   { ShowMessage(a[int(az)][int(L)]);
             //  ShowMessage(az);
             //   ShowMessage(L);
              //  }
 //if(a[int(az)][int(L)]>data[int(j+yj)][int(i+xj)]&&(data1[int(j+yj)][int(i+xj)]>190||xyl[int(j+yj)][int(i+xj)]>0.5||bzf==2))
 if(a[int(az)][int(L)]>vdata[int(j+yj)][int(i+xj)])
 {
 vdata[int(j+yj)][int(i+xj)]=a[int(az)][int(L)];
// ShowMessage(data1[int(j+yj)][int(i+xj)]);
 }
// else
  //data[int(j+yj)][int(i+xj)]=0;



}
  }
}
}

delete p;
}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button43Click(TObject *Sender)
{

int x[16]={255,0,0,50,0,0,0,205,118,248,255,255,174,208,255,119},y[16]={255,224,128,0,251,187,143,201,118,135,107,255,0,112,0,0},z[16]={255,255,255,150,144,153,0,159,118,0,0,0,0,0,0,125};


 for(int i=0;i<16;i++)
 {

         zfpal[i].rB=z[i];
        zfpal[i].rG=y[i];
        zfpal[i].rR=x[i];
        zfpal[i].rX=0;
    }

  FILE *fp;
    char xs[80];


for(int k=0;k<1;k++)
     {
     for(int i=0;i<GMS_H;i++)
     {for(int j=0;j<GMS_W;j++)
     {// if(data[i][j]>=15)
    //ShowMessage(data[i][j]);
      //if(data1[i][j]>=3)
      vdata[i][j]=int((vdata[i][j]+vdata[i][j+1]+vdata[i][j-1]+vdata[i+1][j]+vdata[i-1][j]+vdata[i+1][j+1]+vdata[i-1][j-1]+vdata[i+1][j-1]+vdata[i-1][j+1])/9.);

     //if(data[i][j]>=8)
   // data[i][j]=(data[i][j+1]+data[i][j-1]+data[i+1][j]+data[i-1][j])/4;

     }
     }
     }

   Button44->Click();
 //Button4->Click() ;  */

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button44Click(TObject *Sender)
{
BMP_fileh BMPh1;
    BMP_infoh BMPh2;
  BMPh1.bfType=19778;
    BMPh1.bfSize=(long)(14+40+256*4+GMS_W*GMS_H);
    BMPh1.bf1=0;
    BMPh1.bf2=0;
    BMPh1.bfOffbits=(long)(40+256*4);

    BMPh2.biSize=40L;
    BMPh2.biWidth=(long)GMS_W;
    BMPh2.biHeight=(long)GMS_H;
    BMPh2.biPlanes=1;//1
    BMPh2.biBitcount=8;// 1(2) 4(16) 8(256) 24(true color)
    BMPh2.biComp=0L;//0 1 2
    BMPh2.biSizeimage=((long)GMS_W*(long)GMS_H);
    BMPh2.biX=(long)GMS_W;
    BMPh2.biY=(long)GMS_H;
    BMPh2.biClrused=0L;
    BMPh2.biClrimp=0L;
    FILE *fp;
     if (ss3.SubString(1,1)!="1")
    {
    ss3=ltp+"V\\"+ss3+".bmp";
    fp=fopen(ss3.c_str() ,"wb");
     //1文件头            long
    fwrite(&BMPh1.bfType,2,1,fp);
    fwrite(&BMPh1.bfSize,4,1,fp);
    fwrite(&BMPh1.bf1,2,1,fp);
    fwrite(&BMPh1.bf2,2,1,fp);
    fwrite(&BMPh1.bfOffbits,4,1,fp);

    //2位图信息头
    fwrite(&BMPh2.biSize,4,1,fp);
    fwrite(&BMPh2.biWidth,4,1,fp);
    fwrite(&BMPh2.biHeight,4,1,fp);
    fwrite(&BMPh2.biPlanes,2,1,fp);
    fwrite(&BMPh2.biBitcount,2,1,fp);
    fwrite(&BMPh2.biComp,4,1,fp);
    fwrite(&BMPh2.biSizeimage,4,1,fp);
    fwrite(&BMPh2.biX,4,1,fp);
    fwrite(&BMPh2.biY,4,1,fp);
    fwrite(&BMPh2.biClrused,4,1,fp);
    fwrite(&BMPh2.biClrimp,4,1,fp);

    //3颜色信息
       for(int i=0;i<256;i++){
        fwrite(&zfpal[i],sizeof(BMP_rgb),1,fp);
    }
    int xx=0;//偏移量
    for(int i=GMS_H;i>0;i--){
        for(int j=xx;j<GMS_W;j++){
           if(i<6)
           vdata[i][j]=0;
            if(vdata[i][j]<5)
            vdata[i][j]=0;
            fwrite(&vdata[i][j],1,1,fp);
        }
        for(int j=0;j<xx;j++){
           // if(data[i][j]<6)
            //data[i][j]=0;
          fwrite(&vdata[i][j],1,1,fp);
        }
    }
    fclose(fp);

bzf=0;
 Image1->Picture->LoadFromFile(ss3.c_str());
 AnsiString flsd;
flsd="c:\\雷雨大风.txt";

fp=fopen(flsd.c_str(),"w");
 if (MinutesBetween(tq,tv)<12&&MinutesBetween(tq,tvil)<12&&MinutesBetween(tvil,tv)<12)
 {fprintf(fp,"%s\n",sxr);
 float lon4,lat4,vd,qd,vild;
for(int i=(GMS_H-10);i>0;i=i-10){
        for(int j=0;j<(GMS_W-10);j=j+10){
        for(int ii=i+10;ii>i;ii--)
        {for(int jj=j;jj<j+10;jj++)
        {vd=vd+vdata[ii][jj];
         qd=qd+qdata[ii][jj];
         vild=vild+vildata[ii][jj];
        }
        }
       vd=vd/100.0;
       qd=qd/100.0;
        vild=vild/100.0;

        if (qd>8&&(vd>10||vd<5)&&vild>5)
        { ActToPro(lon4,lat4,j+5,i-5, 114,34.0,500, 500, 1);

         fprintf(fp,"%f %f 1\n",lon4,lat4);

        }
       qd=0;
       vd=0;
       vild=0;
        }
        }
        }
        else
        fprintf(fp,"缺少最够多的同步计算数据\n");
      fclose(fp);
 ///

  Image1->Picture->SaveToFile(ss3.c_str());
  }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button45Click(TObject *Sender)
{
 for(int i=0;i<GMS_H;i++){
        for(int j=0;j<GMS_W;j++){
           data[i][j]=0;
           }
        }
TSearchRec sr;
TDateTime time,t;
      String path=yt+"*.000",sj;
      if (FindFirst(path,faAnyFile,sr)==0)
   {
  do
  { sd=sr.Name;
   sj="20"+sd.SubString(1,2)+"-"+sd.SubString(3,2)+"-"+sd.SubString(5,2)+" "+sd.SubString(7,2)+":00:00";
    time=StrToDateTime(sj);
    if(time>time8)
    {time8=time;
    yth=sd;
                 }
  }


   while(FindNext(sr)==0);
     FindClose(sr);
   }
 

Button9->Click() ;



}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button46Click(TObject *Sender)
{
 for(int i=0;i<GMS_H;i++){
        for(int j=0;j<GMS_W;j++){
           data[i][j]=0;
           }
        }
TSearchRec sr;
TDateTime time,t;
      String path=lljj+"*CR_10X10_230*",sj;
      if (FindFirst(path,faAnyFile,sr)==0)
   {
  do
  { sd=sr.Name;
   sj=sd.SubString(16,4)+"-"+sd.SubString(20,2)+"-"+sd.SubString(22,2)+" "+sd.SubString(24,2)+":"+sd.SubString(26,2)+":"+sd.SubString(28,2);
    time=StrToDateTime(sj);
    if(time>time9)
    {time9=time;
                 }
  }


   while(FindNext(sr)==0);
     FindClose(sr);
   }
    t=time9+8/24.;
    tt=t;
    String nian,yue,ri,shi,fen;
   Word Year,Month,Day,Hour,Me,Mee,Meee;
   DecodeDate(t,Year,Month,Day);
   DecodeTime(t,Hour,Me,Mee,Meee);
   nian=IntToStr(Year);
if(Month<10)
yue="0"+IntToStr(Month);
else
yue=IntToStr(Month);
if(Day<10)
ri="0"+IntToStr(Day);
else
ri=IntToStr(Day);
if(Hour<10)
shi="0"+IntToStr(Hour);
else
shi=IntToStr(Hour);
if(Me<10)
fen="0"+IntToStr(Me);
else
fen=IntToStr(Me);
ss5=nian+yue+ri+shi+fen;



Button47->Click() ;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button47Click(TObject *Sender)
{
for(int i=GMS_H;i>0;i--)
{
        for(int j=0;j<GMS_W;j++)
        {
                    data[i][j]=0;
           }
           }
TSearchRec sr;
    int countMin;
TDateTime time;
      String path=lljj+"*CR_10X10_230*",sj;
      if (FindFirst(path,faAnyFile,sr)==0)
   {
  do
  { sd1=sr.Name;
   sj=sd1.SubString(16,4)+"-"+sd1.SubString(20,2)+"-"+sd1.SubString(22,2)+" "+sd1.SubString(24,2)+":"+sd1.SubString(26,2)+":"+sd1.SubString(28,2);
    time=StrToDateTime(sj);
   countMin=MinutesBetween(time,time9);
   //ShowMessage(sj);
   if(time<=time9&&countMin<6)
   {

        Button48->Click();
   }
  }

   while(FindNext(sr)==0);
     FindClose(sr);
   }
Button49->Click();
 Button50->Click();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button48Click(TObject *Sender)
{
 ///

FILE *fp;
String f;
    float x8,y8;
char hb;
double ele, az,L,dh;
int nian,yue,ri,xiaoshi,fenzhong,miao,pyl,bt[460][460];
 long tt;
float x0=1,y0=1;
 unsigned short Number1;
 for(int i=0;i<460;i++)
{
        for(int j=0;j<460;j++)
        {
          bt[i][j]=0;

           }
           }
////
int low,high,jxs,sjs,h=0,zz,db,yjh;
float yjs,lon,lat;
HEADER  hed;
        DESCRIPTION  nn;
        SYMBOLOGY n3;
         onetow n4;
        ifon1 n5;
        tagLVPacket n6;
        cr  mm;
AnsiString ff;
ff=lljj+sd1;

fp = fopen(ff.c_str(),"rb");
fread(&hed,sizeof(hed),1,fp);
fread(&nn,sizeof(nn),1,fp);
                 fread(&n3,sizeof(n3),1,fp);
                 radlat=(int)ChangeDWord((unsigned int)(nn.RadarLatitude))*0.001;
           radlon=(int)ChangeDWord((unsigned int)(nn.RadarLongtitude))*0.001;
              PointF(xj,yj,radlon,radlat,  114,34.0,500,500,1);

n3.nBlockId=(short)ChangeWord((unsigned short)(n3.nBlockId)) ;

if(n3.nBlockId==1)
{

                       fread(&n4,sizeof(n4),1,fp);
                       n4.NumberOfLayers=(short)ChangeWord((unsigned short)(n4.NumberOfLayers));
                       fread(&n5,sizeof(n5),1,fp);
                         fread(&n6,sizeof(n6),1,fp);
                       fread(&mm,sizeof(mm),1,fp);
                       mm.nJStart= (short)ChangeWord((unsigned short)( mm.nJStart)) ;;
             mm.nRowNum=ChangeWord((unsigned short)(mm.nRowNum)) ;
              mm.nXScale=ChangeWord((unsigned short)(mm.nXScale)) ;
              mm.nYScale=ChangeWord((unsigned short)(mm.nYScale)) ;

              pyl=mm.nRowNum*mm.nYScale/2;
             for(int i=0;i<mm.nRowNum;i++)
             {
               fread(&Number1,sizeof( Number1),1,fp);
                Number1=ChangeWord((unsigned short)(Number1)) ;
                for(int j=0;j<Number1;j++)
                {
                 fread(&hb,sizeof(char),1,fp);
               high=(hb>>4)&0xf;
               low=hb&15;
              for(int x=x0;x<x0+high*mm.nXScale;x=x+1)
               { for(int y=y0;y<y0+mm.nYScale;y=y+1)
               {if(x<460&&y<460)
               bt[x][y]=low;


               }


               }
               x0=x0+high*mm.nXScale;

                }
                y0=y0+mm.nYScale;
                x0=0;

            }



}
 fclose(fp);
 for(int i=-230;i<230;i++)
 {
 for(int j=-230;j<230;j++)
{ if (bt[i+230][j+230]>data[int(j+yj)][int(i+xj)])
 data[int(j+yj)][int(i+xj)]=bt[i+230][j+230];




  }
  }


}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button49Click(TObject *Sender)
{
int x[16]={255,0,198,123,24,165,0,16,255,206,140,255,255,239,214,173},
 y[16]={255,174,195,113,36,255,235,146,247,203,142,173,101,0,142,36},
z[16]={255,165,255,239,214,173,0,24,99,0,0,173,101,0,255,255};

////

 for(int i=0;i<16;i++)
 {

         zfpal[i].rB=z[i];
        zfpal[i].rG=y[i];
        zfpal[i].rR=x[i];
        zfpal[i].rX=0;
    }

  FILE *fp;
    char xs[80];


  /* for(int k=0;k<1;k++)
     {
     for(int i=0;i<GMS_H;i++)
     {for(int j=0;j<GMS_W;j++)
     {// if(data[i][j]>=15)
    //ShowMessage(data[i][j]);
      //if(data[i][j]>=3)
      data[i][j]=int((data[i][j]+data[i][j+1]+data[i][j-1]+data[i+1][j]+data[i-1][j])/5.);

     //if(data[i][j]>=8)
   // data[i][j]=(data[i][j+1]+data[i][j-1]+data[i+1][j]+data[i-1][j])/4;

     }
     }
     }  */






}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button50Click(TObject *Sender)
{
 BMP_fileh BMPh1;
    BMP_infoh BMPh2;
  BMPh1.bfType=19778;
    BMPh1.bfSize=(long)(14+40+256*4+GMS_W*GMS_H);
    BMPh1.bf1=0;
    BMPh1.bf2=0;
    BMPh1.bfOffbits=(long)(40+256*4);

    BMPh2.biSize=40L;
    BMPh2.biWidth=(long)GMS_W;
    BMPh2.biHeight=(long)GMS_H;
    BMPh2.biPlanes=1;//1
    BMPh2.biBitcount=8;// 1(2) 4(16) 8(256) 24(true color)
    BMPh2.biComp=0L;//0 1 2
    BMPh2.biSizeimage=((long)GMS_W*(long)GMS_H);
    BMPh2.biX=(long)GMS_W;
    BMPh2.biY=(long)GMS_H;
    BMPh2.biClrused=0L;
    BMPh2.biClrimp=0L;
    FILE *fp;
     if (ss5.SubString(1,1)!="1")
    {
    ss5=ltp+"\\cref\\"+ss5+".bmp";
    fp=fopen(ss5.c_str() ,"wb");
     //1文件头            long
    fwrite(&BMPh1.bfType,2,1,fp);
    fwrite(&BMPh1.bfSize,4,1,fp);
    fwrite(&BMPh1.bf1,2,1,fp);
    fwrite(&BMPh1.bf2,2,1,fp);
    fwrite(&BMPh1.bfOffbits,4,1,fp);

    //2位图信息头
    fwrite(&BMPh2.biSize,4,1,fp);
    fwrite(&BMPh2.biWidth,4,1,fp);
    fwrite(&BMPh2.biHeight,4,1,fp);
    fwrite(&BMPh2.biPlanes,2,1,fp);
    fwrite(&BMPh2.biBitcount,2,1,fp);
    fwrite(&BMPh2.biComp,4,1,fp);
    fwrite(&BMPh2.biSizeimage,4,1,fp);
    fwrite(&BMPh2.biX,4,1,fp);
    fwrite(&BMPh2.biY,4,1,fp);
    fwrite(&BMPh2.biClrused,4,1,fp);
    fwrite(&BMPh2.biClrimp,4,1,fp);

  //3颜色信息
       for(int i=0;i<256;i++){
        fwrite(&zfpal[i],sizeof(BMP_rgb),1,fp);
    }
    int xx=0;//偏移量
    for(int i=GMS_H;i>0;i--){
        for(int j=xx;j<GMS_W;j++){
           if(i<6)
           data[i][j]=0;
            if(data[i][j]<5)
            data[i][j]=0;
            fwrite(&data[i][j],1,1,fp);
        }
        for(int j=0;j<xx;j++){
           // if(data[i][j]<6)
            //data[i][j]=0;
          fwrite(&data[i][j],1,1,fp);
        }
    }
    fclose(fp);

bzf=0;
Image1->Picture->LoadFromFile(ss5.c_str());
  Image1->Picture->SaveToFile(ss5.c_str());
  }

}
//---------------------------------------------------------------------------




void __fastcall TForm1::Button51Click(TObject *Sender)
{

TSearchRec sr;
TDateTime time,t;
      String path=lljj+"*R_10_230_35.*",sj;
      if (FindFirst(path,faAnyFile,sr)==0)
   {
  do
  { sd=sr.Name;
   sj=sd.SubString(16,4)+"-"+sd.SubString(20,2)+"-"+sd.SubString(22,2)+" "+sd.SubString(24,2)+":"+sd.SubString(26,2)+":"+sd.SubString(28,2);
    time=StrToDateTime(sj);
    if(time>time10)
    {time10=time;
                 }
  }


   while(FindNext(sr)==0);
     FindClose(sr);
   }
    t=time10+8/24.;
    tt=t;
    String nian,yue,ri,shi,fen;
   Word Year,Month,Day,Hour,Me,Mee,Meee;
   DecodeDate(t,Year,Month,Day);
   DecodeTime(t,Hour,Me,Mee,Meee);
   nian=IntToStr(Year);
if(Month<10)
yue="0"+IntToStr(Month);
else
yue=IntToStr(Month);
if(Day<10)
ri="0"+IntToStr(Day);
else
ri=IntToStr(Day);
if(Hour<10)
shi="0"+IntToStr(Hour);
else
shi=IntToStr(Hour);
if(Me<10)
fen="0"+IntToStr(Me);
else
fen=IntToStr(Me);
ss3=nian+yue+ri+shi+fen;
/*ss4=nian+yue+ri+shi;
yth=nian.SubString(3,2) +yue+ri+shi;
String f2=yt+yth+".000";
///
 if(!FileExists(f2))
 {
  t=time1+7/24.;
     DecodeDate(t,Year,Month,Day);
   DecodeTime(t,Hour,Me,Mee,Meee);
   nian=IntToStr(Year);
if(Month<10)
yue="0"+IntToStr(Month);
else
yue=IntToStr(Month);
if(Day<10)
ri="0"+IntToStr(Day);
else
ri=IntToStr(Day);
if(Hour<10)
shi="0"+IntToStr(Hour);
else
shi=IntToStr(Hour);
yth=nian.SubString(3,2) +yue+ri+shi;
} */
Button52->Click() ;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button52Click(TObject *Sender)
{
 for(int i=GMS_H;i>0;i--)
{
        for(int j=0;j<GMS_W;j++)
        {
                    data[i][j]=0;
           }
           }
TSearchRec sr;
    int countMin;
TDateTime time;
      String path=lljj+"*R_10_230_35.*",sj;
      if (FindFirst(path,faAnyFile,sr)==0)
   {
  do
  { sd=sr.Name;
   sj=sd.SubString(16,4)+"-"+sd.SubString(20,2)+"-"+sd.SubString(22,2)+" "+sd.SubString(24,2)+":"+sd.SubString(26,2)+":"+sd.SubString(28,2);
    time=StrToDateTime(sj);
   countMin=MinutesBetween(time,time10);
   if(time<=time10
   &&countMin<6)
   {

        Button53->Click();
   }
  }

   while(FindNext(sr)==0);
     FindClose(sr);
   }
 Button54->Click();


}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button53Click(TObject *Sender)
{

FILE *fp;


int nian,yue,ri,xiaoshi,fenzhong,miao;
 long tt;

////
int low,high,jxs,sjs,h=0,zz,a[360][230],db,yjh;
for(int i=0;i<360;i++)
{
        for(int j=0;j<230;j++)
        {
          a[i][j]=0;

           }
           }

char hb;
HEADER  hed;
        DESCRIPTION  nn;
         SYMBOLOGY n3;
        onetow n4;
               ifon1 n5;
        tagLVPacket n6;
AnsiString ff;
ff=lljj+sd;

fp = fopen(ff.c_str(),"rb");
fread(&hed,sizeof(hed),1,fp);
fread(&nn,sizeof(nn),1,fp);
 radlat=(int)ChangeDWord((unsigned int)(nn.RadarLatitude))*0.001;
           radlon=(int)ChangeDWord((unsigned int)(nn.RadarLongtitude))*0.001;
           radh = (short)ChangeWord((unsigned short)(nn.RadarHeight))*0.3048;
          // ShowMessage(FloatToStr(radh));
           PointF(xj,yj,radlon,radlat,  114,34.0,500,500,1);

           yjh = ChangeWord((unsigned short)(nn.ElevationNumber));
           if(yjh==1)
           ele=0.5;
           if(yjh==2)
           ele=1.5;
           if(yjh==3)
           ele=2.4;
          CRadEPrj *p = new CRadEPrj(radlon,radlat,radh);
p->Initialized(40.0, 0, 0, 1000);

              fread(&n3,sizeof(n3),1,fp);
n3.nBlockId=(short)ChangeWord((unsigned short)(n3.nBlockId)) ;

//long nTimeofMessage=nn.TimeofMessage2[0]<<24|nn.TimeofMessage2[1]<<16|
                                nn.TimeofMessage2[2]<<8|nn.TimeofMessage2[3];

//GetRadialTime(nTimeofMessage*1000,xiaoshi,fenzhong,miao);
////////
if(n3.nBlockId==1)
{ fread(&n4,sizeof(n4),1,fp);
n4.NumberOfLayers=(short)ChangeWord((unsigned short)(n4.NumberOfLayers));

 fread(&n5,sizeof(n5),1,fp);
 fread(&n6,sizeof(n6),1,fp);
n5. LayerDivider=(short)ChangeWord((unsigned short)(n5. LayerDivider)) ;


               jingxiangtow  mm;
                       fread(&mm,sizeof(mm),1,fp);

            jxs = (short)ChangeWord((unsigned short)(mm.NumberofRadials));


                          jingxiang  jx;
             for(int i=0;i<jxs;i++)
             {fread(&jx,sizeof(jx),1,fp);
              sjs = ChangeWord((unsigned short)(jx.Number))*2;
              yjs=ChangeWord((unsigned short)(jx.RadialStartAngle))*0.1;

              if(int(yjs)>=360)
              zz=int(yjs)-360;
              else
              zz=int(yjs);
             for(int j=0;j<sjs;j++)
              {fread(&hb,sizeof(char),1,fp);
               high=(hb>>4)&0xf;
               low=hb&15;

                             for(int ii=0;ii<high;ii++)
               {
               a[zz][ii+h]=low+1;


               }
               h=h+high;
              }
              h=0;
             }
             fclose(fp);


           for(int i=-230;i<230;i++)
             {
for(int j=-230;j<230;j++)
{  if(j!=0||i!=0)
{
  p->tilt_of_gps(1.0,  i, j,  lon, lat,dh,ds) ;
  p->gps_to_tilt(lon,lat,1.0, az,L,dh);

  if(L<230&&az<360)
{  //if(a[int(az)][int(L)]>5)
           //   { ShowMessage(a[int(az)][int(L)]);
             //  ShowMessage(az);
             //   ShowMessage(L);
              //  }
 //if(a[int(az)][int(L)]>data[int(j+yj)][int(i+xj)]&&(data1[int(j+yj)][int(i+xj)]>190||xyl[int(j+yj)][int(i+xj)]>0.5||bzf==2))
 if(a[int(az)][int(L)]>data[int(j+yj)][int(i+xj)])
 {
 data[int(j+yj)][int(i+xj)]=a[int(az)][int(L)];
// ShowMessage(data1[int(j+yj)][int(i+xj)]);
 }
// else
 // data[int(j+yj)][int(i+xj)]=0;



}
  }
}
}

delete p;
}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button54Click(TObject *Sender)
{
 // int x[17]={255,0,0,192,122,30,166,0,16,252,200,140,254,254,238,212,170},y[17]={255,0,172,192,114,38,252,234,146,244,200,140,172,100,2,142,36},z[17]={255,0,164,254,238,208,168,0,26,100,2,0,172,92,48,254,250};

////

 int x[16]={255,0,198,123,24,165,0,16,255,206,140,255,255,239,214,173},
 y[16]={255,174,195,113,36,255,235,146,247,203,142,173,101,0,142,36},
z[16]={255,165,255,239,214,173,0,24,99,0,0,173,101,0,255,255};

////

 for(int i=0;i<16;i++)
 {

         zfpal[i].rB=z[i];
        zfpal[i].rG=y[i];
        zfpal[i].rR=x[i];
        zfpal[i].rX=0;
    }


  FILE *fp;
    char xs[80];


  for(int k=0;k<1;k++)
     {
     for(int i=0;i<GMS_H;i++)
     {for(int j=0;j<GMS_W;j++)
     {// if(data[i][j]>=15)
    //ShowMessage(data[i][j]);
     // if(data[i][j]>=3)
      data[i][j]=int((data[i][j]+data[i][j+1]+data[i][j-1]+data[i+1][j]+data[i-1][j])/5.);

     //if(data[i][j]>=8)
   // data[i][j]=(data[i][j+1]+data[i][j-1]+data[i+1][j]+data[i-1][j])/4;

     }
     }
     }

 Button55->Click() ;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button55Click(TObject *Sender)
{
BMP_fileh BMPh1;
    BMP_infoh BMPh2;
  BMPh1.bfType=19778;
    BMPh1.bfSize=(long)(14+40+256*4+GMS_W*GMS_H);
    BMPh1.bf1=0;
    BMPh1.bf2=0;
    BMPh1.bfOffbits=(long)(40+256*4);

    BMPh2.biSize=40L;
    BMPh2.biWidth=(long)GMS_W;
    BMPh2.biHeight=(long)GMS_H;
    BMPh2.biPlanes=1;//1
    BMPh2.biBitcount=8;// 1(2) 4(16) 8(256) 24(true color)
    BMPh2.biComp=0L;//0 1 2
    BMPh2.biSizeimage=((long)GMS_W*(long)GMS_H);
    BMPh2.biX=(long)GMS_W;
    BMPh2.biY=(long)GMS_H;
    BMPh2.biClrused=0L;
    BMPh2.biClrimp=0L;
    FILE *fp;
     if (ss3.SubString(1,1)!="1")
    {
    ss3=ltp+"QREF\\3.4\\"+ss3+".bmp";
    fp=fopen(ss3.c_str() ,"wb");
     //1文件头            long
    fwrite(&BMPh1.bfType,2,1,fp);
    fwrite(&BMPh1.bfSize,4,1,fp);
    fwrite(&BMPh1.bf1,2,1,fp);
    fwrite(&BMPh1.bf2,2,1,fp);
    fwrite(&BMPh1.bfOffbits,4,1,fp);

    //2位图信息头
    fwrite(&BMPh2.biSize,4,1,fp);
    fwrite(&BMPh2.biWidth,4,1,fp);
    fwrite(&BMPh2.biHeight,4,1,fp);
    fwrite(&BMPh2.biPlanes,2,1,fp);
    fwrite(&BMPh2.biBitcount,2,1,fp);
    fwrite(&BMPh2.biComp,4,1,fp);
    fwrite(&BMPh2.biSizeimage,4,1,fp);
    fwrite(&BMPh2.biX,4,1,fp);
    fwrite(&BMPh2.biY,4,1,fp);
    fwrite(&BMPh2.biClrused,4,1,fp);
    fwrite(&BMPh2.biClrimp,4,1,fp);

    //3颜色信息
       for(int i=0;i<256;i++){
        fwrite(&zfpal[i],sizeof(BMP_rgb),1,fp);
    }
    int xx=0;//偏移量
    for(int i=GMS_H;i>0;i--){
        for(int j=xx;j<GMS_W;j++){
           if(i<6)
           data[i][j]=0;
            if(data[i][j]<5)
            data[i][j]=0;
            fwrite(&data[i][j],1,1,fp);
        }
        for(int j=0;j<xx;j++){
           // if(data[i][j]<6)
            //data[i][j]=0;
          fwrite(&data[i][j],1,1,fp);
        }
    }
    fclose(fp);

bzf=0;
 Image1->Picture->LoadFromFile(ss3.c_str());
  Image1->Picture->SaveToFile(ss3.c_str());
  }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button56Click(TObject *Sender)
{

TSearchRec sr;
TDateTime time,t;
      String path=lljj+"*R_10_230_15.*",sj;
      if (FindFirst(path,faAnyFile,sr)==0)
   {
  do
  { sd=sr.Name;
   sj=sd.SubString(16,4)+"-"+sd.SubString(20,2)+"-"+sd.SubString(22,2)+" "+sd.SubString(24,2)+":"+sd.SubString(26,2)+":"+sd.SubString(28,2);
    time=StrToDateTime(sj);
    if(time>time11)
    {time11=time;
                 }
  }


   while(FindNext(sr)==0);
     FindClose(sr);
   }
    t=time11+8/24.;
    tt=t;
    String nian,yue,ri,shi,fen;
   Word Year,Month,Day,Hour,Me,Mee,Meee;
   DecodeDate(t,Year,Month,Day);
   DecodeTime(t,Hour,Me,Mee,Meee);
   nian=IntToStr(Year);
if(Month<10)
yue="0"+IntToStr(Month);
else
yue=IntToStr(Month);
if(Day<10)
ri="0"+IntToStr(Day);
else
ri=IntToStr(Day);
if(Hour<10)
shi="0"+IntToStr(Hour);
else
shi=IntToStr(Hour);
if(Me<10)
fen="0"+IntToStr(Me);
else
fen=IntToStr(Me);
ss3=nian+yue+ri+shi+fen;

Button57->Click() ;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button57Click(TObject *Sender)
{
 for(int i=GMS_H;i>0;i--)
{
        for(int j=0;j<GMS_W;j++)
        {
                    data[i][j]=0;
           }
           }
TSearchRec sr;
    int countMin;
TDateTime time;
      String path=lljj+"*R_10_230_15.*",sj;
      if (FindFirst(path,faAnyFile,sr)==0)
   {
  do
  { sd=sr.Name;
   sj=sd.SubString(16,4)+"-"+sd.SubString(20,2)+"-"+sd.SubString(22,2)+" "+sd.SubString(24,2)+":"+sd.SubString(26,2)+":"+sd.SubString(28,2);
    time=StrToDateTime(sj);
   countMin=MinutesBetween(time,time11);
   if(time<=time11
   &&countMin<6)
   {

        Button58->Click();
   }
  }

   while(FindNext(sr)==0);
     FindClose(sr);
   }
 Button59->Click();



}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button58Click(TObject *Sender)
{

FILE *fp;


int nian,yue,ri,xiaoshi,fenzhong,miao;
 long tt;

////
int low,high,jxs,sjs,h=0,zz,a[360][230],db,yjh;
for(int i=0;i<360;i++)
{
        for(int j=0;j<230;j++)
        {
          a[i][j]=0;

           }
           }

char hb;
HEADER  hed;
        DESCRIPTION  nn;
         SYMBOLOGY n3;
        onetow n4;
               ifon1 n5;
        tagLVPacket n6;
AnsiString ff;
ff=lljj+sd;

fp = fopen(ff.c_str(),"rb");
fread(&hed,sizeof(hed),1,fp);
fread(&nn,sizeof(nn),1,fp);
 radlat=(int)ChangeDWord((unsigned int)(nn.RadarLatitude))*0.001;
           radlon=(int)ChangeDWord((unsigned int)(nn.RadarLongtitude))*0.001;
           radh = (short)ChangeWord((unsigned short)(nn.RadarHeight))*0.3048;
          // ShowMessage(FloatToStr(radh));
           PointF(xj,yj,radlon,radlat,  114,34.0,500,500,1);

           yjh = ChangeWord((unsigned short)(nn.ElevationNumber));
           if(yjh==1)
           ele=0.5;
           if(yjh==2)
           ele=1.5;
           if(yjh==3)
           ele=2.4;
          CRadEPrj *p = new CRadEPrj(radlon,radlat,radh);
p->Initialized(40.0, 0, 0, 1000);

              fread(&n3,sizeof(n3),1,fp);
n3.nBlockId=(short)ChangeWord((unsigned short)(n3.nBlockId)) ;

//long nTimeofMessage=nn.TimeofMessage2[0]<<24|nn.TimeofMessage2[1]<<16|
                                nn.TimeofMessage2[2]<<8|nn.TimeofMessage2[3];

//GetRadialTime(nTimeofMessage*1000,xiaoshi,fenzhong,miao);
////////
if(n3.nBlockId==1)
{ fread(&n4,sizeof(n4),1,fp);
n4.NumberOfLayers=(short)ChangeWord((unsigned short)(n4.NumberOfLayers));

 fread(&n5,sizeof(n5),1,fp);
 fread(&n6,sizeof(n6),1,fp);
n5. LayerDivider=(short)ChangeWord((unsigned short)(n5. LayerDivider)) ;


               jingxiangtow  mm;
                       fread(&mm,sizeof(mm),1,fp);

            jxs = (short)ChangeWord((unsigned short)(mm.NumberofRadials));


                          jingxiang  jx;
             for(int i=0;i<jxs;i++)
             {fread(&jx,sizeof(jx),1,fp);
              sjs = ChangeWord((unsigned short)(jx.Number))*2;
              yjs=ChangeWord((unsigned short)(jx.RadialStartAngle))*0.1;

              if(int(yjs)>=360)
              zz=int(yjs)-360;
              else
              zz=int(yjs);
             for(int j=0;j<sjs;j++)
              {fread(&hb,sizeof(char),1,fp);
               high=(hb>>4)&0xf;
               low=hb&15;

                             for(int ii=0;ii<high;ii++)
               {
               a[zz][ii+h]=low+1;


               }
               h=h+high;
              }
              h=0;
             }
             fclose(fp);


           for(int i=-230;i<230;i++)
             {
for(int j=-230;j<230;j++)
{  if(j!=0||i!=0)
{
  p->tilt_of_gps(1.5,  i, j,  lon, lat,dh,ds) ;
  p->gps_to_tilt(lon,lat,1.5, az,L,dh);

  if(L<230&&az<360)
{  //if(a[int(az)][int(L)]>5)
           //   { ShowMessage(a[int(az)][int(L)]);
             //  ShowMessage(az);
             //   ShowMessage(L);
              //  }
 //if(a[int(az)][int(L)]>data[int(j+yj)][int(i+xj)]&&(data1[int(j+yj)][int(i+xj)]>190||xyl[int(j+yj)][int(i+xj)]>0.5||bzf==2))
 if(a[int(az)][int(L)]>data[int(j+yj)][int(i+xj)])
 {
 data[int(j+yj)][int(i+xj)]=a[int(az)][int(L)];
// ShowMessage(data1[int(j+yj)][int(i+xj)]);
 }
// else
 // data[int(j+yj)][int(i+xj)]=0;



}
  }
}
}

delete p;
}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button59Click(TObject *Sender)
{
 // int x[17]={255,0,0,192,122,30,166,0,16,252,200,140,254,254,238,212,170},y[17]={255,0,172,192,114,38,252,234,146,244,200,140,172,100,2,142,36},z[17]={255,0,164,254,238,208,168,0,26,100,2,0,172,92,48,254,250};

////

 int x[16]={255,0,198,123,24,165,0,16,255,206,140,255,255,239,214,173},
 y[16]={255,174,195,113,36,255,235,146,247,203,142,173,101,0,142,36},
z[16]={255,165,255,239,214,173,0,24,99,0,0,173,101,0,255,255};

////

 for(int i=0;i<16;i++)
 {

         zfpal[i].rB=z[i];
        zfpal[i].rG=y[i];
        zfpal[i].rR=x[i];
        zfpal[i].rX=0;
    }


  FILE *fp;
    char xs[80];


  for(int k=0;k<1;k++)
     {
     for(int i=0;i<GMS_H;i++)
     {for(int j=0;j<GMS_W;j++)
     {// if(data[i][j]>=15)
    //ShowMessage(data[i][j]);
     // if(data[i][j]>=3)
      data[i][j]=int((data[i][j]+data[i][j+1]+data[i][j-1]+data[i+1][j]+data[i-1][j])/5.);

     //if(data[i][j]>=8)
   // data[i][j]=(data[i][j+1]+data[i][j-1]+data[i+1][j]+data[i-1][j])/4;

     }
     }
     }

 Button60->Click() ;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button60Click(TObject *Sender)
{
BMP_fileh BMPh1;
    BMP_infoh BMPh2;
  BMPh1.bfType=19778;
    BMPh1.bfSize=(long)(14+40+256*4+GMS_W*GMS_H);
    BMPh1.bf1=0;
    BMPh1.bf2=0;
    BMPh1.bfOffbits=(long)(40+256*4);

    BMPh2.biSize=40L;
    BMPh2.biWidth=(long)GMS_W;
    BMPh2.biHeight=(long)GMS_H;
    BMPh2.biPlanes=1;//1
    BMPh2.biBitcount=8;// 1(2) 4(16) 8(256) 24(true color)
    BMPh2.biComp=0L;//0 1 2
    BMPh2.biSizeimage=((long)GMS_W*(long)GMS_H);
    BMPh2.biX=(long)GMS_W;
    BMPh2.biY=(long)GMS_H;
    BMPh2.biClrused=0L;
    BMPh2.biClrimp=0L;
    FILE *fp;
     if (ss3.SubString(1,1)!="1")
    {
    ss3=ltp+"QREF\\1.5\\"+ss3+".bmp";
    fp=fopen(ss3.c_str() ,"wb");
     //1文件头            long
    fwrite(&BMPh1.bfType,2,1,fp);
    fwrite(&BMPh1.bfSize,4,1,fp);
    fwrite(&BMPh1.bf1,2,1,fp);
    fwrite(&BMPh1.bf2,2,1,fp);
    fwrite(&BMPh1.bfOffbits,4,1,fp);

    //2位图信息头
    fwrite(&BMPh2.biSize,4,1,fp);
    fwrite(&BMPh2.biWidth,4,1,fp);
    fwrite(&BMPh2.biHeight,4,1,fp);
    fwrite(&BMPh2.biPlanes,2,1,fp);
    fwrite(&BMPh2.biBitcount,2,1,fp);
    fwrite(&BMPh2.biComp,4,1,fp);
    fwrite(&BMPh2.biSizeimage,4,1,fp);
    fwrite(&BMPh2.biX,4,1,fp);
    fwrite(&BMPh2.biY,4,1,fp);
    fwrite(&BMPh2.biClrused,4,1,fp);
    fwrite(&BMPh2.biClrimp,4,1,fp);

    //3颜色信息
       for(int i=0;i<256;i++){
        fwrite(&zfpal[i],sizeof(BMP_rgb),1,fp);
    }
    int xx=0;//偏移量
    for(int i=GMS_H;i>0;i--){
        for(int j=xx;j<GMS_W;j++){
           if(i<6)
           data[i][j]=0;
            if(data[i][j]<5)
            data[i][j]=0;
            fwrite(&data[i][j],1,1,fp);
        }
        for(int j=0;j<xx;j++){
           // if(data[i][j]<6)
            //data[i][j]=0;
          fwrite(&data[i][j],1,1,fp);
        }
    }
    fclose(fp);

bzf=0;
 Image1->Picture->LoadFromFile(ss3.c_str());
  Image1->Picture->SaveToFile(ss3.c_str());
  }

}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button61Click(TObject *Sender)
{

TSearchRec sr;
TDateTime time,t;
      String path=lljj+"*R_10_230_24.*",sj;
      if (FindFirst(path,faAnyFile,sr)==0)
   {
  do
  { sd=sr.Name;
   sj=sd.SubString(16,4)+"-"+sd.SubString(20,2)+"-"+sd.SubString(22,2)+" "+sd.SubString(24,2)+":"+sd.SubString(26,2)+":"+sd.SubString(28,2);
    time=StrToDateTime(sj);
    if(time>time12)
    {time12=time;
                 }
  }


   while(FindNext(sr)==0);
     FindClose(sr);
   }
    t=time12+8/24.;
    tt=t;
    String nian,yue,ri,shi,fen;
   Word Year,Month,Day,Hour,Me,Mee,Meee;
   DecodeDate(t,Year,Month,Day);
   DecodeTime(t,Hour,Me,Mee,Meee);
   nian=IntToStr(Year);
if(Month<10)
yue="0"+IntToStr(Month);
else
yue=IntToStr(Month);
if(Day<10)
ri="0"+IntToStr(Day);
else
ri=IntToStr(Day);
if(Hour<10)
shi="0"+IntToStr(Hour);
else
shi=IntToStr(Hour);
if(Me<10)
fen="0"+IntToStr(Me);
else
fen=IntToStr(Me);
ss3=nian+yue+ri+shi+fen;

Button62->Click() ;


}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button62Click(TObject *Sender)
{
 for(int i=GMS_H;i>0;i--)
{
        for(int j=0;j<GMS_W;j++)
        {
                    data[i][j]=0;
           }
           }
TSearchRec sr;
    int countMin;
TDateTime time;
      String path=lljj+"*R_10_230_24.*",sj;
      if (FindFirst(path,faAnyFile,sr)==0)
   {
  do
  { sd=sr.Name;
   sj=sd.SubString(16,4)+"-"+sd.SubString(20,2)+"-"+sd.SubString(22,2)+" "+sd.SubString(24,2)+":"+sd.SubString(26,2)+":"+sd.SubString(28,2);
    time=StrToDateTime(sj);
   countMin=MinutesBetween(time,time12);
   if(time<=time12&&countMin<6)
   {

        Button63->Click();
   }
  }

   while(FindNext(sr)==0);
     FindClose(sr);
   }
 Button64->Click();



}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button63Click(TObject *Sender)
{

FILE *fp;


int nian,yue,ri,xiaoshi,fenzhong,miao;
 long tt;

////
int low,high,jxs,sjs,h=0,zz,a[360][230],db,yjh;
for(int i=0;i<360;i++)
{
        for(int j=0;j<230;j++)
        {
          a[i][j]=0;

           }
           }

char hb;
HEADER  hed;
        DESCRIPTION  nn;
         SYMBOLOGY n3;
        onetow n4;
               ifon1 n5;
        tagLVPacket n6;
AnsiString ff;
ff=lljj+sd;

fp = fopen(ff.c_str(),"rb");
fread(&hed,sizeof(hed),1,fp);
fread(&nn,sizeof(nn),1,fp);
 radlat=(int)ChangeDWord((unsigned int)(nn.RadarLatitude))*0.001;
           radlon=(int)ChangeDWord((unsigned int)(nn.RadarLongtitude))*0.001;
           radh = (short)ChangeWord((unsigned short)(nn.RadarHeight))*0.3048;
          // ShowMessage(FloatToStr(radh));
           PointF(xj,yj,radlon,radlat,  114,34.0,500,500,1);

           yjh = ChangeWord((unsigned short)(nn.ElevationNumber));
           if(yjh==1)
           ele=0.5;
           if(yjh==2)
           ele=1.5;
           if(yjh==3)
           ele=2.4;
          CRadEPrj *p = new CRadEPrj(radlon,radlat,radh);
p->Initialized(40.0, 0, 0, 1000);

              fread(&n3,sizeof(n3),1,fp);
n3.nBlockId=(short)ChangeWord((unsigned short)(n3.nBlockId)) ;

//long nTimeofMessage=nn.TimeofMessage2[0]<<24|nn.TimeofMessage2[1]<<16|
                                nn.TimeofMessage2[2]<<8|nn.TimeofMessage2[3];

//GetRadialTime(nTimeofMessage*1000,xiaoshi,fenzhong,miao);
////////
if(n3.nBlockId==1)
{ fread(&n4,sizeof(n4),1,fp);
n4.NumberOfLayers=(short)ChangeWord((unsigned short)(n4.NumberOfLayers));

 fread(&n5,sizeof(n5),1,fp);
 fread(&n6,sizeof(n6),1,fp);
n5. LayerDivider=(short)ChangeWord((unsigned short)(n5. LayerDivider)) ;


               jingxiangtow  mm;
                       fread(&mm,sizeof(mm),1,fp);

            jxs = (short)ChangeWord((unsigned short)(mm.NumberofRadials));


                          jingxiang  jx;
             for(int i=0;i<jxs;i++)
             {fread(&jx,sizeof(jx),1,fp);
              sjs = ChangeWord((unsigned short)(jx.Number))*2;
              yjs=ChangeWord((unsigned short)(jx.RadialStartAngle))*0.1;

              if(int(yjs)>=360)
              zz=int(yjs)-360;
              else
              zz=int(yjs);
             for(int j=0;j<sjs;j++)
              {fread(&hb,sizeof(char),1,fp);
               high=(hb>>4)&0xf;
               low=hb&15;

                             for(int ii=0;ii<high;ii++)
               {
               a[zz][ii+h]=low+1;


               }
               h=h+high;
              }
              h=0;
             }
             fclose(fp);


           for(int i=-230;i<230;i++)
             {
for(int j=-230;j<230;j++)
{  if(j!=0||i!=0)
{
  p->tilt_of_gps(2.4,  i, j,  lon, lat,dh,ds) ;
  p->gps_to_tilt(lon,lat,2.4, az,L,dh);

  if(L<230&&az<360)
{  //if(a[int(az)][int(L)]>5)
           //   { ShowMessage(a[int(az)][int(L)]);
             //  ShowMessage(az);
             //   ShowMessage(L);
              //  }
 //if(a[int(az)][int(L)]>data[int(j+yj)][int(i+xj)]&&(data1[int(j+yj)][int(i+xj)]>190||xyl[int(j+yj)][int(i+xj)]>0.5||bzf==2))
 if(a[int(az)][int(L)]>data[int(j+yj)][int(i+xj)])
 {
 data[int(j+yj)][int(i+xj)]=a[int(az)][int(L)];
// ShowMessage(data1[int(j+yj)][int(i+xj)]);
 }
// else
 // data[int(j+yj)][int(i+xj)]=0;



}
  }
}
}

delete p;
}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button64Click(TObject *Sender)
{
 // int x[17]={255,0,0,192,122,30,166,0,16,252,200,140,254,254,238,212,170},y[17]={255,0,172,192,114,38,252,234,146,244,200,140,172,100,2,142,36},z[17]={255,0,164,254,238,208,168,0,26,100,2,0,172,92,48,254,250};

////

 int x[16]={255,0,198,123,24,165,0,16,255,206,140,255,255,239,214,173},
 y[16]={255,174,195,113,36,255,235,146,247,203,142,173,101,0,142,36},
z[16]={255,165,255,239,214,173,0,24,99,0,0,173,101,0,255,255};

////

 for(int i=0;i<16;i++)
 {

         zfpal[i].rB=z[i];
        zfpal[i].rG=y[i];
        zfpal[i].rR=x[i];
        zfpal[i].rX=0;
    }


  FILE *fp;
    char xs[80];


  for(int k=0;k<1;k++)
     {
     for(int i=0;i<GMS_H;i++)
     {for(int j=0;j<GMS_W;j++)
     {// if(data[i][j]>=15)
    //ShowMessage(data[i][j]);
     // if(data[i][j]>=3)
      data[i][j]=int((data[i][j]+data[i][j+1]+data[i][j-1]+data[i+1][j]+data[i-1][j])/5.);

     //if(data[i][j]>=8)
   // data[i][j]=(data[i][j+1]+data[i][j-1]+data[i+1][j]+data[i-1][j])/4;

     }
     }
     }

 Button65->Click() ;


}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button65Click(TObject *Sender)
{
BMP_fileh BMPh1;
    BMP_infoh BMPh2;
  BMPh1.bfType=19778;
    BMPh1.bfSize=(long)(14+40+256*4+GMS_W*GMS_H);
    BMPh1.bf1=0;
    BMPh1.bf2=0;
    BMPh1.bfOffbits=(long)(40+256*4);

    BMPh2.biSize=40L;
    BMPh2.biWidth=(long)GMS_W;
    BMPh2.biHeight=(long)GMS_H;
    BMPh2.biPlanes=1;//1
    BMPh2.biBitcount=8;// 1(2) 4(16) 8(256) 24(true color)
    BMPh2.biComp=0L;//0 1 2
    BMPh2.biSizeimage=((long)GMS_W*(long)GMS_H);
    BMPh2.biX=(long)GMS_W;
    BMPh2.biY=(long)GMS_H;
    BMPh2.biClrused=0L;
    BMPh2.biClrimp=0L;
    FILE *fp;
     if (ss3.SubString(1,1)!="1")
    {
    ss3=ltp+"QREF\\2.4\\"+ss3+".bmp";
    fp=fopen(ss3.c_str() ,"wb");
     //1文件头            long
    fwrite(&BMPh1.bfType,2,1,fp);
    fwrite(&BMPh1.bfSize,4,1,fp);
    fwrite(&BMPh1.bf1,2,1,fp);
    fwrite(&BMPh1.bf2,2,1,fp);
    fwrite(&BMPh1.bfOffbits,4,1,fp);

    //2位图信息头
    fwrite(&BMPh2.biSize,4,1,fp);
    fwrite(&BMPh2.biWidth,4,1,fp);
    fwrite(&BMPh2.biHeight,4,1,fp);
    fwrite(&BMPh2.biPlanes,2,1,fp);
    fwrite(&BMPh2.biBitcount,2,1,fp);
    fwrite(&BMPh2.biComp,4,1,fp);
    fwrite(&BMPh2.biSizeimage,4,1,fp);
    fwrite(&BMPh2.biX,4,1,fp);
    fwrite(&BMPh2.biY,4,1,fp);
    fwrite(&BMPh2.biClrused,4,1,fp);
    fwrite(&BMPh2.biClrimp,4,1,fp);

    //3颜色信息
       for(int i=0;i<256;i++){
        fwrite(&zfpal[i],sizeof(BMP_rgb),1,fp);
    }
    int xx=0;//偏移量
    for(int i=GMS_H;i>0;i--){
        for(int j=xx;j<GMS_W;j++){
           if(i<6)
           data[i][j]=0;
            if(data[i][j]<5)
            data[i][j]=0;
            fwrite(&data[i][j],1,1,fp);
        }
        for(int j=0;j<xx;j++){
           // if(data[i][j]<6)
            //data[i][j]=0;
          fwrite(&data[i][j],1,1,fp);
        }
    }
    fclose(fp);

bzf=0;
 Image1->Picture->LoadFromFile(ss3.c_str());
  Image1->Picture->SaveToFile(ss3.c_str());
  }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button66Click(TObject *Sender)
{
Timer2->Enabled=true;
Timer1->Enabled=true;
Form1->Visible=false;
 Button6->Click();
 Button17->Click();
 Button21->Click();
 Button26->Click();
 Button38->Click();
    Button36->Click();
  Button40->Click() ;
 Button46->Click() ;
 Button51->Click() ;
 Button56->Click() ;
 Button61->Click() ;
 Button67->Click() ;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button67Click(TObject *Sender)
{

TSearchRec sr;
TDateTime time,t,t10;
String s1,sj;
      String path=lljj+"*_STI_*."+rdz+".*";
      if (FindFirst(path,faAnyFile,sr)==0)
   {
  do
  { sd=sr.Name;
   sj=sd.SubString(16,4)+"-"+sd.SubString(20,2)+"-"+sd.SubString(22,2)+" "+sd.SubString(24,2)+":"+sd.SubString(26,2)+":"+sd.SubString(28,2);
    time=StrToDateTime(sj);
    if(time>time13)
    {time13=time;
    sds=sd;
    ss=sd.SubString(16,4)+"年"+sd.SubString(20,2)+"月"+sd.SubString(22,2)+"日"+sd.SubString(24,2)+"时"+sd.SubString(26,2)+"分";
     s1=sd.SubString(16,4)+"-"+sd.SubString(20,2)+"-"+sd.SubString(22,2)+" "+sd.SubString(24,2)+":"+sd.SubString(26,2)+":00";
        }
  }

   while(FindNext(sr)==0);
     FindClose(sr);
   }

if(time13>time14)
{
  String nian,yue,ri,shi,fen;
   t10=StrToDateTime(s1)+8/24.;
   Word Year,Month,Day,Hour,Me,Mee,Meee;
   DecodeDate(t10,Year,Month,Day);
   DecodeTime(t10,Hour,Me,Mee,Meee);
     nian=IntToStr(Year);
if(Month<10)
yue="0"+IntToStr(Month);
else
yue=IntToStr(Month);
if(Day<10)
ri="0"+IntToStr(Day);
else
ri=IntToStr(Day);
if(Hour<10)
shi="0"+IntToStr(Hour);
else
shi=IntToStr(Hour);
if(Me<10)
fen="0"+IntToStr(Me);
else
fen=IntToStr(Me);
ss=nian+"年"+yue+"月"+ri+"日"+shi+"时"+fen+"分";
time14=time13;
Button68->Click();
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button68Click(TObject *Sender)
{
 Word Year,Month,Day,Hour;
TDate time;
float x8,y8;
FILE *fp,*fp1;
mye  n7;
zbf n8;
String pd,f98;
 short int biao;
////
char hb;
int rb=0,pd1=-1;
double ele, az,L,dh;
int nian,yue,ri,xiaoshi,fenzhong,miao;
 long tt;
float x0=0,y0=0;
 unsigned short Number1;
////
int low,high,jxs,sjs,h=0,zz,a[360][230],db,yjh;
float yjs,lon,lat;
HEADER  hed;
        DESCRIPTION  nn;
        SYMBOLOGY n3;
         onetow n4;
        ifon1 n5;
        cr  mm;
        tagLVPacket n6;
AnsiString ff;
f98="c:\\c.txt";
fp1 = fopen(f98.c_str(),"w");
  fprintf(fp1,"%s",ss);

ff=lljj+sds;
fp = fopen(ff.c_str(),"rb");
fread(&hed,sizeof(hed),1,fp);
fread(&nn,sizeof(nn),1,fp);
radlat=(int)ChangeDWord((unsigned int)(nn.RadarLatitude))*0.001;
           radlon=(int)ChangeDWord((unsigned int)(nn.RadarLongtitude))*0.001;
         nn.VolumeScanDate=ChangeWord((unsigned short)(nn.VolumeScanDate)) ;
GetRadialDate(nn.VolumeScanDate,nian,yue,ri);
        long nTimeofMessage=nn.TimeofMessage2[0]<<24|nn.TimeofMessage2[1]<<16|
                                nn.TimeofMessage2[2]<<8|nn.TimeofMessage2[3];
GetRadialTime(nTimeofMessage*1000,xiaoshi,fenzhong,miao);
if(xiaoshi<8)
{time=StrToDate(IntToStr(nian)+"-"+IntToStr(yue)+"-"+IntToStr(ri))+1;

}
else
time=StrToDate(IntToStr(nian)+"-"+IntToStr(yue)+"-"+IntToStr(ri));
String f90;
f90=DateToStr(time)+" "+IntToStr(xiaoshi)+":"+IntToStr(fenzhong);

                 fread(&n3,sizeof(n3),1,fp);
            n3.nBlockId=(short)ChangeWord((unsigned short)(n3.nBlockId)) ;
                   if(n3.nBlockId==1)
                   {
                                fread(&n4,sizeof(n4),1,fp);
                  n4.NumberOfLayers=(short)ChangeWord((unsigned short)(n4.NumberOfLayers)) ;
                  for(int i=0;i<n4.NumberOfLayers;i++)
                  {
              fread(&n5,sizeof(n5),1,fp);
                long chd=n5.cch[0]<<24|n5.cch[1]<<16|
                                n5.cch[2]<<8|n5.cch[3];
                           long gg=chd;
                             do
                              {
               fread(&n6,sizeof(n6),1,fp);
             n6.PacketCode = (short)ChangeWord((unsigned short)(n6. PacketCode));
                        n6.LengthOfDataBlock = (short)ChangeWord((unsigned short)(n6.LengthOfDataBlock));
                         for(int i=0;i< n6.LengthOfDataBlock;i++)
             { fread(&hb,sizeof(char),1,fp);
             }
             gg=gg-n6.LengthOfDataBlock-4;
         }
         while(gg>0);
         }

          fread(&n3,sizeof(n3),1,fp);
            n3.nBlockId=(short)ChangeWord((unsigned short)(n3.nBlockId)) ;

           fread(&n4,sizeof(n4),1,fp);
           n4. NumberOfLayers=(short)ChangeWord((unsigned short)(n4. NumberOfLayers)) ;

           for(int i=0;i<n4. NumberOfLayers;i++)
           {
            fread(&n7,sizeof(n7),1,fp);
            n7.PageNumber = (short)ChangeWord((unsigned short)(n7.PageNumber));
             n7.LengthOfPage = (short)ChangeWord((unsigned short)(n7.LengthOfPage));
                             for(int i=0;i< n7.LengthOfPage;i++)
             { fread(&hb,sizeof(char),1,fp);

              }


             }

               fread(&n3,sizeof(n3),1,fp);

            n3.nBlockId=(short)ChangeWord((unsigned short)(n3.nBlockId)) ;

             fread(&n8,sizeof(n8),1,fp);
              n8.NumberOfPages=(short)ChangeWord((unsigned short)(n8.NumberOfPages)) ;

           for(int i=0;i<n8.NumberOfPages;i++)
           {   do
                              {
             fread(&biao,sizeof(biao),1,fp);
                               biao=(short)ChangeWord((unsigned short)(biao)) ;
                               if(biao!=-1)
                               {
                               for(int i=0;i<biao;i++)
                               {fread(&hb,sizeof(hb),1,fp);
                               fprintf(fp1,"%c",hb);
                               }
                             }
                               }
                                 while(biao!=-1);

           }

           }
           else
           {
            fread(&n4,sizeof(n4),1,fp);
           n4. NumberOfLayers=(short)ChangeWord((unsigned short)(n4. NumberOfLayers)) ;

           for(int i=0;i<n4. NumberOfLayers;i++)
           {
            fread(&n7,sizeof(n7),1,fp);
            n7.PageNumber = (short)ChangeWord((unsigned short)(n7.PageNumber));
             n7.LengthOfPage = (short)ChangeWord((unsigned short)(n7.LengthOfPage));
                             for(int i=0;i< n7.LengthOfPage;i++)
             { fread(&hb,sizeof(char),1,fp);

              }


             }

               fread(&n3,sizeof(n3),1,fp);

            n3.nBlockId=(short)ChangeWord((unsigned short)(n3.nBlockId)) ;

             fread(&n8,sizeof(n8),1,fp);
              n8.NumberOfPages=(short)ChangeWord((unsigned short)(n8.NumberOfPages)) ;

           for(int i=0;i<n8.NumberOfPages;i++)
           {   do
                              {
             fread(&biao,sizeof(biao),1,fp);
                               biao=(short)ChangeWord((unsigned short)(biao)) ;
                               if(biao!=-1)
                               {
                               for(int i=0;i<biao;i++)
                               {fread(&hb,sizeof(hb),1,fp);
                               fprintf(fp1,"%c",hb);
                               }
                             }
                               }
                                 while(biao!=-1);

           }

           }

             fclose(fp1);
             fclose(fp);
           Button69->Click();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button69Click(TObject *Sender)
{

int pm=0;
FILE *fp,*fp1,*fp2;
char bb[300];
 char zhan[1000],zhan1[1000],zhan2[1000],zhan3[1000];
 float k8,x,y,jl,jiao,x1,y1,lon,lat;
 int nn=0,m4,mmm=0,mm,m5,m6;
AnsiString ff,f98,f3;
PointF(x1,y1,radlon,radlat, 113.697,34.704,500,280,1.);
ff="c:\\c.txt";
f3="c:\\b.txt";
fp = fopen(ff.c_str(),"r");
fp2 = fopen(f3.c_str(),"w");
fscanf(fp, "%s",&bb);
 fprintf(fp2,"%s\n",bb);
 while(!feof(fp))
   {
  fscanf(fp, "%s",&zhan1);

  if(AnsiString(zhan1)=="CELLS")
  {
   fscanf(fp, "%s",&zhan1);
   m4=StrToInt(AnsiString(zhan1));
    }
  if(AnsiString(zhan1)=="(KM)"&&(AnsiString(zhan3)!="20"))
  {
    do
   {mmm++;
   fscanf(fp, "%s",&zhan1);
   if(AnsiString(zhan1)!="STORM")
   {


   do
   {
  fscanf(fp, "%s",&zhan);
   mm=AnsiString(zhan).Length();
   if(AnsiString(zhan).SubString(mm,1)=="/"||AnsiString(zhan)=="NO"||AnsiString(zhan)=="NEW")
     {nn++;
     if(AnsiString(zhan).SubString(mm,1)=="/")
     { m5=AnsiString(zhan).Length();
        jiao=StrToFloat(AnsiString(zhan).SubString(1,(m5-1)));
        fscanf(fp, "%s",&zhan);
     jl=StrToFloat(AnsiString(zhan));
     x=1*jl*sin((180-jiao)*3.1415926/180)+x1;
     y=1*jl*cos((180-jiao)*3.1415926/180)+y1;
     if(nn==1)
     {

     ActToPro(lon,lat,x, y, 113.697,34.704,500, 280, 1);
      fprintf(fp2,"\n%s\n%f %f ",AnsiString(zhan1),lon,lat);
     }
     else if(nn!=2&&nn!=7)
     {
     ActToPro(lon,lat,x, y, 113.697,34.704,500, 280, 1);
      fprintf(fp2,"%f %f ",lon,lat);


    }
     }
     else if(AnsiString(zhan)=="NO")
     { fscanf(fp, "%s",&zhan);


     }


    }
    else
    {
    nn++;
    m5=AnsiString(zhan).Length();
    for(int i=0;i<m5;i++)
    {if(AnsiString(zhan).SubString(i,1)=="/")
      m6=i-1;
    }
     jiao=StrToFloat(AnsiString(zhan).SubString(1,m6));
     jl=StrToFloat(AnsiString(zhan).SubString((m6+2),m5));
     x=1*jl*sin((180-jiao)*3.1415926/180)+x1;
     y=1*jl*cos((180-jiao)*3.1415926/180)+y1;
     if(nn==1)
     {
     ActToPro(lon,lat,x, y, 113.697,34.704,500, 280, 1);
     if(pm!=0)
                 fprintf(fp2,"\n%s\n%f %f ",AnsiString(zhan1),lon,lat);
                 else
                 {pm=1;
                  fprintf(fp2,"%s\n%f %f ",AnsiString(zhan1),lon,lat);
                 }
     }
     else if(nn!=2&&nn!=7)
     {

    ActToPro(lon,lat,x, y, 113.697,34.704,500, 280, 1);
   fprintf(fp2,"%f %f ",lon,lat);

        }
    }

   }
   while(nn<7);  //er
   nn=0;
   }
   }
  while(AnsiString(zhan1)!="STORM");   //di
    
  }
  strcpy(zhan3,zhan1);
  }


  fclose(fp);
  fclose(fp2);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button70Click(TObject *Sender)
{

int n;
n=strlen(ltp.c_str());

if(!DirectoryExists(ltp.SubString(1,(n-1))))//如果路径不存在
{
 ForceDirectories(ltp.SubString(1,(n-1)));  //创建X:\6101\2010//改成这样就可以了
 ForceDirectories(ltp+"cref");
 ForceDirectories(ltp+"ET");
 ForceDirectories(ltp+"v");
 ForceDirectories(ltp+"VIL");
 ForceDirectories(ltp+"QREF");
 ForceDirectories(ltp+"QREF\\0.5");
  ForceDirectories(ltp+"QREF\\1.5");
   ForceDirectories(ltp+"QREF\\2.4");
    ForceDirectories(ltp+"QREF\\3.4");
}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button71Click(TObject *Sender)
{

TSearchRec sr;
    int countMin;
TDateTime time;
///
flj="c:\\龙卷.txt";
fplj=fopen(flj.c_str(),"w");
fprintf(fplj,"%s\n",sxr);
f60="c:\\60.txt";
fp60=fopen(f60.c_str(),"w");
fprintf(fp60,"%s\n",ss8);


///
      String path=lljj+"*_M_*."+rdz+".*",sj,sd;
      if (FindFirst(path,faAnyFile,sr)==0)
   {
  do
  { sd=sr.Name;
   sj=sd.SubString(16,4)+"-"+sd.SubString(20,2)+"-"+sd.SubString(22,2)+" "+sd.SubString(24,2)+":"+sd.SubString(26,2)+":"+sd.SubString(28,2);
    time=StrToDateTime(sj);
   countMin=MinutesBetween(time,time5);

   if(time<=time5&&countMin<6)
   {
        sd1=sd;
        Button37->Click();
   }
  }

   while(FindNext(sr)==0);
     FindClose(sr);
   }

    fclose(fplj);
     fclose(fp60);
}
//---------------------------------------------------------------------------

