#coding:utf-8
import os
from flask import Flask, render_template, session, redirect, url_for
from flask.ext.script import Manager, Shell
from flask.ext.sqlalchemy import SQLAlchemy
from datetime import datetime, date
"""
usage:
    set a mysql uri for this
    export SQLALCHEMY_DATABASE_URI='mysql://root:@localhost/testing'
    python hello.py init_db
    
    see UserInfo: update_d/update_p
"""

basedir = os.path.abspath(os.path.dirname(__file__))

app = Flask(__name__)
app.config['SECRET_KEY'] = 'hard to guess string'
app.config['SQLALCHEMY_DATABASE_URI'] = os.environ.get('SQLALCHEMY_DATABASE_URI')
app.config['SQLALCHEMY_COMMIT_ON_TEARDOWN'] = True

manager = Manager(app)
db = SQLAlchemy(app)

class ClassName(object):
    """docstring for ClassName"""
    def __init__(self, arg):
        super(ClassName, self).__init__()
        self.arg = arg


class UserInfo(db.Model):
    """
    """
    __tablename__ = 'user_info'
    id = db.Column(db.BigInteger, primary_key=True, index=True)
    name = db.Column(db.String(128))
    create_time = db.Column(db.DateTime)
    # wx is UseDetailInfo 1:1
    detail = db.relationship('UseDetailInfo', backref='user', lazy='dynamic')
    # profit is UseProfit 1:n
    profit = db.relationship('UseProfit', backref='user', lazy='dynamic')

    def update_d(self):
        self.d = self.detail.first()

    def update_p(self):
        self.p = self.profit.all()

class UseDetailInfo(db.Model):
    __tablename__ = 'user_detail_info'
    id = db.Column(db.BigInteger, primary_key=True)
    user_id = db.Column(db.BigInteger, db.ForeignKey('user_info.id'))
    sex = db.Column(db.Integer, default=0)
    password = db.Column(db.String(128))
    email = db.Column(db.String(128))
    mobile = db.Column(db.String(11))

class UseProfit(db.Model):
    __tablename__ = 'user_profit'
    id = db.Column(db.BigInteger, primary_key=True)
    user_id = db.Column(db.BigInteger, db.ForeignKey('user_info.id'))
    profit = db.Column(db.Float)
    date = db.Column(db.Date)

def make_shell_context():
    return dict(app=app, db=db, User=User, Role=Role)

manager.add_command("shell", Shell(make_context=make_shell_context))
@manager.command
def init_db():
    """Init db with data"""
    db.drop_all()
    db.create_all()

    user = UserInfo(name=u'dafei', create_time=datetime.utcnow())
    db.session.add(user)
    db.session.commit() # to get the id

    detail = UseDetailInfo(user=user, sex=1, password='123', email='hha@haha.com', mobile='1107754821')
    p1 = UseProfit(user=user, profit=1.1, date=date(2015,10,1))
    p2 = UseProfit(user=user, profit=2.1, date=date(2015,10,2))
    p3 = UseProfit(user=user, profit=3.1, date=date(2015,10,3))
    p4 = UseProfit(user=user, profit=4.1, date=date(2015,10,4))
    db.session.add_all([detail, p1, p2, p3, p4])
    db.session.commit()

@app.route('/', methods=['GET', 'POST'])
def index():
    user = UserInfo.query.first()
    if user is None:
        return 'No user in database'
    print 'user:{}, {}'.format(user, type(user))
    user.update_d()
    user.update_p()
    return render_template('index.html', user=user)


if __name__ == '__main__':
    manager.run()
