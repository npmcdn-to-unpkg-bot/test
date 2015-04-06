<?php
 include "module/page.php";
?>
<style>
 .bottom{width:100%;margin:0 auto;background:#474747;height:80px;padding-top:20px;color:#fff}
  .bottom a{color:#fff;text-decoration: none;}
  .bottom a:hover{text-decoration:underline}

</style> 
<div class="bottom">
<p>友情链接：
<?php
 $get_links=get_frindLinks(); //获取友情链接

 
// 第一种办法显示数组数据
  /* $get_links=get_frindLinks(); //获取友情链接
   
   foreach($get_links as $link)
   {
     echo ' <a href="http://'.$link['href'].'" target="'.$link['target'].'">'.$link["title"].'</a> | ';
   }
   
   
   //var_export($get_links);
  */
  
  /*为演示 另外一种循环的示例代码
   foreach($get_links as $link)
   {
      foreach($link as $key=>$value)
     {
        if($key=="title")
        echo  "标题是:".$value."<br/>";
           if($key=="href")
        echo  "网址是:".$value."<br/>";
     }
   }*/
?>
<?php foreach($get_links as $link):?>
  
<?php  include "tpl/frindlink.tpl";?>
<?php endforeach;?>
</p>
 <p> 苏ICP备14027568号
©jtthink.com Inc. All Rights Reserved </p>

</div>
  
 </body>
</html>