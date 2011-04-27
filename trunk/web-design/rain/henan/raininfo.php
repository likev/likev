<?php
header("Content-Type: application/json; charset=utf-8");

$match_patten = "#<tr class='tContent'><td>(HN[A-Z0-9]+\d+)</td><td>\S+</td><td>\d+</td><td>[:\d\s-]+</td><td>(\d+\.+\d*)</td></tr>#";
if($_GET['history']){
//$history_rain_url = "http://www.hnaws.com/infodisplay.asp?Cityflag=HN&InfoT=historical&DispT=intable&StartT=2011-2-28%2020:00&EndT=2011-3-1%2015:32";
	$rain_info_url = "http://www.hnaws.com/infodisplay.asp?Cityflag=HN&InfoT=historical&DispT=intable&StartT=".rawurlencode($_GET['startTime'])."&EndT=".rawurlencode($_GET['endTime']);	
	$match_patten = "#<tr class='tContent'><td>(HN[A-Z0-9]+\d+)</td><td>\S+</td><td>\d+</td><td>(\d+\.+\d*)</td></tr>#";
}
else{
	$rain_info_url = "http://www.hnaws.com/infodisplay.asp?Cityflag=HN&InfoT=realtime&DispT=intable&StartT=undefined&EndT=undefined";
}

$strfile = file_get_contents($rain_info_url);

if(!$strfile){
	exit();
}

//<tr class="tContent"><td>HNLYMJA0</td><td>S_小浪底</td><td>40077230132</td><td>2011-3-1 15:11:00</td><td>18.2</td></tr>
preg_match_all($match_patten, $strfile,$out, PREG_PATTERN_ORDER);

foreach($out[1] as $index => $name){
	$raininfo[$name] = $out[2][$index];
}

echo json_encode($raininfo);

?>