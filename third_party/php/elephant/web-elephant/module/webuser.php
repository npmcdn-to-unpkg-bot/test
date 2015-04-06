<?php
class webuser //用户处理类
{
    //public $userName="游客";
    /*public $userName;//用户名属性
    
    public $userPwd;//用户密码
    public $userAge;//年龄
    
    public $userDisplayName;//用户显示名*/
    
    public $error_code="000";//错误编码
    private $userinfo=array(); //用户属性 数组
    
    function webuser()
    {
         
      //  echo "用户类已经初始化";
    }
    function __set($key,$value)//设置用户类属性
    {
        if($key=="age")
        {
            //必须 大于21岁  
        }
        
       $this->userinfo[$key]=$value;
    }
    function __get($key) //获取用户类属性
    {
        //为啥不用 下面两种判断方法呢？
      //1、if(isset($this->userinfo[$key]))
      //2、if($this->userinfo[$key]) 
        
        if(array_key_exists($key,$this->userinfo))
        {
            return $this->userinfo[$key];
        }
        else
        {
            //return false;
            return "";
        }
    }
    function validateArgs($args,$num)
    {
        //用来检测 参数是否合法
        if($args && is_array($args) && count($args)==$num)
        {
            return true;
        }
        else
        {
            $this->error_code="008";
            return false;
        }
    }
    function __call($methodName,$args) //默认执行函数
    {
        if($methodName=="add")
        {
            //代表是新增用户(用户注册) ,用户名和邮箱 同时唯一
          /*  if($this->userName=="")
            {
                echo "用户名不能为空";
            }
            else
            {
                echo "用户新增成功";
            }*/
        //mysql 处理方法
            if($this->validateArgs($args,4))
            {
                 $this->addUser($args[0],$args[1],$args[2],$args[4]);
            }
        }
        else if($methodName=="login") //用户登录
        {
            //使用用户名和邮箱均可登录
        }
        else if($methodName=="logout") //注销
        {
            
        }
    }
    static public function getCurrentUser() //获取当前登录用户
    {
        echo "欢迎回来：沈逸";
    }
    
    private function addUser($userName,$userEmail,$userPwd1,$userPwd2) //往数据库插入用户
    {
        
        // 需要实现的函数有 isRepeat:是否重复 isFormat:是否格式正确
        if($userPwd1=="" || $userPwd1!=$userPwd2 ) //密码填写不正确
        {
            $this->error_code="001";
            return false;
        }
        if($userName=="" ||  $userEmail=="") 
        {
              $this->error_code="002";
            return false; //代表用用户填写数据不正确
        }
        
        if(isFormat($userName,$userEmail))
        {
            $this->error_code="003";
            return false;// 代表用户名和邮箱不符合命名规范
        } 
        
        if(isRepeat($userName,$userEmail))  //用户名和Email是否 同时唯一
        {
              $this->error_code="004";
            return false;
        }
        
        
        $ret=DataBase::addData($userName,$userEmail,$userPwd1,$userPwd2); //插入数据,数据层待扩展
        if($ret && intval($ret)>0) //代表插入数据库成功
        {
             $this->error_code="000";
            return true;
        }
        $this->error_code="009";//代表未处理到的错误
        return false;
        
    }
    
    
    
    
    
     /* function login($uname,$upwd) //用户登录方法
    {
        
    }*/
    
    
  /*   //传统方法 
    public static function addUser($userName,$userpwd)  // static public function add()  这样写也可以)
    {
        
    }
    function add()  //新增用户方法
    {
        //self::方法名
        if($this->userName=="")
        {
            echo "用户名不能为空";
        }
        else
        {
            echo "用户新增成功";  
        }
            
    }*/
}

?>