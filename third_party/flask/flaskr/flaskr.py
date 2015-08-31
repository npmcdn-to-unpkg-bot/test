# -*- coding: utf-8 -*-

import os
import sqlite3
from flask import Flask, request, session, g, redirect, url_for, abort, render_template, flash

# configuration
DATABASE = '/tmp/flaskr.db'
DEBUG = True
SECRET_KEY = 'development key'
USERNAME = 'admin'
PASSWORD = 'default'

# create app
app = Flask(__name__)
# app.config.from_object(__name__)
app.config.update(dict(
	DATABASE = os.path.join(app.root_path, 'flaskr.db'),
	DEBUG = True,
	SECRET_KEY = 'development key',
	USERNAME = 'admin',
	PASSWORD = 'default'
))
app.config.from_envvar('FLASKR_SETTINGS', silent=True)

@app.before_request
def before_request():
	g.db = connect_db()

@app.teardown_request
def teardown_request(exception):
	db = getattr(g, 'db', None)
	if db is not None:
		db.close()

def init_db():
	with app.app_context():
		db = get_db()
		with app.open_resource('schema.sql', mode='r') as f:
			db.cursor().executescript(f.read())
		db.commit()

def connect_db():
	"""Connect to the specific database."""
	rv = sqlite3.connect(app.config['DATABASE'])
	rv.row_factory = sqlite3.Row
	return rv

def get_db():
	"""
	Opens a new database connection if there is none
	"""
	if not hasattr(g, 'sqlite_db'):
		g.sqlite_db = connect_db()
	return g.sqlite_db

@app.route('/')
def show_entries():
	cur = g.db.execute('select title, text from entries order by id desc')
	entries = [dict(title=row[0], text=row[1]) for row in cur.fetchall()]
	return render_template('show_entries.html', entries=entries)

@app.route('/add', methods=['POST'])
def add_entry():
	if not session.get('logged_in'):
		abort(401)
	g.db.execute('insert into entries (title, text) values (?,?)', 
			[request.form['title'], request.form['text']])
	g.db.commit()
	flash('New entry was successfully posted')
	return redirect(url_for('show_entries'))

@app.route('/login', methods=['GET', 'POST'])
def login():
	error = None
	if request.method == 'POST':
		if request.form['username'] != app.config['USERNAME']:
			error = 'Invalid Username'
		elif request.form['password'] != app.config['PASSWORD']:
			error = 'Invalid Password'
		else:
			session['logged_in'] = True
			flash('You are logged in')
			return redirect(url_for('show_entries'))
	return render_template('login.html', error=error)

@app.route('/logout')
def logout():
	session.pop('logged_in', None)
	flash('You are logged out')
	return redirect(url_for('show_entries'))

if __name__ == '__main__':
	app.run()