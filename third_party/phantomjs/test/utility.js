
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

function isNocaptchaReady() {
    var nocaptcha = $('#nocaptcha');
    var scale_text = $('#nocaptcha #_scale_text');
    return nocaptcha.css('display') !== 'none'
        && nocaptcha.width() > 0
        && scale_text.width() > 0
        && scale_text.height() > 0;
}

function getPositions() {
    var nocaptcha = $('#nocaptcha');
    var nlz = $('#nocaptcha #_nlz');
    var bg = $('#nocaptcha #_bg');
    var scale_text = $('#nocaptcha #_scale_text');
    return {
        nocaptcha : {
            x : nocaptcha.offset().left,
            y : nocaptcha.offset().top,
            width : nocaptcha.width(),
            height : nocaptcha.height()
        },
        nlz : nlz.offset(),
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

function report(id) {
    var element = $(id);
    if (!element) {
        console.log('element is ' + element);
        return;
    }
    var position = element.position();
    var left = position ? position.left : null;
    var top = position ? position.top : null;
    var offset = element.offset();
    var x = offset ? offset.top : null;
    var y = offset ?  offset.left : null;
    console.log(id + ' width:' + element.width() + ', height:' + element.height()
        + ',left:' + left + ', top:' + top
        + '(' + x + "," + y + ")");
}