var jsdom = require('jsdom');
var fs = require("fs");
var uuid = fs.readFileSync("./uuid.js", "utf-8");
var t = fs.readFileSync("./test.js", "utf-8");

// console.log(uuid)

// jsdom.env({
//     html: '<p><a class="the-link" href="https://github.com">Hello!</a></p>',
//     src: [uuid, t],
//     done: function(err, window) {
//         if (err) {
//             console.log(err);
//             return;
//         }
//         // console.log(window);
//         console.log('------------------');
//         console.log(window.Math)
//         console.log('------------------');
//         console.log(window.test())
//         console.log('------------------');
//         console.log(window.tt)
//         console.log('------------------');
//         console.log(window.Math.uuid());
//     }});

// jsdom.env(
//     '<p><a class="the-link" href="https://github.com">Hello!</a></p>',
//     ['https://ha.ac.10086.cn/js/201405/uuid.js'],
//     function (err, window) {
//         if (err) {
//             console.log(err);
//             return;
//         }
//         console.log(window.document)
//         console.log(window.Math)
//     });


// http://stackoverflow.com/questions/19490572/jsdom-hardcore-way-add-external-script-and-use-it
var document = jsdom.jsdom("<html><head></head><body>hello world</body></html>");
var window = document.parentWindow;

var script =  document.createElement("script");
script.type = "text/javascript";
script.innerHTML = uuid;

var head= document.getElementsByTagName('head')[0];
head.appendChild(script);

window = document.parentWindow;

console.log(document.innerHTML);
console.log("uuid: " + window.Math.uuid());