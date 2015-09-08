from flask import Flask
from flask_restful import Resource, Api

app = Flask(__name__)
api = Api(app)

class HelloWorld(Resource):
    def get(self):
        return {'hello' : 'world'}

class Endpoint(Resource):
    def get(self, to_id):
        return {'to_id': to_id }

api.add_resource(HelloWorld, '/', '/hello')
api.add_resource(Endpoint, '/todo/<int:to_id>', endpoint='todo_default')

if __name__ == '__main__':
    app.run(debug=True)