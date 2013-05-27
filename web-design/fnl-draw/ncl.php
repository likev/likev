<?php

$tmpfname = tempnam("./", "FNL");
unlink($tmpfname);
$tmpfname = basename($tmpfname);

$nclbash = 'map500.ncl';

if(isset($_GET['overlay']) ){
	switch($_GET['overlay']){
		case 200:	$nclbash = 'map200.ncl'; break;
		case 500:	$nclbash = 'map500.ncl'; break;
		case 700:	$nclbash = 'map700.ncl'; break;
		case 850:	$nclbash = 'map850.ncl'; break;
		case 925:	$nclbash = 'map925.ncl'; break;
		case 1000:	$nclbash = 'mapsuf.ncl'; break;
		default:break;
	}
	
}

$nclbash = 'nclbash/'.$nclbash ;

$ncl = file_get_contents($nclbash);
$ncl = preg_replace('/^;;imgname/m','imgname= "'.$tmpfname.'" ', $ncl, 1 );

if(isset($_GET['imgwidth']) ){
	$ncl = preg_replace('/^;;wkWidth/m','wks_type@wkWidth = '.$_GET['imgwidth'], $ncl, 1 );
}

if(isset($_GET['imgheight']) ){
	$ncl = preg_replace('/^;;wkHeight/m','wks_type@wkHeight = '.$_GET['imgheight'], $ncl, 1 );
}

if(isset($_GET['datetime']) ){
	$datetime = $_GET['datetime'];
	$year = substr($datetime,0,4);
	$date = substr($datetime,0,8);
	$hour = substr($datetime,8,2);
	
	$replacement = 'fnlname = "../fnldata/'.$year.'/fnl_'.$date.'_'.$hour;
	
	if(strcmp($datetime,'2008093012') < 0 ){
		$replacement .= '_00.grb"';
	}else{
		$replacement .= '_00_c.grb"';
	}
	
	$ncl = preg_replace('/^;;fnlname/m', $replacement, $ncl, 1 );

}

$tmpnclname = tempnam("./", "ncl");
unlink($tmpnclname);
$tmpnclname .= '.ncl';
file_put_contents($tmpnclname, $ncl);

$last_line = exec('export NCARG_ROOT=/usr/local/soft/ncl/;export PATH=/usr/local/soft/ncl/bin:$PATH ;ncl '.$tmpnclname, $out, $retval);
unlink($tmpnclname);

header('Content-type: image/png');
readfile($tmpfname.'.png');
unlink($tmpfname.'.png');
?>

