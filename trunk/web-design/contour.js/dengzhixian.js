

//-------------- ��Ȩƽ����ֵ gdcla.js --------------
function WgNc(){

   this.DataX;    //ԭʼ��X��������
   this.DataY;
   this.DataZ;

   this.NX=10;//���ȣ��ֳ�10��
   this.NY=10;//���ȣ�
   this.SetN=WGSetN;            //���þ���

   this.MinX=0;            //���η�Χ
   this.MaxX=0;
   this.MinY=0;            
   this.MaxY=0;
   this.SetArea=SetArea;
   
   this.coordx =new Array();        //�����X��������
   this.coordy =new Array();
   this.valueZ =new Array();        //���Ҫ��ֵ

   this.ExData=GDExData;        //���Ŀ������

   this.r=100;            //�����뾶
   this.s    = new Array();        //�����������

   this.ExWgXY=ExWgXY;        //���ɸ��λ������coordx��coordy
   this.findZ=findZ;
   

}
function SetArea(minx,maxx,miny,maxy){
   this.MinX=minx;
   this.MaxX=maxx;
   this.MinY=miny;
   this.MaxY=maxy;

}
function WGSetN(nx,ny){    //���þ���
   this.NX=nx;    
   this.NY=ny;    
}
function ExWgXY(){    // 7:55 06-8-20 �޸ģ���Ϊ10��    

   var widthX=this.MaxX-this.MinX;    //X�ܳ�
   var dtX=widthX/this.NX;    //x�γ�

   var widthY=this.MaxY-this.MinY;    //Y�ܳ�
   var dtY=widthY/this.NY;    //y�γ�

   var fy=this.NY+1;
   var fx=this.NX+1;
   for(var i=0;i<fy;i++){
       for(var j=0;j<fx;j++){
           this.coordx[fx*i+j]=(this.MinX)+dtX*j;
           this.coordy[fx*i+j]=(this.MinY)+dtY*i;            
       }    
   }    

}
function GDExData(DataZ,DataX,DataY){        //���Ŀ������
       
       this.coordx.length=0;    //����֮ǰ������
       this.coordy.length=0;
       this.valueZ.length=0;

       this.DataZ=DataZ;
       this.DataX=DataX;
       this.DataY=DataY;
       
with(this){
       ExWgXY();//���ɸ��λ������coordx��coordy
       r=Math.sqrt(7*((MaxX-MinX)*(MaxY-MinY)/((DataZ.length)*(Math.PI))));    //ȷ�������뾶
       
       var valueZlen=coordx.length;    //������ coordx ��������valueZ

       for(var i=0;i<valueZlen;i++){    //valueZѭ����ֵ
           var dt1=0;dt2=0;

           
           findZ(i);    //�����Ƚ�Ԫ��
           
           
           var tmlen=s.length;
           for(var j=0;j<tmlen;j++){
               var d=(DataX[s[j]]-coordx[i])*(DataX[s[j]]-coordx[i])+(DataY[s[j]]-coordy[i])*(DataY[s[j]]-coordy[i])+0.0001; //d��ƽ��d2=(xi-x)2+(yi-y)2                    
               dt1+=DataZ[s[j]]/d;    //d����Ϊ0,��һ΢����
               dt2+=1/d;    
           }
           valueZ[i]=dt1/dt2;

       }
       
}      
}
function findZ(valueZ){
with(this){
   
   var js=0;    //�����������
   s.length=0;
   //sjs=0;        //��ѭ���ж�
   while((js<4)||(js>9)){

       //sjs++;
       //if(sjs>(MaxX*2)) break;//����뾶��ѭ������>MaxX ���˳�

       var tmlen=DataZ.length;    
       for(var i=0;i<tmlen;i++){

           var d=(DataX[i]-coordx[valueZ])*(DataX[i]-coordx[valueZ])+(DataY[i]-coordy[valueZ])*(DataY[i]-coordy[valueZ]);
           d=Math.sqrt(d);        //�õ���������
           
           if(r>=d){        //����ڰ뾶��
               s[js]=i;    //������Ƶ�λ��
               js++;                
           }            
           if(js>9){        //������Χ >9��
               js=0;
               s.length=0;    //�������
               r--;
               i=-1;        //���Ϊ r--
               break;      //����ѭ��
           }
       }
       
       if((js<4)&&(i>=0)){        //�Ա���<4 ����    
           js=0;
           s.length=0;    //�������
           r++;
       }
   }        
}
   
}
//------------------ ����B�������� bsline.js----------------------------------------------
function BeLine(){


   this.N=10;//���ȣ�ÿ�η�Ϊ10��
   this.SetN=BSSetN;            //���þ���
   
   this.coordx =new Array();;        //�����X��������
   this.coordy =new Array();

   this.ExData=ExData;        //���Ŀ������


   this.DataExX =new Array();    //���Ƶ�X��������
   this.DataExY =new Array();

   this.AddDataEx=AddDataEx;    //��ԭʼ������������ݣ����ɿ��Ƶ�����


}
function BSSetN(n){    //���þ���,��һ�η�Ϊ����С��
   this.N=n;    
}
function AddDataEx(DataX,DataY){    //ǰ�����Ӷ������߶�(������)

   
   var tmX=new Array();//������ʱ������չX����
   var tmY=new Array();        

   tmX[0]=2.0*DataX[0]-DataX[1];//Ҫ��������鿪ͷ��X����
   tmY[0]=2.0*DataY[0]-DataY[1];

   this.DataExX=tmX.concat(DataX);
   this.DataExY=tmY.concat(DataY);
   
   var len=(this.DataExX).length;//�µ����鳤��    
   
   tmX[0]=2.0*(this.DataExX[len-1])-this.DataExX[len-2];//Ҫ����������β��X����
   tmY[0]=2.0*(this.DataExY[len-1])-this.DataExY[len-2];

   this.DataExX=(this.DataExX).concat(tmX);
   this.DataExY=(this.DataExY).concat(tmY);
   
}
function ExData(DataX,DataY){        //���������������

      this.AddDataEx(DataX,DataY);    //ԭʼ����ǰ������������(�Ӷ������߶�)
   
      var A0,A1,A2,A3;        //�ֶλ�������(X������)����:
      var B0,B1,B2,B3;        //Y���������:
   
      var dt=1/(this.N);            //dt�ָ�Ϊʮ�ݻ��ƹ⻬���ߵķָ����ֵ        
      var IP=DataX.length-1;        //������-1�����ߵĶ���,�ĸ�����ȷ��һ�����߶�.    

      with(this){        
      for(var i=0;i<IP;i++){    //IPΪ���ߵĶ���

       A0=(DataExX[i]+4.0*DataExX[i+1]+DataExX[i+2])/6.0;
       A1=-(DataExX[i]-DataExX[i+2])/2.0;
       A2=(DataExX[i]-2.0*DataExX[i+1]+DataExX[i+2])/2.0;
       A3=-(DataExX[i]-3.0*DataExX[i+1]+3.0*DataExX[i+2]-DataExX[i+3])/6.0;
       B0=(DataExY[i]+4.0*DataExY[i+1]+DataExY[i+2])/6.0;
       B1=-(DataExY[i]-DataExY[i+2])/2.0;
       B2=(DataExY[i]-2.0*DataExY[i+1]+DataExY[i+2])/2.0;
       B3=-(DataExY[i]-3.0*DataExY[i+1]+3.0*DataExY[i+2]-DataExY[i+3])/6.0;
                   
       var T1=0,T2=0,T3=0;

          for(var j=0;j<N+1;j++){    //ȷ��һ�����ߣ���10С�� 11����
           T1=dt*j;     //���
           T2=T1*T1;     //���ƽ��
           T3=T1*T2;     //�������

           coordx[i*N+j]=(A0+A1*T1+A2*T2+A3*T3);
           coordy[i*N+j]=(B0+B1*T1+B2*T2+B3*T3);
           }
      }
      }
}
//-------------------------------------- ��ֵ�� dline.js----------------------------------------------

