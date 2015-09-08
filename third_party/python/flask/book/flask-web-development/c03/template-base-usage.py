from flask import Flask, render_template

app = Flask(__name__)

@app.route('/')
def index():
	mylist = ['list00', 'list01', 'list02', 'list03', 'list04']
	mydict = {'key':'haha', 'a': 1}
	myintvar = 2
	class Obj:
		def somemethod(self):
			return 33
	myobj = Obj()
	comments = [1,2,3,4,5]
	return render_template('index.html', mydict=mydict,
			mylist=mylist, myintvar=myintvar, myobj=myobj,
			comments=comments)

if __name__ == '__main__':
	app.run(debug=True)