 <script>
  $(document).ready(function(){
    //页面加载完成后 执行以下代码
    //alert($(".text").length);
    $("#cmdLogin").css("display","inline-block");
    $("#cmdLogin").click(function(){
    if(isBlank("txtUserName","red"))
    {
        alert("用户名不能为空");
        return false;//阻止了 submit行为
    }
   
   if(isBlank("txtUserPwd","blue"))
    {
        alert("密码不能为空");
        return false;//阻止了 submit行为
    }   
  })
  })
 
 </script>
<form method="post"> <!--默认是get 所有method=post一定要写 -->
<style>
 .regtable{width:600px;background:#fff;border-radius:5px;padding-top:30px;padding-bottom:100px}
 .regtable th{font-size:26px;color:#9c9c9c;font-weight:normal}
  .regtable td{padding: 6px;}
  .regtable td a{color:green}
 .regtable .lefttd{text-align: right;width:25%;color:gray}
 .regtable .righttd{text-align: left;width:75%}
 .regtable .text{width:58%;border: solid 1px #ddd;height:34px;line-height:34px;background:#f5f5f5;border-radius:5px;}
 
 #cmdLogin{width:200px;height:40px;text-align:center;color:#fff;border:0;background:#e96481;border-radius:5px;}
</style>
<table class="mytable regtable">
 <tr>
 <th></th>
  <th class="righttd">用户登录</th>
 </tr>
 <tr>
   <td  class="lefttd">用户名:</td>
   <td class="righttd"><input type="text" name="userName" id="txtUserName"  class="text"/></td> 
 </tr>
  
 <tr>
   <td  class="lefttd">密码:</td>
   <td  class="righttd"><input type="password" name="userPwd" id="txtUserPwd" class="text"/></td> 
 </tr>
 
 
 <tr>
  <td></td>
  <td class="righttd" >
    <input type="submit" value="登录" name="cmdLogin"  id="cmdLogin"  class="readyShow"   />
  </td>
 
 </tr>
</table>
<script>


</script>
 </form>
 