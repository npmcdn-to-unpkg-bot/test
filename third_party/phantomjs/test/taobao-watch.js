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

// some status for page
var needInjectJS = true;
var loadFinished = false;

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
};

page.onResourceRequested = function(requestData, networkRequest) {
    // console.log('=> Request (#' + requestData.id + '): ' + requestData.url);
};

page.onUrlChanged = function(targetUrl) {
    console.log('=> New URL: ' + targetUrl);
};

page.onLoadFinished = function(status) {
    loadFinished = true;
    console.log('=> Load Finished: ' + status);
    injectJsIfNeed();
};

page.onLoadStarted = function() {
    console.log('=> Load Started');
};

page.onNavigationRequested = function(url, type, willNavigate, main) {
    // injected js only exsits in the current page.
    // so you need to reinject javascript again when you navigate to
    // a new URL
    needInjectJS = true;
    console.log('=> Trying to navigate to: ' + url + ', type:' + type + ', willNavigate:' + willNavigate + ', main:' + main);
};

page.onCallback = function(data) {
    console.log('onCallback');
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
            var t = $('#J_LoginBox');
            if (t.length > 0) {
                console.log('t is not none');
                t.watch({ properties:'display', callback: function(data, i) {
                    console.log('callback aaaa:' + i);
                }});
            } else {
                t.watch({properties:'display', callback: function(data, i) {
                    console.log('callback bbbb');
                }});
                t.watch({properties : 'display'});
            }

            $('#dafei').watch({ watchChildren: true, callback: function(data, i) {
                console.log('dafei aaaa:' + i);
            }});
            login(username, password);
        }, username, password);


        // setInterval(function() {
        //     console.log('render page interval')
        //     page.render('interval.png');
        // }, 1000);
    } else {
        console.log('Fail to open ' + url);
        phantom.exit();
    }
});

var injectJsIfNeed = function() {
    if (!needInjectJS) {
        console.log('no need to inject...')
        return;
    }

    var files = [
        './scripts/jquery.min.js',
        './scripts/jquery-watch.js',
        './utility.js'
    ];

    for (var i in files) {
        var file = files[i];
        if (page.injectJs(file)) {
            console.log('Success to inject [' + file + ']');
        } else {
            console.log('Failed to inject [' + file + ']');
            phantom.exit();
        }
    }
    needInjectJS = false;
};