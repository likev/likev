
//初始化
//最后修改 last edit time: 2011 3 9 22:40

function initialize() {
    var myLatLng = new google.maps.LatLng(34.323907, 112.109291);
    var myOptions = {
      zoom: 9,
      center: myLatLng,
      mapTypeId: google.maps.MapTypeId.ROADMAP
    };

	window.googleMap = new google.maps.Map($("#map_canvas")[0],myOptions);
	
	var alarmCircleOptions = {
		strokeColor: "#FF0000",
		strokeOpacity: 0.8,
		strokeWeight: 2,
		fillColor: "#FF0000",
		fillOpacity: 0.2,
		map: null,
		clickable:false,
		center:	lyRain.alarmOption.alarmArea.center,
		radius: lyRain.alarmOption.alarmArea.radius*1000
	};
	lyRain.alarmOption.alarmArea.circle = new google.maps.Circle(alarmCircleOptions);
	google.maps.event.addListener(window.googleMap,
		'rightclick', 
		function(e) {
			if(lyRain.alarmOption.alarmArea.isSetting){
				if(lyRain.alarmOption.alarmArea.isSetBegin){
						lyRain.alarmOption.alarmArea.isSetBegin = false;
						lyRain.alarmOption.alarmArea.isSetting = false;
						
						
						$("#set-alarm-area-tips").remove();
						$("#ajax-info").children().show();
						
						$("#alarm-center").text(lyRain.alarmOption.alarmArea.center.lng().toFixed(3)
								+", "+lyRain.alarmOption.alarmArea.center.lng().toFixed(3));
						$("#alarm-radius").text(lyRain.alarmOption.alarmArea.radius.toFixed(3)+"km");
												
						if(lyRain.alarmOption.isAlarmSet){
							lyRain.dealAllAlarm(true);
						}else{ 
							lyRain.alarmOption.alarmArea.circle.setMap(null);
							$("#set-alarm-dialog" ).dialog("open");
						}
				}else{
						lyRain.alarmOption.alarmArea.isSetBegin = true;
						lyRain.alarmOption.alarmArea.center = e.latLng;
						
						lyRain.alarmOption.alarmArea.circle.setCenter(e.latLng);
						lyRain.alarmOption.alarmArea.circle.setMap(window.googleMap);
						
						$("#set-alarm-area-tips").text("移动鼠标选择报警范围，点击右键结束设置...");
				}
				
			}
		});
	google.maps.event.addListener(window.googleMap, 
		'mousemove', 
		function(e) {
			if(lyRain.alarmOption.alarmArea.isSetting){
				if(lyRain.alarmOption.alarmArea.isSetBegin){
				
					var rads = lyRain.SphericalDistance(lyRain.alarmOption.alarmArea.center,e.latLng);
					lyRain.alarmOption.alarmArea.radius = rads;
					lyRain.alarmOption.alarmArea.circle.setRadius(rads*1000);
				}
			}
		});
	
	//设置地图外围容器高度和宽度
	lyRain.setContainerSize = function (){
		var newMapHeight = $(window).height()-$("#container").offset().top;
		$("#container").height(newMapHeight).width($(window).width());
		
		google.maps.event.trigger(window.googleMap, 'resize');
	}
	
	lyRain.setContainerSize();
	$(window).resize(lyRain.setContainerSize);
	
	//显示范围改变时
	google.maps.event.addListener(window.googleMap, 
			'bounds_changed', 
			function(){
				if(lyRain.isDisplayRain) lyRain.displayRain();
				if(lyRain.isDisplayTemph) lyRain.displayTemph();
				if(lyRain.isDisplayWind2) lyRain.displayWind2();
			});
   //设置县界
	var ctaLayer = new google.maps.KmlLayer('http://lyqx.de/jingdian/luoyang.kml');
	ctaLayer.setMap(googleMap);
	
	lyRain.reloadAllData((new Date()).getTime());
    window.setInterval("lyRain.reloadAllData((new Date()).getTime())",60*1000);

	
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
	    $("#alarm-volume-check").attr({checked:false, disabled:"disabled"});
		$("#alarm-volume-test").text("您的浏览器不支持报警，请切换firefox或chrome浏览器");
	}

	//某些浏览器不支持audio loop
	$('#alarm-sound').bind('ended',function(){
		this.play();
	});
}