<?php
require_once('db.class.php');		//引入db.class.php
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
		
		$size = file_put_contents($remote_file, $content);//$local_file
		return $size;

		// set up basic connection
		$conn_id = ftp_connect($ftp_server);

		// login with username and password
		$login_result = ftp_login($conn_id, $ftp_user_name, $ftp_user_pass);

		// upload a file
		if (ftp_put($conn_id, $remote_file, $local_file, FTP_ASCII)) {
			echo "successfully uploaded $file\n";
		} else {
			echo "There was a problem while uploading $file\n";
		}

		// close the connection
		ftp_close($conn_id);
		
		return $size;
	
	}
}
?>