//处理Ajax
//最后修改 last edit time:2011 3 8 18:00

var lyRain={

    isSetAlarm: false,
	isSuccess:false,
	endRainRequestTime:0,
    alarmValue:30,
	levelValue:[0.1,10,25,50,100,250],
	levelCount:[],
	levelRain:[],
	rainOverlayArray:[],
    to2:function (n){
            return n>=10 ? n : '0'+n;
        },
	loading:false,
	timeOut:0,
    timeOutSpan: 60*1000,
    format_time: function (time){

		time = time ? time : new Date();

		return time.getFullYear()+"-"+this.to2(time.getMonth()+1)+"-"+this.to2(time.getDate())+" "
				+this.to2(time.getHours())+":"+this.to2(time.getMinutes());//+":"+this.to2(time.getSeconds())
	},
	get_time_from_str:function(timeStr){
		var a = timeStr.split(/-|:|\s/);
		return new Date(a[0],a[1]-1,a[2],a[3],a[4],0,0);
	},
	removeLock:false,
	removeRain:function(){
		if(! this.removeLock) this.removeLock = true;
		else return false;
		if (this.rainOverlayArray) {
			for (var i in this.rainOverlayArray) {
				this.rainOverlayArray[i].setMap(null);
			}
			this.rainOverlayArray.length = 0;
		}
		this.removeLock = false;
	},
	
	maxDisplayStations:400,
	displayRain: function(){
		//$('.rain-overlay').remove();//去掉之前的内容
		this.removeRain();
		var count = 0;
		var curBound = window.googleMap.getBounds();
		for(var key in this.jsonRain){//  
            var value = Number(this.jsonRain[key]);
			if(count > this.maxDisplayStations) break;
			//alert(lonlat[1]+' '+lonlat[0]);
			//var text = (Math.random()*100).toFixed(1);
			if(value>0){
				var text = value;
				key = key.toUpperCase();
				if(key in allLonLats){
					var lonlat = allLonLats[key].lonlat ||[-60,90];

				}else{
					//console.log(key);
					continue;
				}
				var pos = new google.maps.LatLng(lonlat[1], lonlat[0]);
				if(curBound.contains(pos) ){
					count++;
					//if(!$('.rain-overlay[stationid='+key+']').length){
						var overlay = new RainOverlay(window.googleMap, pos, text, key);
						this.rainOverlayArray.push(overlay);
					//}
				}
			}
		}
	},
	
	wind2OverlayArray:[],
	removeWind2:function(){
		if(! this.removeLock) this.removeLock = true;
		else return false;
		if (this.wind2OverlayArray) {
			for (var i in this.wind2OverlayArray) {
				this.wind2OverlayArray[i].setMap(null);
			}
			this.wind2OverlayArray.length = 0;
		}
		this.removeLock = false;
	},
	displayWind2: function(){
		//$('.rain-overlay').remove();//去掉之前的内容
		this.removeWind2();
		var count = 0;
		var curBound = window.googleMap.getBounds();
		for(var key in this.jsonWind2){//  
            var value = Number(this.jsonWind2[key][1]);
			var direction = Number(this.jsonWind2[key][0])
			if(count > this.maxDisplayStations) break;
			//alert(lonlat[1]+' '+lonlat[0]);
			//var text = (Math.random()*100).toFixed(1);
			if(value >= 0){
				var text = value;
				key = key.toUpperCase();
				if(key in allLonLats){
					var lonlat = allLonLats[key].lonlat ||[-60,90];

				}else{
					//console.log(key);
					continue;
				}
				var pos = new google.maps.LatLng(lonlat[1], lonlat[0]);
				if(curBound.contains(pos) ){
					count++;
					//if(!$('.rain-overlay[stationid='+key+']').length){
						var overlay = new WindOverlay(window.googleMap, pos, [value,direction], key);
						this.wind2OverlayArray.push(overlay);
					//}
				}
			}
		}
	},
	
	temphOverlayArray:[],
	removeTemph:function(){
		if(! this.removeLock) this.removeLock = true;
		else return false;
		if (this.temphOverlayArray) {
			for (var i in this.temphOverlayArray) {
				this.temphOverlayArray[i].setMap(null);
			}
			this.temphOverlayArray.length = 0;
		}
		this.removeLock = false;
	},
	displayTemph: function(){
		//$('.rain-overlay').remove();//去掉之前的内容
		this.removeTemph();
		var count = 0;
		var curBound = window.googleMap.getBounds();
		for(var key in this.jsonTemph){//  
            var value = Number(this.jsonTemph[key]);
			if(count > this.maxDisplayStations) break;
			//alert(lonlat[1]+' '+lonlat[0]);
			//var text = (Math.random()*100).toFixed(1);
			if(value>-30 && value<50){
				var text = value;
				key = key.toUpperCase();
				if(key in allLonLats){
					var lonlat = allLonLats[key].lonlat ||[-60,90];

				}else{
					//console.log(key);
					continue;
				}
				var pos = new google.maps.LatLng(lonlat[1], lonlat[0]);
				if(curBound.contains(pos) ){
					count++;
					//if(!$('.rain-overlay[stationid='+key+']').length){
						var overlay = new TemphOverlay(window.googleMap, pos, text, key);
						this.temphOverlayArray.push(overlay);
					//}
				}
			}
		}
	},
	reloadAllData:function(requestTime,once){
		this.reloadRainData(requestTime,once);
		this.reloadTemphWind2Data(requestTime,once);
	},
    reloadRainData: function(requestTime,once){//刷新数据并显示
				
		var jsonUrl = "raininfo.php";
		
		if(! this.isFromLast20){
			if(this.isLatestRequest){
				
				this.setTimeFromSlider();			
			}else if(!once){
				return;
			}
			
			jsonUrl = "raininfo.php?history=true&startTime="+this.format_time(this.beginTime)+"&endTime="+this.format_time(this.endTime);
		}		
		
		this.endRainRequestTime = requestTime;		
		$("#ajax-rain-info").text("正在请求雨量数据...");

		$.getJSON(jsonUrl,$.proxy(this.ajaxRainSuccess(requestTime),this) );

    },
	
	isLatestRequest:true,
	reloadTemphWind2Data: function(requestTime,once){//刷新数据并显示
							
		var jsonUrl = "lib/t-wind2.php";
		
		//改变请求url
		if(this.isLatestRequest){
			this.setTimeFromSlider();
		}else if(once){
			jsonUrl = "lib/t-wind2.php?history=true&wind2Time="+this.format_time(this.endTime);
		}else{
			return;
		}
		
		this.endTemphWind2RequestTime = requestTime;
		$("#ajax-wind-temph-info").text("正在请求温度和风场数据...");

		$.getJSON(jsonUrl,$.proxy(this.ajaxTemphWind2Success(requestTime),this) );

    },
	
	isDisplayRain:true,
	ajaxRainSuccess:function (requestTime){
	
		return function(jsonRain){
			if(this.endRainRequestTime != requestTime) return;
			
			this.isSuccess = true;
			this.jsonRain = jsonRain;
			
			this.titleStr = "实时数据 更新时间: ";
			if($("#setend").is(":checked")){
				this.titleStr = "历史数据 更新时间: ";
			}
			
			var now = new Date();

			this.titleStr += now.getFullYear()+"-"+(now.getMonth()+1)+"-"+now.getDate()+" "
							+this.to2(now.getHours())+":"+this.to2(now.getMinutes())+":"+this.to2(now.getSeconds());
			
			
			if(this.isDisplayRain) this.displayRain();
						
			$("#ajax-rain-info").text("请求雨量数据完成！");
			$("#title").text(this.titleStr);
			
			//this.calcLevelRain();
			//this.setSortRainInfo();
						
			//this.dealAlarm();
		}
	},
	
	isDisplayTemph:false,
	isDisplayWind2:false,
	ajaxTemphWind2Success:function (requestTime){
	
		return function(jsonTemphWind2){
			if(this.endTemphWind2RequestTime != requestTime) return;
			
			this.jsonTemph = {};
			this.jsonWind2 = {};
			for(var key in jsonTemphWind2){
				this.jsonTemph[key] = jsonTemphWind2[key][0];
				this.jsonWind2[key] = new Array(jsonTemphWind2[key][1],jsonTemphWind2[key][2]);
			}
			
			if(this.isDisplayTemph) this.displayTemph();
			if(this.isDisplayWind2) this.displayWind2();
						
			$("#ajax-wind-temph-info").text("请求温度和风场数据完成！");
			//$("#title").text(this.titleStr);
			
			//this.calcLevelRain();
			//this.setSortRainInfo();
						
			//this.dealAlarm();
		}
	},
	
	
	SphericalDistance: function(latLonA,latLonB){
		var tor = Math.PI/180;
		var a1 = latLonA.lng()*tor,
			b1 = latLonA.lat()*tor,
			a2 = latLonB.lng()*tor,
			b2 = latLonB.lat()*tor;

		//var radius = 100000*Math.abs(e.latLng.lat()-populationOptions.center.lat());
		var rads = 6300*Math.acos(Math.cos(b1)*Math.cos(b2)*Math.cos(a1-a2)+Math.sin(b1)*Math.sin(b2) );
		
		return rads;//km
	},
	
	startSoundAlarm:function(current){
		var alarm = $("#alarm-sound")[0];
        var ispaused = alarm.paused, isended = alarm.ended;

        if(ispaused || isended){ 
            alarm.play();
			if(current) setTimeout("$('#alarm-sound')[0].pause();",3000);
        }
	},
	
	temphAlarmedStations:new Array(3),
	windAlarmedStations:new Array(3),
	rainAlarmedStations:new Array(3),
	
	dealTemphAlarm:function(current){
		if(!this.alarmOption.isAlarmSet 
		|| !this.alarmOption.alarmCondition.temphAlarm ) return;
		
		var count=0;
        var resultStr = "";
		var addStr = current ? "] 目前有 " : "] 新增 ";
		
		for(var index in this.alarmOption.alarmCondition.temph){
			var infoStr="";
			var n = 0;
			var alarmValue = this.alarmOption.alarmCondition.temph[index];
			
			for(var key in this.jsonTemph){//
				
				var lonlat;
				if(key in allLonLats){
					lonlat = allLonLats[key].lonlat;
				}else{
					continue;
				}
				
				var pos = new google.maps.LatLng(lonlat[1], lonlat[0]);
				if(this.SphericalDistance(this.alarmOption.alarmArea.center, pos) 
					> this.alarmOption.alarmArea.radius ){
					continue;
				}
				
				var value = Number(this.jsonTemph[key]);
				
				if(value >= alarmValue && $.inArray(key,this.temphAlarmedStations[index])== -1){
					n++;
					this.temphAlarmedStations[index].push(key);
				   				   
					infoStr += "<tr><td>"+this.getStationName(key)+"</td><td>"+value+"</td></tr>";
				}			
			}
			
			count += n;
			infoStr = "<div class='new-alarm-info'><h4>[" + this.format_time() + addStr+ n +" 个四要素站的气温 ≥ "+ alarmValue
								+" mm</h4><table>" + infoStr+'</table></div>';
			
			resultStr = infoStr + resultStr;
        };

        if(! count) return;
       
		var oldAlarmHtml = $("#temph-alarm-log").html();
		$("#temph-alarm-log").html(resultStr + oldAlarmHtml);
        
		$( "#log-info-tabs" ).tabs("select" , "#temph-alarm-log");
		$( "#log-info-dialog" ).dialog("open");
		
		this.startSoundAlarm(current);
        	
	},
	dealWindAlarm:function(current){
	},
	dealRainAlarm:function(current){
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
		return (stationID in allLonLats) ? allLonLats[stationID].name : stationID;
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