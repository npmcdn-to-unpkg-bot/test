'use strict'

const request = require('request');
// require('request-debug')(request);
const fs = require('fs');


request({
	url: `https://www.baidu.com/img/bd_logo1.png`,
	encoding: null
}, function(err, res, body) {
	if (err) {
		console.log(err)
	} else {
		fs.writeFile('example.png', body);
	}
})
