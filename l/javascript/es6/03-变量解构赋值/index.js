"use strict"

//  目前node需要这个 flag
// --harmony_destructuring

let [a, b, c] = [1, 2, 3];
console.log(a,b,c);


let [ , , third] = ['one', 'two', 'three'];
console.log(third);

let [x, , y] = [1, 2, 3];
console.log(x, y);