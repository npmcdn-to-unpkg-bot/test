<?php
interface  Boss
{
    public function getMoney();//帮老子赚钱
    
    public function working(); //都给我干活，不许请假
    
    public function fuckOut();  //不听话的员工 滚粗
}
abstract class  Manager implements  Boss
{
    function __construct()
    {
        
    }
    public function getMoney()
    {
        //只负责收到项目款，上交老板，讨欢心
        
        echo "经理收项目款"."<br/>";
    }
    public function fuckOut()
    {
       //开除员工的事 一般是自己亲自干的，要帮老板背黑锅 
       
       echo "开除你"."<br/>";
    }  
    abstract function baoxiao();//报销
}
class Coder extends Manager
{
    function Coder()
    {
        
    }
    /*
   function getMoney()
   {
    echo "经理犯了错误.码农来帮老板赚钱"."<br/>";
   }*/
   function working()
   {
     echo "码农干活"."<br/>";
   } 
   function baoxiao()
   {
     echo "把票给经理，报销的钱他拿"."<br/>";
   }
}
$c=new Coder();
$c->getMoney();
 $c->working();
 $c->baoxiao();

?>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />