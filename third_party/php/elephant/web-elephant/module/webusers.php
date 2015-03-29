<?php 
class webuser // 用户处理类
{
//	public $userName;
//	public $userPwd;
//	public $userAge;
//	public $userDisplayName;
	
	public $userinfo = array(); // 用户属性数组,初始化
	function webuser()
	{
		echo "用户类已经初始化";	
	}
	
	function __set($key, $value) // 设置用户类属性
	{
		if ($key == "age") {
			// > 21岁
		}
		$this->userinfo[$key] = $value;
	}
	
	function __get($key) // 获取用户类属性
	{
		// 为啥不用 issset() 或者 if($this->userinfo[$key])
		// 如果 value是null,key不是,下面是对的,上面2个是判断value的
		if (array_key_exists($key, $this->userinfo)) {
			return $this->userinfo[$key];
		}
		
		return "";
	}
	
	function __call($method, $args) // 默认执行函数,如果没找到对应名字的函数,对调用这个
	{
		if ($method == "add") {
			if ($this->userName == "") {
				echo "用户名不能为空";
			} else {
				echo "用户新增陈工";
			}
		}
	}
	
	static function getCurrentUser()
	{
		echo "欢迎回来:大飞";
	}
	
	function login($uname, $upwd)
	{
		
	}
	
	// 传统方法
//	public static function addUser($uname, $upwd, $uage) // static function
//	{
//		
//	}
//	
//	function add()
//	{
//		if ($this->userName == "")
//		{
//			echo "用户名不能为空";
//		} else {
//			echo "用户新增成功";		
//		}
//	}
}
?>