<?php  
  $result=the_news();
?>
<div class="outer">
 <div class="content">
  
  <!-- 左边新闻列表部分 -->
    <div class="left">
    <?php foreach($result as $news):?>
      <dl class="newsregion">
       <dt><?php echo $news["news_title"]  ?></dt>
       <dd>
        <?php echo $news["news_intr"]  ?>
       </dd>
       <dd class="pubtime">
        作者:<?php echo $news["pubuser"]  ?> 发布时间:<?php echo $news["pubtime"]  ?> 
       </dd>
      </dl>
    <?php endforeach;?>
    </div>
    
    
     <!-- 右边相关新闻部分 -->
    <div class="right">
    
    
    </div>
 
 </div>

</div> 
 