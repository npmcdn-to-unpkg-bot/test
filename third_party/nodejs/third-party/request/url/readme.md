#测试正常返回200的网站以及302跳转的网站的url变化

    server.js 提供一个跳转的网页

    $ node server.js
    Example app listening at http://127.0.0.1:3000

    then test
    res.request.uri 是显示跳转之后的url，前提是你允许跳转，
    默认request是允许跳转的，但是不是所有跳转,maxredirects = 10