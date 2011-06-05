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
		
		$("#begin-time").val(lyRain.format_time(lyRain.beginTime));
		$("#end-time").val(lyRain.format_time(lyRain.endTime));		
		
		lyRain.slideSpan = 12;
		lyRain.rainTimeSpan = 180;
		$("#rain-range").change(function(){
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
			
			if( value == 'after20' || value == 'any'){
				$("#time-slider").slider( "disable" );
			}else{
				$("#time-slider").slider( "enable" );
				
				lyRain.beginTime = new Date(lyRain.endTime);
				lyRain.beginTime.setMinutes(lyRain.endTime.getMinutes() - lyRain.rainTimeSpan);
					
				$("#begin-time").val(lyRain.format_time(lyRain.beginTime));
			}
		});
		
		$( "#time-slider" ).slider({
				max:0, 
				min:-100, 
				value:0,
				step:0.01,
				slide: function(event, ui) {
					var now = new Date();
					lyRain.endTime = new Date(now);
					lyRain.endTime.setMinutes(now.getMinutes() + ui.value*lyRain.slideSpan);
					
					lyRain.beginTime = new Date(lyRain.endTime);
					lyRain.beginTime.setMinutes(lyRain.endTime.getMinutes() - lyRain.rainTimeSpan);
					
					$("#begin-time").val(lyRain.format_time(lyRain.beginTime));
					$("#end-time").val(lyRain.format_time(lyRain.endTime));
				},
				change: function(event, ui) { 
					if(ui.value){
						lyRain.isLatestRequest = false;
					}else{
						lyRain.isLatestRequest = true;
					}
				}
			});
		
		$("#set-alarm-dialog" ).dialog({ autoOpen: false, modal:true, width:700, height:300});
		
		$("#alarm-volume-test").click(function(){
			$('#alarm-sound')[0].play();
			setTimeout("$('#alarm-sound')[0].pause();",3000);
		});
	});