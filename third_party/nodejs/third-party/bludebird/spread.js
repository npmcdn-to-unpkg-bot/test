var Promise = require('bluebird');


Promise.delay(500).then(function() {
	return ['a', 'b', 'c'];
}).spread(function(a,b,c) {
	console.log(a);
	console.log(b);
	console.log(c);
}).then(function() {
	console.log('hahahaha,nothing is here');
	return 'wo kao';
}).then(function(d) {
	console.log(d);
});