from flask import Flask
from flask_restful import Resource, Api

app = Flask(__name__)
api = Api(app)

class Todo1(Resource):
    def get(self):
        # Default to 200 OK
        return { 'task' : 'HelloWorld'}
class Todo2(Resource):
    def get(self):
        # Response to 201
        return { 'task' : 'HelloWorld'}, 201
class Todo3(Resource):
    def get(self):
        # Response to 201 and return custom headers
        return { 'task' : 'HelloWorld'}, 201, {'Etag' : 'some-opaque-string'}


api.add_resource(Todo1, '/todo1')
api.add_resource(Todo2, '/todo2')
api.add_resource(Todo3, '/todo3')

if __name__ == '__main__':
    app.run(debug=True)