<?php 
    include 'includefiles/top.php';
?>
  <br />
  <br />
  <br />
  <div>新闻页面</div>
  <br />
  <?php 
  	$get_id = $_GET["id"];
	if ($_GET["id"])
		echo "获取到id参数:".$get_id;
	else
		echo "没有获取参数id";
  ?>
  <br />
  <br />
   <?php 
    include 'includefiles/bottom.php';
  ?>