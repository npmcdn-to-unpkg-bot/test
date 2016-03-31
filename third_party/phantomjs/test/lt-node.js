var request = require('request');
var path = require('path');

request = request.defaults({jar: true});
var j = request.jar();

function login(username, password) {
    var hostname = 'https://uac.10010.com/portal/homeLogin';
    request({ url: hostname, jar: j}, function() {
        pCookie(hostname);

        hostname = 'https://uac.10010.com/portal/Service/MallLogin?callback=jQuery17208017945039430452_1459410841956&req_time='
            + new Date().getTime()
            + '&redirectURL=http://www.10010.com/&'
            + 'userName=' + username
            + '&password=' + password
            + '&pwdType=01&productType=01&redirectType=01&rememberMe=1'

        request({ url: hostname, jar: j}, function(error, res, body) {
            if (!error) {
                console.log('statusCode:' + res.statusCode);
                console.log(body);
                pCookie(hostname);

                hostname = 'http://www.10010.com/';
                request({url: hostname, jar: j}, function() {
                    console.log('statusCode:' + res.statusCode);
                    pCookie(hostname);
                    navigateToPayrecorPage();
                })
            } else {
                console.log('request error:' + error);
            }
        });
    });



    function parseLoginResult(body) {

    }
}

function navigateToPayrecorPage() {
    var hostname = 'http://iservice.10010.com/e3/query/paid_record.html?menuId=000100010003';
    request({ url: hostname, jar: j }, function(error, res, body) {
        if (!error) {
            console.log('statusCode:' + res.statusCode);
            pCookie(hostname);
            console.log(body);
            getPaymentRecord();
        } else {
            console.log('request error:' + error);
        }
    });
}

function pCookie(url) {
    var cookie_string = j.getCookieString(url);
    // var cookies = request.jar().getCookies(url);
    console.log('cookie for ' + url + ' is:' + cookie_string);
}


function getPaymentRecord(argument) {
    //  menuId=000100010003  getNaviId() { return $.cookie('MII'); }

    var hostname = 'http://iservice.10010.com/e3/static/query/paymentRecord?_=' + new Date().getTime() +'&menuid=000100010003';
    request.post({ url: hostname, jar: j, form: {
        beginDate: "20160101",
        endDate: "20160131",
        pageNo: "1",
        pageSize: "20"
    }}, function (error, res, body) {
        if (!error) {
            console.log('statusCode:' + res.statusCode);
            console.log(body);
            pCookie(hostname);
        } else {
            console.log('request error:' + error);
        }
    })
}


if (process.argv.length !== 4) {
    console.log('Usage: ' + path.basename(process.argv[1]) + ' <username> <password>')
    process.exit();
}
var username = process.argv[2];
var password = process.argv[3];

login(username, password);