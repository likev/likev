<?php
function vlogin($url,$request){
    //在当前或系统目录下生成一个随机文件名的临时文件
    $cookie_jar = tempnam("","");//'./tmp','cookie'
	//echo $cookie_jar;
	//echo file_get_contents($cookie_jar);
    $ch = curl_init(); //初始化curl模块
	//echo "<pre>curl_init: ".$ch;
    curl_setopt($ch, CURLOPT_URL,$url);//登录页地址
	//curl_setopt($ch, CURLOPT_PORT, 8080);//端口
    curl_setopt($ch, CURLOPT_POST, 1);//post方式提交
    curl_setopt($ch, CURLOPT_POSTFIELDS, $request);//要提交的内容
    //把返回$cookie_jar来的cookie信息保存在$cookie_jar文件中
	curl_setopt($ch, CURLOPT_AUTOREFERER, 1);
	//curl_setopt($ch, CURLOPT_FOLLOWLOCATION, true);
    curl_setopt($ch, CURLOPT_COOKIEJAR, $cookie_jar);
	curl_setopt($ch, CURLOPT_USERAGENT, 'Mozilla/5.0 (Windows NT 5.1; rv:2.0) Gecko/20100101 Firefox/4.0');
    
	//设定是否将返回的数据保存给变量
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    //设定是否返回头信息
    curl_setopt($ch, CURLOPT_HEADER, true);  
    //设定是否输出页面内容
    curl_setopt($ch, CURLOPT_NOBODY, false);
	$header = curl_exec ($ch);
	//echo curl_error($ch);
    //echo 'login: '.$header.'</pre>';
	
	
	
	/*
HTTP/1.1 302 Found
Server: nginx/0.6.31
Date: Wed, 18 May 2011 03:36:00 GMT
Content-Type: text/html
Transfer-Encoding: chunked
Connection: close
X-Powered-By: PHP/4.3.9
Set-Cookie: PHPSESSID=1751c2566b9b8f2af61faec1ed0e8c70; path=/
Expires: Thu, 19 Nov 1981 08:52:00 GMT
Cache-Control: no-store, no-cache, must-revalidate, post-check=0, pre-check=0
Pragma: no-cache
Location: index.php
	*/
	
	$match_patten = "#(PHPSESSID=\w+);#";
	preg_match($match_patten, $header,$out);
	//print_r($out);

    curl_close($ch); //get data after login        
    //return $cookie_jar;
	return $out[1];
}
   
//登录成功后通过cookies获取页面内容
function get_content_by_cookie($url,$cookie_str){
    $ch2 = curl_init();        
    curl_setopt($ch2, CURLOPT_URL, $url);
	//curl_setopt($ch2, CURLOPT_PORT, 8080);//端口
    curl_setopt($ch2, CURLOPT_HEADER, false);
    curl_setopt($ch2, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch2, CURLOPT_COOKIE, $cookie_str);
    $content=curl_exec($ch2);        
    curl_close($ch2);
    return $content;
}

function clear_cookie($cookie_tmp_name){
    @unlink($cookie_tmp_name);
}
?>