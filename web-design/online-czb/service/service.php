<?php
require_once('message.class.php');			//引入message.class.php

/**/
$action = $_POST['action'];				//获取提交的action值
if($action == 'getLast')						//如果action值为'getall'，则
{
	$messages1 = EditCZB::readLastest();
	echo json_encode($messages1);
}
else if($action == 'getZdb')				//如果action值为'addnew'，则
{
	echo 'ok';								//输出'ok'
}
else if($action == 'postCzb')
{
	$messages = new EditCZB($_POST['ftime'],$_POST['type'],$_POST['json'],$_POST['text'],$_POST['title']);
	echo $messages->insert();
	echo $messages->putFtp();
}
else
{
	$messages1 = EditCZB::readLastest();
	echo json_encode($messages1);
}





?>