var Task = {
    createNew : function(selector, check, onReady) {
        var task = {};
        task.check = check;
        task.onReady = onReady;
        task.watch = function(selector) {
            if (check()) {
                onReady();
                return;
            }

            $(selector).watch({
                properties: 'prop_innerHTML',
                callback: function() {
                    if (check()) onReady();
                }
            });
        }
        task.watch(selector);
        return task;
    }
}

function login(username, password) {
    console.log('fillForm username:' + username);
    $('#TPL_username_1').focus();
    $('#TPL_username_1').val(username);
    $('#TPL_password_1').focus();
    $('#TPL_password_1').val(password);

    $('#J_SubmitStatic').click();

    // window.callPhantom({
    //     type : 'fillForm'
    // });
}

function startWatching(username, password) {
    var nocaptchaCheck = function () {
        var nocaptcha = $('#nocaptcha');
        var scale_text = $('#nocaptcha #_scale_text');
        var start_text = $('#nocaptcha #_scale_text span[data-nc-lang="_startTEXT"]');
        console.log('nocaptcha display:' + nocaptcha.css('display')
            + ', width:' + nocaptcha.width()
            + ', scale_text width:' + scale_text.width()
            + ', height:' + scale_text.height());

        return nocaptcha.css('display') !== 'none'
            && nocaptcha.width() > 0
            && scale_text.width() > 0
            && scale_text.height() > 0
            && start_text.length > 0;
    };
    var nocaptchaOnReady = function() {
        console.log('nocaptcha is ready to move');
        // tell phantom to sendEvent to move the button
        var bg = $('#nocaptcha #_bg');
        var scale_text = $('#nocaptcha #_scale_text');
        var width = scale_text.width();
        var startX = bg.offset().left + 20;
        var startY = bg.offset().top + bg.height()/2;

        var events = [
            { type: 'mousedown',
                x: startX,
                y: startY },
            { type: 'mousemove',
                x: startX + 20,
                y: startY },
            { type: 'mousemove',
                x: startX + width,
                y: startY }

        ];
        window.callPhantom({
            name: 'nocaptcha',
            type: 'sendEvent',
            events: events
        });
    };

    var clickCaptchaCheck = function() {
        var img = $('#clickCaptcha .clickCaptcha_img img');
        return img.length === 1;
    };

    var clickCaptchaOnReady = function() {
        console.log('click Image shows up!!!!');
        var img = $('#clickCaptcha .clickCaptcha_img img');
        var desc = $('#clickCaptcha .captcha-error p').text();

        window.callPhantom({
            name: 'clickCaptcha',
            type: 'controlMsg',
            info: {
                type: 'click',
                imgURL: img.attr('src'),
                describe: desc,
                x: img.offset().left,
                y: img.offset().top,
                width: img.width(),
                height: img.height()
            }
        });
    };

    var imgCaptchaCheck = function() {
        var img = $('#imgCaptcha #_imgCaptcha_img img');
        return $('#imgCaptcha').css('display') !== 'none'
            && img.length > 0;
    };
    var imgCaptchaOnReady = function() {
        console.log('imgCaptcha shows up!!!!');
    };

    var captchaPassCheck = function() {
        var nocaptcha = $('#nocaptcha');
        var scale_text = $('#nocaptcha #_scale_text');
        var yes_text = $('#nocaptcha #_scale_text span[data-nc-lang="_yesTEXT"]');
        console.log('nocaptcha display:' + nocaptcha.css('display')
            + ', width:' + nocaptcha.width()
            + ', scale_text width:' + scale_text.width()
            + ', height:' + scale_text.height());

        return nocaptcha.css('display') !== 'none'
            && nocaptcha.width() > 0
            && scale_text.width() > 0
            && scale_text.height() > 0
            && yes_text.length > 0;
    };
    var captchaPassOnReady = function() {
        console.log('captcha passed...start to login...');
        login(username, password);
    }

    var navigateBoughtListCheck = function() {
        // check if login then navigate to bought list page
        var loginInfo = $('#J_LoginInfo');
        return loginInfo.length > 0
            && window.location.host === 'i.taobao.com'
            && window.location.pathname == '/my_taobao.htm';
    };
    var navigateBoughtListOnReady = function() {
        console.log('We lonin, navigate to bought list page...');
        window.callPhantom({
            name: 'navigateBoughtList',
            type: 'pageOpen',
            url: 'https://buyertrade.taobao.com/trade/itemlist/list_bought_items.htm'
        });
    };

    var boughtListCheck = function() {
        // taobao store data of first one page into a JS var data in
        // https://buyertrade.taobao.com/trade/itemlist/list_bought_items.htm
        // so after load finished, you will get the data of first page.
        return typeof data === 'object'
            && window.location.host  === 'buyertrade.taobao.com'
            && window.location.pathname === '/trade/itemlist/list_bought_items.htm';
    };
    var boughtListOnReady = function() {
        console.log('we got the bought list...');
        console.log(data.mainOrders.length);
        for (var i=0; i<data.mainOrders.length; i++) {
            var item = data.mainOrders[i];
            console.log('------------------------------------------------')
            console.log('id:' + item.id + ',createTime:' + item.orderInfo.createTime + '\n'
                + 'fee:' + item.payInfo.actualFee);
        }
        
        function doPOST() {
            var o = new XMLHttpRequest();
            o.onreadystatechange= function() {
                console.log('XMLHttpRequest readyState:' + o.readyState + ', status:' + o.status);
                console.log(o.responseText);
            }
            o.open('post', "https://buyertrade.taobao.com/trade/itemlist/asyncBought.htm?action=itemlist/BoughtQueryAction&event_submit_do_query=1&_input_charset=utf8", true);
            
            var headers = {
                'Accept' : "application/json, text/javascript, */*; q=0.01",
                'Content-Type' : "application/x-www-form-urlencoded; charset=UTF-8",
                'X-Requested-With' : "XMLHttpRequest"
            }
            for (var key in headers) {
                o.setRequestHeader(key, headers[key]);
            }

            o.send("pageNum=1&pageSize=5&prePageNo=1");
        }

        doPOST();
    };

    var nocaptchaTask = Task.createNew('#nocaptcha', nocaptchaCheck, nocaptchaOnReady);
    var clickCaptchaTask = Task.createNew('#clickCaptcha', clickCaptchaCheck, clickCaptchaOnReady);
    var imgCaptchaTask = Task.createNew('#imgCaptcha', imgCaptchaCheck, imgCaptchaOnReady);
    var captchaPassTask = Task.createNew('#nocaptcha', captchaPassCheck, captchaPassOnReady);
    var navigateBoughtListTask = Task.createNew('html', navigateBoughtListCheck, navigateBoughtListOnReady);
    var boughtListTask = Task.createNew('html', boughtListCheck, boughtListOnReady);
}
