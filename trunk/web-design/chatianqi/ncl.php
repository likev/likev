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
	
	$replacement = 'fnlname = "/home/ubuntu/mydata/fnldata/'.$year.'/fnl_'.$date.'_'.$hour;
	
	if(strcmp($datetime,'2008093012') < 0 ){
		$replacement .= '_00.grb"';
	}else{
		$replacement .= '_00_c.grb"';
	}
	
	$ncl = preg_replace('/^;;fnlname/m', $replacement, $ncl, 1 );

}

if(isset($_GET['projection']) ){
	$ncl = preg_replace('/^;;mpProjection/m','res@mpProjection = "'.$_GET['projection'].'"', $ncl, 1 );
}

if(isset($_GET['minlat']) ){
	$ncl = preg_replace('/^;;mpMinLatF/m','res@mpMinLatF = '.$_GET['minlat'], $ncl, 1 );
}
if(isset($_GET['maxlat']) ){
	$ncl = preg_replace('/^;;mpMaxLatF/m','res@mpMaxLatF = '.$_GET['maxlat'], $ncl, 1 );
}
if(isset($_GET['minlon']) ){
	$ncl = preg_replace('/^;;mpMinLonF/m','res@mpMinLonF = '.$_GET['minlon'], $ncl, 1 );
}
if(isset($_GET['maxlon']) ){
	$ncl = preg_replace('/^;;mpMaxLonF/m','res@mpMaxLonF = '.$_GET['maxlon'], $ncl, 1 );
}
if(isset($_GET['centerlat']) ){
	$ncl = preg_replace('/^;;mpCenterLatF/m','res@mpCenterLatF = '.$_GET['centerlat'], $ncl, 1 );
}
if(isset($_GET['centerlon']) ){
	$ncl = preg_replace('/^;;mpCenterLonF/m','res@mpCenterLonF = '.$_GET['centerlon'], $ncl, 1 );
	
	$ncl = preg_replace('/^;;mpLambertMeridianF/m','res@mpLambertMeridianF = '.$_GET['centerlon'], $ncl, 1 );
}

$tmpnclname = tempnam("./", "ncl");
unlink($tmpnclname);
$tmpnclname .= '.ncl';
file_put_contents($tmpnclname, $ncl);

$last_line = exec('export NCARG_ROOT=/home/ubuntu/mydata/soft/ncl/;export PATH=/home/ubuntu/mydata/soft/ncl/bin:$PATH ;ncl '.$tmpnclname, $out, $retval);
unlink($tmpnclname);

header('Content-type: image/png');
readfile($tmpfname.'.png');
unlink($tmpfname.'.png');
?>

