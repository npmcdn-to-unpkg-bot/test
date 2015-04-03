<?php
    include "module/page.php";
?>

<style>
.bottom {width: 100%; margin: 0 auto; background: #474747; height: 80px; padding-top: 20px;
    color: #fff
}

.bottom a{color: #fff; text-decoration:  none;}
.bottom a:hover{text-decoration: underline;}
</style>

<div class="bottom">
    <p>友情链接:
    <?php
        $get_links = get_friendLinks();
        // // var_export($get_links);
        // foreach ($get_links as $link) {
        //     echo '<a href="'.$link['href'].'" target="'.$link['target'].'">'.$link['title'].'</a> |';
        // }
    ?> 
    <?php foreach ($get_links as $link): ?>
    <?php include "tpl/friendlink.tpl"; ?>
    <?php endforeach;?>
    </p>
    <p>苏ICP备14027568号 ©jtthink.com Inc. All Rights Reserved</p>
</div>

    </body>
</html>