function login(username, password) {
    console.log('fillForm username:' + username);
    $('#userName').focus();
    $('#userName').val(username);
    $('#userPwd').focus();
    $('#userPwd').val(password);

    $('#login1').click();

    // window.callPhantom({
    //     type : 'fillForm'
    // });
}

function getBills() {
    console.log('is isLogin ? '+ _BaseTools.isLogin());
    
}