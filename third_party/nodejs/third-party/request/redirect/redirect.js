var request = require('request');
// require('request-debug')(request);



function callback(error, res, body) {
    console.log('-----------------------------------');
    if (error) {
        console.log(JSON.stringify(error));
        console.log(error);
        if (error && error.code === 'ETIMEDOUT') {
            console.log('We got a timeout ERROR')
        }
    } else {
        // res.request.uri is an Object of Url.
        // console.log(res)
        console.log(res.request.uri)
        console.log(`hostname:${res.request.uri.hostname}`)
        console.log(`host:${res.request.uri.host}`)
        console.log(`pathname:${res.request.uri.pathname}`)
        console.log(`path:${res.request.uri.path}`)
        console.log(`href:${res.request.uri.href}`)
        console.log(`statusCode:${res.statusCode}`)

        console.log(body)
    }
}


var options1 = {
    url: `http://127.0.0.1:3000`,
    method: 'POST'
}
request(options1, callback)

var options1 = {
    url: `http://127.0.0.1:3000`,
    method: 'GET'
}
request(options1, callback)
