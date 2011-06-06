/*
	设置UI初始化和事件响应
*/
$(function() {
		
		function changeDivIcon(div,icon_string){
			$(div).button( "option" , "icons", {primary: icon_string});
		}
		
		$( "#toggle-temph" )
			.toggle(
					function(){
						lyRain.isDisplayTemph = true;
						lyRain.displayTemph();
						changeDivIcon(this,"ui-icon-check");
					},
					function(){
						lyRain.isDisplayTemph = false;
						lyRain.removeTemph();
						changeDivIcon(this,null);
					}
			)
			.parent()
				.buttonset();
				
		$( "#toggle-wind" )
			.toggle(
					function(){
						lyRain.isDisplayWind2 = true;
						lyRain.displayWind2();
						changeDivIcon(this,"ui-icon-check");
					},
					function(){
						lyRain.isDisplayWind2 = false;
						lyRain.removeWind2();
						changeDivIcon(this,null);
					}
			);
		
		$("#toggle-rain")
			.button("option", "icons", { primary: "ui-icon-check" })
			.toggle(
					function(){
						lyRain.isDisplayRain = false;
						lyRain.removeRain();
						changeDivIcon(this,null);
					},
					function(){
						lyRain.isDisplayRain = true;
						lyRain.displayRain();
						changeDivIcon(this,"ui-icon-check");
					}
			);
		$( "#toggle-alarm" )
			.toggle(
					function(){
						changeDivIcon(this,"ui-icon-check");
					},
					function(){
						changeDivIcon(this,null);
					}
			);
			
		$( "#desc-time" )
			.button()
			.next()
				.button( {
					text: false,
					icons: {
						primary: "ui-icon-triangle-1-s"
					}
				})
				.click(function() {
					$("#set-time-range").toggle();
				})
				.toggle(
					function(){
						changeDivIcon(this,"ui-icon-triangle-1-n");
						//$(this).button( "option" , "icons", {primary: "ui-icon-triangle-1-n"});
					},
					function(){
						$(this).button( "option" , "icons", {primary: "ui-icon-triangle-1-s"});
					}
				)
				.parent()
					.buttonset();
		$( "#toggle-alarm" ).button();
		$( "#set-alarm" ).button( {
				text: false,
				icons: {
					primary: "ui-icon-gear"
				}
			})
			.click(function() {
				$("#set-alarm-dialog" ).dialog("open");
				
			})
			.parent()
				.buttonset();
				
		lyRain.beginTime = new Date();
		lyRain.endTime = new Date();
		lyRain.beginTime.setHours(lyRain.endTime.getHours() - 3);
		
		$("#begin-time")
			.val(lyRain.format_time(lyRain.beginTime))
			.change(function(){
					lyRain.beginTime = lyRain.get_time_from_str(this.value);
					//重新请求雨量和风温度场
					lyRain.reloadAllData((new Date()).getTime());
				});
		$("#end-time")
			.val(lyRain.format_time(lyRain.endTime))
			.change(function(){
					lyRain.endTime = lyRain.get_time_from_str(this.value);
					
					if(! $("#time-slider").slider( "option","disabled" )){
						var timeSpan = ((new Date()).getTime() - lyRain.endTime.getTime())/(1000*60);
						
						var value = -timeSpan/lyRain.slideSpan;//可能小于-100
						$("#time-slider").slider( "value" , value);
						lyRain.setSliderTime(value);
					}
					//重新请求雨量和风温度场
					lyRain.reloadAllData((new Date()).getTime());
				});		
		
		lyRain.isFromLast20 = false;
		lyRain.slideSpan = 12;
		lyRain.rainTimeSpan = 180;
		$("#rain-range").change(function(){
			var value = $(this).val();
			if( value == 'after20'){
				lyRain.isFromLast20 = true;
				
				lyRain.beginTime = new Date();
				lyRain.endTime = new Date();
			
				if(lyRain.beginTime.getHours()<20) lyRain.beginTime.setDate(lyRain.beginTime.getDate()-1);
				lyRain.beginTime.setHours(20,0,0);
								
				$("#begin-time").val(lyRain.format_time(lyRain.beginTime));
				$("#end-time").val(lyRain.format_time(lyRain.endTime));
				
				$("#begin-time").attr("readonly","readonly");
				$("#end-time").attr("readonly","readonly");
				
				$("#time-slider").slider('value',0);
			}else if(value == '30m'){
				lyRain.slideSpan = 2;
				lyRain.rainTimeSpan = 30;
			}else if(value == '1h'){
				lyRain.slideSpan = 6;
				lyRain.rainTimeSpan = 60;
			}else if(value == '3h'){
				lyRain.slideSpan = 12;
				lyRain.rainTimeSpan = 180;
			}else if(value == '6h'){
				lyRain.slideSpan = 24;
				lyRain.rainTimeSpan = 360;
			}else if(value == '12h'){
				lyRain.slideSpan = 30;
				lyRain.rainTimeSpan = 720;
			}else if(value == '24h'){
				lyRain.slideSpan = 48;
				lyRain.rainTimeSpan = 1440;
			}else{
				lyRain.slideSpan = 60;
				$("#begin-time").removeAttr("readonly");
				$("#end-time").removeAttr("readonly");
			}
			
			if( value == 'after20' || value == 'any'){
				$("#time-slider").slider( "disable" );
			}else{
				$("#time-slider").slider( "enable" );
				
				lyRain.beginTime = new Date(lyRain.endTime);
				lyRain.beginTime.setMinutes(lyRain.endTime.getMinutes() - lyRain.rainTimeSpan);
					
				$("#begin-time").val(lyRain.format_time(lyRain.beginTime));
				
				$("#begin-time").attr("readonly","readonly");
				$("#end-time").removeAttr("readonly");
			}
			
			if( value != 'after20' ) lyRain.isFromLast20 = false;
			
			if( value == "any" ){
				$("#time-slider").slider( "value" , -50);
				lyRain.isLatestRequest = false;
			}
			else{
				$("#time-slider").slider( "value" , 0);
				lyRain.isLatestRequest = true;				
			}
		});
		
		//根据滑块位置和雨量范围设置时间范围
		lyRain.setSliderTime = function(sliderValue){
				if(typeof(sliderValue) === 'undefined') sliderValue = $("#time-slider").slider( "value" );
				
				var now = new Date();
				lyRain.endTime = new Date(now);
				lyRain.endTime.setMinutes(now.getMinutes() + sliderValue*lyRain.slideSpan);
				
				lyRain.beginTime = new Date(lyRain.endTime);
				lyRain.beginTime.setMinutes(lyRain.endTime.getMinutes() - lyRain.rainTimeSpan);
				
				$("#begin-time").val(lyRain.format_time(lyRain.beginTime));
				$("#end-time").val(lyRain.format_time(lyRain.endTime));
			}
		$( "#time-slider" ).slider({
				max:0, 
				min:-100, 
				value:0,
				step:0.01,
				slide: function(event, ui) {
					
					lyRain.setSliderTime(ui.value);
				},
				change: function(event, ui) {
					
					if(ui.value){
						lyRain.isLatestRequest = false;
						$("#desc-time span.ui-button-text").text("["+$("#begin-time").val()+" , "+$("#end-time").val()+"]");
					}else{
						lyRain.isLatestRequest = true;
						$("#desc-time span.ui-button-text").text("最新");
					}
					
					//重新请求雨量和风温度场
					lyRain.reloadAllData((new Date()).getTime());
				}
			});
		
		$("#set-alarm-dialog" ).dialog({ autoOpen: false, modal:true, width:700, height:300});
		
		$("#alarm-volume-test").click(function(){
			$('#alarm-sound')[0].play();
			setTimeout("$('#alarm-sound')[0].pause();",3000);
		});
	});