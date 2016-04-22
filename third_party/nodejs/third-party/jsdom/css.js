'use strict';

var jsdom = require("jsdom");

// Our mission is to get something very close to a headless browser, 
// with emphasis more on the DOM/HTML side of things than the CSS side.
// As such, our primary goals are supporting The DOM Standard and The
// HTML Standard. We only support some subset of these so far;
// in particular we have the subset covered by the outdated DOM 2
// spec family down pretty well. We're slowly including more and
// more from the modern DOM and HTML specs, including some Node APIs,
// querySelector(All), attribute semantics, the history and URL APIs,
// and the HTML parsing algorithm.

// We also support some subset of the CSSOM, largely via @chad3814's
// excellent cssstyle package. In general we want to make webpages run
// headlessly as best we can, and if there are other specs we should
// be incorporating, let us know.

jsdom.env({
  url: "https://github.com/",
  scripts: ["http://cdn.bootcss.com/jquery/3.0.0-beta1/jquery.js"],
    features: { // 使用这些features, 注入的代码是自动可以运行的，除非你网页里需要加载的资源，才需要这些功能打开
        FetchExternalResources: ["script",],
        ProcessExternalResources: ["script",],
        SkipExternalResources: false
    },
  done: function (err, window) {
    let $ = window.$;
    $('img').each(function() {
        console.log('img: ' + $(this).attr('src')
            + ', position:' + JSON.stringify($(this).position()) //
            + ', border:' + JSON.stringify($(this).css('border'))); // 
    });
  }
});