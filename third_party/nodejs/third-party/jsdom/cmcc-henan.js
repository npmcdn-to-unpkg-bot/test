var jsdom = require('jsdom');
var cookieJar = jsdom.createCookieJar();


jsdom.env({
    url: "https://ha.ac.10086.cn/login",
    cookieJar: cookieJar,
    done: function (err1, window1) {
        if (err1) {
            console.log(err1);
            return;
        }
        jsdom.env({
            url: "https://ha.ac.10086.cn/login",
            cookieJar: cookieJar,
            features: {
                FetchExternalResources: ["script"],
                ProcessExternalResources: ["script"],
                SkipExternalResources: false
            },
            done: function (err, window) {
                if (err) {
                    console.log(err);
                    return;
                }
                var $ = window.$;
                // console.log($.jCryption.getKeys);
                $.jCryption.getKeys('/rsaKey?broUUid=' + window.Math.uuid() + '&random=' + Math.random() + '&jsoncallback=?', function(keys) {
                    console.log(keys);
                })
            }
        });
    }
});
