<?php
require_once("vlogin.php");

if(extension_loaded('zlib')) ob_start('ob_gzhandler');
//header("Content-Type: application/json; charset=utf-8");

if($_GET['history']){
//$history_rain_url = "http://218.28.7.244:8080/ylnew/biao.php?type=*qw*fxfs*yl&city=HN&time=2011-05-18%2010:58";
	$t_wind_info_url = "http://218.28.7.244:8080/ylnew/biao.php?type=*qw*fxfs&city=HN&time=".rawurlencode($_GET['wind2Time']);
}
else{
//空格等必须经过编码
	$date = new DateTime();
	$date->sub(new DateInterval('PT2M'));
	$dataStr = $date->format('Y-m-d%20H:i');
	
	$t_wind_info_url = "http://218.28.7.244:8080/ylnew/biao.php?type=*qw*fxfs&city=HN&time=".$dataStr;
}

$cookie_str = vlogin('http://218.28.7.244:8080/ylnew/sess.php','username=hnrain&userpassword=BJAY2008');
$result = get_content_by_cookie($t_wind_info_url,$cookie_str);

/*
                <TR class=tContent>
          <TD>HNZZC0B3</TD>
          <TD>花园口</TD>
          <TD>郑州 郑州市</TD>

          <TD>O2261</TD>
         <TD>33.5</TD><TD>283度 1.4m/s</TD><TD>0</TD>           </tr>
*/
//
$match_patten = "#<TR class=tContent>\s+<TD>(HN[A-Z0-9]+\d+)</TD>\s+<TD>\S+</TD>\s+<TD>\S+\s\S+</TD>\s+<TD>O?\d+</TD>\s+<TD>([1-9]\d*\.?\d*|0\.\d*)</TD><TD>(\d+)\S+\s([1-9]\d*\.?\d*|0\.\d*)m/s</TD>\s+</tr>#";

preg_match_all($match_patten, $result,$out, PREG_PATTERN_ORDER);

$sizeofout1 = count($out[1]);
$retern_json = array();
for($index = 0; $index != $sizeofout1; $index++){
	$retern_json[$out[1][$index] ] = array($out[2][$index], $out[3][$index], $out[4][$index]);
}
//echo "<pre>";
//echo $result;
echo json_encode($retern_json);

//echo "</pre>";
?>