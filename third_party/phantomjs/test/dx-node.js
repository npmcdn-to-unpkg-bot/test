var request = require('request');
var async = require('async');
var path = require('path');
var dx = require('./dxAesEncrypt.js');

// debug info
require('request-debug')(request);


request = request.defaults({jar: true});
var j = request.jar();

function step1(username, password, callback) {
    var hostname = 'http://login.189.cn/login';
    var form = {
        Account: username,
        UType: "201",
        ProvinceID: "01",
        AreaCode: "",
        CityNo: "",
        RandomFlag: "0",
        Password: dx.aesEncrypt(password),
        Captcha: ""
    };
    request.post({
        url: hostname,
        jar: j,
        form: form,
        followRedirect: true,
        followAllRedirects: true
    }, function(error, res, body) {
        if (error) {
            callback('step1 error:' + error, 'step1 failed...');
        } else {
            console.log('step1: status code:'+ res.statusCode)
            // console.log(body);
            // console.log(res);
            callback(null, 'step1 success...');
        }
    });
}

function step2(callback) {
    // go to billing page
    var url = 'http://www.189.cn/dqmh/my189/initMy189home.do?fastcode=01390635&tab=1';
    request({
        url: url,
        jar: j,
        followRedirect: true,
        followAllRedirects: true
    }, function(error, res, body) {
        if (error) {
            callback('step2 error:' + error, 'step2 failed...');
        } else {
            console.log('step2: status code:'+ res.statusCode)
            // console.log(body);
            // console.log(res);
            callback(null, 'step2 success...');
        }
    })
}

function step3(callback) {
    // go to built-in iframe
    var url = 'http://www.189.cn/dqmh/ssoLink.do?method=linkTo&platNo=10001&toStUrl=http://bj.189.cn/iframe/feequery/custFeeIndex.action?fastcode=01390635&tab=1';
    request({
        url: url,
        jar: j,
        followRedirect: true,
        followAllRedirects: true
    }, function(error, res, body) {
        if (error) {
            callback('step3 error:' + error, 'step3 failed...');
        } else {
            console.log('step3: status code:'+ res.statusCode)
            // console.log(body);
            // console.log(res);
            callback(null, 'step3 success...');
        }
    })
}

function step4(callback) {
    // this will get the iframe html.
    var url = 'http://bj.189.cn/iframe/feequery/custFeeIndex.action?tab=tab1&time=' + new Date().getTime();
    request({
        url: url,
        jar: j,
        followRedirect: true,
        followAllRedirects: true
    }, function(error, res, body) {
        if (error) {
            callback('step4 error:' + error, 'step4 failed...');
        } else {
            console.log('step4: status code:'+ res.statusCode)
            // console.log(body);
            // console.log(res);
            callback(null, 'step4 success...');
        }
    })
}

function step5(username, callback) {
    // this will get the iframe html.
    var url = 'http://bj.189.cn/iframe/feequery/qryBalance.action?requestFlag=asynchronism&p1QueryFlag=2&accNum='
        + username + '&time=' + new Date().getTime();
    request({
        url: url,
        jar: j,
        followRedirect: true,
        followAllRedirects: true
    }, function(error, res, body) {
        if (error) {
            callback('step5 error:' + error, 'step5 failed...');
        } else {
            console.log('step5: status code:'+ res.statusCode)
            console.log(body);
            // console.log(res);
            callback(null, 'step5 success...');
        }
    })
}

function start(username, password) {
    async.series([
        function (cb) {
            step1(username, password, cb);
        },
        step2,
        step3,
        step4,
        function (cb) {
            step5(username, cb);
        }
    ], function callback(err, results) {
        if (err) {
            console.log(err);
        } else {
            console.log(results);
        }
    });
}

if (process.argv.length !== 4) {
    console.log('Usage: ' + path.basename(process.argv[1]) + ' <username> <password>')
    process.exit();
}http://bj.189.cn/iframe/feequery/custFeeIndex.action?tab=tab1&time=1460013918983
var username = process.argv[2];
var password = process.argv[3];
start(username, password);







