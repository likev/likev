

//初始化UI
$(function(){
	var now = new Date();
	$('label[for="toggle-today"]').text(now.getDate()+'/'+(now.getMonth()+1));
	now.setDate(now.getDate()+1);
	$('label[for="toggle-tomorrow"]').text(now.getDate()+'/'+(now.getMonth()+1));
	
	
	//默认为第一天
	$('#select-day')
	.buttonset()
	.find('input[type="radio"]:checked')
	.button( "option" , {"icons":{primary:'ui-icon-check'} } );
	
	//报文时次
	$('#select-message').buttonset();
	
	$('#prev-next-time').buttonset();
	$('#view-message').button();
	
	$( "#change-time-confirm" ).dialog({
		autoOpen: false,
		resizable: false,
		height:140,
		modal: true
	});
})


$(function(){
	
	var app = new WebCzb(czbConfig);
	
	app.getLastJson();
	
	$('#edit-czb #edit tbody').append(app.getUIHtml('#edit-czb'));
	$('#zdb').append(app.getUIHtml('#zdb'));
	$('#zdb-title').text(app.getZdbName());


	//改变日期或初始场时 初始化时次标记
	var initTimeSelectMark = function(){
		$('#time-select-mark li')
			.text(function(index,text){
				return text.replace('*','');
			})
			.removeClass('time-mark-edited time-mark-disabled')
			.addClass(function(){
				var value = $(this).attr('timeValue');
				if(value > app.maxPeriod) return 'time-mark-disabled';
			});
		
		app.changeMessage = true;
		$( "#time-slider" ).slider('value', -12);
	}
	

	//改变预报日期
	$('#select-day input[type="radio"]')
		.change(function(){
			if(false){
				//提示是否切换
			}
			app.initForcast();
		
			$('#select-day input[type="radio"]').button( "option" , {"icons": {primary:null} } );
			$('#select-day input[type="radio"]:checked').button( "option" , {"icons":{primary:'ui-icon-check'} } );
			
			initTimeSelectMark();
		});
	
	
	
	//改变预报起始场时次 04|06|10|16
	$('#select-message input[type="radio"]')
		.change(function(){
			
			if(false){
				//提示是否切换
			}
			app.initForcast();
			
			$('#select-message input[type="radio"]').button( "option" , {"icons": {primary:null} } );
			
			var jdom = $('#select-message input[type="radio"]:checked');
			jdom.button( "option" , {"icons":{primary:'ui-icon-check'} } );
		
			app.setMessageType(jdom[0].id);
			
			if(jdom[0].id == 'toggle-forth' ) app.maxPeriod = 168;
			else app.maxPeriod = 72;
			
			
			
			//首先移除所有li,input[disabled]元素 仅当04时次时添加disabled属性
			$('#edit .station').each(function(index,dom){
				$(this).removeClass('disabled');
				$('td',this).removeClass('disabled');
				
				if(jdom[0].id == 'toggle-first' ){
					if( app.getSingleCityID() != $(this).attr('num') ){
						$(this).addClass('disabled');
						$('td',this).addClass('disabled');
					}
				}
			});
			
			
			initTimeSelectMark();
			app.haveSelectMessage = true;
		});
	
	$('#view-message').click(function(){
			if(!app.haveSelectMessage){
				window.alert("请首先选择预报时次");
				return;
			}
			
			$( "#time-slider" ).slider('value', -app.timeValue);
			app.viewMessage();
		});
		
	$('#dialog-preview')
		.dialog({
			height:640,
			width:880,
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
	
	//自动高亮对应的指导报
	$('#edit .station').hover(
		function(){
			$('#zdb .station[num="'+$(this).attr('num')+'"]').addClass('highlight');
		},function(){
			$('#zdb .highlight').removeClass('highlight');
		});
	
	//编辑预报要素时的响应
	$('#edit .value').click(function(){
		if(!app.haveSelectMessage){
			window.alert("请首先选择预报时次");
			return;
		}
		
		if($(this).hasClass('disabled') ) return;
		
		$('#forcast-select ul').hide();
		$(app.focusDom).removeClass('editing');
		
		app.focusDom = this;
		$(this).addClass('editing');

		var inputname = $(this).attr('name');
		
		var base = $('.base .'+inputname);
		var border = parseFloat(base.css('border-left-width')) + parseFloat(base.css('border-right-width')),
			padding = parseFloat( base.css('padding-left') ),
			left = base.offset().left + border + base.width() + padding,
			top  = base.offset().top;
		
		app.fillForcastSelect();
		
		//console.log(base.offset().left +' '+ base.offset().top +' ');
		$('#forcast-select ul[selectfor="'+ inputname +'"]')			
			.css({'top':top, 'left':left-1, display:'block'})
			.find('li')
				.removeClass('curValue')
				.each(function(){
					var code = $(this).attr('code');
					if( code && (code === $(app.focusDom).attr('code') )
						|| $(this).text() == $(app.focusDom).text() ){
						
						$(this).addClass('curValue');
					};
				});
		
		window.clearTimeout(app.timeout);
		app.timeout = window.setTimeout(function(){
			$('#forcast-select ul').hide();
			$(app.focusDom).removeClass('editing');
		},5000);
	});
	
	
	//选择预报要素
	$('#forcast-select').on("click", "li",  function(){
		
		$(app.focusDom).text($(this).text());
		var code = $(this).attr('code');
		if(code){$(app.focusDom).attr('code',code) };
		
		$('#forcast-select ul').hide();
		$(app.focusDom).removeClass('editing');
		
		//必需手动触发
		app.onBaseChange(app.focusDom);
	});
	
	$('#zdb-title').on("click", "#regain-zdb", function(){
		app.getLatestZdb();
	});
	
	//改变预报时次
	$( "#time-slider" ).slider({
		orientation: "vertical",
		max:-12, 
		min:-168, 
		value:-12,
		step:12,
		slide: function(event, ui) {
			if(-ui.value > app.maxPeriod){
				return false;//取消事件将保持之前的值
			}
			
		},
		change: function(event, ui) {
			
			//是否改变预报起始时次
			if(app.changeMessage) {
				app.changeMessage = false;
			}else{
				$('#time-select-mark li.time-mark-current')
					.text(function(index,text){
						if(text.indexOf('*') == -1) $(this).text(text+'*')						
					})
					.addClass('time-mark-edited');//添加已编辑状态
					
				app.updateJsonFromUI();	
			}
			
			//console.log(ui.value);
			app.timeValue = -ui.value;
			
			$('#time-select-mark li.time-mark-current').removeClass('time-mark-current');
			$('#time-select-mark li')
				.eq(app.timeValue/12 - 1)
				.addClass('time-mark-current');
			
			if((app.timeValue/12)%2){
				$('#edit .high-t, #edit .low-t').addClass('disabled');
			}
			else{
				$('.high-t, .low-t',"#edit .station:not(.disabled)").removeClass('disabled');
			}
			
			app.updateUIFromJson();
		}
	});
	
	//滚动条标记
	$('#time-select-mark li')
		.height( $('#time-slider').height()/13 - 5 )
		.click(function(){
			
			var value = $(this).attr('timeValue');
			var disable = $(this).hasClass('time-mark-disabled');
			if( !disable ) $( "#time-slider" ).slider('value', -value);
		})		
		.hover(
			function(){
				var disable = $(this).hasClass('time-mark-disabled');
				if( !disable ) $(this).addClass('time-mark-hover');
			},
			function(){
				$(this).removeClass('time-mark-hover');
			}
		)
});