
 CList StepList; 


  struct Step 
    { 
      int  m; //m,n表示两个坐标值 
      int  n; 
      char side; //side表示下子方 
    }; 


   char FiveArea[FIVE_max_LINE][FIVE_MAX_LINE]; 

   CList CountList; 
    class CBoardSituation 
	{ 
       CList  StepList; //每一步的列表 
       char FiveArea[FIVE_MAX_LINE][FIVE_MAX_LINE]; 
       struct Step machineStep;    //机器所下的那一步 
       double value;  //该种盘面状态所得到的分数 
	} 

    void MainDealFunction() 
	{ 
        value=－MAXINT; //对初始根节点的value赋值 
        CalSeveralGoodPlace(currentBoardSituation,CountList); 
/*该函数是根据当前的盘面情况来比较得到比较好的可以考虑的几个盘面的情况，
可以根据实际的得分情况选取分数比较高的几个盘面，也就是说在第一层节点选择
的时候采用贪婪算法，直接找出相对分数比较高的几个形成第一层节点，
目的是为了提高搜索速度和防止堆栈溢出。 */
        pos=CountList.GetHeadPosition(); 
        CBoardSituation＊ pBoard; 
        for(i=0;ivalue=Search(pBoard,min,value,0); 
        Value=Select(value,pBoard－>value,max);  
  //取value和pBoard－>value中大的赋给根节点 
	} 
for(i=0;ivalue)  
//找出那一个得到最高分的盘面 
  { 
    currentBoardSituation=pBoard; 
    PlayerMode=min; //当前下子方改为人 
    Break; 
  } 
} 

   /* 其中对于Search函数的表示如下：实际上核心的算法是一个剪枝过程，
   其中在这个搜索过程中相关的四个参数为：（1）当前棋局情况；（2）当前的下子方，
   可以是机器(max)或者是人(min)；（3）父节点的值oldValue；
   （4）当前的搜索深度depth。 */

       double Search(CBoardSituation＆ 
       board,int mode,double oldvalue,int depth) 
	   { 
            CList  m_DeepList; 
           if((deptholdvalue)==    TRUE) 
		   { 
            if(mode==max) 
            value=select(value,search(successor 
             Board,min,value,depth＋1),max); 
            else 
            value=select(value,search(successor 
            Board,max,value,depth＋1),min); 
		   } 
           return value; 
  
           else 
		   { 
             if ( goal(board)<>0)
             //这里goal(board)<>0表示已经可以分出胜负 
             return goal(board); 
             else 
             return evlation(board); 
		   } 
	   } 


double Select(double a,double b,int mode) 
{ 
  if(a>b ＆＆ mode==max)&brvbar;&brvbar; (a< b && mode==min) 
return a; 
  else 
return b; 
} 
