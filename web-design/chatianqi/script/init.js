$(function(){
	//inner var
	
	var setSaved = {};
	var paramSaved;
	
	//core function
	
	function saveSet(){
		$('#app-set input,#app-set select').each(function(){
			setSaved[this.id] = $(this).val();
		})
		
		paramSaved = $('#app-set input,#app-set select').serialize();
		
		$('.onetime:visible').each(function(){//retrive all
			var timestr = $(this).attr('timestr');
			$(this).remove();
			addone(timestr);
		})
		
		$('#description').html('');
		$('#overlay-set input:checked').each(function(){
			
			var label = $('label[for="'+this.id+'"]').text();
			var overlay = $(this).attr('overlay');
			var html = '<div for="'+overlay+'">'+label+'</div>';
			
			$('#description').append(html);
		})
		$('#description > div').height(Number($('#imgheight').val() )+10 );//$('.overlay').innerHeight()
	}
	
	function cancleSet(){
		$('#app-set input,#app-set select').each(function(){
			$(this).val( setSaved[this.id] );
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
		
		var newoverlay = $('#nextone .overlay').clone();

		//var para = $('#app-set input,#app-set select').serialize();//$.param(setSaved) //
		
		$('#overlay-set input:checked').each(function(){
			var url = 'ncl.php?overlay='+$(this).attr('overlay')+ '&datetime='+ timestr + '&imgheight=' + $('#imgwidth').val() + '&' + paramSaved;
			
			newoverlay.find('img.fnlpic').attr('src',url);
			
			newone.append(newoverlay.clone());	
		});
		
		
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
			minDate:'2004-01-01',
			maxDate:'2012-01-31',
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
	
		saveSet();
	
		$('#apply-set').hide();
		$('#cancle-set').hide();
		$('#app-set').hide();
		$('#display-set').show();
	});
	$('#cancle-set').click(function(){
		cancleSet();
		
		$('#apply-set').hide();
		$('#cancle-set').hide();
		$('#app-set').hide();
		$('#display-set').show();
	});
	
	$('#content').on('click', '.delete-one', function(){
		$(this).parents('.onetime').remove();
		
		if(!$('.onetime:visible').length){
			$('#description').hide();
		}
		
		resizePageWidth();
	})
	
	$('#addone').click(function(){
		$("#select-datetime-dialog" ).dialog('open');
	})
	
	//exec
	saveSet();
	addone('2012010100');
})
