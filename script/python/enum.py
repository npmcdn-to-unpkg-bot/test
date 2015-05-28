#!/usr/bin/python

class parser_machine:
    (LINK, DEFINES, INCLUDES, CFLAGS, CFLAGS_C, CFLAGS_CC, ARFLAGS, LDFLAGS, LIBS) = range(0, 9)
    current_type = 0
    def set_current(self, type):
        if (type < self.LINK or type > self.LIBS):
            print "Wrong type {}".format(type)
            return;
        current_type = type
        print "Current type : {}".format(current_type)

print parser_machine.LINK
print parser_machine.LIBS

parser = parser_machine()
parser.set_current(3)

