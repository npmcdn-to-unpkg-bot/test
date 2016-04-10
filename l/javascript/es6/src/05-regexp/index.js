"use strict"

{
    // ES5 .1.
    let regex = new RegExp('xyz', 'i');
    // equivalent
    let regex1 = /xyz/i;
}

{
    // ES5 .2.
    let regex = new RegExp(/xyz/i); // 不允许有第二个参数ES5
    let regex1 = /xyz/i;
}

{
    // ES6, node 现在不支持，没找到对应的 runtime flag
    // let regex = new RegExp(/abc/ig, 'i');
    // console.log(regex.flags);
}

{
    // 字符串的正则
    // match()
    // replace()
    // search()
    // split()
}