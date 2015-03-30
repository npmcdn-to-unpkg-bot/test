<form method="post"> <!--默认是get 所有method=post一定要写 -->
<style>
.regtable {width: 600px; background: #fff;}
.regtable .lefttd {text-align: right; width: 25%;}
.regtable .righttd {text-align: left; width: 75%;}
.regtable .text {width: 61%; border: solid 1px #ddd; height: 25px; line-height: 25px;}
</style>
	
<table class="mytable regtable">
 <tr>
  <th colspan="2">用户注册</th>
 </tr>
 <tr>
   <td class="lefttd">用户名:</td>
   <td class="righttd"><input type="text" name="userName"  class="text"/></td> 
 </tr>
 <tr>
   <td class="lefttd">密码:</td>
   <td class="righttd"><input type="password" name="userPwd" class="text"/></td> 
 </tr>
 <tr>
  <td colspan="2">
    <input type="submit" value="注册" name="cmdLogin"  />
  </td>
 
 </tr>
</table>
 </form>