function qxz(){    //��ֵ��
   this.ax=new Array();    //x����
   this.ay=new Array();    

   this.bx=new Array();    //��˳��x����
   this.by=new Array();    

   this.title="";        //ֵ    
}

function GZ(wgnc){    //������    ����������Ŀ�ꡢ��ֵ������

   this.coordx;    //ԭʼ��X��������
   this.coordy;
   this.valueZ;

   this.NX;    //���ȣ��ֳ�10��
   this.NY;

   this.SetN=SetN;        //���þ���

   this.addwg =     //��������
		function(wgnc){
		   this.coordx =wgnc.coordx;    //ԭʼ��X��������
		   this.coordy =wgnc.coordy;
		   this.valueZ =wgnc.valueZ;

		   this.NX=wgnc.NX;//���ȣ��ֳ�10��
		   this.NY=wgnc.NY;
		}

   this.Z=40;        //��ֵ�� 80��90��
   
   this.Dline=Dline;
   this.outDzx =     //����ֵ��
		function(myaz){
			with(this){
			   oa.length=0;    //����֮ǰ������
			   var myazlength=myaz.length;
			   for(var i=0;i<myazlength;i++){
				   Dline(myaz[i]);
				   GetRect();
				   GetNRect();
				   
				   LineEx();
				   LineExB();
			   }    
			   var bl=new BeLine();        //������
			   bl.SetN(10);
			   var oalength=oa.length;
			   for(var i=0;i<oalength;i++){    
			   
				   bl.coordx.length=0;
				   bl.coordy.length=0;
			   
				   bl.ExData(oa[i].ax,oa[i].ay);
				   var blcoordxlength=(bl.coordx).length;
				   for(var j=0;j<blcoordxlength;j++){
					   oa[i].bx[j]=bl.coordx[j];
					   oa[i].by[j]=bl.coordy[j];            
				   }

			   }        
			}    
		}

   this.up     =1;    //����
   this.down =2;    //����
   this.left =3;    //����
   this.right=4;    //����
   this.GetNext=GetNext;

   
   this.Rect = new Array();    //��߽�������
   this.GetRect=GetRect;    //�õ���߽�������

   this.NRect= new Array();    //�����ڽ�������,ˮƽ
   this.GetNRect=GetNRect;    //�õ������ڽ�������    

   
   this.x=0;            //��������
   this.y=0;
   this.x0=0;            //ǰһ��������    
   this.y0=0;
   this.a=0;            //�߶�
   this.b=0;
   
   this.sta=0;    //���

   this.oa = new Array(); //������
   
   
   this.ifxj=ifxj;    //�ж��Ƿ��ཻ
   this.GetJD=GetJD;    //�õ���������


   this.FromN=FromN;
   this.FromS=FromS;
   this.FromW=FromW;
   this.FromE=FromE;
   this.LineEx=LineEx;
   this.LineExB=LineExB;
   this.dela=dela;
   this.determine_direction=determine_direction;    
   
}

