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
    console.log('onCallback:' + data.name + ', data:' + data.data);
};

var url = 'https://login.taobao.com/';

//viewportSize being the actual size of the headless browser
page.viewportSize = { width: 1920, height: 1080 };
//the clipRect is the portion of the page you are taking a screenshot of
page.clipRect = { top: 0, left: 0, width: 1920, height: 1080 };

console.log('start to open ' + url);
page.open(url, function(status) {
    if (status === 'success') {
        // use jquery
        console.log('open success...');
        page.includeJs('https://cdn.bootcss.com/jquery/2.2.1/jquery.min.js', function() {
            console.log('jquery included ...');
            page.render('p0.png');

            console.log('start to run js in webpage...')
            var result = page.evaluate(function(username, password) {
                // test info
                var detectNocaptcha = function() {
                    console.log('>nocaptcha display is ' + $('#nocaptcha').css('display'));
                };

                detectNocaptcha();

                console.log('TPL_username_1:' + $('#TPL_username_1').val());
                $('#TPL_username_1').focus();
                $('#TPL_username_1').val(username);
                $('#TPL_password_1').focus();
                $('#TPL_password_1').val(password);

                detectNocaptcha();
                window.callPhantom({'name' : 'testing', 'data' : 'ahahahahahah'});
                return {
                    'username' : $('#TPL_username_1').val(),
                    'password' : $('#TPL_password_1').val()
                }
            }, username, password);
            console.log('result is :' + result.username);

            console.log('render p1.png');
            page.render('p1.png');

            page.evaluate(function() {
                console.log('submit...');
                $('#J_SubmitStatic').click();

                var detectNocaptcha = function() {
                    console.log('>nocaptcha display is ' + $('#nocaptcha').css('display'));
                };
                detectNocaptcha();
            });
            
            console.log('p2.png');
            page.render('p2.png');

            page.evaluate(function() {
                console.log('test for jquery:' + $('#nocaptcha').css('display'));
                var detectNocaptcha = function() {
                    console.log('>nocaptcha display is ' + $('#nocaptcha').css('display'));
                };
                detectNocaptcha();
            });

            setInterval(function() {
                page.render('interval.png');
            }, 500);
        });
    } else {
        console.log('Fail to open ' + url);
        phantom.exit();
    }
});

