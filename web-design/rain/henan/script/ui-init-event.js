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
		
		lyRain.alarmOption = {
			isAlarmSet:false,
			alarmCondition:{
				rain:[10,30,50],
				temph:[37,40,42],
				wind:[12,16,20],
				
				rainAlarm:true,
				temphAlarm:true,
				windAlarm:true
			},
			alarmWay:{
				sound:true,
				sms:false,
				phone:[13698835392,13663880026]
			},
			alarmArea:{
				isSetBegin:false,
				isSetting:false,
				center:new google.maps.LatLng(34.323907, 112.109291),
				radius:100,
				circle:null
				
			}
		};
		
		$( "#toggle-alarm" )
			.button()
			.toggle(
					function(){
						changeDivIcon(this,"ui-icon-check");
						lyRain.alarmOption.isAlarmSet = true;
						lyRain.alarmOption.alarmArea.circle.setMap(window.googleMap);
						
						if($("#set-time-range").css("display") != 'none'){
							$( "#select-time" ).click();
						}
						$( "#select-time" ).button( "disable" );
						$("#rain-range").attr("disabled","disabled");
						
						lyRain.setTimeFromSlider(0);
						$("#time-slider").slider( "value" , 0);
					},
					function(){
						changeDivIcon(this,null);
						lyRain.alarmOption.isAlarmSet = false;
						lyRain.alarmOption.alarmArea.circle.setMap(null);
						
						$( "#select-time" ).button( "enable" );
						$("#rain-range").removeAttr("disabled");
					}
			);
		$("#set-alarm-area")
			.click(function(){
				lyRain.alarmOption.alarmArea.isSetting = true;
				$("#set-alarm-dialog" ).dialog("close");
			});
			
		$( "#select-time" )
			.button( {
				text: false,
				icons: {
					primary: "ui-icon-triangle-1-s"
				}
			})
			.click(function() {
				
				$("#set-time-range").toggle();
				lyRain.setContainerSize();
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
			.keypress(function(){
				lyRain.isBeginTimeChangedByUser = true;
			})
			.change(function(){
					if(lyRain.isBeginTimeChangedByUser ){
						lyRain.beginTime = lyRain.get_time_from_str(this.value);
						
						$("#time-slider").slider( "value" , $("#time-slider").slider( "value") );
						
						lyRain.isBeginTimeChangedByUser = false;
					}
				});
		$("#end-time")
			.val(lyRain.format_time(lyRain.endTime))
			.keypress(function(){
				lyRain.isEndTimeChangedByUser = true;
			})
			.change(function(){
					if(lyRain.isEndTimeChangedByUser){
						lyRain.endTime = lyRain.get_time_from_str(this.value);

						var timeSpan = ((new Date()).getTime() - lyRain.endTime.getTime())/(1000*60);
						
						var value = -timeSpan/lyRain.slideSpan;//可能小于-100
						
						lyRain.setTimeFromSlider(value);
						$("#time-slider").slider( "value" , value);
						
						lyRain.isEndTimeChangedByUser = false;
					}
				});		
		
		lyRain.isFromLast20 = false;
		lyRain.slideSpan = 12;
		lyRain.rainTimeSpan = 180;
		$("#rain-range").change(function(){
			lyRain.isBeginTimeChangedByUser = false;
			lyRain.isEndTimeChangedByUser = false;
			
			var value = $(this).val();
			if( value == 'after20'){
					
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
			}
						
			if( value == 'after20' ){
				lyRain.isFromLast20 = true;

				$("#time-slider").slider( "disable" );					
				$("#begin-time").attr("readonly","readonly");
				$("#end-time").attr("readonly","readonly");
			}else{ 
				lyRain.isFromLast20 = false;
				
				if(value == 'any'){
					$("#time-slider").slider( "disable" );
					$("#begin-time").removeAttr("readonly");
					$("#end-time").removeAttr("readonly");
				}else{
					$("#time-slider").slider( "enable" );									
					$("#begin-time").attr("readonly","readonly");
					$("#end-time").removeAttr("readonly");
				}
			}
			
			lyRain.setTimeFromSlider(0);
			$("#time-slider").slider( "value" , 0);//将触发slider-change事件

			//重新请求雨量和风温度场
			//lyRain.reloadAllData((new Date()).getTime());
		});
		
		//根据滑块位置和雨量范围设置时间范围
		lyRain.setTimeFromSlider = function(sliderValue){
		
				if(typeof(sliderValue) === 'undefined') sliderValue = $("#time-slider").slider( "value" );
				
				var now = new Date();
				lyRain.endTime = new Date(now);
				lyRain.endTime.setMinutes(now.getMinutes() + sliderValue*lyRain.slideSpan);
				
				$("#end-time").val(lyRain.format_time(lyRain.endTime));
				
				var rrv = $("#rain-range").val();
				if(rrv != 'after20' && rrv != 'any'){
					lyRain.beginTime = new Date(lyRain.endTime);
					lyRain.beginTime.setMinutes(lyRain.endTime.getMinutes() - lyRain.rainTimeSpan);
					
					$("#begin-time").val(lyRain.format_time(lyRain.beginTime));
				}else if(rrv == 'after20'){
					lyRain.beginTime = new Date();
			
					if(lyRain.beginTime.getHours()<20) lyRain.beginTime.setDate(lyRain.beginTime.getDate()-1);
					lyRain.beginTime.setHours(20,0,0);
								
					$("#begin-time").val(lyRain.format_time(lyRain.beginTime));
				}
			};
		$( "#time-slider" ).slider({
				max:0, 
				min:-100, 
				value:0,
				step:0.01,
				slide: function(event, ui) {
					
					lyRain.setTimeFromSlider(ui.value);
				},
				change: function(event, ui) {
					var buttonText = "最新";
					
					if(ui.value){
						lyRain.isLatestRequest = false;
						buttonText = "["+$("#begin-time").val()+" , "+$("#end-time").val()+"]";
					}else{
						lyRain.isLatestRequest = true;
						
						if($("#rain-range").val() == 'any'){
							buttonText = "["+$("#begin-time").val()+" , 最新]"
						}						
					}
					$("#desc-time span.ui-button-text").text(buttonText);
					
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