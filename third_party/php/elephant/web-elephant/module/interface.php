<?php
interface news //新闻类接口，（信息类）包含内部新闻、投稿新闻、第三方新闻
{
    function loadNews($classids,$keyword,$page,$pagesize);//加载新闻列表
    function loadNewsDetail($newsid);//加载新闻详细
    
    function clickNews($newsid);//新闻点击量计算
    
    function reviewNews($newsid,$reviewData);//评论新闻
}

/*
 写一些架构和设计心得。
*/

interface users
{
    
}

?>