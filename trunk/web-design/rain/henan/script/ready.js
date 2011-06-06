
//初始化
//最后修改 last edit time: 2011 3 9 22:40

function initialize() {
    
	function setContainerSize(){
		var newMapHeight = $(window).height()-$("#container").offset().top;
		$("#container").height(newMapHeight).width($(window).width());
	}
	
	setContainerSize();
	
    var myLatLng = new google.maps.LatLng(34.323907, 112.109291);
    var myOptions = {
      zoom: 9,
      center: myLatLng,
      mapTypeId: google.maps.MapTypeId.ROADMAP
    };

	window.googleMap = new google.maps.Map($("#map_canvas")[0],myOptions);
	//显示范围改变时
	google.maps.event.addListener(window.googleMap, 'bounds_changed', $.proxy(lyRain.displayRain,lyRain));
   //设置县界
	var ctaLayer = new google.maps.KmlLayer('http://lyqx.de/jingdian/luoyang.kml');
	ctaLayer.setMap(googleMap);
	
	lyRain.reloadAllData((new Date()).getTime());
    window.setInterval("lyRain.reloadAllData((new Date()).getTime())",60*1000);
	
	$(window).resize(setContainerSize);
	
	$("#alarm-num").val(lyRain.alarmValue);
	var beginTime = new Date();
	if(beginTime.getHours()<20) beginTime.setDate(beginTime.getDate()-1);
	beginTime.setHours(20,0,0);
	
	var defaultBegin = lyRain.format_time(beginTime);
	$("#beginTime").val(defaultBegin);
	$("#endTime").val(lyRain.format_time());
	
	$("#setend").click(function(){
		if($(this).is(":checked")){
			$("#endTime").removeAttr("disabled");
			
			if(!$("#setbegin").is(":checked")){
				$("#setbegin")[0].checked = true;
				$("#beginTime").removeAttr("disabled");
			}		
		}
		else{
			$("#endTime").attr("disabled","disabled");
		}
	});
	
	$("#setbegin").click(function(){
		if($(this).is(":checked")){
			$("#beginTime").removeAttr("disabled");
		}
		else{
			$("#beginTime").attr("disabled","disabled");
			
			if($("#setend").is(":checked")){
				$("#setend")[0].checked=false;
				$("#endTime").attr("disabled","disabled");
			}			
		}
	});
	
	$("#set-alarm").click(function(){
	    if(this.checked){
	        $("#alarm-num").removeAttr("disabled");
	        lyRain.isSetAlarm = true;
	    }
	    else{
	        $("#alarm-num").attr("disabled","disabled");
	        lyRain.isSetAlarm = false;
	    }
	});
	
	$("#collaps").click(function(){
		$("#map-toolbar").css("width","60%")
		$("#left").css("width","60%");
		$("#collaps").hide();
		$("#expand").show();
	});
	$("#expand").click(function(){
		$("#map-toolbar").css("width","100%");
		$("#left").css("width","100%");
		$("#collaps").show();
		$("#expand").hide();
	});
	
	$("#info-toolbar .header a").click(function(){
		$("#info-toolbar .header span").hide();
		$("#info-toolbar .header a").show();
		$(this).hide();
		$(this).next("span").show();
		
		$(".rain-info").hide();
		$($(this).attr('mapid')).show();
	});
	
	//点击站名时将地图放大并置于中心
	$("#stat-info").delegate("td.rain-station a","click",function(){
		var stationID = $(this).attr('stationId');
		var lonlat = allLonLats[stationID].lonlat ||[-60,90];
		var pos = new google.maps.LatLng(lonlat[1], lonlat[0]);
		window.googleMap.setZoom(11);
		window.googleMap.setCenter(pos);
	});
	
	//检测是否支持报警
	if(!('play' in $("<audio/>")[0]) ){
	    $(".tips").show();
	    $("#set-alarm").attr("disabled","disabled");
	}
	
	$("#alarm-num").change(function(){
		var newValue = Number(this.value);
	    //if( newValue > lyRain.alarmValue){
			lyRain.alarmedStation = [];
		//}
		
		lyRain.alarmValue = newValue;
		
		lyRain.dealAlarm(true);
	}) ;
	
	$("#set input").change(function(){
		$("#ajax-info").text("修改已生效 将重新加载数据");
		lyRain.removeRain();
		$(".rain-info").not('#alarm-info').hide();
		lyRain.reloadRainData((new Date()).getTime());
	}) ;
	
	$("#alarm-info").mousemove(function(){
		$("#alarm-sound")[0].pause();
	});
	
	//某些浏览器不支持audio loop
	$('#alarm-sound').bind('ended',function(){
		this.play();
	});
}