function LineExB(){    //�պ�����
with(this){

   
   var k=oa.length;
   var q=0;        
   var ex1=1;
   var ex2=1;


   while(NRect.length){    //��֧
       

       q=0;    //��Ϊ��ˮƽ�ߣ��������ϱ��߽��룬�����ܶ����˱պ����ߣ����뿪����    
       ex1=1;
       
       GetJD(NRect[0],GetNext(NRect[0],right));
       
       var j=0;    //����    
       oa[k]=new qxz();
       oa[k].ax[j]=x;    
       oa[k].ay[j]=y;
       oa[k].title=Z;
               
       j++;    
       x0=x;y0=y;

       var bjx=x;//���x
       var bjy=y;

       a=NRect[0];
       dela(a);//ɾ��a��
       
       var bja=a;    //���a
       tmpa=1;
       
       while((tmpa>=0)&&(tmpa!=bja)){    //���ҵ���һ�㲢�Ҹõ㲻�����

           if(j>((valueZ.length)/2)){delete oa[k]; k--; (oa.length)--; break;}    //��ֹѭ����ɾ������

           switch(determine_direction(q,ex1,ex2)){               //�жϽ����ĸ�����
               case '��':tmpa=FromN(a);break;//�õ��µ�����x,y,�µ��ཻ�߶�a,b    
               case '��':tmpa=FromS(a);break;    
               case '��':tmpa=FromW(a);break;    
               case '��':tmpa=FromE(a);break;    
           }
           if(tmpa<0){delete oa[k]; k--; (oa.length)--; break;};//����Ҳ�����һ�㣬ɾ������        
           if(tmpa!=bja){ //������պ�    
                       
               
               //ɾ��a��
               dela(a);            

               //Ϊ��һ���жϽ����ĸ�����
               if(coordx[a]==coordx[b])q=1;    
               if(coordy[a]==coordy[b])q=0;
               ex1=x-x0;
               ex2=y-y0;
               
               x0=x;//��¼ǰһ������
               y0=y;

               oa[k].ax[j]=x;    
               oa[k].ay[j]=y;
               
               j++;    //����һ��
           }
       }
       if(tmpa==bja){        //��պϣ�����β����
           oa[k].ax[j]=bjx;    
           oa[k].ay[j]=bjy;            
       }
       k++;    //����һ���պ�����
   
   }
}
}
function LineEx(){    //������
with(this){

   var q=0;    
   var ex1=1;
   var ex2=1;

   
   var k=oa.length;
   var tmpb=0;    //��ʼ��b    

   while(Rect.length){    //��֧

       
       //�õ�q,ex1,ex2        14:34 06-8-21
       
       tmpU=GetNext(Rect[0],up);
       tmpD=GetNext(Rect[0],down);
       tmpL=GetNext(Rect[0],left);
       tmpR=GetNext(Rect[0],right);

       if(tmpU<0&&tmpR>0){    //��
           if(ifxj(Rect[0],tmpR)){
               q=0;ex2=-1;tmpb=tmpR;
           }
       }        
       if(tmpD<0){    //��
           q=0;ex2=1;tmpb=tmpR;
       }        
       if(tmpL<0&&tmpR>0){    //��
           if(ifxj(Rect[0],tmpD)){
               q=1;ex1=1;tmpb=tmpD;
           }
       }        
       if(tmpR<0){    //��
           q=1;ex1=-1;tmpb=tmpD;
       }        
       

       GetJD(Rect[0],tmpb);

       var j=0;    //����    
       oa[k]=new qxz();
       oa[k].ax[j]=x;    
       oa[k].ay[j]=y;
       oa[k].title=Z;
       j++;
       x0=x;y0=y;
       
       a=Rect[0];
       dela(a);//ɾ��a��
       
       tmpa=1;
       while(tmpa>=0){        //����ҵ���һ��            

           if(j>((valueZ.length)/2)){ delete oa[k]; k--; (oa.length)--; break;}    //��ֹѭ����ɾ������

           switch(determine_direction(q,ex1,ex2)){        //�жϽ����ĸ�����
               case '��':tmpa=FromN(a);break;//�õ��µ�����x,y,�µ��ཻ�߶�a,b    
               case '��':tmpa=FromS(a);break;    
               case '��':tmpa=FromW(a);break;    
               case '��':tmpa=FromE(a);break;    
           }
           
           if(tmpa>=0){    //����ҵ���һ��                
               
               //ɾ��a��
               dela(a);            
               //Ϊ��һ���жϽ����ĸ�����
               if(coordx[a]==coordx[b])q=1;    
               if(coordy[a]==coordy[b])q=0;
               ex1=x-x0;
               ex2=y-y0;
               
               x0=x;//��¼ǰһ������
               y0=y;

               oa[k].ax[j]=x;    
               oa[k].ay[j]=y;
               
               j++;    //����һ��
           }    
       }
   k++;    //����һ��������    
   }    
}
}
function dela(ia){    //ɾ��aԪ��
with(this){
   var leng=Rect.length;
   for(var i=0;i<leng;i++){
       if(Rect[i]==ia){

           Rect[i]=Rect[leng-1];
           Rect.length--;    
           return 1;
       }
   }
   var leng=NRect.length;
   for(var i=0;i<leng;i++){
       if(NRect[i]==ia){
           NRect[i]=NRect[leng-1];
           NRect.length--;    
               
           return 1;
       }
   }
   return 0;
}    
}

