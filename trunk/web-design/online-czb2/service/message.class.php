<?php
require_once('db.class.php');		//引入db.class.php

$require_stations = array('57065' , '57066' , '57070' , '57071' , '57073' , '57074' , '57076' , '57077' , '57078' , '57162');
function filter_czb($name)
{
	return !!preg_match('/\S*\d{8}(08|20)\.ZDB\S*/',$name);
}
/*
 * 类名：EditCZB
 * 说明：留言类
 */
class EditCZB
{
	/*
	 * 属性名：$name
	 * 类型：string
	 * 说明：留言人的姓名
	 */
	public $name;
	/*
	 * 属性名：$EditCZB
	 * 类型：string
	 * 说明：留言的内容
	 */	
	public $forcastBegin;
	/*
	 * 属性名：$forcastType
	 * 类型：string
	 * 说明：留言的时间
	 */	
	public $forcastType;
	
	public $forcastJson;
	public $forcastText;

	/*
	 * 方法名：EditCZB()
	 * 说明：构造函数
	 * 参数列表：
	 * 		参数名：$name
	 *			说明：留言人的姓名
	 *			类型：string
	 *			默认值：无
	 * 		参数名：$EditCZB
	 *			说明：留言的内容
	 *			类型：string
	 *			默认值：无
	 * 		参数名：$forcastType
	 *			说明：留言的时间
	 *			类型：datetime
	 *			默认值：无
	 * 返回值：无
	 */		
	public function EditCZB($forcastBegin,$forcastType,$forcastJson,$forcastText,$forcastTitle,$name='')
	{
		$this->name = $name;
		$this->forcastBegin = $forcastBegin;
		$this->forcastType = $forcastType;
		$this->forcastJson = $forcastJson;
		$this->forcastText = $forcastText;
		$this->forcastTitle = $forcastTitle;
	}
	/*
	 * 方法名：readAll()
	 * 说明：读取所有的留言信息
	 * 参数列表：无
	 * 返回值：包含留言数据的数组
	 */			
	public static function readLastest()
	{
		$db = new DB();
		$lastest = $db->getObjListBySql('select postTime,DATE_FORMAT(forcastBegin,"%Y-%c-%e-%k") as forcastBegin,forcastJson,editName from czbEdit where postTime = 
										(select max(postTime) from czbEdit)');
		
		return $lastest[0] ;
	}
	/*
	 * 方法名：insert()
	 * 说明：插入新留言
	 * 参数列表：无
	 * 返回值：无
	 */			
	public function insert()
	{
		$fname = str_replace("'","\'",$this->name);
		$fBegin = str_replace("'","\'",$this->forcastBegin);
		$fType = str_replace("'","\'",$this->forcastType);
		$fJson = str_replace("'","\'",$this->forcastJson);
		$fText = str_replace("'","\'",$this->forcastText);
	
		$dbb = new DB();
		
		$sql = "INSERT INTO czbEdit ( postTime,forcastBegin,forcastType,forcastJson,forcastText,editName ) VALUES (NOW(), '" . $fBegin . "', '" . $fType ."', '". $fJson ."', '". $fText ."', '". $fname . "' )";
				
		return $dbb -> doSql($sql);
	}
	
	public function putFtp()
	{
		$content = iconv("UTF-8", "GB2312", $this->forcastText );
		
		$local_file = 'local.txt';
		$remote_file = iconv("UTF-8", "GB2312", $this->forcastTitle );
		
		$size = file_put_contents($local_file, $content);//$local_file
		
		$ftp_server = '172.18.152.5';
		$ftp_user_name = 'luoyang';
		$ftp_user_pass = 'luoyang';
		$ftp_path = '/';

		// set up basic connection
		if(!($conn_id = ftp_connect($ftp_server, 21, 10)) ) return false;
		
		if(!ftp_login($conn_id, $ftp_user_name, $ftp_user_pass) ) return false;
		
		ftp_chdir($conn_id, $ftp_path);

		// upload a file
		$result = ftp_put($conn_id, $remote_file, $local_file, FTP_BINARY);

		// close the connection
		ftp_close($conn_id);
		
		return $result;
	
	}
	
	public static function getZdb(){
		$ftp_server = '172.18.152.5';
		$ftp_user_name = 'dsbwdown';
		$ftp_user_pass = 'dsbw2004';
		$ftp_path = '/baowen/zdb/zz/';

		if(!($conn_id = ftp_connect($ftp_server, 21, 10)) ) return false;

		// login with username and password
		$login_result = ftp_login($conn_id, $ftp_user_name, $ftp_user_pass);

		ftp_chdir($conn_id, $ftp_path);
		
		$list = ftp_nlist($conn_id, ".");
			
		if(!$list) return false;
		
		$list = array_filter($list, 'filter_czb');
		
		$server_file =  max($list) ;
		$local_file = 'zdb.txt';
		if (!ftp_get($conn_id, $local_file, $server_file, FTP_ASCII)) return false;
		
		ftp_close($conn_id);
		
		$content = file_get_contents($local_file);
		
		preg_match_all('/^SPCC\s+(\d+)/m',$content,$matchs,PREG_PATTERN_ORDER);
		
		$result = array();
		$result['fileName'] = $server_file;
		$result['zdbBegin'] = $matchs[1][0];
		$result['forcast'] = array();
		
		//用尽量简单清晰的正则表达式 捕获两个站号之间的文本 Lookahead assertions断言之后的站号
		preg_match_all('/^[\t\040]?(\d{5}).+(?=^[\t\040]?\d{5})/smU',$content,$matchs,PREG_PATTERN_ORDER);//
		
		/*
			$matchs[0] 包含各个站的多时次预报
			$matchs[1] 仅包含所有站号
		*/
		
		$forcast = array();
		global $require_stations;
		for($i = 0; $i < count($matchs[1]); $i++){
			$num = $matchs[1][$i];
			if(in_array($num,$require_stations) ){
				$forcast[$num] = $matchs[0][$i];
			}
		}
		
		foreach($forcast as $key => $value){
			preg_match_all('/\n[\t\040]*(?:[\d.]+[\t\040]+){11}(-?[\d.]+)[\t\040]+(-?[\d.]+)[\t\040]+(?:[\d.]+[\t\040]+){6}([\d.]+)[\t\040]+([\d.]+)[\t\040]+([\d.]+)[\t\040\r]*/',$value,$matchs,PREG_SET_ORDER);//
			
			$result['forcast'][$key] = array();
			foreach($matchs as $key2 => $value2){
				$result['forcast'][$key][] = array('highT'=>$value2[1],'lowT'=>$value2[2],'weather'=>$value2[3],'dire'=>$value2[4],'level'=>$value2[5]);
			}

		}
		
		return $result;
	}
}
?>