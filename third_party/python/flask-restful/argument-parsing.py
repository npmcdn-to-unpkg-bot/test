from flask import Flask
from flask_restful import Resource, Api, reqparse

app = Flask(__name__)
api = Api(app)

class HelloWorld(Resource):
    def get(self):
        parser = reqparse.RequestParser()
        parser.add_argument('rate', type=int, help='Rate to charge for this')
        args = parser.parse_args()
        return {'hello' : 'world'}
api.add_resource(HelloWorld, '/')

if __name__ == '__main__':
    app.run(debug=True)