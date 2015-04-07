<?php
$dig=0;
function test(){
     global $dig;   //全局变量
    if($dig++<10)	//如果dig加1后小于10，继续这个函数。直到dig为10止。
	{
        echo $dig;
        test();
    }
}
 

function test2(){
     global $dig;   //全局变量
    if($dig++<13)	//如果dig加1后小于10，继续这个函数。直到dig为10止。
	{
        echo $dig;
        test2();
    }
}
 test();
test2();

?>