#!/usr/bin/python
#coding:utf-8

import argparse
import os
import string
import shutil

def create_question(number, name, is_force=False):
    if None in (number, name):
        raise Exception('question number and name can not be None')

    print 'create {}, {}, force:{}'.format(string.zfill(number, 4), name, is_force)
    folder = string.zfill(str(number), 4)
    if os.path.exists(folder):
        if is_force:
            shutil.rmtree(folder)
        else:
            raise Exception('{} already exists, use --force to remove old one'.format(folder))

    # create folder 0003
    os.makedirs(folder)

    # create files in 0003
    with open(os.path.join(folder, 'question.md'), 'w') as f:
        f.write(' ')

    with open(os.path.join(folder, 'solution.cpp'), 'w') as f:
        f.write(' ')

    # add index in index.md
    new_lines = []
    with open('index.md', 'r') as f:
        lines = f.readlines()
        for line in lines:
            current_no = int(line[0:4])
            if current_no != number:
                new_lines.append(line)

        new_lines.append('{} {}\n'.format(folder, name))
        new_lines.sort()

    with open('index.md', 'w') as f:
        f.writelines(new_lines)

    print 'Question {} is created ...'.format(folder)

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('number', help='number of question', type=int)
    parser.add_argument('name', help='the name of the question')
    parser.add_argument('-f', '--force', help='Force to create the question, this will remove the old one', action='store_true')

    args = parser.parse_args()

    create_question(args.number, args.name, args.force)