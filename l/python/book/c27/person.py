#!/usr/bin/python
#coding:utf-8

class Persion:
    def __init__(self, name, job=None, pay=0):
        self.name = name
        self.job = job
        self.pay = pay
    def lastName(self):
        return self.name.split()[-1]
    def giveRaise(self, percent):
        self.pay = int(self.pay * (1 + percent))
    def __str__(self):
        return '[Persion:%s %s]' % (self.name, self.pay)

class Manager(Persion):
    def __init__(self, name, pay):
        Persion.__init__(self, name, 'mgr', pay)

    def giveRaise(self, percent, bonus=0.10):
        Persion.giveRaise(self, percent + bonus) # use superclass function
class Manager2:
    def __init__(self, name, pay):
        self.persion = Persion(name, 'mgr', pay)
    def __getattr__(self, attr):
        return getattr(self.persion, attr)
    def __str__(self):
        return str(self.persion)

class Department:
    def __init__(self, *args):
        self.members = list(args)
    def addMember(self, persion):
        self.members.append(persion)
    def giveRaises(self, percent):
        for persion in self.members:
            persion.giveRaise(percent)
    def showAll(self):
        for p in self.members:
            print p

if __name__ == '__main__':
    bob = Persion('Bob Smith')
    sue = Persion('Sue Jones', job='dev', pay=10000)
    print bob.name, bob.pay
    print sue.name, sue.name
    print bob.lastName(), sue.lastName()
    sue.giveRaise(.10)
    print sue.pay
    print sue
    tom = Manager('Tom Jones', 50000)
    tom.giveRaise(.10)
    print tom.lastName()
    print tom

    print '----All three-----' # 多态
    for obj in (bob, sue, tom):
        obj.giveRaise(.10)
        print obj
    print '------Department------'
    development = Department(bob,sue)
    development.addMember(tom)
    development.giveRaises(0.10)
    development.showAll()
    print '-----Built-in--------'
    print bob
    print bob.__class__
    print bob.__class__.__name__
    print bob.__dict__.keys()
    for k in bob.__dict__:
        print k,'=>',bob.__dict__[k]
    for k in bob.__dict__:
        print k,'=>',getattr(bob, k)