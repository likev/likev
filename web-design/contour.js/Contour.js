/*      网格点标识如下:

(i+1,j) ·---------·(i+1,j+1)
		|         |
		|         |
		|         |
		|         |
 (i,j)  ·---------· (i,j+1)

  i:表示行号(向上增加)
  j:表示列号(向右增加)
  标识一个网格交点时，行号在前，列号在右，如：(i,j)
*/

function Contour(initArgument){

	var gridData, gridRows = 0, gridCols = 0;
	var contourLevel, cur_follow_value;
	
	
	var edgeInfoX, edgeInfoY, edgeRows = 0, edgeCols = 0, Excursion=0.001;
	
	var now_iso_line , all_iso_line = [];
	var xMin, deltX, yMin, deltY;
	
//----------------------------------------	
	this.setGridData = function(data){
		gridData = data; //[ [{x0,y0,value00},{x0,y1,value01},{x0,y2,value02}],
						//	 [{x1,y0,value10},{x1,y1,value11},{x1,y2,value12}] ]
		
		gridRows = gridData.length;
		if(gridRows) gridCols = gridData[0].length;
		
		if(gridRows>1 && gridCols > 1){
			xMin = gridData[0][0].x;
			yMin = gridData[0][0].y;
			deltX = gridData[1][0].x - gridData[0][0].x;
			deltY = gridData[0][1].y - gridData[0][0].y;
		}
		
		edgeInfoX = [];
		edgeInfoY = [];
		edgeRows = gridRows - 1;
		edgeCols = gridCols - 1;
	}
	
	this.setGridData(initArgument);

	this.setContourLevel = function(level){
		contourLevel = level;
	}
	
	this.track = function(){
		for (var i = 0; i < contourLevel.length; i++){
			cur_follow_value = contourLevel[i];

			interpolate_tracing_value(); //扫描并计算纵、横边上等值点的情况

			tracing_non_closed_contour();  //追踪开等值线

			tracing_closed_contour();    //追踪封闭等值线
		}
		
		return all_iso_line;
	}
	
//----------------------------------------- 
	var beql = function(a,b){
		if(Math.abs(a,b) < 10E-9 )
			return true;
		else
			return false;
	}
//扫描并计算纵、横边上等值点的情况
	var interpolate_tracing_value = function(){
		
		function interpolate_xy(edge, isHorizon){
			var nrow = edgeRows, ncol = edgeCols;
			
			if(isHorizon) nrow++;
			else ncol++;
			
			//扫描每一条边
			for (var i = 0; i < nrow; i++){
				edge[i] = [];
				for (var j = 0; j < ncol; j++){
					edge[i][j] = {};
					
					var h0, h1;       //计录一条边上的两个值
					h0 = gridData[i][j].value;
					if(isHorizon){
						//x边的端点
						h1 = gridData[i][j + 1].value;
					}else{
						h1 = gridData[i + 1][j].value;
					}

					if (beql(h0, h1))
					{
						edge[i][j].rate = -2.0;
						edge[i][j].have_iso_point = false;
					}
					else
					{
						var flag = (cur_follow_value - h0) * (cur_follow_value - h1);

						if (flag > 0) //同时大于或小于两端点
						{
							edge[i][j].rate = -2.0;
							edge[i][j].have_iso_point = false;
						}
						else if (flag < 0) //在两点之间
						{
							edge[i][j].rate = (cur_follow_value - h0) / (h1 - h0);
							edge[i][j].have_iso_point = true;
						}
						else //与其中一个相等
						{
							//修正
							if (beql(cur_follow_value, h0))
								h0 += Excursion;
							else
								h1 += Excursion;

							edge[i][j].rate = (cur_follow_value - h0) / (h1 - h0);

							if (edge[i][j].rate < 0 || edge[i][j].rate > 1)
								edge[i][j].have_iso_point = false;
							else
								edge[i][j].have_iso_point = true;
						}
					}
				}
			}
		}
		
		interpolate_xy(edgeInfoX,true);
		interpolate_xy(edgeInfoY,false);
		
		for(var i=0; i<edgeRows; i++){
			for(var j=0; j<edgeCols; j++){
				log('('+i+','+j+'):' + edgeInfoX[i][j].have_iso_point+ ' '+ edgeInfoX[i][j].rate );
			}
			log('<br>');
		}
	}

	function IsoPointPos(_row, _col, _isHorizon){
		this.row = _row;
		this.col = _col;
		this.isHorizon = _isHorizon;
	}
	IsoPointPos.clone = function(pointA, pointB){
		 pointB.row = pointA.row, 
		 pointB.col = pointA.col, 
		 pointB.isHorizon = pointA.isHorizon;
	}
	
	var pre_iso_point = new IsoPointPos(),
		cur_iso_point = new IsoPointPos(),
		next_iso_point = new IsoPointPos();

	//追踪开等值线
	var tracing_non_closed_contour = function(){
		
		var i=0, j=0;
		//追踪左边框
		for ( i = 0; i < edgeRows; i++)
		{
			if (edgeInfoY[i][0].have_iso_point)
			{
				pre_iso_point = new IsoPointPos(i,-1,false);
				cur_iso_point = new IsoPointPos(i, 0,false);

				tracing_one_non_closed_contour();
			}
		}
		//追踪上边框
		for ( j = 0; j < edgeCols; j++)
		{
			if (edgeInfoX[edgeRows][j].have_iso_point)
			{
				pre_iso_point = new IsoPointPos(edgeRows+1,j,true);
				cur_iso_point = new IsoPointPos(edgeRows,j,true);

				tracing_one_non_closed_contour();
			}
		}
		//追踪右边框
		for ( i = 0; i < edgeRows; i++)
		{
			if (edgeInfoY[i][edgeCols].have_iso_point)
			{
				pre_iso_point = new IsoPointPos(i,edgeCols+1,false);
				cur_iso_point = new IsoPointPos(i,edgeCols,false);

				tracing_one_non_closed_contour();
			}
		}
		//追踪下边框
		for ( j = 0; j < edgeCols; j++)
		{
			if (edgeInfoX[0][j].have_iso_point)
			{
				pre_iso_point = new IsoPointPos(-1,j,true);
				cur_iso_point = new IsoPointPos(0, j,true);

				tracing_one_non_closed_contour();
			}
		}
	}
	
	//追踪一条等值线
	var tracing_one_non_closed_contour = function()
	{
		now_iso_line = {
			value:cur_follow_value,
			path :[] 
			};
			
		dealIsoPoint(cur_iso_point);
		var over = false;
		
		while(!over)
		{
			trace_next_point();
			pre_iso_point = cur_iso_point;
			cur_iso_point = next_iso_point;

			over = (!cur_iso_point.row && cur_iso_point.isHorizon)//网格底边
				|| (!cur_iso_point.col && !cur_iso_point.isHorizon)//网格左边
				|| (cur_iso_point.row == edgeRows)//网格上边
				|| (cur_iso_point.col == edgeCols);//网格右边
		}

		all_iso_line.push(now_iso_line);
		
	}
	
	//追踪到等值点时进行处理
	var dealIsoPoint = function(point){
		//计算坐标并将此点加入当前等值线中
		
		var row = point.row, col = point.col;
		var is_h = point.isHorizon;
		
		var x= xMin + col*deltX,
			y= yMin + row*deltY;
			
		if(is_h)
		{
			x += edgeInfoX[row][col].rate * deltX;
			edgeInfoX[row][col].have_iso_point = false;
		}
		else
		{
			y += edgeInfoY[row][col].rate * deltY;
			edgeInfoY[row][col].have_iso_point = false;
		}

		now_iso_line.path.push( {'x':x,'y':y} );

		next_iso_point = point;
	}

			//判断方向
		var determine_direction = function( left, right, oppsite )
		{
			//判断从网格哪边进入
            if (cur_iso_point.row > pre_iso_point.row) //从下至上
            {
				IsoPointPos.clone(cur_iso_point, left); 
				left.isHorizon = false;

				IsoPointPos.clone(left, right); 
				right.col += 1;

				IsoPointPos.clone(cur_iso_point, oppsite); 
				oppsite.row += 1;
				
                return;
            }
            else if (cur_iso_point.col > pre_iso_point.col)  //从左至右
            {
				IsoPointPos.clone(cur_iso_point, right); 
				right.isHorizon = true;
				
				IsoPointPos.clone(right, left);
				left.row += 1;

				IsoPointPos.clone(cur_iso_point, oppsite);
				oppsite.col += 1;

                return;
            }
			else if (cur_iso_point.isHorizon)  //从上至下
            {
				IsoPointPos.clone(cur_iso_point, right); 
				right.row -= 1;
				right.isHorizon = false;
				
				IsoPointPos.clone(right, left);
				left.col += 1;

				IsoPointPos.clone(cur_iso_point, oppsite); 
				oppsite.row -= 1;

                return;
            }
            else                               //从右至左
            {
				IsoPointPos.clone(cur_iso_point, left);
				left.col -= 1;
				left.isHorizon = true;

				IsoPointPos.clone(left, right); 
				right.row += 1;

				IsoPointPos.clone(cur_iso_point, oppsite ); 
				oppsite.col -= 1;

                return;
            }
		}
		
		var isHaveIsoPoint = function(position){
			log('<br>position: row ' + position.row +' col '+position.col+ ' isHorizon:' + position.isHorizon);
			if(position.isHorizon){
				return edgeInfoX[position.row][position.col].have_iso_point;
			}else{
				return edgeInfoY[position.row][position.col].have_iso_point;
			}
		}

		//追踪下一点
        var trace_next_point = function()
        {
			var left = new IsoPointPos(),
				right = new IsoPointPos(),
				oppsite = new IsoPointPos();

			determine_direction(left,right,oppsite);

			var points = [left, right, oppsite];
			
			for(var i in points){
				if(isHaveIsoPoint(points[i]) ){
					dealIsoPoint( points[i] );
				}
			}
        }
		
		var tracing_closed_contour = function(){
			var i, j;
			for(j=0; j<edgeCols; j++){
				for(i=0; i<edgeRows; i++){//每一列的各层
					if(edgeInfoY[i][j].have_iso_point){//垂直边上是否有等值点
						pre_iso_point = iso_point(i,0,false);
						cur_iso_point = iso_point(i,j,false);

						tracing_one_closed_contour();
					}
				}
			}
		}

		var tracing_one_closed_contour = function()
		{
			var start_r = cur_iso_point.row, start_c = cur_iso_point.col;
			
			now_iso_line = {
			value:cur_follow_value,
			path :[] 
			};
			
			dealIsoPoint(cur_iso_point);
			var over = false;

			while(!over)
			{
				trace_next_point();

				pre_iso_point = cur_iso_point;
				cur_iso_point = next_iso_point;

				over = (cur_iso_point.row==start_r) && (cur_iso_point.col == start_c)
					&& (!cur_iso_point.is_horizon);
			}

			all_iso_line.push(now_iso_line);
		}
	
}

var log = function(html){
	$('#log').append(html);
}