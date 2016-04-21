var request = require('request');
// require('request-debug')(request);

var options = {
    url: 'https://www.badu1.com',
};
var options1 = {
    url: 'https://www.fakeurl.com',
    timeout: 1000, // ms
};

var options2 = {
    url: 'http://127.0.0.1',
    timeout: 1000, // ms
};


function callback(error, res, body) {
    console.log('-----------------------------------');
    if (error) {
        console.log(JSON.stringify(error));
        console.log(error);
        if (error && error.code === 'ETIMEDOUT') {
            console.log('We got a timeout ERROR')
        }
    } else {
        console.log(res.req)
        console.log( res.statusCode);
    }
}

request(options, callback);
request(options1, callback);
request(options2, callback);
