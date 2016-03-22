var page = require('webpage').create();

var url = 'https://www.baidu.com'
page.onConsoleMessage = function(msg) {
    console.log(msg);
}

page.open(url , function(status) {
    page.evaluation(function() {
        consolo.log('Page title is ' + document.title);
    });

    phantom.exit();
})