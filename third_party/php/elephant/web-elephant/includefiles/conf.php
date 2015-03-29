<?php
  $config_defaulttitle='_程序员在囧途';//网站的默认标题(title)
  $get_pagepath=$_SERVER["PHP_SELF"];//获取当前访问页
//  echo $get_pagepath; // /news.php代表是新闻  /index.php 代表是首页
  
  if($get_pagepath=='/news.php') // /news.php代表是新闻 
  {
     $config_defaulttitle="新闻".$config_defaulttitle;
  } else if($get_pagepath=="/index.php") {
    $config_defaulttitle="首页".$config_defaulttitle;
  } else if($get_pagepath=="/userreg.php") {
    $config_defaulttitle="用户注册页面".$config_defaulttitle;
	if ($_POST["cmdLogin"]) {
		// include 类库
		$get_username=$_POST["userName"];
		$get_password=$_POST["userPwd"];
		echo "用户输入的用户名".$get_username."密码是".$get_password;
	}
  } else {
    $config_defaulttitle="404".$config_defaulttitle;
  }
?>