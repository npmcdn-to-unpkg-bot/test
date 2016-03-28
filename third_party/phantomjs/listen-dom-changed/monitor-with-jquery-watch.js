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
        console.log('open success ...');
        if (page.injectJs('./scripts/jquery-watch.js')) {
            console.log('injectJS successfully');
        } else {
            console.log('injectJS failed');
            phantom.exit();
        }

        // set listener with jquery-watch!!!
        page.evaluate(function() {
            $('#change-css h4').watch({
                properties: 'color',
                callback: function(data, i) {
                    var propChanged = data.props[i];
                    var newValue = data.vals[i];
                    console.log('propChanged:' + propChanged + ', newValue:' + newValue);
                }
            });

            $('#ele-change').watch({
                properties: 'prop_innerHTML',
                watchChildren: true,
                callback: function(data, i, mutations) {
                    var propChanged = data.props[i];
                    var newValue = data.vals[i];
                    // console.log('propChanged:' + propChanged + ', newValue:' + newValue);

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
                    });
                }
            });
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