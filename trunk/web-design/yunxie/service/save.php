<?php

require_once('functions.php');

/**/

if($_SERVER[HTTP_REFERER] != 'http://current.sinaapp.com/'){
	//die(0);
}

$action = $_POST['action'];				//获取提交的action值
if($action == 'savedata'){						//如果action值为'getall'，则
	$name = $_POST['name'];
	$message = $_POST['message'];
	$version = $_POST['version'];
	$force = $_POST['force'];
	
	$pre_mes = get_text_version_from_name($name);
	
	$pre_version = $pre_mes->mes_version;
	
	$result = array();
	
	if($pre_version == $version || $force){
		save_text_version_of_name($name, $message);
		
		$result['state'] = 'ok';
		$result['version'] = $pre_version+1;
		echo json_encode($result);
	}else{
		$result['state'] = 'conflict';
		$result['version'] = $pre_version;
		$result['message'] = $pre_mes->message;
		
		echo json_encode($result);
	}
}
else if($action == 'getdata')				//如果action值为'addnew'，则
{
	$name = $_POST['name'];
	$version = $_POST['version'];

	$cur_mes = get_text_version_from_name($name);
	
	$cur_version = $cur_mes->mes_version;
	
	$result = array();
	
	if($cur_version > $version){
		$result['state'] = 'new';
		$result['version'] = $cur_version;
		$result['message'] = $cur_mes->message;
		
		echo json_encode($result);
	}else if($cur_version == $version){
		$result['state'] = 'none';

		echo json_encode($result);
	}	
}
else if($action == 'post')
{

}
else
{
	//echo json_encode(EditCZB::getZdb());
}





?>