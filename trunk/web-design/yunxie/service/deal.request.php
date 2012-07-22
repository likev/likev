<?php
require_once('db.class.php');		//引入db.class.php

function trans_google_level($level){
	switch($level){
		case 1:
		case 2:
		case 3:return 1;
		case 4:
		case 5: 
		case 6:return 2;
		case 7: 
		case 8:return 16;
		case 9:
		case 10:return 32;
		case 11:
		case 12: 
		case 13:
		case 14: return 64;
		
		default: return 1;
	}
}

function get_lastest_tablename(){
	$date = new DateTime();
	$table_name =  'surface'. $date->format('Ym');
	
	$mydb = new DB();
	$sql = "show tables like '$table_name'";

	if($mydb->doSql($sql) <1){
	
		$date = new DateTime($date->format('Y-m-1') );
		$date = $date->sub(new DateInterval('P1M'));
		$table_name =  'surface'. $date->format('Ym');
	}
	
	return $table_name;
}

function get_near_station($option, $limit_num = 60){
	$mydb = new DB();
	
	$center_lon = ($option['left']+$option['right'])/2;
	$center_lat = ($option['top']+$option['bottom'])/2;
	
	$level = trans_google_level($option['level']);
	
	$sql  = 'SELECT id, lon, lat, level ';
	$sql .= 'FROM station ';
	$sql .= 'WHERE level <='.$level.' and lon>'.$option[left].' and lon<'.$option[right];
	$sql .= ' and lat>'.$option[bottom].' and lat<'.$option[top];
	$sql .= " ORDER BY sqrt( (lon-$center_lon)*(lon-$center_lon) + (lat-$center_lat)*(lat- $center_lat) ) ";
	$sql .= " LIMIT $limit_num";
	
	return $mydb -> getObjListBySql($sql);
}

function get_weather($option){
	$mydb = new DB();
	
	$stations = get_near_station($option);
	
	if($option[time] = 'lastest'){
		
		$table_name = get_lastest_tablename();
		
		$obj = $mydb -> getObjListBySql("select max(recordTime) as time from $table_name limit 1");
		$requestTime = $obj[0]->time;
	}
	else{
		$requestTime = $option[time];
	}
	
	$datas = array();
	
	for($i = 0; $i < count($stations); $i++){
		$sql  = "select temperature,windDirection,windSpeed,totalCloudAmount,seaLevelPressure,visibility,dewpoint, presentWeather,hour6precipitation,pastWeather1,pastWeather2 from $table_name ";
		$sql .= 'where stationId = '.$stations[$i]->id .' and recordTime = "'.$requestTime .'" ';
		$sql .= 'limit 1';
		
		
		
		$weather = $mydb -> getObjListBySql($sql);
		
		if(! count($weather)) continue;
		
		$s = $stations[$i];
		$w = $weather[0];
		
		$datas[] = array($s->id, $s->lat, $s->lon, $s->level, $w->temperature, $w->windDirection, $w->windSpeed, $w->totalCloudAmount, $w->seaLevelPressure ,$w->visibility, $w->dewpoint, $w->presentWeather, $w->hour6precipitation, $w->pastWeather1,$w->pastWeather2);
	}
	$results[data] = $datas;
	$results[time] = $requestTime;
	
	return $results;
}

?>