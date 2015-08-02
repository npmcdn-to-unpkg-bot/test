#!/usr/bin/python
#coding:utf-8

s = """
- 最小化from * 的破坏: _X 和 __all__
  . _X 可以防止 from * 导入, 下划线不是私有,你可以用import导入他\
  . 可以用__all__ 指定要导入的,实现和 _X 一样的效果,同样只针对from *
     __all__ = ["Error", "encode] # export these only
- 一些扩展类(默认不开启的)
   from __future__ import featurename
- 混合用法模式 __name__ 和 __main__
  . 如果文件以顶程序文件执行,在启动时, __name__ 会设置为 "__main__"
  . 如果文件被导入, __name__ 会被设置成客户端所了解的模块名字
- 修改模块搜索路径 sys.path
  . sys.path.append('../..')
- import/from 的as 扩展
  . import modulename as name
  . from modulename import attrname as name
- 元程序 see mydir.py
- 以名称字符串导入模块
   modname = "string
   exec("import " + modname)
   # 或者
   string = __import__(modname)
   print string
"""

print s.decode('utf-8')

modname = "string"
exec("import " + modname)
print string

modname = "sys"
sys = __import__(modname)
print sys