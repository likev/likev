<?php
require_once('db.class.php');		//引入db.class.php


function get_unique_name(){
	$mydb = new DB();
	
	$sql_max = "select max(num) as maxnumber from available_num";
	$max_num = $mydb -> getObjListBySql($sql_max);
	
	$max_num = $max_num[0]->maxnumber;
	
	$sql_min = "select min(num) as minnumber from available_num";
	$min_num = $mydb -> getObjListBySql($sql_min);
	$min_num = $min_num[0]->minnumber;
	
	if($max_num == $min_num){
		$mydb -> doSql('delete from available_num where num = '.$max_num );
		$mydb -> insertData('available_num', array('num'),array($max_num+1) );
		
		return $max_num;
	}else{
		$mydb -> doSql('delete from available_num where num = '.$min_num );
		return $min_num;
	}
	
}

function is_user_exit($name){
	$mydb = new DB();
	
	$sql = "select name from user where name = '".mysql_real_escape_string($name)."'";
	$result = $mydb -> rows_of_select( $sql );
	
	return ( $result == 1 );
}

function add_user($name){
	$mydb = new DB();
	
	$sql  = "insert into user (name, createtime, lastreadtime, message) ";
	$sql .= "values ( '".mysql_real_escape_string($name)."', NOW(), NOW(), ' ')";
	
	$result = $mydb -> doSql($sql);
	
	return $result;
}

function get_text_version_from_name($name){
	$mydb = new DB();
	
	$sql = "select message, mes_version from user where name = '".mysql_real_escape_string($name)."'";
	$result = $mydb -> getObjListBySql($sql);
	
	$result = $result[0];
	
	return $result;
	
}

function save_text_version_of_name($name, $message){
	$mydb = new DB();
	
	$sql = "update user set message = '".mysql_real_escape_string($message)."' , mes_version = mes_version+1 where name = '".mysql_real_escape_string($name)."'";
	$result = $mydb -> doSql( $sql );
	
	return $result;
}
?>