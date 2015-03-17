<?php
	include("xphp.conf");
//	include(XPHP_PATH."/mvc/view/".XPHP_VIEWPATH."/index.php");

	$_controller = isset($_GET["controller"]) ? $_GET["controller"] : ""; // 获取controller参数
	$_action = isset($_GET["action"]) ? $_GET["action"] : "";	// 获取action参数,这个参数可以没有,没有的话会执行controller的构造函数
	if ($_controller == "" || in_array($_controller, explode(",", XPHP_FORBIDDEN_TYPE))) exit();

	// 加载全局函数库
	include(XPHP_PATH."/common/functions.inc");	
	// 加载controller父类 _Master
	include(XPHP_PATH."/mvc/controller/_Master.inc");
	
	include(XPHP_PATH."/mvc/controller/".$_controller.".inc");
	$_init_controller = new $_controller(); // == $_init_controller = new index(); 因为我没加载这个类了.不过是以变量的形式
	$_init_controller->$_action(); // 执行类方法
?>