from flask import Flask, request
from flask_restful import Resource, Api, reqparse

app = Flask(__name__)
api = Api(app)

"""
The input is
'{
    "id" : "id-value",
    "name" : "myname",
    "devices" : [ "dev01", "dev02", "dev03"],
    "nested_one" : {
        "id" : 29,
        "good" : true,
        "name" : "dafei"
    },
    "nested_two" : {
        "id" : 30,
        "bad" : true
    }
}'


test:
curl -l -H "Content-type: application/json" -X POST -d '{"id":"id-value","name":"myname","devices":["dev01","dev02","dev03"],"nested_one":{"id":29,"good":true,"name":"dafei"},"nested_two":{"id":30,"bad":true}}' http://127.0.0.1:5000/test

"""



root_parser = reqparse.RequestParser()
root_parser.add_argument('id', required=True, help='id string')
root_parser.add_argument('name', required=True, help='name string')
root_parser.add_argument('devices', action='append', required=True, help='a list of devices')
root_parser.add_argument('nested_one', type=dict, help='nested_one dict')
root_parser.add_argument('nested_two', type=dict, required=True, help='nested_two dict')

nested_one_parser = reqparse.RequestParser()
nested_one_parser.add_argument('id', type=int, location=('nested_one',))
nested_one_parser.add_argument('good', type=bool, location=('nested_one',))
nested_one_parser.add_argument('name', location=('nested_one',))

nested_two_parser = reqparse.RequestParser()
nested_two_parser.add_argument('id', type=int, location=('nested_two',))
nested_two_parser.add_argument('bad', type=bool, location=('nested_two',))


class TodoSimple(Resource):
    def post(self):
        root_args = root_parser.parse_args()
        print '-' * 50
        print root_args
        one_args = nested_one_parser.parse_args(req=root_args)
        print '-' * 50
        print one_args
        two_args = nested_two_parser.parse_args(req=root_args)
        print '-' * 50
        print two_args
        return 'ok',200

api.add_resource(TodoSimple, '/test')

if __name__ == '__main__':
        app.run(debug=True)