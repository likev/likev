<?php
require_once('message.class.php');			//引入message.class.php

/**/
$action = $_POST['action'];				//获取提交的action值
if($action == 'getLast')						//如果action值为'getall'，则
{
	$lastForcast = EditCZB::readLastest();
	echo json_encode($lastForcast);
}
else if($action == 'getZdb')				//如果action值为'addnew'，则
{
	echo json_encode(EditCZB::getZdb());	
}
else if($action == 'postCzb')
{
	$messages = new EditCZB($_POST['ftime'],$_POST['type'],$_POST['json'],$_POST['text'],$_POST['title']);
	if($messages->insert() ){
		echo '<br>预报已保存至数据库...';
	}else{
		echo '<br>预报保存至数据库失败！';
	}
	
	if($messages->putFtp() ){
		echo '<br>预报已成功上传至FTP';
	}else{
		echo '<br>预报上传FTP失败，请重新上传！';
	};
}
else
{
	//echo json_encode(EditCZB::getZdb());
}





?>