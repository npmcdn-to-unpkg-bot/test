<?php
 include "conf.php";//加载全站配置文件
?>
<html>
 <head>
 <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
  <title><?php echo $config_defaulttitle ?></title>  
  <style>
 *{margin:0 auto;text-align:center; font-size: 14px; font-family: "微软雅黑";}
 body {background: url(../images/bg.jpg);}
 .container {background-color: #474747; height: 130px; margin: 0 auto; color: #fff;}
 .container a{color: #fff; text-decoration: none;}
 .container a:hover {text-decoration: underline;}
 .container .top{width: 1000px;}
 
 .container .logo {float: left; width: 300px; margin-top: 30px;}
 .container .menu {float: left; margin-top: 45px; width: 500px; text-align: left;}
 
 .container .userinfo {float: right;text-align: right;}
 .container .search {border:solid 1px grey; 
 	width: 180px; height: 21px; line-height: 21px;
 	background: url(../images/topsearch.gif) no-repeat #FFFFFF right;
 	}
 
 .mytable{margin:30px auto;}
 input{text-align:left;text-indent: 3px;}
 .1text{width:150px;height: 22px;border:0;border-bottom:solid 1px #000}
</style>
 </head>
 <body>
 <div class="container">  <!-- 外部大div -->
 	<div class="top"> <!-- 外部大div -->
 		<div class="logo"><a href="/"><img src="../images/logo.png" alt="程序员在囧途" /></a></div>

 		<div class="userinfo">
 			<span ">
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
 		
 		<div class="menu"><a href="/">首页</a>  |  <a href="/news">新闻</a> |  <a href="/reg">用户注册</a>
 			<input type="text" class="search" />
 		</div>
 	</div>  
 </div>
 	
 
 <?php func_loadTpl(); //加载模板 ?>