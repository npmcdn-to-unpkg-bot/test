var request = require('request');
require('request-debug')(request);

var options = {
    uri: '/',
    baseUrl: 'https://www.baidu.com',
    qs: {
        arg1: 'fake-arg1',
        arg2: 'fake-arg2',
        arg3: '中文'
    }
};

function callback(error, res, body) {
    if (error) {
        console.log('error:' + error);
    } else {
        console.log(res.statusCode);
    }
}

// 'https://www.baidu.com/?arg1=fake-arg1&arg2=fake-arg2&arg3=%E4%B8%AD%E6%96%87',

request(options, callback);
