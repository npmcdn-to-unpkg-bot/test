'use strict';

var urlencode = require('urlencode');

console.log(urlencode('苏千')); // default is utf8
console.log(urlencode('苏千', 'gbk')); // '%CB%D5%C7%A7'

// 有些中文网站form提交的时候编码是 gbk，然后再做的urlENCODE(这步一般是浏览器自己做的)
// 碰到这种情况可以自己来编码，然后自己组装body
