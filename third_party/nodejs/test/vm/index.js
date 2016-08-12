'use strict';

const vm = require('vm');

function r(str) {
    str = str.replace(/\n/g, '\t');
    return str;
}

var s = '\naaaa\nbbbb'
console.log('[' + s + ']');
s = r(s)
console.log('[' + s + ']');


// 反斜杠是不能直接用的, 因为会转义
// 我们也不能直接把js这个string先JSON.stringify然后再替换\ => \\
// 因为换行也会被替换的。从文件中读出来的，本身就是下面这种格式.
var js = `
function r(str) {
    str = str.replace(/\\n/g, '\\t');
    return str;
}

var s = '\\naaaa\\nbbbb'
r(s)
`


console.log('--------------------')
// console.log(JSON.stringify(js))
// console.log(JSON.stringify(js).replace(/\\/g, '\\\\'))
var script = new vm.Script(js);
console.log('--------------------')
var ret = script.runInNewContext();
console.log(ret)
