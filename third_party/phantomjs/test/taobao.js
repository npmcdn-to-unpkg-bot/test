"use strict";

var webPage = require('webpage'),
    system = require('system');

if (system.args.length !== 3) {
    console.log('Usage: taobao.js <username> <password>');
    phantom.exit();
}

var username = system.args[1];
var password = system.args[2];
console.log('username:' + username + ", password: xxxxx");

var page = webPage.create();
page.settings.userAgent = 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:45.0) Gecko/20100101 Firefox/45.0';
page.settings.javascriptEnabled = true;
page.settings.loadImages = true;
phantom.cookieEnabled = true;
phantom.javascriptEnabled = true;

page.onConsoleMessage = function(msg) {
    console.log(msg);
}

page.onResourceReceived = function(response) {
    if (response.stage !== "end")
        return;
    // console.log('> Response (#' + response.id + ', stage "' + response.stage + '"): ' + response.url);
};
page.onResourceRequested = function(requestData, networkRequest) {
    // console.log('> Request (#' + requestData.id + '): ' + requestData.url);
};
page.onUrlChanged = function(targetUrl) {
    console.log('> New URL: ' + targetUrl);
};
var loaded = 0;
page.onLoadFinished = function(status) {
    console.log('> Load Finished: ' + status);
    loaded = loaded + 1;
    page.render('loaded' + loaded + '.png');
};
page.onLoadStarted = function() {
    console.log('> Load Started');
};
page.onNavigationRequested = function(url, type, willNavigate, main) {
    console.log('> Trying to navigate to: ' + url);
};
page.onCallback = function(data) {
    console.log('onCallback');
};

var url = 'https://login.taobao.com/';

//viewportSize being the actual size of the headless browser
page.viewportSize = { width: 1920, height: 1080 };
//the clipRect is the portion of the page you are taking a screenshot of
page.clipRect = { top: 0, left: 0, width: 1920, height: 1080 };

console.log('start to open ' + url);
page.open(url, function(status) {
    if (status === 'success') {
        console.log('open success...');

        var injectJs = function(name) {
            if (page.injectJs(name)) {
                console.log('Success to inject [' + name + ']');
            } else {
                console.log('Failed to inject [' + name + ']');
                phantom.exit();
            }
        };

        injectJs('./scripts/jquery.min.js');
        injectJs('./utility.js');

        // set listener for key element's css change
        page.evaluate(function(username, password) {
            login(username, password);
        }, username, password);

        var injected = false;
        waitFor(function check() {
            if (!injected) {
                injectJs('./scripts/jquery.min.js'); // why need to inject again?
                injectJs('./utility.js');
                injected = true;
            }

            return page.evaluate(function() {
                return isNocaptchaReady();
            });
        }, function onReady() {
            console.log('nocaptcha is showing...');
            page.evaluate(function() {
                report('#nocaptcha');
                report('#nocaptcha #_nlz');
                report('#nocaptcha #_bg');
                report('#nocaptcha #_scale_text');
            });

            var pos = page.evaluate(function() {
                return getPositions();
            });

            var downX = pos.bg.x + 20;
            var downY = pos.bg.y + pos.bg.height/2;
            console.log('mousedown...');
            page.sendEvent('mousedown', downX, downY);

            console.log('mousemove...');
            page.sendEvent('mousemove', downX + 20, downY);
            page.sendEvent('mousemove', downX + pos.scale_text.width, downY);

            // set another waitFor to check picture
            waitFor(function check() {
                return page.evaluate(function() {
                    return isClickCaptchaImgReady();
                });
            }, function onReady() {
                var imgURL = page.evaluate(function() {
                    return getClickCaptchaImgURL();
                });
                console.log('image src = ' + imgURL);
            }); // waitFor

        }, 10000); // waitFor

        setInterval(function() {
            console.log('render page interval')
            page.render('interval.png');
            page.evaluate(function() {
                report();
            })
        }, 1000);
    } else {
        console.log('Fail to open ' + url);
        phantom.exit();
    }
});

function waitFor(testFx, onReady, timeOutMillis) {
    var maxtimeOutMillis = timeOutMillis ? timeOutMillis : 5000, //< Default Max Timout is 5s
        start = new Date().getTime(),
        condition = false,
        interval = setInterval(function() {
            if ( (new Date().getTime() - start < maxtimeOutMillis) && !condition ) {
                // If not time-out yet and condition not yet fulfilled
                condition = (typeof(testFx) === "string" ? eval(testFx) : testFx()); //< defensive code
            } else {
                if(!condition) {
                    // If condition still not fulfilled (timeout but condition is 'false')
                    console.log("'waitFor()' timeout");
                    clearInterval(interval);
                } else {
                    // Condition fulfilled (timeout and/or condition is 'true')
                    console.log("'waitFor()' finished in " + (new Date().getTime() - start) + "ms.");
                    typeof(onReady) === "string" ? eval(onReady) : onReady(); //< Do what it's supposed to do once the condition is fulfilled
                    clearInterval(interval); //< Stop this interval
                }
            }
        }, 250); //< repeat check every 250ms
};