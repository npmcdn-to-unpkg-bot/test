<?php 
    include 'includefiles/top.php';
?>



<form method="post">
<table class = "mytable">
<tr>
	<th colspan="2">用户注册</th>
</tr>	
<tr>
	<td>用户名</td>
	<td><input type="text" name="userName" class="text" /></td>
</tr>
<tr>
	<td>密码</td>
	<td><input type="password" name="userPwd" class="text"/></td>
</tr>
<tr>
	<td colspan="2">
		<input type="submit" value="注册"  name="cmdLogin" />
	</td>
</tr>
</table>
</form>
   <?php 
    include 'includefiles/bottom.php';
  ?>