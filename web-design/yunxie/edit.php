<!doctype html>
<html>
	<head>
		<meta charset="utf-8">
	  
		<meta name="description" content="云笔记 云复制粘贴" >
	  
		<title>云写-在线保存文字,随时随地复制粘贴</title>
		
		<style>
		#container{
			margin:20px 30px 20px 20px;
			
		}
		#message{
			font-family: Consolas,Menlo,"Liberation Mono",Courier,monospace;
			font-size: 17px;
			width:100%;
			clear:both;
		}
		#input-tips{
			float:left;
		}
		#input-tips h3{
			margin-top:0;
		}
		#conflict-tips{
			float:left;
			display:none;
		}
		</style>

		<script src="js/jquery.min.js"></script>
		<script src='js/textareaAutoHeight.js'></script>
		<script>
			var yunxie = 	
			<?php
				require_once('service/functions.php');
				
				$name = $_GET['name'];
				$mes = '';
				$version = 0;
				
				if(is_user_exit($name) ){
					$result = get_text_version_from_name($name);
					
					$mes = $result->message ;
					//$mes = htmlspecialchars($result->message, ENT_QUOTES | ENT_HTML401);
					//$mes = str_replace(array("\\","\r\n","\n"), array("\\\\","\\n","\\n"), $mes);
					
					$version = $result->mes_version;
				}else{
					add_user($name);
				}
				
				$result = array("name"=>$name, "message"=>$mes, "version"=>$version, "forcesave"=>0, "forceget"=>0, "conflict"=>0, "lastdone"=>1);
				echo json_encode($result);
			/*	*/
			?>
		</script>
		<script>
			$(function(){
				$('#message').tah({
					moreSpace:10,   //输入框底部预留的空白, 默认10, 单位像素
					maxHeight:800,  //指定Textarea的最大高度, 默认600, 单位像素
					animateDur:100  //调整高度时的动画过渡时间, 默认200, 单位毫秒
				});
			
				$('#message').val(yunxie.message);
				
				var saveData = function(){
					var new_message = $('#message').val();
					yunxie.lastdone = 0;
					var jqxhr = $.post("service/save.php", 
						{    
							action:'savedata',
							name : yunxie.name,
							message: new_message,
							version: yunxie.version,
							force :yunxie.forcesave
						},
						function(result) {
							if(result.state === 'ok'){
								yunxie.message = new_message;
								yunxie.version = result.version;
								yunxie.conflict = 0;
								yunxie.forcesave = 0;
								
								$("#conflict-tips").hide();
							}else if(result.state === 'conflict'){
								yunxie.conflict = 1;
								$("#conflict-tips").show();
							}
						},'json')
						.done(function() { //alert("second success"); 
						})
						.fail(function() {// alert("网络连接异常，请稍后重试！"); 
						})
						.always(function() { //alert("complete");
							yunxie.lastdone = 1;
						});
				}
				
				var getData = function(){
									
					var jqxhr = $.post("service/save.php", 
						{    
							action:'getdata',
							name : yunxie.name,
							version: yunxie.version
						},
						function(result) {
							var now_message = $('#message').val();
							if(result.state === 'new'){
								if(yunxie.message === now_message || yunxie.forceget){
									yunxie.message = result.message;
									yunxie.version = result.version;
									
									yunxie.forceget = 0;
									$("#conflict-tips").hide();
									
									$('#message').val(yunxie.message);
								}
							}
						},'json')
						.done(function() { //alert("second success"); 
						})
						.fail(function() { //alert("网络连接异常，请稍后重试！"); 
						})
						.always(function() { //alert("complete"); 
						});
				}
				
				setInterval(function(){
					var new_message = $('#message').val();
					if(!yunxie.conflict && yunxie.lastdone && new_message !== yunxie.message){
						saveData();

					}
				},1000);
				
				setInterval(function(){
					var new_message = $('#message').val();
					if( new_message === yunxie.message){//本地没变化
						getData();
					}
				},1000);
				
				$('#force-save').click(function(){
					yunxie.forcesave = 1;
					saveData();
				})
				
				$('#force-get').click(function(){
					yunxie.forceget = 1;
					getData();
				})
			})
		</script>
		
		<script type="text/javascript">

		  var _gaq = _gaq || [];
		  _gaq.push(['_setAccount', 'UA-9425897-7']);
		  _gaq.push(['_trackPageview']);

		  (function() {
			var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
			ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
			var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
		  })();

		</script>
	</head>
	<body>
		<div id="container">
			<div id='input-tips'><h3>在下面输入的文字将自动保存</h3></div> <div id='conflict-tips'>（数据冲突，<a href='#' id='force-save'>强制保存</a> 或者 <a href='#' id='force-get'>获取远程数据</a> ）</div>
			<textarea id='message' rows=10 required="required" autofocus=false></textarea>
		</div>

	</body>
</html>
