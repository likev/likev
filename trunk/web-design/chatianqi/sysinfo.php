<?php
//get free cpu and memeory
function get_cpufree(){
	$cmd =  "top -n 1 -b -d 0.1 | grep 'Cpu'";//'free -m'- 
	$lastline = exec($cmd,$output);

	preg_match('/(\S+)%id/',$lastline, $matches);
	$cpufree = $matches[1];
	return $cpufree;
}

function get_memfree(){
	$cmd =  'free -m';//"top -n 1 -b -d 0.1 | grep 'Cpu'"
	$lastline = exec($cmd,$output);

	preg_match('/Mem:\s+(\d+)/',$output[1], $matches);
	$memtotal = $matches[1];
	preg_match('/(\d+)$/',$output[2], $matches);
	$memfree = $matches[1]*100.0/$memtotal;
	
	return $memfree;
}

function get_proc_count($name){
	$cmd =  "ps -e";
	$output = shell_exec($cmd);

	$result = substr_count($output, ' '.$name);
	return $result;
}
?>
