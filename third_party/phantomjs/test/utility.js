function setSentry() {
    // listen to css display for '#nocaptcha'
    $('#nocaptcha').watch({
        properties: 'display',
        callback: function(data, i) {
            var propChanged = data.props[i];
            var newValue = data.vals[i];
            window.callPhantom({
                type : 'nocaptcha',
                property : propChanged,
                value : newValue });
        }
    });
}

function report() {
        window.callPhantom({
            type : 'report',
            property : 'nocaptcha display',
            'value' : $('#nocaptcha').css('display')
        });
    console.log('no setInterval.......')
    setTimeout(function() {
        console.log('timeout in page............')
    }, 1000);
    setInterval(function() {
        console.log('dafei dafei ......')
        // window.callPhantom({
        //     type : 'report',
        //     property : 'nocaptcha display',
        //     'value' : $('#nocaptcha').css('display')
        // });
    }, 1000);
}

function fillForm(username, password) {
    console.log('fillForm username:' + username);
    $('#TPL_username_1').focus();
    $('#TPL_username_1').val(username);
    $('#TPL_password_1').focus();
    $('#TPL_password_1').val(password);

    window.callPhantom({
        type : 'fillForm'
    });
}

function login() {
    $('#J_SubmitStatic').click();
    window.callPhantom({
        type : 'login'
    });
}