"use strict";

var page = require('webpage').create();

page.onConsoleMessage = function(msg) {
    console.log(msg);
};

page.onCallback = function(data) {
    console.log('onCallback:' + data.msg);
};

var url = 'http://127.0.0.1:3333/';
page.open(url, function(status) {
    if (status === 'success') {
        console.log('open success');
        page.evaluate(function() {
            console.log('start to monitor the element')
            var e = $('#log');
            e.on('DOMSubtreeModified',function(){ 
                  console.log('+++dom changed');
            });
        });
    } else {
        console.log('failed to open')
    }
});