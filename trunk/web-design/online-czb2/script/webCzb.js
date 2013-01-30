
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

/*
	生成编辑界面和指导报界面
----------------------------------------------------------
*/	
	var getSingleHtml = function(id){
		var html = 
		
		"<tr class='" + (id=='00000' ? 'base ' : '') + "station' num='" + id + "'>" + "<td class='name'>" + stationMap[id].name + "</td><td class='value weather' name='weather'>晴天</td><td class='value wind-dire'  name='wind-dire'>静风</td><td class='value wind-level'  name='wind-level'>≤ 3级</td><td class='value high-t'  name='high-t'>13</td><td class='value low-t'  name='low-t'>-3</td></tr>";
		
		return html;
	}
	this.getUIHtml = function(part){
		var html="";
		
		if('#edit-czb' == part) html += getSingleHtml('00000');
		
		for(var i=0; i < option.stations.length; i++){
			id = option.stations[i];
			html += getSingleHtml(id);
		}
		return html;
	}
/*
----------------------------------------------------------
*/
	
	var forcastElements = option.forcastElements;
	var possibleMaxPeriod = option.possibleMaxPeriod;
	
	this.timeout = 0; //保存控制预报列表隐藏的定时器
	this.focusDom = null; //保存最近的焦点输入dom
	this.maxPeriod = 168; //保存当前最大预报时次
	this.haveSelectMessage = false;
	
	var isSingleForcast = false; //当前是否在制作单站预报
	
	this.timeValue = 12; //保存当前预报时次
	
	var forcastJsonCode = {}; //预报值保存在这个数组里
	var lastForcastJson = {};//保存上次预报值
 
	var appOpenTime = new Date(); //打开网站的时间
	var forcastEditTime = new Date(0); //制作预报的时间
	var forcastBeginTime = new Date(0); //预报的起始时刻
	
	var lastForcastBegin = forcastBeginTime;
	
	var weatherMap = {
		"0.0": '晴', 
		"1.0": '多云', 
		"2.0": '阴', 
		"3.0": '阵雨', 
		"4.0": '雷阵雨', 
		"5.0": '冰雹', 
		 
		"7.0": '小雨', 
		"8.0": '中雨', 
		"9.0": '大雨', 
		"10.0": '暴雨', 
		"11.0": '大暴雨', 
		"12.0": '特大暴雨', 
		
		"19.0": '冻雨',
		"6.0": '雨夹雪',
		
		"13.0": '阵雪', 
		"14.0": '小雪', 
		"15.0": '中雪', 
		"16.0": '大雪', 
		"17.0": '暴雪', 
		
		"18.0": '雾',
		"53.0": '霾',
		
		 
		"20.0": '沙尘暴', 
		"29.0": '浮尘', 
		"30.0": '扬沙',
		"31.0": '强沙尘暴'
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

/*
获取上次的预报 和 省台的指导报
---------------------------------------------------------------------
*/	
	var getDateFromStr = function(str){
		var value = $.trim(str).split('-');
		
		return new Date(value[0],value[1]-1,value[2],value[3],0,0)
	}
	
	//从数据库中取出上次的预报JSON
	this.getLastForcastJson = function(){
		$('#container').hide();

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
			$('#container').show();			
		});
	};

	
	var lastestZdbForcast = {};
	var lastestZdbBegin = new Date(0);
	
	var lastestZdbFilename;
	this.getZdbName = function(){
		return lastestZdbFilename;
	}
	
	this.getLatestZdb = function(){

		var jqxhr = $.post("service/service.php", 
			{	
				action:'getZdb'
			},
			function(json) {
			  //alert("success");
			  lastestZdbForcast = json.forcast;
			  lastestZdbBegin = moment.utc(json.zdbBegin, "YYYYMMDDHH").local().toDate();
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
	
	
	this.getLastJson = function(){
		this.getLastForcastJson();
		this.getLatestZdb();
	}
/* --------------------------------------------------------------------- */
	
	
/*
动态获取天气和高低温选择列表
---------------------------------------------------------------------
*/
	this.getHighTSelectHtml = function(){
		var curT = $('.base .high-t').text() - 0;

		var html='';
		
		var lowT = $(this.focusDom).siblings('.low-t').text() - 0;
		if(curT-8 > lowT ) lowT = curT-8;
		
		for(var t= lowT; t<curT+8; t++){
			html += '<li>' + t + '</li>'
		}
		return html;
	}
	this.getLowTSelectHtml = function(){
		var curT = $('.base .low-t').text() - 0;

		var html='';
		
		var highT = $(this.focusDom).siblings('.high-t').text() - 0;
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
	

/*
数据模型与UI界面的交互
---------------------------------------------------------------------
*/	
	
	var messageType = '';
	this.setMessageType = function(selectid){
		if('toggle-first' == selectid) messageType = 'first';
		else if('toggle-second' == selectid) messageType = 'second';
		else if('toggle-third' == selectid) messageType = 'third';
		else if('toggle-forth' == selectid) messageType = 'forth';
	}
	
	//基准站改变时 更新其他的站
	this.onBaseChange = function(dom){
		if(! ($(dom).parents(".base").length ) ) return;
		
		if( 'high-t' === $(dom).attr('name') ){
			$('#edit td.high-t').each(function(){
				if(this != dom){
					var diff = stationMap[$(this).parent('.station').attr('num')].highTdiff
					$(this).text( $(dom).text() - (-diff) );
				}
			})
		}else if( 'low-t' === $(dom).attr('name') ){
			$('#edit td.low-t').each(function(){
				if(this != dom){
					var diff = stationMap[$(this).parent('.station').attr('num')].lowTdiff
					$(this).text( $(dom).text() - (-diff) );
				}
			})
		}else{
			//console.log(dom.name + dom.value + $(dom).attr('code'));
			$('#edit td.' + $(dom).attr('name') )
				.text($(dom).text() )
				.attr('code',$(dom).attr('code'));
		}
	}

	//根据日期和时次 初始化forcastEditTime forcastBeginTime
	var initForcastTime = function(){
		
		var selectDay = new Date( appOpenTime.getTime() );
	
		var selectDayId = $('#select-day input[type="radio"]:checked').attr('id');
		var selectMessageId = $('#select-message input[type="radio"]:checked').attr('id');
		
		if( 'toggle-tomorrow' == selectDayId) selectDay.setDate(selectDay.getDate()+1);
		
		var hour = 0, minute = 0, second = 0;
		
		forcastEditTime.setTime(selectDay.getTime());
		forcastBeginTime.setTime(selectDay.getTime());
		
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
	
	//根据thisBegin,lastBegin 获取天气 高低温的偏移量
	var getForcastOffset = function(thisBegin,lastBegin){
		var diffHours = (thisBegin.getTime() - lastBegin.getTime())/1000/3600;
		var lastHour = lastBegin.getHours();
		
		var offset = {
				weather : Number( (diffHours/12).toFixed(0) ),
				highT : 0, 
				lowT : 0
			};
		
		//console.log(lastBegin.getFullYear()+' '+lastBegin.getMonth()+' '+lastBegin.getDate()+' '+lastBegin.getHours());
		
		if( 20 === lastHour ){
			offset.highT = Math.floor(diffHours/24)*2;
			offset.lowT = Math.ceil(diffHours/24)*2;
		}else if( 8 === lastHour){
			offset.highT = Math.ceil(diffHours/24)*2; 
			offset.lowT = Math.floor(diffHours/24)*2;
		}
		
		return offset;
	}
	
	//初始化本次预报Json数据
	this.initForcast = function(){
	
		initForcastTime();
		
		var offset = getForcastOffset(forcastBeginTime,lastForcastBegin);

		forcastJsonCode  = {};
		
		for(var id in stationMap){
			//single station code
			forcastJsonCode[id] = [];
			var last = (lastForcastJson[id] ? lastForcastJson[id] : []);
			
			
			//每个时次
			for(var index=0; index < possibleMaxPeriod/12; index++){
				forcastJsonCode[id][index] = {
						weather: last[index+offset.weather] ? last[index+offset.weather].weather : '0.0',
						dire: last[index+offset.weather] ? last[index+offset.weather].dire : '0.0',
						level: last[index+offset.weather] ? last[index+offset.weather].level : '0.0',
						highT: last[index+offset.highT] ? last[index+offset.highT].highT : option.defaultHighT,
						lowT: last[index+offset.lowT] ? last[index+offset.lowT].lowT : option.defaultLowT
					}
			}
		}
	}
	
	//根据最新的指导报更新UI
	this.updateZDBFromCode = function(){
		var offset = getForcastOffset(forcastBeginTime,lastestZdbBegin);
		
		for(var id in lastestZdbForcast){
			var last = lastestZdbForcast[id] ? lastestZdbForcast[id] : [];
			var index = this.timeValue/12 - 1;
			var forcast = {
						weather: last[index+offset.weather] ? last[index+offset.weather].weather : '0.0',
						dire: last[index+offset.weather] ? last[index+offset.weather].dire : '0.0',
						level: last[index+offset.weather] ? last[index+offset.weather].level : '0.0',
						highT: last[index+offset.highT] ? last[index+offset.highT].highT : '',
						lowT: last[index+offset.lowT] ? last[index+offset.lowT].lowT : ''
					};
					
			//console.log(forcast);
			var jdom = $('#zdb .station[num="'+ id +'"]');
						
			$('td.weather', jdom).attr('code',forcast.weather).text(weatherMap[forcast.weather]);
			$('td.wind-dire', jdom).attr('code',forcast.dire).text(windDireMap[forcast.dire]);
			$('td.wind-level', jdom).attr('code',forcast.level).text(windLevelMap[forcast.level]);
			$('td.high-t', jdom).text(Number(forcast.highT).toFixed(0) );
			$('td.low-t', jdom).text(Number(forcast.lowT).toFixed(0) );
			
		}
	}
	
	//更新时间说明
	var updateCurForcastSpanText = function(timeValue){
		var forcastTime = moment(forcastBeginTime).clone();
		
		//console.log(timeValue);
		forcastTime.add('hours', timeValue - 12);
		
		var str = forcastTime.date()+'日 ';
		
		if(forcastTime.hours() === 8)  str += '白天';
		else str += '夜间';
		
		$('#cur-forcast-span').text(str);
	}
	
	//当改变时次时 更新时间说明 编辑部分UI 指导报UI
	this.updateUIFromJson = function(){
		updateCurForcastSpanText(this.timeValue);

		for(var id in forcastJsonCode){
			var singleCode= forcastJsonCode[id];
			var forcast = singleCode[this.timeValue/12 - 1];
			
			var jdom = $('#edit .station[num="'+ id +'"]');
						
			$('td.weather', jdom).attr('code',forcast.weather).text(weatherMap[forcast.weather]);
			$('td.wind-dire', jdom).attr('code',forcast.dire).text(windDireMap[forcast.dire]);
			$('td.wind-level', jdom).attr('code',forcast.level).text(windLevelMap[forcast.level]);
			$('td.high-t', jdom).text(Number(forcast.highT).toFixed(0) );
			$('td.low-t', jdom).text(Number(forcast.lowT).toFixed(0) );
			
		}
		
		this.updateZDBFromCode();
		
		if((this.timeValue/12)%2){
			$('.station td.high-t').text('');
			$('.station td.low-t').text('');
		}
	}
	
	//从编辑部分UI更新预报JSON
	this.updateJsonFromUI = function(){
		
		var times = this.timeValue/12 - 1;
		
		for(var id in forcastJsonCode){
			var lidom = $('#edit .station[num="'+ id +'"]');
			
			var f = forcastJsonCode[id][times];
			
			f.weather = $('td.weather', lidom).attr('code');
			f.dire = $('td.wind-dire', lidom).attr('code');
			f.level = $('td.wind-level', lidom).attr('code');
			f.highT = $('td.high-t', lidom).text();
			f.lowT =  $('td.low-t', lidom).text();

		}
	}
	
/*
生成报文
-----------------------------------------------------------------------
*/
	
	//生成单站预报
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
	
	var czbForcastFileName = '';
	
	//设置城镇报文件名
	this.setCzbForcastFileName = function(){
		var toN = function(num,n){
			return num < Math.pow(10,n-1) ? '0'+toN(num,n-1) : num;
		}
		
		var period = isSingleForcast ? toN(this.maxPeriod,3) : toN(possibleMaxPeriod,3);
		
		var medit = moment(forcastEditTime).clone(), mbegin = moment(forcastBeginTime).clone();
		
	
		czbForcastFileName = 'Z_SEVP_C_'+cityCode+'_'+ medit.utc().format('YYYYMMDDHHmmss') + 
		
		'_P_RFFC-SPCC-'+ mbegin.utc().format('YYYYMMDDHHmm') + 
		
		'-'+period+'12.TXT';
	}
	
	//生成完整的城镇报
	this.generateAllForcast = function(){
		
		this.setCzbForcastFileName();
		
		var medit = moment(forcastEditTime).clone(), mbegin = moment(forcastBeginTime).clone();
		
		var str = 'ZCZC\r\n';
		str += 'FSCI50 '+cityCode+' '+ medit.utc().format('DDHHmm') +'\r\n';
		str += mbegin.utc().format('YYYYMMDDHH') + 
				'时' + cityName + '订正预报产品\r\n';
		str += 'SPCC '+ mbegin.utc().format('YYYYMMDDHH') +'\r\n'; 
		str += isSingleForcast ? '1' : option.stations.length;
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
				ftime: moment(forcastBeginTime).format('YYYYMMDDHHmmss')
			},
			function(data) {
			  $('#preview-czb').html(data);
			  $('#dialog-preview').dialog( "option" , {title:'返回信息'}).dialog( "open" );
			},'text')
		.done(function() { //alert("second success"); 
		})
		.fail(function() { alert("网络连接异常，请稍后重试！"); })
		.always(function() { //alert("complete"); 
		});
	}
}
/* -----------------------------------------------------------------------  */
