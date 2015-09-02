# -*- coding: utf-8 -*-

"""

$ pip install flask-mail


Flask-Mail SMTP服务器的配置
--------------------------------------------------
配  置 			默认值 		说  明
--------------------------------------------------
MAIL_SERVER 	localhost 	电子邮件服务器的主机名或 IP 地址
MAIL_PORT 		25 			电子邮件服务器的端口
MAIL_USE_TLS 	False 		启用传输层安全(Transport Layer Security,TLS)协议
MAIL_USE_SSL 	False 		启用安全套接层(Secure Sockets Layer,SSL)协议
MAIL_USERNAME 	None 		邮件账户的用户名
MAIL_PASSWORD 	None 		邮件账户的密码
--------------------------------------------------

"""

import os
from flask import Flask, render_template, session, redirect, url_for, flash
from flask.ext.script import Manager
from flask.ext.script import Shell
from flask.ext.bootstrap import Bootstrap
from flask.ext.wtf import Form
from flask.ext.moment import Moment
from flask.ext.sqlalchemy import SQLAlchemy
from flask.ext.mail import Mail, Message
from wtforms import StringField, SubmitField
from wtforms.validators import Required

basedir = os.path.abspath(os.path.dirname(__file__))

app = Flask(__name__)
app.config['SECRET_KEY'] = 'hard to guess string'
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///' + os.path.join(basedir, 'data.sqlite')
app.config['SQLALCHEMY_COMMIT_ON_TEARDOWN'] = True

app.config['MAIL_SERVER'] = 'smtp.googlemail.com'
app.config['MAIL_PORT'] = 587
app.config['MAIL_USE_TLS'] = True
app.config['MAIL_USERNAME'] = os.environ.get('MAIL_USERNAME')
app.config['MAIL_PASSWORD'] = os.environ.get('MAIL_PASSWORD')

app.config['DAFEI_MAIL_SUBJECT_PREFIX'] = '[MrDafei]'
app.config['DAFEI_MAIL_SENDER'] = 'Dafei <dafei@example.cn>'
app.config['DAFEI_ADMIN'] = os.environ.get('DAFEI_ADMIN')

manager = Manager(app)
bootstrap = Bootstrap(app)
moment = Moment(app)
db = SQLAlchemy(app)
mail = Mail(app)

class NameForm(Form):
	name = StringField('What is your name?', validators=[Required()])
	submit = SubmitField('Submit')

class Role(db.Model):
	__tablename__ = 'roles'
	id = db.Column(db.Integer, primary_key=True)
	name = db.Column(db.String(64), unique=True)

	users = db.relationship('User', backref='role', lazy='dynamic')
	
	def __repr__(self):
		return '<Role %r>' % self.name

class User(db.Model):
	__tablename__ = 'users'
	id = db.Column(db.Integer, primary_key=True)
	username = db.Column(db.String(64), unique=True, index=True)
	role_id = db.Column(db.Integer, db.ForeignKey('roles.id'))

	def __repr__(self):
		return '<User %r>' % self.username

def create_db():
	dbpath = os.path.join(basedir, 'data.sqlite')
	if os.path.exists(dbpath):
		os.remove(dbpath)
	db.create_all()

	admin_role = Role(name='Admin')
	mod_role = Role(name='Moderator')
	user_role = Role(name='User')
	john = User(username='john', role=admin_role)
	susan = User(username='susan', role=user_role)
	david = User(username='david', role=user_role)

	db.session.add_all([admin_role, mod_role, user_role, john, susan, david])
	db.session.commit()
	print User.query.all()
	print Role.query.all()

def make_shell_context():
	return dict(app=app, db=db, User=User, Role=Role)
manager.add_command("shell", Shell(make_context=make_shell_context))

def send_email(to, subject, template, **kwargs):
	print 'send send_email....'
	msg = Message(app.config['DAFEI_MAIL_SUBJECT_PREFIX'] + subject,
			sender=app.config['DAFEI_MAIL_SENDER'], recipients=[to])
	msg.body = render_template(template + '.txt', **kwargs)
	msg.html = render_template(template + '.html', **kwargs)
	mail.send(msg)

@app.route('/', methods=['GET', 'POST'])
def index():
	form = NameForm()
	if form.validate_on_submit():
		user = User.query.filter_by(username=form.name.data).first()
		if user is None:
			user = User(username = form.name.data)
			db.session.add(user)
			session['known'] = False
			# if app.config['DAFEI_ADMIN']:
			# 	send_email(app.config[DAFEI_ADMIN], 'New User',
			# 		'mail/new_user', user=user)
		else:
			session['known'] = True

		session['name'] = form.name.data
		form.name.data = ''
		return redirect(url_for('index'))
	return render_template('index.html', form=form, name=session.get('name'),
			known=session.get('known', False))

if __name__ == '__main__':
	manager.run()
