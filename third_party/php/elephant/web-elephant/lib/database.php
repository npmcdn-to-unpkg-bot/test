<?php
require("adodb.inc.php");
 class myDataBase 
 {
    //数据库处理类
    
    public $_dbAddr="localhost"; //数据库服务器IP
    public $_dbName="money"; //数据库名
    public $_dbUser="root"; //用户名
    public $_dbPwd="";//密码
    public $_db=false;
    function myDataBase() // __construct
    {
        //写一些数据库  connect 过程 
    }
    function __destruct() //析构函数
    {
         if($this->_db && $this->_db->IsConnected())
            $this->_db->disconnect();
    }
    function initConnect()
    {
        //初始化 数据库链接
        if($this->_db && $this->_db->IsConnected())
         return;
        $this->_db=NewADOConnection("mysqli");
        $this->_db->connect($this->_dbAddr,$this->_dbUser,$this->_dbPwd,$this->_dbName);
        $this->_db->Query("set names utf8"); //客户端编码
        $this->_db->SetFetchMode(ADODB_FETCH_ASSOC); 
         
    }
    function execForArray($sql)
    {
        //执行一个sql语句 ，返回类型是数组
        $this->initConnect();
        $result=$this->_db->Execute($sql);
        if($result)
        {
            $returnArray=array();
            while(!$result->EOF)
            {
                $returnArray[]=$result->fields;
                $result->MoveNext();
            }
            return $returnArray;
        }
        else
            return  false;
          
        
    }
    function execForOne($sql)
    {
      //执行一个sql语句 ，返回字符串
      
      
    }
    
    function test()
    {
        
       $ret=$this->execForArray("select * from friendlinks order by id desc ");
       
       var_export($ret);
        
        
    }
   
 }
 
 $myDB=new myDataBase();


?>