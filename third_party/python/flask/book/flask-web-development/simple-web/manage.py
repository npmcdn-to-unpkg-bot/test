#!/usr/bin/env python
import os
from app import create_app, db
from app.models import User, Role
from flask.ext.script import Manager, Shell
from flask.ext.migrate import Migrate, MigrateCommand

app = create_app(os.getenv('FLASK_CONFIG') or 'default')
manager = Manager(app)
migrate = Migrate(app, db)


def make_shell_context():
    return dict(app=app, db=db, User=User, Role=Role)

manager.add_command("shell", Shell(make_context=make_shell_context))
manager.add_command('db', MigrateCommand)

def create_db():
    dbpath = app.config['SQLALCHEMY_DATABASE_URI']
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

@manager.command
def test():
    """Run the unit tests."""
    import unittest
    tests = unittest.TestLoader().discover('tests')
    unittest.TextTestRunner(verbosity=2).run(tests)


if __name__ == '__main__':
    manager.run()
