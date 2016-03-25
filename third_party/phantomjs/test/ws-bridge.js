"use strict";

var page = require('webpage').create();

page.onConsoleMessage = function(msg) {
    console.log(msg);
};

page.onCallback = function(data) {
    console.log('onCallback:' + data.msg);
    page.evaluate(function() {
        socket.emit('control', 'hi from phontomjs')
    })
};

var url = 'http://127.0.0.1:3333/control';
page.open(url, function(status) {
    if (status === 'success') {
        console.log('open success');
    } else {
        console.log('failed to open')
    }
});
