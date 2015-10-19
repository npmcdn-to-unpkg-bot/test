#!/usr/bin/python
#coding:utf-8

import xml.etree.ElementTree as ET

xml_data="""
<deals>  
    <data>  
        <deal>  
             <deal_id>11111111</deal_id>  
             <sales_num>120</sales_num>  
             <price>15.0</price>  
        </deal>  
    </data>  
</deals> 
"""

xml_data1="""
 <data>  
        <deal>  
             <deal_id>11111111</deal_id>  
             <sales_num>120</sales_num>  
             <price>15.0</price>  
        </deal>  
 </data>  
"""

def find_and_print(xml, key):
    val = xml.find(key)
    if val is None:
        print 'Found no {}'.format(key)
    else:
        print '{}:{}'.format(key, val.text)


if __name__ == '__main__':
    # you can parse from file 
    # ET.parse(filepath)
    xml = ET.fromstring(xml_data1)
    # print xml

    deal = xml.find('deal')
    if deal is not None:
        find_and_print(deal, 'deal_id')
        find_and_print(deal, 'sales_num')
        find_and_print(deal, 'price')
        find_and_print(deal, 'fake_key')
    else:
        print 'Found no deal info'