function determine_direction(q,ex1,ex2){    //a,b,���㣬ǰһ��

   if(q==1){
       if(ex1>0){    //��
           return "��";            
       }else{        //��
           return "��";            
       }
   }else{
       if(ex2>0){    //��
           return "��";                        
       }else{        //��
           return "��";            
       }
   }
}

function FromN(ka){    //�ӱ��߽���
with(this){    
    a=ka;
    b=GetNext(a,down);    //(W)
    if(ifxj(a,b)){        //�ж��Ƿ��ཻ
       GetJD(a,b);    //�õ���������
       return a;    //�˳�
    }    

    a=b;            //(S)
    b=GetNext(a,right);
    if(ifxj(a,b)){        
       GetJD(a,b);    
       return a;    
    }    

    a=b;
    b=GetNext(a,up);    //(E)
    tmp=a;a=b;b=tmp;
    if(ifxj(a,b)){        
       GetJD(a,b);    
       return a;    
    }    
   
    return -1;
}
}
function FromS(ka){    //���ϱ߽���
with(this){    
    a=ka;
    b=GetNext(a,up);    //(W)
    tmp=a;a=b;b=tmp;
    if(ifxj(a,b)){        
       GetJD(a,b);    
       return a;    
    }    
           
    b=GetNext(a,right);    //(N)
    if(ifxj(a,b)){        
       GetJD(a,b);    
       return a;    
    }    

    a=b;
    b=GetNext(a,down);    //(E)    
    if(ifxj(a,b)){        
       GetJD(a,b);    
       return a;    
    }    
   
    return -1;
}    
}
function FromW(ka){    //�����߽���
with(this){    
    a=ka;
    b=GetNext(a,right);    //(N)
    if(ifxj(a,b)){        
       GetJD(a,b);    
       return a;    
    }    

    a=b;            //(E)
    b=GetNext(a,down);
    if(ifxj(a,b)){        
       GetJD(a,b);    
       return a;    
    }    

    a=b;
    b=GetNext(a,left);    //(S)
    tmp=a;a=b;b=tmp;
    if(ifxj(a,b)){        
       GetJD(a,b);    
       return a;    
    }    
   
    return -1;
}    
}
function FromE(ka){    //�Ӷ��߽���
with(this){    
    a=ka;
    b=GetNext(a,left);    //(N)
    tmp=a;a=b;b=tmp;
    if(ifxj(a,b)){        
       GetJD(a,b);    
       return a;    
    }    

               
    b=GetNext(a,down);    //(W)
    if(ifxj(a,b)){        
       GetJD(a,b);    
       return a;    
    }    

    a=b;
    b=GetNext(a,right);    //(S)
   
    if(ifxj(a,b)){        
       GetJD(a,b);    
       return a;    
    }    
   
    return -1;
}    
}

