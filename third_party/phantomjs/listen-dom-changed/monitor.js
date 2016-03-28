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
            var observer = new MutationObserver(function(mutations) {
                mutations.forEach(function(m) {
                window.callPhantom({'type' : m.type});
                switch (m.type) {
                    case 'attributes':
                        console.log('attributes:' + m.attributeName + ' changed: oldValue [' + m.oldValue + ']');
                        break;
                    case 'characterData':
                        console.log('characterData:' + 'changed');
                        break;
                    case 'childList':
                        console.log('childList:' + 'changed');
                        break;
                    default:
                        console.log('unkown type:' + m.type);
                }
              })
            });
            var config = { 
                attributes: true,
                childList: true,
                characterData: true,
                attributeOldValue: true,
                subtree: true
            };

            var target1 = document.querySelector('#change-css h4');
            var target2 = document.querySelector('#ele-change');
            observer.observe(target1, config);
            observer.observe(target2, config);
        });

        // change css
        var changeCSS = function() {
            page.evaluate(function() {
                $('#change-css #color').click();
            });
        };
        var addDom = function() {
            page.evaluate(function() {
                $('#ele-change #add').click();
            })
        };
        var deleteDom = function() {
            page.evaluate(function() {
                $('#ele-change #del').click();
            });
        };

        setInterval(changeCSS, 1000);
        setInterval(addDom, 2000);
        setInterval(deleteDom, 4000);

    } else {
        console.log('failed to open')
    }
});