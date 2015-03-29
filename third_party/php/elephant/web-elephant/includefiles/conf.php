<?php
  $config_defaulttitle='_程序员在囧途';//网站的默认标题(title)
  $get_pagepath=$_SERVER["PHP_SELF"];//获取当前访问页
//  echo $get_pagepath; // /news.php代表是新闻  /index.php 代表是首页
  
  if($get_pagepath=='/news.php') // /news.php代表是新闻 
  {
     $config_defaulttitle="新闻".$config_defaulttitle;
  } 
  else if($get_pagepath=="/index.php")
  {
    $config_defaulttitle="首页".$config_defaulttitle;
  }
  else
  {
    $config_defaulttitle="404".$config_defaulttitle;
  }
  
  
?>