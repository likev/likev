<?php
/*
 * 类名：DB
 * 说明：数据库操作类
 */
class DB
{
	/*
	 * 属性名：$host
	 * 类型：string
	 * 说明：数据库服务器的地址
	 */
	public $host;
	/*
	 * 属性名：$username
	 * 类型：string
	 * 说明：数据库服务器的用户名
	 */
	public $username;
	/*
	 * 属性名：$password
	 * 类型：string
	 * 说明：数据库服务器的密码
	 */
	public $password;
	/*
	 * 属性名：$host
	 * 类型：string
	 * 说明：所要操作的数据库名
	 */
	public $dbname;
	/*
	 * 属性名：$conn
	 * 类型：object
	 * 说明：数据库连接
	 */
	public $conn;
	/*
	 * 方法名：DB()
	 * 说明：构造函数
	 * 参数列表：
	 * 		参数名：$host
	 *			说明：数据库服务器地址
	 *			类型：string
	 *			默认值：'localhost'
	 * 		参数名：$username
	 *			说明：数据库服务器的用户名
	 *			类型：string
	 *			默认值：'a0413112509'
	 * 		参数名：$password
	 *			说明：数据库服务器的密码
	 *			类型：string
	 *			默认值：'271828han'
	 * 		参数名：$dbname
	 *			说明：需要操作的数据库
	 *			类型：string
	 *			默认值：'a0413112509'
	 * 返回值：无
	 */	
	public function DB($host='localhost',$username='root',$password='271828',$dbname='onlineWork')
	{
		$this->host = $host;
		$this->username = $username;
		$this->password = $password;
		$this->dbname = $dbname;
	}
	/*
	 * 方法名：open()
	 * 说明：打开一个数据库连接
	 * 参数列表：无
	 * 返回值：无
	 */	
	private function open()
	{
		$this->conn = mysql_connect($this->host,$this->username,$this->password);
		mysql_select_db($this->dbname);
	}
	/*
	 * 方法名：close()
	 * 说明：关闭一个数据库连接
	 * 参数列表：无
	 * 返回值：无
	 */	
	private function close()
	{
		mysql_close($this->conn);
	}
	/*
	 * 方法名：getObjListBySql()
	 * 说明：根据查询语句返回一个对象数组
	 * 参数列表：
	 *			参数名：$sql
	 *				类型：string
	 *				说明：需要执行的查询语句
	 *				默认值：无
	 * 返回值：对象数组
	 */	
	public function getObjListBySql($sql)
	{
		$this->open();
		$rs = mysql_query($sql,$this->conn);
		if(! $rs) return false;
		
		$objList = array();
		while($obj = mysql_fetch_object($rs))
		{
			if($obj)
			{
				$objList[] = $obj;
			}
		}
		$this->close();
		return $objList;
	}
	/*
	 * 方法名：insertData()
	 * 说明：插入一条新纪录
	 * 参数列表：
	 *			参数名：$table
	 *				类型：string
	 *				说明：目标表
	 *				默认值：无
	 *			参数名：$columns
	 *				类型：数组
	 *				说明：需要插入的字段集合
	 *				默认值：空数组
	 *			参数名：$values
	 *				类型：数组
	 *				说明：需要插入的字段值集合
	 *				默认值：空数组	 
	 * 返回值：对象数组
	 */	
	public function insertData($table,$columns=array(),$values=array())
	{
		$sql = 'insert into '.$table .'( ';
		for($i = 0; $i < sizeof($columns);$i ++)
		{
			$sql .= $columns[$i];
			if($i < sizeof($columns) - 1)
			{
				$sql .= ',';
			}
		}
		$sql .= ') values ( '; 
		for($i = 0; $i < sizeof($values);$i ++)
		{
			$sql .= "'".$values[$i]."'";
			if($i < sizeof($values) - 1)
			{
				$sql .= ',';
			}
		}
		$sql .= ' )';
		$this->open();
		mysql_query($sql,$this->conn);
		$id = mysql_insert_id($this->conn);
		$this->close();
		return $id;
	}
	
	public function doSql($sql)
	{
		$this->open();
		$issuccess = mysql_query($sql,$this->conn);
		$this->close();
		
		return !!$issuccess;
	}
}
?>