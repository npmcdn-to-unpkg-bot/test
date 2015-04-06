<?php
interface news
{
	function loadNews($classids, $keyword, $page, $pagesize);
	function loadNewsDetail($newsid);
	
	function clickNews($newsid); // 点击量计算
	
	function reviewNews($newsid, $reviewData); // 评论新闻
	
}

interface users
{
	
}

?>