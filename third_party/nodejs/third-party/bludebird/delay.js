var Promise = require('bluebird');

console.log('start to test ....');
Promise.delay(2000).then(function() {
	console.log('  timer-1 2 second passed...');
});

Promise.delay(1000).then(function() {
	console.log('  timer-2 1 second passed (1)..');
}).delay(1000).then(function() {
	console.log('  timer-2 1 second passed (2)..');
}).delay(1000).then(function() {
	console.log('  timer-2 1 second passed (3)..');
}).delay(1000).then(function() {
	console.log('  timer-2 1 second passed (4)..');
});

var i = 0;
var delay_func = function(timer_name) {
	console.log('i = ' + i);
	if (i < 10) {
		Promise.delay(1000).then(function(timer_name, count) {
			return function() {
				console.log(timer_name + ' 1 second passed (' + count + ')...');
				delay_func(timer_name);
			}
		}(timer_name, i+1));
		i = i + 1;
	}
};

delay_func('timer-3');