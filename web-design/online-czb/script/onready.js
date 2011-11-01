	
	
	var app = new WebCzb(czbConfig);

$(function(){

	$('#edit-czb').append(app.getUIHtml('#edit-czb'));
	//$('#edit-czb .station:odd').css('background-color','#eee');
	app.setTitlePosition();
	
	$('#zdb').append(app.getUIHtml('#zdb'));
	$('#zdb-title').text(app.getZdbName());

	var now = new Date();
	$('label[for="toggle-today"]').text(now.getDate()+'/'+(now.getMonth()+1));
	now.setDate(now.getDate()+1);
	$('label[for="toggle-tomorrow"]').text(now.getDate()+'/'+(now.getMonth()+1));
	
	$('#select-day')
		.buttonset()
		.find('input[type="radio"]:checked')
		.button( "option" , {"icons":{primary:'ui-icon-check'} } );
	
	$('#select-day input[type="radio"]')
		.change(function(){
			if(false){
				//提示是否切换
			}
			app.initForcastCode();
		
			$('#select-day input[type="radio"]').button( "option" , {"icons": {primary:null} } );
			$('#select-day input[type="radio"]:checked').button( "option" , {"icons":{primary:'ui-icon-check'} } );
			
			app.changeMessage = true;
			$( "#time-slider" ).slider('value', -12);
		});
	
	$('#select-message').buttonset();
	
	//改变预报时次
	$('#select-message input[type="radio"]')
		.change(function(){
			
			if(false){
				//提示是否切换
			}
			app.initForcastCode();
			
			$('#select-message input[type="radio"]').button( "option" , {"icons": {primary:null} } );
			
			var jdom = $('#select-message input[type="radio"]:checked');
			jdom.button( "option" , {"icons":{primary:'ui-icon-check'} } );
		
			app.setMessageType(jdom[0].id);
			
			if(jdom[0].id == 'toggle-forth' ) app.maxPeriod = 168;
			else app.maxPeriod = 72;
			
			$('#time-select-mark li')
				.text(function(index,text){
					return text.replace('*','');
				})
				.removeClass('time-mark-edited time-mark-disabled')
				.addClass(function(){
					var value = $(this).attr('timeValue');
					if(value > app.maxPeriod) $(this).addClass('time-mark-disabled');
				});
			
			//首先移除所有li,input[disabled]元素 仅当04时次时添加disabled属性
			$('#edit-czb .station').each(function(index,dom){
				$(this).removeAttr('disabled');
				$('input',this).removeAttr('disabled');
				
				if(jdom[0].id == 'toggle-first' ){
					if( app.getSingleCityID() != $(this).attr('num') ){
						$(this).attr('disabled','disabled')
						$('input',this).attr('disabled','disabled')
					}
				}
			});
			
			app.changeMessage = true;
			$( "#time-slider" ).slider('value', -12);
		});
	
	$('#prev-next-time').buttonset();
	$('#view-message')
		.button()
		.click(function(){
			app.viewMessage();
		});
		
	$('#dialog-preview')
		.dialog({
			height:640,
			width:940,
			autoOpen: false,
			modal: true,
			buttons: {
				"上传至FTP": function() {
					app.PostMessage();
				},
				"上传个人城镇报": function() {
					alert('很快将实现此功能...');
					$( this ).dialog( "close" );
				}
			}
		});
	
	$('#prev-time').click(function(){
		var nextValue = app.timeValue - 12;
		if( nextValue < 12 ) nextValue = app.maxPeriod;
		
		$( "#time-slider" ).slider('value', -nextValue);
	})
	
	$('#next-time').click(function(){
		var nextValue = app.timeValue + 12;
		if( nextValue > app.maxPeriod ) nextValue = 12;
		
		$( "#time-slider" ).slider('value', -nextValue);
	})
	
	$('#edit-czb .station').hover(
		function(){
			$('#zdb .station').css('background-color','transparent');
			$('#zdb .station[num="'+$(this).attr('num')+'"]').css('background-color','#fde');
		},function(){
			$('#zdb .station').css('background-color','transparent');
		});
	
	$('.station input').keydown(function(){
		return false;
	});
	
	$('#edit-czb .station input').focus(function(){		
		app.focusDom = this;
	});
	
	$('#edit-czb .station input').click(function(){
		$('#forcast-select ul').hide();
		
		var inputname = this.name;
		
		var base = $('.base .'+inputname);
		var border = parseFloat(base.css('border-left-width')) + parseFloat(base.css('border-right-width')),
			padding = parseFloat(base.css('padding-left')) + parseFloat(base.css('padding-right')),
			left = base.offset().left + border + base.width() + padding,
			top  = base.offset().top;
		
		app.fillForcastSelect();
		
		//console.log(base.offset().left +' '+ base.offset().top +' ');
		$('#forcast-select ul[selectfor="'+ inputname +'"]')			
			.css({'top':top, 'left':left+1, display:'block'})
			.find('li')
				.removeClass('curValue')
				.each(function(){
					var code = $(this).attr('code');
					if( code && (code === $(app.focusDom).attr('code') )
						|| $(this).text() == $(app.focusDom).val() ){
						
						$(this).addClass('curValue');
					};
				});
		
		window.clearTimeout(app.timeout);
		app.timeout = window.setTimeout("$('#forcast-select ul').hide()",5000);
	});
	
	$('#forcast-select').delegate("li", "click", function(){
		
		$(app.focusDom).val($(this).text());
		var code = $(this).attr('code');
		if(code){$(app.focusDom).attr('code',code) };
		$('#forcast-select ul').hide();
		
		//必需手动触发
		app.onBaseChange(app.focusDom);
	});
	
	$('#zdb-title').delegate("#regain-zdb", "click", function(){
		app.getLatestZdb();
	});
	
	$( "#time-slider" ).slider({
				orientation: "vertical",
				max:-12, 
				min:-168, 
				value:-12,
				step:12,
				slide: function(event, ui) {
					if(-ui.value > app.maxPeriod){
						$( "#time-slider" ).slider('value', -app.maxPeriod);
						return false;
					}
					
				},
				change: function(event, ui) {
					//标记修改时次
					$('#time-select-mark li').eq(app.timeValue/12 - 1)
						.each(function(){
							if(app.changeMessage) {
								app.changeMessage = false;
								return;
							}
							
							$(this).text(function(index,text){
								if(text.indexOf('*') == -1) $(this).text(text+'*')						
							})
							.addClass('time-mark-edited');
							
							app.updateForcast();							
						});
					
					//console.log(ui.value);
					app.timeValue = -ui.value;
					
					$('#time-select-mark li').removeClass('time-mark-current');
					$($('#time-select-mark li')[app.timeValue/12 - 1])
						.addClass('time-mark-current');
					
					if((app.timeValue/12)%2) $('input.high-t, input.low-t').attr('disabled', 'disabled');
					else $('input.high-t, input.low-t',".station[disabled!='disabled']").removeAttr('disabled');
					
					app.updateUIFromCode();
				}
			});
	
	$('#time-select-mark li')
		.height( $('#time-slider').height()/13 - 5 )
		.click(function(){
	
			var value = $(this).attr('timeValue');
			if(value <= app.maxPeriod) $( "#time-slider" ).slider('value', -value);
		})		
		.hover(
			function(){
				var value = $(this).attr('timeValue');
				if(value <= app.maxPeriod) $(this).addClass('time-mark-hover');
			},
			function(){
				$(this).removeClass('time-mark-hover');
			}
		)
});