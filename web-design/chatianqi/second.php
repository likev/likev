<?php
//get free cpu and memeory
function get_proc_count($name){
	$cmd =  "ps -e";
	$output = shell_exec($cmd);

	$result = substr_count($output, ' '.$name);
	return $result;
}

get_proc_count('apache2');
?>
