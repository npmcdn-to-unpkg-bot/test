#coding:utf-8
import logging
import os
import random
import time
from datetime import datetime
from . import main
from ..import db

_logger = logging.getLogger(__name__)

class TestTable(db.Model):
    __tablename__ = 'test_table'
    id = db.Column(db.Integer, primary_key=True)
    col_01 = db.Column(db.String(96), nullable=False)
    col_02 = db.Column(db.Integer, nullable=False)
    col_03 = db.Column(db.String(32), nullable=False)
    col_04 = db.Column(db.String(96), nullable=False)
    col_05 = db.Column(db.Boolean, default=True)
    col_06 = db.Column(db.DateTime)

_id = random.randint(0, 99999)
def get_num():
	global _id
	_id = _id + 1
	return _id

@main.route('/')
def index():
    return 'a length = 30 string!!!!!!!!!!'

@main.route('/slow_task')
def slow_task():
	"""
	every task use 1 seconds to response
	"""
	time.sleep(1)
	return 'a slow task'

@main.route('/mysql_insert')
def mysql_insert():
	item = TestTable(col_01='This is a test,This is a test,This is a test,This is a test',
			col_02=get_num(),
			col_03='This is a test',
			col_04='This is a test,This is a test,This is a testThis is a testThis is a test',
			col_05=True,
			col_06=datetime.utcnow())
	db.session.add(item)
	return 'ok'

@main.route('/mysql_query')
def mysql_query():
	item = TestTable.query.filter_by(id=35131).first()
	if item is None:
		return 'no', 404
	return 'ok'

@main.route('/mysql_delete')
def mysql_delete():
	return 'ok'