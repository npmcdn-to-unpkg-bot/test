# -*- coding: utf-8 -*-

"""
Flask-SQLAlchemy(http://pythonhosted.org/ Flask-SQLAlchemy/),这个 
Flask 扩展包装了 SQLAlchemy(http://www.sqlalchemy.org/)框架


$ pip install flask-sqlalchemy


表5-1 FLask-SQLAlchemy数据库URL
------------------------------------------
数据库引擎 		URL
------------------------------------------
MySQL			mysql://username:password@hostname/database
Postgres 		postgresql://username:password@hostname/database
SQLite(Unix) 	sqlite:////absolute/path/to/database
SQLite(Windows) sqlite:///c:/absolute/path/to/database
------------------------------------------
在这些 URL 中,hostname 表示 MySQL 服务所在的主机,可以是本地主机(localhost),
也可以是远程服务器。数据库服务器上可以托管多个数据库,因此 database 表示要使用的
数据库名

表5-2 最常用的SQLAlchemy列类型
---------------------------------------------------
类型名 			Python类型  		说  明
---------------------------------------------------
Integer 		int 			普通整数,一般是 32 位 
SmallInteger 	int 			取值范围小的整数,一般是 16 位 
BigInteger 		int 或 long 		限制精度的整数
Float 			float 			浮点数
Numeric 		decimal.Decimal 定点数
String 			str 			变长字符串
Text 			str 			变长字符串,对较长或不限长度的字符串做了优化
Unicode 		unicode         变长Unicode字符串
UnicodeText 	Unicode 		变长Unicode字符串,对较长或不限长度的字符串做了优化
Boolean 		bool 			布尔值
Date 			datetime.date   日期
Time 			datetime.time   时间
DateTime 		datetime.datetime  	日期和时间
Interval 		datetime.timedelta 	时间间隔
Enum 			str 				一组字符串
PickleType 		任何 Python 对象 		自动使用 Pickle 序列化
LargeBinary 	str 				二进制文件
---------------------------------------------------

表5-3 最常使用的SQLAlchemy列选项
--------------------------------------------
primary_key 	如果设为 True,这列就是表的主键
unique 			如果设为 True,这列不允许出现重复的值
index 			如果设为 True,为这列创建索引,提升查询效率
nullable 		如果设为 True,这列允许使用空值;如果设为 False,这列不允许使用空值 
default  		为这列定义默认值
--------------------------------------------

常用的SQLAlchemy关系选项
--------------------------------------------------
选项名 			说  明
--------------------------------------------------
backref  		在关系的另一个模型中添加反向引用
primaryjoin 	明确指定两个模型之间使用的联结条件。只在模棱两可的关系中需要指定
lazy 			指定如何加载相关记录。可选值有 select(首次访问时按需加载)、immediate(源对象加
 				载后就加载)、joined(加载记录,但使用联结)、subquery(立即加载,但使用子查询), 
				noload(永不加载)和 dynamic(不加载记录,但提供加载记录的查询)
uselist 		如果设为False，不使用列表，而使用标量值
order_by 		指定关系中记录的排序方式
secondary 		指定多对多关系中关系表的名字
secondaryjoin   SQLAlchemy无法自行决定时,指定多对多关系中的二级联结条件
--------------------------------------------------

常用的SQLAlchemy查询过滤器
--------------------------------------------------
filter()  		把过滤器添加到原查询上,返回一个新查询
filter_by() 	把等值过滤器添加到原查询上,返回一个新查询
limit() 		使用指定的值限制原查询返回的结果数量,返回一个新查询
offset() 		偏移原查询返回的结果,返回一个新查询
order_by() 		根据指定条件对原查询结果进行排序,返回一个新查询
group_by()		根据指定条件对原查询结果进行分组,返回一个新查询
--------------------------------------------------

最常使用的SQLAlchemy查询执行函数
--------------------------------------------------
all() 			以列表形式返回查询的所有结果
first() 		返回查询的第一个结果,如果没有结果,则返回 None
first_or_404() 	返回查询的第一个结果,如果没有结果,则终止请求,返回404错误响应
get() 			返回指定主键对应的行,如果没有对应的行,则返回 None
get_or_404() 	返回指定主键对应的行,如果没找到指定的主键,则终止请求,返回 404 错误响应 count() 返回查询结果的数量
paginate() 		返回一个 Paginate 对象,它包含指定范围内的结果
--------------------------------------------------
"""

import os
from flask import Flask, render_template, session, redirect, url_for, flash
from flask.ext.script import Manager
from flask.ext.bootstrap import Bootstrap
from flask.ext.wtf import Form
from flask.ext.moment import Moment
from flask.ext.sqlalchemy import SQLAlchemy
from wtforms import StringField, SubmitField
from wtforms.validators import Required

basedir = os.path.abspath(os.path.dirname(__file__))

app = Flask(__name__)
app.config['SECRET_KEY'] = 'hard to guess string'
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///' + os.path.join(basedir, 'data.sqlite')
app.config['SQLALCHEMY_COMMIT_ON_TEARDOWN'] = True

manager = Manager(app)
bootstrap = Bootstrap(app)
moment = Moment(app)
db = SQLAlchemy(app)

class NameForm(Form):
	name = StringField('What is your name?', validators=[Required()])
	submit = SubmitField('Submit')

class Role(db.Model):
	__tablename__ = 'roles'
	id = db.Column(db.Integer, primary_key=True)
	name = db.Column(db.String(64), unique=True)

	users = db.relationship('User', backref='role')
	
	def __repr__(self):
		return '<Role %r>' % self.name

class User(db.Model):
	__tablename__ = 'users'
	id = db.Column(db.Integer, primary_key=True)
	username = db.Column(db.String(64), unique=True, index=True)
	role_id = db.Column(db.Integer, db.ForeignKey('roles.id'))

	def __repr__(self):
		return '<User %r>' % self.username

@app.route('/', methods=['GET', 'POST'])
def index():
	form = NameForm()
	if form.validate_on_submit():
		old_name = session.get('name')
		if old_name is not None and old_name != form.name.data:
			flash('Looks like you have chagned your name!')
		session['name'] = form.name.data
		return redirect(url_for('index'))
	return render_template('index.html', form=form, name=session.get('name'))

if __name__ == '__main__':
	manager.run()
