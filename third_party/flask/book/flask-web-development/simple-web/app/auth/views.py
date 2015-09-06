from flask import render_template
from flask.ext.login import login_required
form . import auth

@auth.route('/login')
def login():
    return render_template('auth/login.html')

@app.route('/secret')
@login_required
def secrect():
    return 'Only authenticated users are allowed'
