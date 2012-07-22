<?php
require_once('deal.request.php');			//引入message.class.php

/**/

if($_SERVER[HTTP_REFERER] != 'http://current.sinaapp.com/'){
	die(0);
}

$action = $_POST['action'];				//获取提交的action值
if($action == 'getdata')						//如果action值为'getall'，则
{
	$weather = get_weather($_POST);
	echo json_encode($weather);
}
else if($action == 'getZdb')				//如果action值为'addnew'，则
{
		
}
else if($action == 'postCzb')
{

}
else
{
	//echo json_encode(EditCZB::getZdb());
}





?>