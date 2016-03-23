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
page.onCallback = function(event) {
    console.log('Receive event [' + event.type + ']')
    switch (event.type) {
    case 'nocaptcha':
        console.log('  ' + event.property + '=>' + event.value);
        break;
    case 'fillForm':
        break;
    case 'login':
        break;
    case 'report':
        console.log('report');
        break;
    default:
        console.log('unkonw event...');
        console.log(event);
    }
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
        injectJs('./scripts/jquery-watch.min.js');
        injectJs('./utility.js');

        // set listener for key element's css change
        page.evaluateAsync(function(username, password) {
            report();
            setSentry();

            fillForm(username, password);
            login();
        }, 0, password, username); // it seems a bug, arguments are past in a reversed order

        setInterval(function() {
            console.log('render page interval')
            page.render('interval.png');
        }, 1000);
    } else {
        console.log('Fail to open ' + url);
        phantom.exit();
    }
});

