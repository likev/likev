$(function(){
	//inner var
	
	var setSaved = {};
	var paramSaved;
	var imgSet = [];
	
	//core function
	function loadNextImg(set, i){
		if(i >= set.length ) return;
		//console.log(imgSet);
		var loadnext = (function(j){
				return function(e){
					//setTimeout(function(){;console.log(j)},1000);
					loadNextImg(set, j);
				}
			})(i+1);
		
		if( ! set[i] ){ 
			loadnext();
			return;
		}
		
		var img = set[i].jdom;
		imgReady(set[i].url, loadnext);
		img.attr('src',set[i].url);
	}
	
	function saveSet(){
		$('#app-set input,#app-set select').each(function(){
			var target = $(this);
			
			if(target.is(':checkbox') ){
				setSaved[this.id] = this.checked;
			}else{
				setSaved[this.id] = $(this).val();
			}	
		})
		
		paramSaved = $('#app-set input,#app-set select').serialize();
				
		$('#description').html('');
		$('#overlay-set input:checked').each(function(){
			
			var label = $('label[for="'+this.id+'"]').text();
			var overlay = $(this).attr('overlay');
			var html = '<div for="'+overlay+'">'+label+'</div>';
			
			$('#description').append(html);
		})
		$('#description > div').height(Number($('#imgheight').val() )+10 );//$('.overlay').innerHeight()
		
		$('.onetime:visible').each(function(){//retrive all
			var timestr = $(this).attr('timestr');
			$(this).remove();
			addone(timestr);
		})
		
		
	}
	
	function cancleSet(){
		$('#app-set input,#app-set select').each(function(){
			var target = $(this);
			
			if(target.is(':checkbox') ){
				this.checked =  setSaved[this.id];
			}else{
				$(this).val( setSaved[this.id] );
			}
			
		})
	}
	
	function addone(timestr){
		
	
		var newone = $('#nextone')
						.clone()
						.removeAttr('id')
						.attr('timestr',timestr);
		newone.children('.overlay').remove();
		
		var title = timestr.substr(0,4)+'-'
					+timestr.substr(4,2)+'-'
					+timestr.substr(6,2)+'日 '
					+timestr.substr(8,2)+'时';
		
		newone.find('.time-title h3').text(title);
		
		//load each overlay

		$('#overlay-set input:checked').each(function(){
			//pics/logo_twitter.png
			var url = 'http://chatianqi.org/ncl.php?overlay='+$(this).attr('overlay')+ '&datetime='+ timestr + '&imgheight=' + $('#imgwidth').val() + '&' + paramSaved;
			
			var newoverlay = $('#nextone .overlay').clone();

			var img = newoverlay.find('img.fnlpic');
			
			newone.append(newoverlay);
			
			imgSet.push({jdom: img, url: url});

		});
		

		
		//load one time
		$('.onetime').each(function(){
		
			if( $(this).attr('timestr') > timestr){
				$(this).before(newone);
				return false;
			}
		})
		
		var width = $('#imgwidth').val(), height = $('#imgheight').val();
		$('.pic-bound').height(height).width(width);
		
		resizePageWidth();
	}
	
	function resizePageWidth(){
		var width = $('.onetime').length * $('.onetime').outerWidth();
		$('#content').width(width);
	}
	
	//ui
	$("#select-datetime-dialog" )
		.dialog({ 
			autoOpen: false, 
			modal:true, 
			width:480, 
			height:460,
			buttons: {
				"取消": function() {
					$( this ).dialog( "close" );
				},
				"确定": function() {
					
					$( this ).dialog( "close" );
					
					var timestr = $.trim($('#addoneDate').val() ).replace(/-/g,'');
					timestr += $('#addoneHour').val();
					
					addone(timestr);
					
					$('#description').show();
				}
			}
		});
	
	$('#addoneDate').datepicker({
			dateFormat: 'yy-mm-dd',
			minDate:'2000-01-01',
			maxDate:'2012-03-01',
			changeMonth: true,
			changeYear: true,
			//showButtonPanel: true,
			showOtherMonths: true,
			selectOtherMonths: true,
			onSelect: function(dateText, inst) {
				
			}
		});
	
	//events
	$('#display-set').click(function(){
		$('#app-set').show();
		
		$(this).hide();
		$('#cancle-set').show();
	})
	
	$('#app-set').change(function(){
		$('#apply-set').show();
		
	});
	
	$('#apply-set').click(function(){
	
		$('#apply-set').hide();
		$('#cancle-set').hide();
		$('#app-set').hide();
		$('#display-set').show();
		
		var index;
		for(index in imgSet){
			imgSet[index] = null;
		}
		
		saveSet();
		loadNextImg(imgSet,0);
	});
	$('#cancle-set').click(function(){
		cancleSet();
		
		$('#apply-set').hide();
		$('#cancle-set').hide();
		$('#app-set').hide();
		$('#display-set').show();
	});
	
	$('#content').on('click', '.delete-one', function(){
		var jdom = $(this).parents('.onetime');
		
		jdom.find('img.fnlpic').each(function(){
			var index;
			for(index in imgSet){
				if(imgSet[index] && this === imgSet[index].jdom[0] ) imgSet[index] = null;
			}
		})
		//console.log(imgSet);
		jdom.remove();
		
		if(!$('.onetime:visible').length){
			$('#description').hide();
			$('#search-bar').removeClass('top-search').addClass('home-search');
		}
		
		resizePageWidth();
	})
	
	$('#addone').click(function(){
		var timestr = $.trim($('#addoneDate').val() ).replace(/-/g,'');
		timestr += $('#addoneHour').val();

		$('#description').show();
		$('#search-bar').removeClass('home-search').addClass('top-search');
		
		addone(timestr);
		loadNextImg(imgSet,0);
	})
	
	//exec
	saveSet();
//	addone('2012010100');

})
