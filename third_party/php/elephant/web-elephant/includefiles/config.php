<?php	
	$config_default_title='_程序员在囧途'; // 网站的默认标题
	$get_page_path = $_SERVER["PHP_SELF"];
	echo $get_page_path;
	
	if ($get_page_path == '/news.php') {
		$config_default_title = "新闻".$config_default_title;
	} else ($get_page_path == "/index.php") {
		$config_default_title = "首页".$config_default_title;
	}
	
	echo "dafeiaaaa";
?>