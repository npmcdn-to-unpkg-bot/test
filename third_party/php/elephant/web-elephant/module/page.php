<?php
    function get_frindLinks()
    {
        //获取友情链接
        
        //第一种写法
        //$db=new myDataBase();
        //return $db->execForArray("select * from frindlinks");
        
        //第二种写法
         global $myDB;
         return $myDB->execForArray("select * from friendlinks ");
        
      
    }

?>