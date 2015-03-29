<?php
 include "conf.php";//加载全站配置文件
?>
<html>
 <head>
 <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
  <title><?php echo $config_defaulttitle ?></title>  
  <style>
 *{margin:0 auto;text-align:center;}
 .mytable{margin:30px auto;}
 input{text-align:left;text-indent: 3px;}
 .text{width:150px;height: 22px;border:0;border-bottom:solid 1px #000}
</style>
 </head>
 <body>
 <div>
  <a href="/">首页</a>  |  <a href="/news">新闻</a> |  <a href="/reg">用户注册</a>
 
 <span style="color: green;">
 <?php include "module/webusers.php"; 
 
	echo webuser::getCurrentUser();
	
// 	$user = new webuser();
//	$user->userName = "大飞";
//	$user->userAge = 18;
//	$user->userDisplayName = "Mrdafei";
//	$user->userPwd = "123";
//	
//	var_export($user->userinfo);
//	$user->add();
 ?>
 </span>
 <a href="#">安全退出</a>
 </div>
 
 <?php func_loadTpl(); //加载模板 ?>