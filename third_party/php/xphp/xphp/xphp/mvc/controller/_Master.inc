<?php
abstract class _Master
{
	// controller类的父类
	var $_view; // 模板名称
	function setView($viewName) {
		$this->_view = $viewName;
	}
	
	function getView() {
		return 	XPHP_PATH."/mvc/view/".XPHP_VIEWPATH."/".$this->_view.XPHP_VIEWEXT;
	}
}
?>