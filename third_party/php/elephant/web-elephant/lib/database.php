<?php
 class myDataBase 
 {
    //数据库处理类
    
    public $_dbAddr="localhost"; //数据库服务器IP
    public $_dbName="money"; //数据库名
    public $_dbUser="root"; //用户名
    public $_dbPwd="123";//密码
    public $_db = false;
    function myDataBase()
    {
        //写一些数据库  connect 过程 
    }
    function execForArray($sql)
    {
        //执行一个sql语句 ，返回类型是数组
        
        $link1=array(
            "title"=>"51cto",
            "href"=>"www.51cto.com",
            "target"=>"_blank"
        );
        
         $link2=array(
            "title"=>"程序员在囧途",
            "href"=>"www.jtthink.com",
            "target"=>"_blank"
        );
        
        $links[]=$link1;
        $links[]=$link2;
     //   array_push($links,$link2);//把元素 压到数组（从后面压)
        
        //array_unshift($links,$link2);//把元素 压到数组（从前面压)
        return $links;
    }
    function execForOne($sql)
    {
      //执行一个sql语句 ，返回字符串
    }
	
	function test()
	{
		$this->$_db = NewADOConnection("mysqli");
		$this->$_db->connect($this->_dbAddr, $this->_dbUser, $this->_dbPwd, $this->_dbName);
		$this->$_db->Query("set names utf8");
		$this->$_db->SetFetchMole(ADODB_FETCH_ASSOC);
		
		$result = $this->$_db->Execute("select * from friendlinks order by id desc");
		
		while(!$result->EOF) {
			$returnArray[] = $result->fields;
			$result->MoveNext();
		}
	}
 }
 
 $myDB=new myDataBase();


?>