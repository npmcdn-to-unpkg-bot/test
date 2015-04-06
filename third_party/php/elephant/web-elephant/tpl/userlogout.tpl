<?php 
	require_once("module/webuser.php");
	$user = new webuser;
	$user->logout();
?>

<p>
注销成功....<a href="/">点此返回首页</a>	
</p>