function GetJD(ka,kb){    //�õ���������

   var xa=this.coordx[ka];
   var ya=this.coordy[ka];
   var fa=this.valueZ[ka];

   var xb=this.coordx[kb];
   var yb=this.coordy[kb];
   var fb=this.valueZ[kb];

   var z=this.Z;
   
   this.x=xa+((z-fa)/(fb-fa))*(xb-xa);
   this.y=ya+((z-fa)/(fb-fa))*(yb-ya);

}
function ifxj(ka,kb){    //�ж��Ƿ��ཻ
with(this){
   if((valueZ[ka]-Z)*(valueZ[kb]-Z)<0) return 1;
   return 0;
}        
}

function GetNRect(){    //�õ������ڽ���
with(this){
   var m=0;            //�ཻ�����
   var len=(NX+1)*(NY+1)-(NX+1);
   for(var i=NX+1;i<len;i+=NX+1){
       for(var j=i;j<i+NX;j++){
           if(ifxj(j,j+1)){
               NRect[m]=j;
               m++;
           }
       }        
   }    
}
}

function GetRect(){    //�õ����α߽���    
with(this){


   var j=0;                //�ཻ�����
   var ka=0;                //�ϱ�->
   var kb=1;    
   while(kb>=0){                
       if(ifxj(ka,kb)){
           Rect[j]=ka;
           j++;
       }
       ka=kb;
       kb=GetNext(ka,right);    
   }
   
   kb=GetNext(ka,up);            //����
   while(kb>=0){                
       if(ifxj(ka,kb)){
           Rect[j]=kb;
           j++;
       }
       ka=kb;
       kb=GetNext(ka,up);    
   }

   ka=0;                    //����
   kb=GetNext(ka,up);            
   while(kb>=0){                
       if(ifxj(ka,kb)){
           Rect[j]=kb;
           j++;
       }
       ka=kb;
       kb=GetNext(ka,up);    
   }

   kb=GetNext(ka,right);            //����
   while(kb>=0){                
       if(ifxj(ka,kb)){
           Rect[j]=ka;
           j++;
       }
       ka=kb;
       kb=GetNext(ka,right);    
   }
}
}

