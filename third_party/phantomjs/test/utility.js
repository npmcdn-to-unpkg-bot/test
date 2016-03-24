
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

function isClickCaptchaImgReady() {
    var img = $('#clickCaptcha .clickCaptcha_img img');
    return img.length === 1;
}

function getClickCaptchaImgURL() {
    var img = $('#clickCaptcha .clickCaptcha_img img');
    if (img.length === 1) {
        return img.attr('src');
    }
    return;
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

function report(id) {

}