var jsdom = require('jsdom');
var fs = require("fs");
var uuid = fs.readFileSync("./uuid.js", "utf-8");
var t = fs.readFileSync("./test.js", "utf-8");

// console.log(uuid)

jsdom.env({
    // html: '<p><a class="the-link" href="https://github.com">Hello!</a></p>',
    html: '<p>test</p><script> function aa() { return "function in html body"; aa(); } </script>',
    src: [uuid, t],
    features: { // 使用这些features, 注入的代码是自动可以运行的，除非你网页里需要加载的资源，才需要这些功能打开
        // FetchExternalResources: ["script"],
        // ProcessExternalResources: ["script"],
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

        console.log('---------------------')
        console.log('aa(): ' + window.aa());
        console.log('------------------');
        console.log('window.t(): ' + window.t());
        console.log('------------------');
        console.log('window.str: ' + window.str)
        console.log('------------------');
        console.log(window.Math.uuid());
        console.log('------------------');
        console.log('window.random: ' + window.random())
        console.log('window.Math.random: ' + window.Math.random())

        window.close(); // 释放资源
    }});
