<?php
	require("xphp.conf");
//	include(XPHP_PATH."/mvc/view/".XPHP_VIEWPATH."/index.php");

	$_controller = isset($_GET["controller"]) ? $_GET["controller"] : ""; // 获取controller参数
	$_action = isset($_GET["action"]) ? $_GET["action"] : "";	// 获取action参数,这个参数可以没有,没有的话会执行controller的构造函数
	if ($_controller == "" || in_array($_controller, explode(",", XPHP_FORBIDDEN_TYPE))) exit();

	// 加载全局函数库
	require(XPHP_PATH."/common/functions.inc");	
	// 加载controller父类 _Master
	require(XPHP_PATH."/mvc/controller/_Master.inc");
	
	$_control_path = XPHP_PATH."/mvc/controller/".$_controller.".inc";
	if (!file_exists($_control_path)) exit(); // 临时,切换 404
	require($_control_path); // 加载 controller文件
	if (!class_exists($_controller)) exit(); // 临时,同上
	
	$_init_controller = new $_controller(); // == $_init_controller = new index(); 因为我没加载这个类了.不过是以变量的形式
	if (method_exists($_init_controller, $_action)) {
		$_init_controller->$_action(); // 执行类方法
		include($_init_controller->getView()); // 加载模板	
	}
?>