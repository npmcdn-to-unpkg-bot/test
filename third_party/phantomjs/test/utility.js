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

function startWatching() {
    detectNocaptcha();
}

function detectNocaptcha() {
    watch('#nocaptcha');

    function watch(selector) {
        // check if ready
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

    function check() {
        var nocaptcha = $('#nocaptcha');
        var scale_text = $('#nocaptcha #_scale_text');
        console.log('nocaptcha display:' + nocaptcha.css('display')
            + ', width:' + nocaptcha.width()
            + ', scale_text width:' + scale_text.width()
            + ', height:' + scale_text.height());

        return nocaptcha.css('display') !== 'none'
            && nocaptcha.width() > 0
            && scale_text.width() > 0
            && scale_text.height() > 0;
    }

    function onReady() {
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
    }
}

function detectClickPiture() {

}

function isClickCaptchaImgReady() {
    var img = $('#clickCaptcha .clickCaptcha_img img');
    return img.length === 1;
}

function isPassed() {
    var passed = $('#nocaptcha #_scale_text b');
    return passed.length === 1;
}

function isLoginin() {
    var loginInfoNick = $('#J_LoginInfo .login-info-nick');
    return loginInfoNick.length === 1;
}

function isInBoughtListPage() {
    return $('#J_bought_main').length === 1;
}

function getBoughtList() {
    var list = [];
    list.push({'id' : 1});
    list.push({'id' : 2});
    return list;
}

function getClickCaptchaInfo() {
    var img = $('#clickCaptcha .clickCaptcha_img img');
    var desc = $('#clickCaptcha .captcha-error p').text();
    return { 'imgURL' : img.attr('src'),
        'describe' : desc,
        'x' : img.offset().left,
        'y' : img.offset().top,
        'width' : img.width(),
        'height' : img.height()
    }
}

function getPositions() {
    var bg = $('#nocaptcha #_bg');
    var scale_text = $('#nocaptcha #_scale_text');
    return {
        scale_text : {
            x : scale_text.offset().left,
            y : scale_text.offset().top,
            width : scale_text.width(),
            height : scale_text.height()
        },
        bg : {
            x : bg.offset().left,
            y : bg.offset().top,
            width : bg.width(),
            height : bg.height()
        }
    }
}

function getBoughtList() {

}

function report(id) {

}