<?php
echo "<pre>";
$output = shell_exec('ls');
echo "shell_exec :<br>$output";

exec('ls',$output);
echo "exec :<br>$output";
?>
