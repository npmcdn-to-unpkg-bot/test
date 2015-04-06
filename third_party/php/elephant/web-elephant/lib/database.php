<?php

class myDataBase
{
	public $_dbAddr = "localhost";
	public $_dbName = "money";
	public $_dbUser = "root";
	public $_dbPwd = "123";
	
	function myDataBase()
	{
		
	}
	
	function execForArray($sql)
	{
		// 执行一个sql语句返回类型是数组
		$link1=array(
            "title"=>"51cto",
            "href"=>"www.51cto.com",
            "target"=>"_blank",
            );

        $link2=array(
            "title"=>"jtthink",
            "href"=>"www.jtthink.com",
            "target"=>"_blank",
            );
        $links[] = $link1;
        $links[] = $link2;

        return $links;
	}
	
	function execForOne($sql)
	{
		// 执行一个sql语句返回时字符串
		
	}
}

$myDB = new myDataBase();

?>