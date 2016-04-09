"use strict"

//  目前node需要这个 flag
// --harmony_destructuring 或者使用 babel-node
// ./node_modules/.bin/babel-node file.js

let [a, b, c] = [1, 2, 3];
console.log(a,b,c);


let [ , , third] = ['one', 'two', 'three'];
console.log(third);

let [x, , y] = [1, 2, 3];
console.log(x, y);