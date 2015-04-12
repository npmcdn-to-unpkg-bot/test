 <script>
 $(document).ready(function(){
    function showError()
    {
        if($("#userName").parent().find(".errInfo").length>0)
        {
            $("#userName").parent().find(".errInfo").html("用户名已被占用");
        }
        else
        $("#userName").parent().append("<span class='errInfo'>用户名已被占用</span>");
    }
      $("#userName").blur(function(){
       if(isBlank("userName","red")) return; //用户假设没填数据，则不作判断
            //foucus相反，一个是获得焦点 blur是失去焦点
            execServer(1,{username:$("#userName").val()},function(result){
            if(result==null || result!="1") //返回1 代表用户名不重复 ，否则就是重复
            {
                  showError();
            }
           
         });
         })
         blankBlur("userEmail");
    $("#cmdReg").click(function(){
        if(isBlank("userName","red"))
         {
            return false;
         }
         if(isBlank("userEmail","red"))
         {
            return false;
         }
         if(isBlank("userPwd1","red"))
         {
            return false;
         }
         if(isBlank("userPwd2","red"))
         {
            return false;
         }
         if(!isEqual("userPwd1","userPwd2"))
         {
            alert("两次输入的密码不一致");
            return false;
         }
         if(!isCheck("cbRead"))
         {
            alert("请先阅读《程序员在囧途》网站用户条款");
            return false;
         }
         
       
         execServer(1,{username:$("#userName").val()},function(result){
            if(result!=null && result=="1") //返回1 代表用户名不重复 ，否则就是重复
            {
                 $("#regForm").submit();//手动提交form
            }
            else //重复了 ，给出提示
            {
              showError();
            }
         });
         
         
    })
 })
  
 </script>
<form method="post" id="regForm" > <!--默认是get 所有method=post一定要写 -->
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
  <th class="righttd">用户注册</th>
 </tr>
 <tr>
   <td  class="lefttd">用户名:</td>
   <td class="righttd"><input type="text" autocomplete="off" name="userName" id="userName"  class="text"/></td> 
 </tr>
 
  <tr>
   <td  class="lefttd">邮箱:</td>
   <td class="righttd"><input type="text" autocomplete="off" name="userEmail" id="userEmail"  class="text"/></td> 
 </tr>
 <tr>
   <td  class="lefttd">密码:</td>
   <td  class="righttd"><input type="password" name="userPwd1"  id="userPwd1" class="text"/></td> 
 </tr>
  <tr>
   <td  class="lefttd">确认密码:</td>
   <td  class="righttd"><input type="password" name="userPwd2" id="userPwd2"  class="text"/></td> 
 </tr>
 <tr>
  <td></td>
  <td class="righttd"><input type="checkbox" name="cbRead"  id="cbRead" /> <a href="#">请先阅读《程序员在囧途》网站用户条款</td></a>
 </tr>
 <tr>
  <td></td>
  <td class="righttd" >
    <input type="button" value="注册" name="cmdReg"  id="cmdReg" class="abc readyShow" />
  </td>
 
 </tr>
</table>
 </form>
 