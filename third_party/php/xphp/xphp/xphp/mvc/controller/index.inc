<?php
class index extends _Master
{
	function index()
	{
		
	}
	
	function showindex()
	{
//		include(XPHP_PATH."/mvc/view/".XPHP_VIEWPATH."/index.php");
		
//		echo "id:".$_GET["id"];
		$this->setView("index");
	}
}
?>