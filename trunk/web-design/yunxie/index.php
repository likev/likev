<?php
require_once('service/functions.php');		//引入db.class.php

$num = get_unique_name();
header("Location: http://yunxie.me/".$num);
?>