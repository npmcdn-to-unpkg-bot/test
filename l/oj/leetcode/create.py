#!/usr/bin/python
#coding:utf-8

import argparse
import os
import string
import shutil

def get_range(number):
    # 3   return (1, 50)
    # 103 return (101, 150)
    factor = (number-1)/50;
    return (factor*50 + 1, (factor+1)*50)

def get_folder(number):
    (start, end) = get_range(number)
    return "{}-{}".format(zfill(start,4), zfill(end, 4))

def zfill(number, len):
    return string.zfill(str(number), len)

def create_question(number, name, is_force=False):
    if None in (number, name):
        raise Exception('question number and name can not be None')

    print 'create {}, {}, force:{}'.format(string.zfill(number, 4), name, is_force)
    range_folder = get_folder(number)
    if not os.path.exists(range_folder):
        os.makedirs(range_folder)
    task_num = zfill(number, 4)
    task_folder = os.path.join(range_folder, task_num)
    if os.path.exists(task_folder):
        if is_force:
            shutil.rmtree(task_folder)
        else:
            raise Exception('{} already exists, use --force to remove old one'.format(task_folder))

    # create task 0003 in 0001-0050
    os.makedirs(task_folder)

    # create files in 0003
    with open(os.path.join(task_folder, 'question.md'), 'w') as f:
        f.write(' ')

    with open(os.path.join(task_folder, 'solution.cpp'), 'w') as f:
        f.write(' ')

    # add index in index.md
    new_lines = []
    with open('index.md', 'r') as f:
        lines = f.readlines()
        for line in lines:
            current_no = int(line[0:4])
            if current_no != number:
                new_lines.append(line)

        new_lines.append('{} {}\n'.format(task_num, name))
        new_lines.sort()

    with open('index.md', 'w') as f:
        f.writelines(new_lines)

    print 'Question {} is created in {}...'.format(task_num, range_folder)

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('number', help='number of question', type=int)
    parser.add_argument('name', help='the name of the question')
    parser.add_argument('-f', '--force', help='Force to create the question, this will remove the old one', action='store_true')

    args = parser.parse_args()

    create_question(args.number, args.name, args.force)