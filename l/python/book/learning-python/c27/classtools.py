#!/usr/bin/python
#coding:utf-8

class AttrDisplay:
    """

    """
    def _getherAttrs(self):
        attrs = []
        for key in sorted(self.__dict__):
            attrs.append('%s=%s' %(key, getattr(self, key)))
        return ', '.join(attrs)
    def __str__(self):
        return '[%s: %s]' % (self.__class__.__name__, self._getherAttrs())

if __name__ == '__main__':
    class TopTest(AttrDisplay):
        count = 0 # 只是附加到了类,没有向下复制到实例
        def __init__(self):
            self.attr1 = TopTest.count
            self.attr2 = TopTest.count+1
            TopTest.count += 2
    class SubTest(TopTest):
        pass
    X,Y = TopTest(), SubTest()
    print X
    print Y