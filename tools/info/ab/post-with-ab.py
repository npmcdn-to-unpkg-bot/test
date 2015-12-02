#!/usr/bin/python
#coding:utf-8

"""
when you want use ab to test a post (with file and form field),
you can use this to generate the data file and command

i.e
You use curl to test an api which is multipart/form-data with text and image

curl  https://ABC.net/api/create -F identity=a_fake_identity -F username=Alice \
      -F file1=@/path/to/file/big.png \
      -F file2=@/path/to/file/big.png \
      -F file3=@/path/to/file/big.png \
      -F file4=@/path/to/file/big.png \
      -F file5=@/path/to/file/big.png


"""

import base64
import os
import argparse

BOUNDARY = '----WebKitFormBoundaryG2rNb8XzHo4BKQPD'
DELEMITOR = '\n'

def check_args_format(arg):
    e = Exception('please use -F fieldname=field_content or -F fieldname=@file_path')
    if '=' not in arg:
        raise e
    if arg.startswith('=') or arg.endswith('='):
        raise e

def get_field_name(field):
    return field.split('=')[0]

def get_field_content(field):
    return field.split('=')[1]

def encode_file(file):
    if not os.path.exists(file):
        raise Exception('File {} not exsits'.format(file))
    return base64.b64encode(open(file, 'rb').read())

def generate_text_field(field):
    global BOUNDARY, DELEMITOR
    s = '--{boundary}{delemitor}\
Content-Disposition: form-data; name="{fieldname}"{delemitor}\
{delemitor}\
{field_content}{delemitor}'.format(
        boundary=BOUNDARY,
        delemitor=DELEMITOR,
        fieldname=get_field_name(field),
        field_content=get_field_content(field))
    return s

def generate_image_field(field):
    global BOUNDARY, DELEMITOR
    file_path = get_field_content(field).replace('@', '')
    file_name = os.path.basename(file_path)
    s = '--{boundary}{delemitor}\
Content-Disposition: form-data; name="{fieldname}"; filename="{field_content}"{delemitor}\
Content-Type: image/png{delemitor}\
Content-Transfer-Encoding: base64{delemitor} \
{delemitor}\
{encoded_content}{delemitor}'.format(
        boundary=BOUNDARY,
        delemitor=DELEMITOR,
        fieldname=get_field_name(field),
        field_content=file_name,
        encoded_content=encode_file(file_path))
    return s

def generate_ending():
    global BOUNDARY, DELEMITOR
    s = '--{boundary}--{delemitor}'.format(boundary=BOUNDARY, delemitor=DELEMITOR)
    return s

def generate_command(text_fields, file_fields):
    data = ''
    for field in text_fields:
        data += generate_text_field(field)
    for field in file_fields:
        data += generate_image_field(field)
    data += generate_ending()

    with open('post_data', 'w') as data_file:
        data_file.write(data)

    print 'Use the following command to test ...'
    print 'ab -c 100 -n 500 -v 4 -p post_data -T "multipart/form-data; boundary={}" http://abc.net/api'.format(BOUNDARY)

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-F', '--field', help='form field, if file, use @, ie -F file01=@/path/head.png', action='append')

    args = parser.parse_args()

    if not args.field or len(args.field) == 0:
        raise Exception('Need specify -F')

    fields = args.field
    text_fields = []
    file_fields = []
    for field in fields:
        check_args_format(field)

        if '@' in field:
            file_fields.append(field)
        else:
            text_fields.append(field)

    generate_command(text_fields, file_fields)