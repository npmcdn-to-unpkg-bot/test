#!/usr/bin/python

# pip install flask-script

# usage:
# python flask-script.py -h
# python flask-script.py runserver --help
# python flask-script.py runserver --host 0.0.0.0 --port 80	

from flask import Flask
from flask.ext.script import Manager
app = Flask(__name__)
manager = Manager(app)

if __name__ == '__main__':
	manager.run()