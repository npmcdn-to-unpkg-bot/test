"use strict";

var page = require('webpage').create();

page.onConsoleMessage = function(msg) {
    console.log(msg);
};

page.onCallback = function(data) {
    console.log('onCallback:' + data.type);
};

var url = 'http://127.0.0.1:3333/';
page.open(url, function(status) {
    if (status === 'success') {
        console.log('open success and start to monitor dom change');

        // set listener
        page.evaluate(function() {
            var target = document.querySelector('#change-css h4');
            var observer = new MutationObserver(function(mutations) {
                mutations.forEach(function(m) {
                window.callPhantom({'type' : m.type});
                if (m.type === 'attributes') {
                    console.log(m.attributeName + ' changed: ' + m.oldValue + ', target:');
                    console.log(m.target);
                } else {
                    console.log(m.type + ' changed, ');
                }
              })
            });
            var config = { attributes: true, childList: true, characterData: true};
            observer.observe(target, config);
        });

        // change css
        var changeCSS = function() {
            page.evaluate(function() {
                $('#change-css #color').click();
            });
        };
        setInterval(changeCSS, 1000);

    } else {
        console.log('failed to open')
    }
});