function GetNext(i,fd){        //�����±����
with(this){
   var j=0;
   if(fd==down){
       j=i-(NX+1);        //��
       if(j<0)j=-1;        //��ֹ����
   }
   if(fd==up){
       j=i+(NX+1);        //��
       if(j>(NX+1)*(NY+1)-1)j=-1;        
   }
   if(fd==left){
       if(i%(NX+1)==0)j=-1;
       else j=i-1;        //��
       
   }
   if(fd==right){
       j=i+1;            //��
       if(j%(NX+1)==0)j=-1;
   }
   return j;
}
}

function SetN(nx,ny){    //���þ���
   this.NX=nx;    
   this.NY=ny;    
}
function Dline(z){    //��ֵ��
with(this){
   this.Z=z;
   var leng=valueZ.length;
   for(var i=0;i<leng;i++){
       if(valueZ[i]==z)valueZ[i]=z+0.00001;
   }
}
}
//---------------------------------------------��ֱ�߽��� ---------------------------------------------

function    WeatherChart(DAViewer){    //ͼ���� ��ͼ����

   this.DAViewer=DAViewer;
   this.lib = DAViewer.PcoordxelLibrary;  
   //�õ�DAStatics Class

   this.face= this.lib.NewDrawingSurface();
   //�õ�DADrawingSurface Class
   
   this.faceTs= this.lib.NewDrawingSurface();

   this.run=run;
}
function run(){

   var TsImg=this.faceTs.Image;
   TsImg=TsImg.Opacity(0.2);
   TsImg=TsImg.Transform(this.lib.Translate2(-(parseInt(DAViewer.style.width)/2),-parseInt(DAViewer.style.height)/2));
   
   var LineImg=this.face.Image;
   LineImg=LineImg.Transform(this.lib.Translate2(-(parseInt(DAViewer.style.width)/2),-parseInt(DAViewer.style.height)/2));

   //var DtImg=this.lib.ImportImage("dt.gif");//������ͼ��͸��
   //var aImg= new Array(LineImg,DtImg,TsImg);

   var aImg= new Array(LineImg,TsImg);

   this.DAViewer.Image=this.lib.OverlayArray(aImg);

   this.DAViewer.Start();
   

}
//------------------------------------------------------------------------------------


window.top.moveTo(0,0);


//Ҫ��ֵ
var CityName=new Array(231,230,264,249,251,240,218,265,255,209,258,279,266,288,251,225,311,277,297,257,305,313,222,290,284,273,225,208,277,298,247,314,220,286,315,217,305,210,234,219,287,270,294,237,199,287,264);
//Ҫ�ص�x����
var CityX=new Array(427.1,626.08,710.22,445.93,496.5,555.28,379.54,583.91,281.1,459.36,340.56,777.05,263.13,192.39,255.38,272.84,145.16,375.63,282.73,360.69,202.39,107.08,360.02,339.91,636.87,771.85,550.74,446,401.62,666.07,550.48,90.34,446.69,369.49,72.55,497.91,240.52,346.1,485.87,398.34,683.04,737.72,234.96,633.38,376.5,290.07,422.73);
//Ҫ�ص�y����
var CityY=new Array(449.84,415.18,363.8,483.75,444.46,419.27,503.27,491.52,356.76,233.58,243.3,285.6,329.76,289.38,485.02,456.18,207.84,117.17,135.77,180.28,156.02,126.3,313.84,114.55,157.37,210.49,268.8,204.53,80.76,102.95,526.19,349.25,323.51,27.23,212.45,284.2,49.96,403.58,400.88,287.23,34.26,299.52,239.37,434.4,377.03,77.56,112.32);

