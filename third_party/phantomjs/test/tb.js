"use strict";

var webPage = require('webpage'),
    system = require('system');

if (system.args.length !== 3) {
    console.log('Usage: ' + system.args[0] + ' <username> <password>');
    phantom.exit();
}

var username = system.args[1];
var password = system.args[2];
console.log('username:' + username + ", password: xxxxx");

var page = webPage.create();
// page settings
page.settings.userAgent = 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:45.0) Gecko/20100101 Firefox/45.0';
page.settings.javascriptEnabled = true;
page.settings.loadImages = true;
phantom.cookieEnabled = true;
phantom.javascriptEnabled = true;
page.viewportSize = { width: 1920, height: 1080 };
page.clipRect = { top: 0, left: 0, width: 1920, height: 1080 };

// page callbacks
page.onConsoleMessage = function(msg) {
    console.log(msg);
};

page.onResourceReceived = function(response) {
    if (response.stage !== "end") {
        return;
    }
    // console.log('=> Response (#' + response.id + ', stage "' + response.stage + '"): ' + response.url);
    // console.log(JSON.stringify(response));
};

page.onResourceRequested = function(requestData, networkRequest) {
    // console.log('=> Request (#' + requestData.id + '): ' + requestData.url);
    // console.log('onResourceRequested:' + JSON.stringify(requestData));
    // console.log('onResourceRequested networkRequest:' + JSON.stringify(networkRequest));
    // console.log('onResourceRequested cookies:' + JSON.stringify(page.cookies));
};

page.onUrlChanged = function(targetUrl) {
    console.log('=> New URL: ' + targetUrl);
};

page.onLoadFinished = function(status) {
    console.log('=> Load Finished: ' + status);
    injectJsIfNeed();
};

page.onLoadStarted = function() {
    console.log('=> Load Started');
};

page.onNavigationRequested = function(url, type, willNavigate, main) {
    console.log('=> Trying to navigate to: ' + url + ', type:' + type + ', willNavigate:' + willNavigate + ', main:' + main);
};

page.onCallback = function(event) {
    console.log('onCallback: ' + event.name);
    switch (event.type) {
    case 'sendEvent':
        for (var i in event.events) {
            var evt = event.events[i];
            console.log('  ' + evt.type + '=>(' + evt.x + ',' + evt.y + ')');
            page.sendEvent(evt.type, evt.x, evt.y);
        }
        break;
    case 'controlMsg':
        pushToServer(event.info, function onResult(result) {
            var x = event.info.x + event.info.width * result.xPercent;
            var y = event.info.y + event.info.height * result.yPercent;
            console.log('   click on =>(' + x + ',' + y + ')');
            page.sendEvent('click', x, y);
        });
        break;
    case 'pageOpen':
        page.open(event.url);
        break;
    default:
        console.log('onCallback unkown type:' + event.type);
    }
};

// control page.
var controlURL = 'http://127.0.0.1:3333/control/';
var controlPage = webPage.create();
var reusultCallback = null;
controlPage.onConsoleMessage = function(msg) {
    console.log('control:' + msg);
};

controlPage.onCallback = function(data) {
    console.log('control onCallback:' + data.msg);
    var result = JSON.parse(data.msg);
    reusultCallback(result);
};
controlPage.open(controlURL, function(status) {
    if (status === 'success') {
        console.log('control page open success');
    } else {
        console.log('failed to open control page');
    }
});

var pushToServer = function(info, callback) {
    var data = JSON.stringify(info);
    reusultCallback = callback;
    controlPage.evaluate(function(data) {
        socket.emit('control', data);
    }, data);
}

// main
var url = 'https://login.taobao.com/';

console.log('start to open ' + url);
page.open(url, function(status) {
    if (status === 'success') {
        console.log('open success...');

        page.evaluate(function(username, password) {
            login(username, password);
        }, username, password);

        setInterval(function() {
            console.log('render page interval')
            page.render('interval.png');
        }, 1000);
    } else {
        console.log('Fail to open ' + url);
        phantom.exit();
    }
});

var injectJsIfNeed = function() {
    var files = [
        { exists: isJqueryIn, location: './scripts/jquery.min.js' },
        { exists: isJQueryWatchIn, location: './scripts/jquery-watch.js' },
        { exists: notIn, location: './scripts/tb.js'}
    ];

    for (var i in files) {
        var entry = files[i];
        if (!entry.exists()) {
            if (page.injectJs(entry.location)) {
                console.log('Success to inject [' + entry.location + ']');
            } else {
                console.log('Failed to inject [' + entry.location + ']');
                phantom.exit();
            }
        } else {
            console.log('already in???')
        }
    }

    // do something initialization
    page.evaluate(function(username, password) {
        startWatching(username, password);
    }, username, password);

    function isJqueryIn() {
        return page.evaluate(function() {
            return typeof jQuery !== 'undefined';
        })
    }
    function isJQueryWatchIn() {
        return page.evaluate(function() {
            return typeof jQuery !== 'undefined' &&
                typeof jQuery.fn.watch !== 'undefined';
        })
    }
    function notIn() {
        // TODO
        return false;
    }
};