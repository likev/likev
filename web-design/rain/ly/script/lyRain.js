
//处理Ajax
//最后修改 last edit time:2011 3 8 18:00

var lyRain={

    isSetAlarm: false,
	isSuccess:false,
	endRequestTime:0,
    alarmValue:30,
	levelValue:[0.1,10,25,50,100,250],
	levelCount:[],
	levelRain:[],
    to2:function (n){
            return n>=10 ? n : '0'+n;
        },
	loading:false,
	timeOut:0,
    timeOutSpan: 60*1000,
    format_time: function (time){

		time = time ? time : new Date();

		return time.getFullYear()+"-"+this.to2(time.getMonth()+1)+"-"+this.to2(time.getDate())+" "
				+this.to2(time.getHours())+":"+this.to2(time.getMinutes())+":"+this.to2(time.getSeconds());
	},
    reloadData: function(requestTime){//刷新数据并显示
		
		this.endRequestTime = requestTime
		
		$("#ajax-info").text("正在请求数据...");
			
		var jsonUrl = "http://lyqx.de/rain/ly/raininfo.php";
		
		//改变请求url
		if($("#setbegin").is(":checked")){

			if(!$("#setend").is(":checked")){
				$("#endTime").val(this.format_time());
			}
			
			var beginTimeStr = $("#beginTime").val(),
				endTimeStr = $("#endTime").val();

			jsonUrl = "http://lyqx.de/rain/ly/raininfo.php?history=true&startTime="+beginTimeStr+"&endTime="+endTimeStr;
		}

		$.getJSON(jsonUrl,$.proxy(this.ajaxSuccess(requestTime),this) );

    },
	ajaxSuccess:function (requestTime){
	
		return function(jsonRain){
			
			this.isSuccess = true;
			this.jsonRain = jsonRain;
			
			this.titleStr = "实时数据 更新时间: ";
			if($("#setend").is(":checked")){
				this.titleStr = "历史数据 更新时间: ";
			}
			
			var now = new Date();

			this.titleStr += now.getFullYear()+"-"+(now.getMonth()+1)+"-"+now.getDate()+" "
							+this.to2(now.getHours())+":"+this.to2(now.getMinutes())+":"+this.to2(now.getSeconds());
			
			$('.rain-overlay').remove();
			$.each(jsonRain, function(key,value){
				//alert(lonlat[1]+' '+lonlat[0]);
				//var text = (Math.random()*100).toFixed(1);
				if(value>0){
					var text = value;
					var lonlat = allLonLats[key].lonlat ||[-60,90];
					var pos = new google.maps.LatLng(lonlat[1], lonlat[0]);
					var overlay = new RainOverlay(window.googleMap, pos, text, key);
				}
			});
			
			if(this.endRequestTime != requestTime) return;
			
			$("#ajax-info").text("请求数据完成！");
			$("#title").text(this.titleStr);
			
			this.calcLevelRain();
			this.setSortRainInfo();
						
			this.dealAlarm();
		}
	},
    alarmedStation:new Array(),
    dealAlarm:function(current){
    
        //console.log("begin");
        if(! this.isSetAlarm)  return;
   
        var isNeedAlarm = false, count=0;
        //var infoNames = [], infoValues=[];
        var infoStr="";
        //console.log("jsonRain");
        //console.dir(this.jsonRain);
        for(var key in this.jsonRain){//  
            var value = Number(this.jsonRain[key]);
            //console.log(value+" "+lyRain.alarmValue);
            if(value >= this.alarmValue && $.inArray(key,this.alarmedStation)== -1){
			   isNeedAlarm= true;
			   this.alarmedStation.push(key);
			   //infoNames[index] = this.getStationName(key);
			   //infoValues[index] = value;
			   count++;
			   
			   infoStr += "<tr><td>"+this.getStationName(key)+"</td><td>"+value+"</td></tr>";
            }
        };
        //console.log("is need alarm");
        //没有需要报警的站点
        if(! isNeedAlarm) return;
        
        //console.log("show alarm info");
		var addStr = "] 新增 ";
		if(current) addStr = "] 目前有 ";
        infoStr = "<div class='new-alarm-info'><h4>[" + this.format_time() + addStr+count+" 个雨量站的雨量 ≥ "+this.alarmValue
				  +" mm</h4><table>" + infoStr+'</table></div>';
        
		var oldAlarmHtml = $("#alarm-info").html();
		$("#alarm-info").html(infoStr + oldAlarmHtml);
        
		$("#info-toolbar a[mapid='#alarm-info']").click();
        
		var alarm = $("#alarm-sound")[0];
		/*
        alarm.loop = true;*/
        var ispaused = alarm.paused, isended = alarm.ended;

        if(ispaused || isended){//notplaying
        //console.log("begin alarm"); 
            alarm.play();
			if(current) setTimeout("$('#alarm-sound')[0].pause();",1000);
        }
    
    },
	
	getCountyId:function(stationID){
		for(var key in allLyCounty){
			if($.inArray(stationID,allLyCounty[key].stations) != -1 ) return key;
		}
		return -1;
	},
	getCountyName:function(stationID){
		var key = this.getCountyId(stationID);
		return allLyCounty[key].name;
	},
	getStationName:function(stationID){
		return allLonLats[stationID].name;
	},
	setSortRainInfo:function(){

		var sortInfoHtml = "<table class='sort-table'><thead><tr><th>站名</th><th>雨量</th></tr></thead><tbody>";
		for(var key in this.jsonRain){
			var rainValue = this.jsonRain[key];
			if(rainValue > 0) {
				sortInfoHtml += "<tr><td>"+this.getStationName(key)+"</td><td>"+rainValue+"</td></tr>";
			}
		}
		sortInfoHtml += "</tbody></table>";
		
		var statInfoHtml = "<table class='stat-table'><thead><tr><th>量级</th><th>总数</th></tr></thead><tbody>";
		for(index = this.levelCount.length-1; index>=0; index--){
			var count = this.levelCount[index];
			if(count){
				var min=this.levelValue[index], max=-1;
				var describe = "大于 "+min+" mm";
				if(index+1 < this.levelValue.length){
					max = this.levelValue[index+1]
					describe = min+ " ~ " +max + " mm";
				}
				
				statInfoHtml += "<tr><td>"+describe+"</td><td>"+count+"</td></tr>";
			}
		}
		statInfoHtml += "</tbody></table>";
		
		$("#sort-info").html(sortInfoHtml + statInfoHtml);
	},
	calcLevelRain:function(){
		//init
		this.levelRain = [];
		this.levelCount = [];
		for(var index=0; index<this.levelValue.length;index++){
			this.levelRain.push({});
			this.levelCount.push(0);
			for(var key in allLyCounty){
				this.levelRain[index][key] = [];
			}
		}
		
		for(var key in this.jsonRain){
			var rainValue = this.jsonRain[key];
			if(rainValue > 0) {
				for(var index=this.levelValue.length-1; index>=0;index--){
					if(rainValue >= this.levelValue[index]) {
						this.levelCount[index]++;
						
						//var singleRain = [this.getStationName(key), rainValue];
						var singleRain = [key, rainValue];
						var county = this.getCountyId(key);
						this.levelRain[index][county].push(singleRain);
						break;
					}
				}
			}
		}
		
		$("#stat-info").html(this.allLevleToTable(this.levelRain) );
		$("#info-toolbar a[mapid='#stat-info']").click();
		
	},
	
	countyRainToTable:function(countyRain){
		/*
		<table>
			<tr><td><a href="#">mj01</a></td><td>53</td></tr>
			<tr><td><a href="#">mj02</a></td><td>64</td></tr>
			<tr><td><a href="#">mj03</a></td><td>71</td></tr>
		</table>
		*/
		var html ="";
		for(var index in countyRain){
			html += "<tr><td class='rain-station'><a href='#' stationId='"+ countyRain[index][0] +"'>"+this.getStationName(countyRain[index][0])+"</a></td><td class='rain-value'>"+countyRain[index][1]+"</td></tr>";
		}
		
		return "<table class='countyRain'>"+html+"</table>";
	},
	levelRainToTable:function(levelRain){
	/*
		<table>
			<tr>
				<td>孟津(10个)</td>
				<td>
					<table>
						<tr><td><a href="#">mj01</a></td><td>53</td></tr>
						<tr><td><a href="#">mj02</a></td><td>64</td></tr>
						<tr><td><a href="#">mj03</a></td><td>71</td></tr>
					</table>
				</td>
			</tr>
			<tr>
				<td>汝阳(10个)</td>
				<td>
					<table>
						<tr><td>ry01</td><td>73</td></tr>
						<tr><td>ry02</td><td>89</td></tr>
						<tr><td>ry03</td><td>71</td></tr>
					</table>
				</td>
			</tr>
	</table>
	*/
		var html ="";
		for(var key in levelRain){
			var length = levelRain[key].length;
			if(length){
				html += "<tr><td>"+allLyCounty[key].name+"("+length+"个)</td><td>"+this.countyRainToTable(levelRain[key])+"</td></tr>";
			}
		}
		
		return "<table class='levelRain'>"+html+"</table>";
	},
	allLevleToTable:function(allLevelRain){
	
		var html ="";
		for(var index = allLevelRain.length-1; index>=0; index--){
			var count = this.levelCount[index];
			if(count){
				html += "<tr><td> >"+this.levelValue[index]+"mm("+count+"个)</td><td>"+this.levelRainToTable(allLevelRain[index])+"</td></tr>";
			}
		}
		
		return "<table id='allLevelRain'><thead><tr><th>级别</th><th><div>县区 站名 雨量</div></th></tr></thead><tbody>"+html+"</tbody></table>";
	}
};