var MaxZ=315;
var MinZ=199;
var myaz=new Array(220,230,240,250,260,270,280,290,300,310);//��ֵ��ֵ    

//---------------------------------------------
var mywg= new WgNc(); //��������Ŀ��

mywg.SetArea(20,780,20,530);//����������Сx���꣬���x���꣬��Сy���꣬���y����

mywg.SetN(25,20);//���ø�� ��/25 ��/20

mywg.ExData(CityName,CityX,CityY);    //����

var MyLine = new GZ();//���ɵ�ֵ�߶���

MyLine.addwg(mywg);//������

MyLine.outDzx(myaz);//�����ֵ��

//---------------------------------------------

var myg=new WeatherChart(DAViewer);//��������ͼ�����

//--------------- ��ɫ�� --------------------
myg.faceTs.BorderDashStyle(0);
var wgk=(mywg.MaxX-mywg.MinX)/(mywg.NX)+1;
var wgg=(mywg.MaxY-mywg.MinY)/(mywg.NY)+1;

var cdt=0.5/(MaxZ-MinZ+0.0001);

for(var i=0;i<(mywg.valueZ).length;i++){

   var tmp=0.5-(mywg.valueZ[i]-MinZ)*cdt;
   myg.faceTs.FillColor(myg.lib.ColorHsl(tmp,1.0,1.0/2+0.1));
   myg.faceTs.Rect(mywg.coordx[i]-wgk/2,mywg.coordy[i]-wgg/2,wgk,wgg);    
}
//-------------- ��Ҫ��ֵ----------------------
var fontsvalueZe=10;
myg.face.Font("����_GB2312",fontsvalueZe,0,0,0,0);
myg.face.BorderDashStyle(0);
myg.face.FillColor(myg.lib.blue);
var DZlength=CityName.length;
for(var i=0;i<DZlength;i++){    //����Ҫ��
   var zl=CityName[i]/10;
   if(parseInt(zl,10)==zl) zl=zl+".0";
   else zl=zl+"";
   var zlen=zl.length;
   myg.face.Text(zl,CityX[i]-(zlen*fontsvalueZe)/4-zlen,CityY[i]+fontsvalueZe+6-1);
}
//------------ ����ֵ�� ------------------------
var dtdj=40;    
myg.face.LineColor(myg.lib.ColorRgb255(255,0,0));    
myg.face.LineWidth(1);    
with(MyLine){
var oalength=oa.length;
var k=1;
for(var i=0;i<oalength;i++){
   var oabxlength=(oa[i].bx).length-1;
   
   for(var j=0;j<oabxlength;j++){
       if((k*dtdj)>(oa[i].bx.length-1)) k=1;
       if((j<(k*dtdj-4))||(j>(k*dtdj+3)))    
       myg.face.Line(oa[i].bx[j],oa[i].by[j],oa[i].bx[j+1],oa[i].by[j+1]);            
   }
   k++;
}
}
var fontszie=12;
myg.face.BorderDashStyle(0);
myg.face.Font("����_GB2312",fontszie,0,0,0,0);
myg.face.FillColor(myg.lib.ColorRgb255(255,0,0));    
var oalength=(MyLine.oa).length;    
var j=1;

for(var i=0;i<oalength;i++){

   var zl=(MyLine.oa[i].title)/10;
   if(parseInt(zl,10)==zl) zl=zl+".0";
   else zl=zl+"";
   var zlen=zl.length;

   if((j*dtdj)>(MyLine.oa[i].bx.length-1))j=1;
   myg.face.Text(zl,MyLine.oa[i].bx[j*dtdj]-fontszie*zlen/4,MyLine.oa[i].by[j*dtdj]+fontszie/2);    
   j++;
}

//---------------------------------------
myg.face.BorderDashStyle(0);
myg.face.FillColor(myg.lib.white);
myg.face.Rect(0,0,20,550);
myg.face.Rect(0,0,800,20);
myg.face.Rect(800-20+1,20,20,550);
myg.face.Rect(0,550-20+1,800,20);

myg.run();
window.resvalueZeTo(850,600);
wait.style.display="none";