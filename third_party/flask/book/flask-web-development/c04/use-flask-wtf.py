# -*- coding: utf-8 -*-

"""
Flask-WTF(http://pythonhosted.org/Flask-WTF/)扩展可以把处理 
Web 表单的过程变成一 种愉悦的体验。这个扩展对独立的 
WTForms(http://wtforms.simplecodes.com)包进行了包 
装,方便集成到 Flask 程序中


$ pip install flask-wtf


"""

from flask import Flask, render_template, session, redirect, url_for, flash
from flask.ext.bootstrap import Bootstrap
from flask.ext.wtf import Form
from flask.ext.moment import Moment
from wtforms import StringField, SubmitField
from wtforms.validators import Required

app = Flask(__name__)
app.config['SECRET_KEY'] = 'hard to guess string'

bootstrap = Bootstrap(app)
moment = Moment(app)

class NameForm(Form):
	name = StringField('What is your name?', validators=[Required()])
	submit = SubmitField('Submit')

@app.route('/', methods=['GET', 'POST'])
def use_wtf():
	form = NameForm()
	if form.validate_on_submit():
		old_name = session.get('name')
		if old_name is not None and old_name != form.name.data:
			flash('Looks like you have chagned your name!')
		session['name'] = form.name.data
		return redirect(url_for('use_wtf'))
	return render_template('use-wtf.html', form=form, name=session.get('name'))

if __name__ == '__main__':
	app.run(debug=True)
