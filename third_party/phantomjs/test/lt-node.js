var request = require('request');
var async = require('async');
var path = require('path');

request = request.defaults({jar: true});
var j = request.jar();

function step1(callback) {
    var hostname = 'https://uac.10010.com/portal/homeLogin';
    request({ url: hostname, jar: j}, function(error, res, body) {
        if (error) {
            callback('step1 error:' + error, 'step1 failed...');
        } else {
            callback(null, 'step1 success...');
        }
    });
}

function step2(username, password, callback) {
        var hostname = 'https://uac.10010.com/portal/Service/MallLogin?callback=jQuery17208017945039430452_1459410841956&req_time='
            + new Date().getTime()
            + '&redirectURL=http://www.10010.com/&'
            + 'userName=' + username
            + '&password=' + password
            + '&pwdType=01&productType=01&redirectType=01&rememberMe=1'
        request({ url: hostname, jar: j}, function(error, res, body) {
            if (!error) {
                var resultCode = parseLoginResultCode(body);
                if (resultCode !== '0000') {
                    callback('step2 resultCode:' + resultCode, 'step2 failed...');
                } else {
                    callback(null, 'step2 success...');
                }
            } else {
                callback('step2 error:' + error, 'login failed...');
            }
        });

        function parseLoginResultCode(body) {
            var t = body.match(/{.+}/);
            if (t.length > 0) {
                var d = t[0].replace('resultCode', '"resultCode"').replace('redirectURL', '"redirectURL"');
                try {
                    var result = JSON.parse(d);
                    return result.resultCode;
                } catch(e) {
                    return null;
                }
            }
            return null;
        }
}

function step3(callback) {
    var hostname = 'http://www.10010.com/';
    request({url: hostname, jar: j}, function(error, res, body) {
        if (error) {
            callback('step3 error:' + error, 'step3 failed...');
        } else {
            callback(null, 'step3 success...');
        }
    });
}

function step4(callback) {
    var hostname = 'http://iservice.10010.com/e3/query/paid_record.html?menuId=000100010003';
    request.post({ url: hostname, jar: j }, function(error, res, body) {
        if (error) {
            callback('step4 error:' + error, 'step4 failed...');
        } else {
            callback(null, 'step4 success...');
        }
    });
}

function pCookie(url) {
    var cookies = j.getCookies(url);
    // var cookies = request.jar().getCookies(url);
    console.log('\n=> Cookies [' + url + ']---------');
    for (var key in cookies) {
        console.log('[' + key + '] = [' + cookies[key] + ']');
    }
}


function step5(callback) {
    //  menuId=000100010003  getNaviId() { return $.cookie('MII'); }
    var hostname = 'http://iservice.10010.com/e3/static/query/paymentRecord?_=' + new Date().getTime() +'&menuid=000100010003';
    j.setCookie(request.cookie('MIE=00020001'), 'http://iservice.10010.com');
    j.setCookie(request.cookie('MII=000100010003'), 'http://iservice.10010.com');
    pCookie(hostname);
    request.post({ url: hostname, jar: j, form: {
        beginDate: "20160101",
        endDate: "20160131",
        pageNo: "1",
        pageSize: "20"
    }}, function (error, res, body) {
        if (error) {
            callback('step5 error:' + error, 'step5 failed...');
        } else {
            callback(null, 'step5 success...' + body);
        }
    })
}

function start(username, password) {
    async.series([
        step1,
        function (cb) {
            step2(username, password, cb);
        },
        step3,
        step4,
        step5
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
}
var username = process.argv[2];
var password = process.argv[3];
start(username, password);







