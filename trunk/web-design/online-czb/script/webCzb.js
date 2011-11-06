
function WebCzb(option) {
	
	var stationMap = option.stationMap;
	stationMap['00000'] = {name:"基准"};
	
	var cityCode = option.cityCode || 'BFLB',
		cityName = option.cityName || '洛阳市气象台',
	    
		isSendSingle = option.isSendSingle || true,
		singleCityID = option.singleCityId || '57073';
	
	this.getSingleCityID = function(){
		return singleCityID;
	}
	
	function getIdFromName(name){
		for(var id in stationMap){
			if(name == stationMap[id].name)
			
			return id;
		}
		
		return false;
	}
	
	this.getUIHtml = function(part){
		var html="";
		
		if('#edit-czb' == part) html += this.getSingleHtml('00000');
		for(var id in stationMap){
			if( id=='00000') continue;
			html += this.getSingleHtml(id);
		}
		return html;
	}

	this.getSingleHtml = function(id){
		var html = 
		"<li class='" + (id=='00000' ? 'base ' : '') + "station' num='" + id + "'>" +
		"<label class='name'>" + stationMap[id].name + "</label>" +

		"<label></label><input type=text readonly='readonly' size=7 value='晴天' code='0.0' class='weather' name='weather'>" +
		
		"<label></label><input type=text readonly='readonly' size=5 value='静风' code='0.0' class='wind-dire' name='wind-dire'>" +
		
		"<label></label><input type=text readonly='readonly' size=5 value='≤ 3级' code='0.0' class='wind-level' name='wind-level'>" +
		
		"<label></label><input type=text readonly='readonly' size=2 value='' class='high-t' name='high-t'>" +

		"<label></label><input type=text readonly='readonly' size=2 value='' class='low-t'  name='low-t'>" +

		"</li>";
		
		return html;
	}
	
	var stationCount = (function(){
		var count = 0;
		for(var attr in stationMap){
			if('00000' !== attr) count++;
		}
		return count;
	})();
	
	var forcastElements = option.forcastElements;
	var possibleMaxPeriod = option.possibleMaxPeriod;
	
	this.timeout = 0; //保存控制预报列表隐藏的定时器
	this.focusDom = null; //保存最近的焦点输入dom
	this.maxPeriod = 168; //保存当前最大预报时次
	var isSingleForcast = false; //当前是否在制作单站预报
	
	this.timeValue = 12; //保存当前预报时次
	
	var forcastJsonCode = {}; //预报值保存在这个数组里
	var lastForcastJson = {};//保存上次预报值
 
	var forcastEditTime = new Date(); //制作预报的时间
	var forcastBeginTime = new Date(); //预报的起始时刻
	
	var lastForcastBegin = forcastBeginTime; 
	
	var weatherMap = {
		"0.0": '晴天', 
		"1.0": '多云', 
		"2.0": '阴天', 
		"3.0": '阵雨', 
		"4.0": '雷阵雨', 
		"5.0": '雷雨冰雹', 
		 
		"7.0": '小雨', 
		"8.0": '中雨', 
		"9.0": '大雨', 
		"10.0": '暴雨', 
		"11.0": '大暴雨', 
		"12.0": '特大暴雨', 
		
		"6.0": '雨夹雪',
		"13.0": '阵雪', 
		"14.0": '小雪', 
		"15.0": '中雪', 
		"16.0": '大雪', 
		"17.0": '暴雪', 
		
		"18.0": '雾', 
		"19.0": '冻雨', 
		"20.0": '沙尘暴', 
		"29.0": '浮尘', 
		"30.0": '扬沙'
	};
	var windDireMap = {
		"0.0": '静风',
		"1.0": '东北',
		"2.0": '东',
		"3.0": '东南',
		"4.0": '南',
		"5.0": '西南',
		"6.0": '西',
		"7.0": '西北',
		"8.0": '北',
		"9.0": '旋转风'
	};
	var windLevelMap = {
		"0.0": '≤ 3级',
		"1.0": '3-4级',
		"2.0": '4-5级',
		"3.0": '5-6级',
		"4.0": '6-7级',
		"5.0": '7-8级',
		"6.0": '8-9级',
		"7.0": '9-10级',
		"8.0": '10-11级',
		"9.0": '11-12级'
	};
	
	var getDateFromStr = function(str){
		var value = $.trim(str).split('-');
		
		return new Date(value[0],value[1]-1,value[2],value[3],0,0)
	}
	
	var getLastJson = function(){
		$('#toolbar,#new-czb').hide();

		var jqxhr = $.post("service/service.php", 
			{	
				action:'getLast'
			},
			function(json) {
			  //alert("success");
			  lastForcastJson = $.parseJSON(json.forcastJson);
			  lastForcastBegin = getDateFromStr(json.forcastBegin);
			},'json')
		.done(function() { //alert("second success"); 
		})
		.fail(function() { //alert("error"); 
		})
		.always(function() { //alert("complete");
			$('#load-info').hide();
			$('#toolbar,#new-czb').show();			
		});
	};
	
	getLastJson();
	
	var lastestZdbForcast = {};
	var lastestZdbBegin;
	
	var lastestZdbFilename;
	this.getZdbName = function(){
		return lastestZdbFilename;
	}
	
	var transZdbBegin = function(str){
		var year = Number(str.slice(0,4)), month = Number(str.slice(4,6))-1, day = Number(str.slice(6,8)), hour = Number(str.slice(8,10));
		var begin = new Date();
		begin.setUTCFullYear(year,month,day,hour,0,0);
		
		return begin;
	}
	
	this.getLatestZdb = function(){

		var jqxhr = $.post("service/service.php", 
			{	
				action:'getZdb'
			},
			function(json) {
			  //alert("success");
			  lastestZdbForcast = json.forcast;
			  lastestZdbBegin = transZdbBegin(json.zdbBegin);
			  lastestZdbFilename = json.fileName;
			  
			  $('#zdb-title').text(json.fileName);
			},'json')
		.done(function() { //alert("second success"); 
		})
		.fail(function() { //alert("error");
			$('#zdb-title').html('获取指导报失败,请稍后<a href="#" id="regain-zdb">重新获取</a>');
		})
		.always(function() { //alert("complete"); 
		});
	};
	
	this.getLatestZdb();
	
	this.getWeatherMap = function(){
		return weatherMap;
	}
	this.getWindDireMap = function(){
		return windDireMap;
	}
	this.getWindLevelMap = function(){
		return windLevelMap;
	}
	
	this.getHighTSelectHtml = function(){
		var curT = Number($('.base .high-t').val() );

		var html='';
		
		var lowT = $(this.focusDom).siblings('.low-t').val() - 0;
		if(curT-8 > lowT ) lowT = curT-8;
		
		for(var t= lowT; t<curT+8; t++){
			html += '<li>' + t + '</li>'
		}
		return html;
	}
	this.getLowTSelectHtml = function(){
		var curT = Number($('.base .low-t').val() );

		var html='';
		
		var highT = $(this.focusDom).siblings('.high-t').val() - 0;
		if(curT+8 < highT ) highT = curT+8;
		
		for(var t=curT-8; t< highT; t++){
			html += '<li>' + t + '</li>'
		}
		return html;
	}
	
	this.fillForcastSelect = function(){
		var html = '';
		
		var map = weatherMap;	
		for(var id in map){
			html += '<li code="'+id+'">' + map[id] + '</li>';
		}
		$('#weather-select').html(html);
		
		map = windDireMap;
		html = '';		
		for(var id in map){
			html += '<li code="'+id+'">' + map[id] + '</li>';
		}
		$('#wind-dire-select').html(html);
		
		map = windLevelMap;	
		html = '';
		for(var id in map){
			html += '<li code="'+id+'">' + map[id] + '</li>';
		}
		$('#wind-level-select').html(html);
		
		$('#high-t-select').html( this.getHighTSelectHtml());
		$('#low-t-select').html( this.getLowTSelectHtml());
	}
	
	this.setTitlePosition = function(){
		var classs = ['name', 'weather', 'wind-dire', 'wind-level', 'high-t', 'low-t'];
		
		var baseLeft = parseFloat($('.base').offset().left);
		for(var i in classs){
			//console.log($('.base .'+classs[i]).offset().left+ ' ' + baseLeft);
			var left = parseFloat($('.base .'+classs[i]).offset().left) - baseLeft + 10;
			
			$('.title li[titlefor='+classs[i]+']').css({left:left})
		}
	}
	
	var messageType = '';
	this.setMessageType = function(selectid){
		if('toggle-first' == selectid) messageType = 'first';
		else if('toggle-second' == selectid) messageType = 'second';
		else if('toggle-third' == selectid) messageType = 'third';
		else if('toggle-forth' == selectid) messageType = 'forth';
	}
	
	this.onBaseChange = function(dom){
		if(! ($(dom).parents("li.base").length ) ) return;
		
		if( 'high-t' == dom.name){
			$('#edit-czb input[name="high-t"]').each(function(){
				if(this != dom){
					var diff = stationMap[$(this).parent('li.station').attr('num')].highTdiff
					this.value = dom.value - (-diff);
				}
			})
		}else if( 'low-t' == dom.name){
			$('#edit-czb input[name="low-t"]').each(function(){
				if(this != dom){
					var diff = stationMap[$(this).parent('li.station').attr('num')].lowTdiff
					this.value = dom.value - (-diff);
				}
			})
		}else{
			//console.log(dom.name + dom.value + $(dom).attr('code'));
			$('#edit-czb  input[name="' + dom.name + '"]')
				.val(dom.value)
				.attr('code',$(dom).attr('code'));
		}
	}

	
	var initForcastTime = function(){
		var curDay = new Date();
		
		var selectDayId = $('#select-day input[type="radio"]:checked').attr('id');
		var selectMessageId = $('#select-message input[type="radio"]:checked').attr('id');
		
		if( 'toggle-tomorrow' == selectDayId) curDay.setDate(curDay.getDate()+1);
		
		var hour = 0, minute = 0, second = 0;
		
		forcastEditTime.setFullYear(curDay.getFullYear(), curDay.getMonth(), curDay.getDate());
		forcastBeginTime.setFullYear(curDay.getFullYear(), curDay.getMonth(), curDay.getDate());
		
		isSingleForcast = false;
		//console.log(selectMessageId);
		if( 'toggle-forth' == selectMessageId){
			
			forcastEditTime.setHours(16,20,0,0);			
			forcastBeginTime.setHours(20,0,0,0);			
		}else{
			forcastBeginTime.setHours(8,0,0,0);
			
			if( 'toggle-first' == selectMessageId){
				forcastEditTime.setHours(4,50,0,0);
				isSingleForcast = true;
			}else if( 'toggle-second' == selectMessageId){
				forcastEditTime.setHours(6,35,0,0);
			}else if( 'toggle-third' == selectMessageId){
				forcastEditTime.setHours(10,20,0,0);
			}
		}
		
	}
	
	var getForcastOffset = function(thisBegin,lastBegin){
		var diffHours = (thisBegin.getTime() - lastBegin.getTime())/1000/3600;
		var lastHour = lastBegin.getHours();
		
		var offset = {
				weather : Number( (diffHours/12).toFixed(0) ),
				highT : 0, 
				lowT : 0
			};
		
		if( 20 == lastHour ){
			offset.highT = Math.floor(diffHours/24)*2;
			offset.lowT = Math.ceil(diffHours/24)*2;
		}else if( 8 == lastHour){
			offset.highT = Math.ceil(diffHours/24)*2; 
			offset.lowT = Math.floor(diffHours/24)*2;
		}
		
		return offset;
	}
	
	this.initForcastCode = function(){
	
		initForcastTime();
		
		var offset = getForcastOffset(forcastBeginTime,lastForcastBegin);

		forcastJsonCode  = {};
		
		for(var attr in stationMap){
			//single station code
			forcastJsonCode[attr] = [];
			var last = (lastForcastJson[attr] ? lastForcastJson[attr] : []);
			
			
			//每个时次
			for(var index=0; index < possibleMaxPeriod/12; index++){
				forcastJsonCode[attr][index] = {
						weather: last[index+offset.weather] ? last[index+offset.weather].weather : '0.0',
						dire: last[index+offset.weather] ? last[index+offset.weather].dire : '0.0',
						level: last[index+offset.weather] ? last[index+offset.weather].level : '0.0',
						highT: last[index+offset.highT] ? last[index+offset.highT].highT : '18',
						lowT: last[index+offset.lowT] ? last[index+offset.lowT].lowT : '10'
					}
			}
		}
	}
	
	this.updateZDBFromCode = function(){

		for(var id in lastestZdbForcast){
			var last = lastestZdbForcast[id] ? lastestZdbForcast[id] : [];
			
			var offset = getForcastOffset(forcastBeginTime,lastestZdbBegin);
			
			var index = this.timeValue/12 - 1;
			var forcast = {
						weather: last[index+offset.weather] ? last[index+offset.weather].weather : '0.0',
						dire: last[index+offset.weather] ? last[index+offset.weather].dire : '0.0',
						level: last[index+offset.weather] ? last[index+offset.weather].level : '0.0',
						highT: last[index+offset.highT] ? last[index+offset.highT].highT : '',
						lowT: last[index+offset.lowT] ? last[index+offset.lowT].lowT : ''
					};
					
			//console.log(forcast);
			var jdom = $('#zdb li.station[num="'+ id +'"]');
						
			$('input[name="weather"]',jdom).attr('code',forcast.weather).val(weatherMap[forcast.weather]);
			$('input[name="wind-dire"]',jdom).attr('code',forcast.dire).val(windDireMap[forcast.dire]);
			$('input[name="wind-level"]',jdom).attr('code',forcast.level).val(windLevelMap[forcast.level]);
			$('input[name="high-t"]',jdom).val(Number(forcast.highT).toFixed(0) );
			$('input[name="low-t"]',jdom).val(Number(forcast.lowT).toFixed(0) );
			
		}
	}
	
	var updateCurForcastSpanText = function(timeValue){
		var forcastTime = new Date(forcastBeginTime.getTime());
		
		forcastTime.setHours(forcastTime.getHours() + timeValue - 12);
		
		var str = forcastTime.getDate()+'日 ';
		
		if(forcastTime.getHours() == 8) $('#cur-forcast-span').text(str + '白天');
		else $('#cur-forcast-span').text(str + '夜间');
	}
	
	this.updateUIFromCode = function(){
		updateCurForcastSpanText(this.timeValue);

		for(var id in forcastJsonCode){
			var singleCode= forcastJsonCode[id];
			var forcast = singleCode[this.timeValue/12 - 1];
			
			var jdom = $('#edit-czb li.station[num="'+ id +'"]');
						
			$('input[name="weather"]',jdom).attr('code',forcast.weather).val(weatherMap[forcast.weather]);
			$('input[name="wind-dire"]',jdom).attr('code',forcast.dire).val(windDireMap[forcast.dire]);
			$('input[name="wind-level"]',jdom).attr('code',forcast.level).val(windLevelMap[forcast.level]);
			$('input[name="high-t"]',jdom).val(forcast.highT);
			$('input[name="low-t"]',jdom).val(forcast.lowT);
			
		}
		
		this.updateZDBFromCode();
		
		if((this.timeValue/12)%2){
			$('.station input[name="high-t"]').val('');
			$('.station input[name="low-t"]').val('');
		}
	}
	
	this.updateForcast = function(){
		
		var times = this.timeValue/12 - 1;
		
		for(var id in forcastJsonCode){
			var lidom = $('#edit-czb li.station[num="'+ id +'"]');
			
			var f = forcastJsonCode[id][times];
			
			f.weather = $('input[name="weather"]', lidom).attr('code');
			f.dire = $('input[name="wind-dire"]', lidom).attr('code');
			f.level = $('input[name="wind-level"]', lidom).attr('code');
			f.highT = $('input[name="high-t"]', lidom).val();
			f.lowT =  $('input[name="low-t"]', lidom).val();

		}
	}
	
	this.generateSingleForcast = function(id, f){
		
		var spans = isSingleForcast ? this.maxPeriod/12 : possibleMaxPeriod/12 ;
		
		var str='';
		str += id + ' ' + stationMap[id].lon + ' ' + stationMap[id].lat + ' ' + stationMap[id].height + ' ' + spans + ' ' + forcastElements + '\r\n';
		
		for(var i=0; i<spans; i++){
			str += 12*(i+1);
			for(var j=0; j<forcastElements; j++){
				if( i+1 > this.maxPeriod/12){
					str += ' 999.9';
					continue;
				}
				
				if(i%2){
					if( 10 == j){
						str += ' ' + Number(f[i].highT).toFixed(1);
						continue;
					}else if( 11 == j){
						str += ' ' + Number(f[i].lowT).toFixed(1);
						continue;
					}
				}
				
				if( 18 == j){
					str += ' ' + f[i].weather;
				}else if(19 == j){
					str += ' ' + f[i].dire;
				}else if(20 == j){
					str += ' ' + f[i].level;
				}else{
					str += ' 999.9';
				}
			}
			
			str += '\r\n';
		
		}
		
		return str;
		
	}
	
	var to2 = function(num){
			return num < 10 ? '0'+num : num;
		}
	
	var getTimeStr = function(time, year,month,minute,second){
		var str = '';
		if(year) str += time.getFullYear();
		if(month) str += to2(time.getMonth()+1);
		
		str += to2(time.getDate() );
		str += to2(time.getHours() );
		
		if(minute) str += to2(time.getMinutes());
		if(second) str += to2(time.getSeconds());
		
		return str;
	}
	var getUTCTimeStr = function(time, year,month,minute,second){
		var str = '';
		if(year) str += time.getUTCFullYear();
		if(month) str += to2(time.getUTCMonth()+1);
		
		str += to2(time.getUTCDate() );
		str += to2(time.getUTCHours() );
		
		if(minute) str += to2(time.getUTCMinutes());
		if(second) str += to2(time.getUTCSeconds());
		
		return str;
	}
	
	var czbForcastFileName = '';
	
	this.setCzbForcastFileName = function(){
		var toN = function(num,n){
			return num < Math.pow(10,n-1) ? '0'+toN(num,n-1) : num;
		}
		
		var period = isSingleForcast ? toN(this.maxPeriod,3) : toN(possibleMaxPeriod,3);
	
		czbForcastFileName = 'Z_SEVP_C_'+cityCode+'_'+
		getUTCTimeStr(forcastEditTime,true,true,true,true)+
		'_P_RFFC-SPCC-'+
		getUTCTimeStr(forcastBeginTime,true,true,true)+
		'-'+period+'12.TXT';
	}
	this.generateAllForcast = function(){
		this.updateForcast();
		
		this.setCzbForcastFileName();
		
		var str = 'ZCZC\r\n';
		str += 'FSCI50 '+cityCode+' '+getUTCTimeStr(forcastEditTime,false,false,true)+'\r\n';
		str += getUTCTimeStr(forcastBeginTime,true,true) + 
				'时' + cityName + '订正预报产品\r\n';
		str += 'SPCC '+ getUTCTimeStr(forcastBeginTime,true,true) +'\r\n';
		str += isSingleForcast ? '1' : stationCount;
		str += '\r\n';
		
		for(var id in forcastJsonCode){
			if(id == '00000') continue;
			
			if(isSingleForcast){
				if(id != singleCityID) continue;
			}
			str += this.generateSingleForcast(id, forcastJsonCode[id]);
		}
		
		str += 'NNNN';
		
		return str;
	}
	
	
	this.viewMessage = function(){
		//$('#preview-czb').text(JSON.stringify(forcastJsonCode) );//, null,'<pre>'++'</pre>' '\t'
		$('#preview-czb').html(this.generateAllForcast().replace(/\n/g,'<br/>'));
		
		$('#dialog-preview').dialog( "option" , {title:czbForcastFileName}).dialog( "open" );
	}
	
	this.PostMessage = function(){

		var jqxhr = $.post("service/service.php", 
			{	
				action:'postCzb',
				type : messageType,
				json : JSON.stringify(forcastJsonCode),
				title: czbForcastFileName,
				text : this.generateAllForcast(),
				ftime: getTimeStr(forcastBeginTime,true,true,true,true)
			},
			function(data) {
			  $('#preview-czb').html(data);
			  $('#dialog-preview').dialog( "option" , {title:''}).dialog( "open" );
			},'text')
		.done(function() { //alert("second success"); 
		})
		.fail(function() { alert("网络连接异常，请稍后重试！"); })
		.always(function() { //alert("complete"); 
		});
	}
}