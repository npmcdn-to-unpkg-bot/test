<?php 
// 处理用户层面ajax方法
if(isset($_GET["type"]))
{
	switch(intval($_GET["type"]))
	{
		case 1: // 代表用户名重复判断
			break;
			exit(1);
	}
}
exit("");
?>