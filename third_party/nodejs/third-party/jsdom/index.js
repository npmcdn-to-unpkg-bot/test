var jsdom = require('jsdom');
var fs = require("fs");
var uuid = fs.readFileSync("./uuid.js", "utf-8");
var t = fs.readFileSync("./test.js", "utf-8");

// console.log(uuid)

jsdom.env({
    html: '<p><a class="the-link" href="https://github.com">Hello!</a></p>',
    src: [uuid, t],
    features: { // 使用这些features
        // FetchExternalResources: ["script"],
        ProcessExternalResources: ["script"],
        // SkipExternalResources: false
    },
    done: function(err, window) {
        if (err) {
            console.log(err);
            return;
        }
        // console.log(window);
        console.log('------------------');
        console.log(window.Math)
        console.log('------------------');
        console.log(window.t());
        console.log('------------------');
        console.log(window.tt)
        console.log('------------------');
        console.log(window.Math.uuid());

        window.close(); // 释放资源
    }});
