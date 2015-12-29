var Promise = require('bluebird');

Promise.delay(10).then(function() {
	return a.b.c();
}).catch(TypeError, ReferenceError, function(e) {
	console.log(e);
});


Promise.delay(10).then(function() {
	var a = 0;
	return a.b.c();
}).catch(function(e) {
	console.log(e);
});


// custom exception
function MyCustomError(message) {
	this.message = message;
	this.name = 'MyCustomError';
	Error.captureStackTrace(this, MyCustomError); // in nodejs and v8
}
MyCustomError.prototype = Object.create(Error.prototype);
MyCustomError.prototype.constructor = MyCustomError;

Promise.resolve().then(function() {
	throw new MyCustomError('Super error');
}).catch(MyCustomError, function(e) {
	console.log(e);
});