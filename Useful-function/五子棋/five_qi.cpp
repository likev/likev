
 CList StepList; 


  struct Step 
    { 
      int  m; //m,n��ʾ��������ֵ 
      int  n; 
      char side; //side��ʾ���ӷ� 
    }; 


   char FiveArea[FIVE_max_LINE][FIVE_MAX_LINE]; 

   CList CountList; 
    class CBoardSituation 
	{ 
       CList  StepList; //ÿһ�����б� 
       char FiveArea[FIVE_MAX_LINE][FIVE_MAX_LINE]; 
       struct Step machineStep;    //�������µ���һ�� 
       double value;  //��������״̬���õ��ķ��� 
	} 

    void MainDealFunction() 
	{ 
        value=��MAXINT; //�Գ�ʼ���ڵ��value��ֵ 
        CalSeveralGoodPlace(currentBoardSituation,CountList); 
/*�ú����Ǹ��ݵ�ǰ������������Ƚϵõ��ȽϺõĿ��Կ��ǵļ�������������
���Ը���ʵ�ʵĵ÷����ѡȡ�����Ƚϸߵļ������棬Ҳ����˵�ڵ�һ��ڵ�ѡ��
��ʱ�����̰���㷨��ֱ���ҳ���Է����Ƚϸߵļ����γɵ�һ��ڵ㣬
Ŀ����Ϊ����������ٶȺͷ�ֹ��ջ����� */
        pos=CountList.GetHeadPosition(); 
        CBoardSituation�� pBoard; 
        for(i=0;ivalue=Search(pBoard,min,value,0); 
        Value=Select(value,pBoard��>value,max);  
  //ȡvalue��pBoard��>value�д�ĸ������ڵ� 
	} 
for(i=0;ivalue)  
//�ҳ���һ���õ���߷ֵ����� 
  { 
    currentBoardSituation=pBoard; 
    PlayerMode=min; //��ǰ���ӷ���Ϊ�� 
    Break; 
  } 
} 

   /* ���ж���Search�����ı�ʾ���£�ʵ���Ϻ��ĵ��㷨��һ����֦���̣�
   ���������������������ص��ĸ�����Ϊ����1����ǰ����������2����ǰ�����ӷ���
   �����ǻ���(max)��������(min)����3�����ڵ��ֵoldValue��
   ��4����ǰ���������depth�� */

       double Search(CBoardSituation�� 
       board,int mode,double oldvalue,int depth) 
	   { 
            CList  m_DeepList; 
           if((deptholdvalue)==    TRUE) 
		   { 
            if(mode==max) 
            value=select(value,search(successor 
             Board,min,value,depth��1),max); 
            else 
            value=select(value,search(successor 
            Board,max,value,depth��1),min); 
		   } 
           return value; 
  
           else 
		   { 
             if ( goal(board)<>0)
             //����goal(board)<>0��ʾ�Ѿ����Էֳ�ʤ�� 
             return goal(board); 
             else 
             return evlation(board); 
		   } 
	   } 


double Select(double a,double b,int mode) 
{ 
  if(a>b ���� mode==max)&brvbar;&brvbar; (a< b && mode==min) 
return a; 
  else 
return b; 
} 
