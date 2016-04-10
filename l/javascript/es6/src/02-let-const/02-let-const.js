"use strict"

{
	let a = 10;
	var b = 1;
}

// console.log(a); // ReferenceError: a is not defined
console.log(b);

for (var i=0; i<10; i++) {}

console.log('i is ' + i);

for (let j=0; j<10; j++) {}
// console.log('j is' + j); // ReferenceError: j is not defined


var a = [], b=[];
for (var i=0; i<20; i++) {
	a[i] = function() {
		console.log(i);
	}
}
a[5](); // 20

for (let j=0; j<20; j++) {
	b[j] = function() {
		console.log(j);
	}
}
b[5]() // 5

// 不存在变量提升
// 脚本开始运行时，变量foo已经存在了，但是没有值，所以会输出undefined。变量bar用let命令声明，不会发生变量提升。这表示在声明它之前，变量bar是不存在的，这时如果用到它，就会抛出一个错误。
console.log(foo);
// console.log(bar); // ReferenceError: j is not defined
var foo = 2;
let bar = 2;


const PI = 3.14;
// PI = 3; // TypeError: Assignment to constant variable.

// const命令声明的常量也是不提升，同样存在暂时性死区，只能在声明的位置后面使用。

// 对于复合类型的变量，变量名不指向数据，而是指向数据所在的地址。const命令只是保证变量名指向的地址不变，并不保证该地址的数据不变，所以将一个对象声明为常量必须非常小心
const obj = {}
obj.pp = 123;
console.log('const object pp ' + obj.pp);
// obj = {} // TypeError: Assignment to constant variable.

const aa = [];
aa.push("Hello"); // 可执行
aa.length = 0;    // 可执行
// aa = ["Dave"];    // 报错

// 如果真的想将对象冻结，应该使用Object.freeze方法。
const freeze = Object.freeze({}); 
// 常规模式时，下面一行不起作用；
// 严格模式时，该行会报错
// freeze.pp =123 // TypeError: Can't add property pp, object is not extensible

// 除了将对象本身冻结，对象的属性也应该冻结。下面是一个将对象彻底冻结的函数。

var constantize = (obj) => {
  Object.freeze(obj);
  Object.keys(obj).forEach( (key, value) => {
    if ( typeof obj[key] === 'object' ) {
      constantize( obj[key] );
    }
  });
};


// 跨模块常量
// 上面说过，const声明的常量只在当前代码块有效。如果想设置跨模块的常量，可以采用下面的写法。

// constants1/2.js 模块
// export const A = 1;
// export const B = 3;
// export const C = 4;

// import node not supported now.
// test1.js 模块
import * as constants from './constants1';
console.log(constants.A); // 1
console.log(constants.B); // 3

// test2.js 模块
import {A, B} from './constants2';
console.log(A); // 1
console.log(B); // 3




// 全局对象的属性
// 全局对象是最顶层的对象，在浏览器环境指的是window对象，在Node.js指的是global对象。ES5之中，全局对象的属性与全局变量是等价的。

// window.a = 1;
// a // 1

// a = 2;
// window.a // 2
// 上面代码中，全局对象的属性赋值与全局变量的赋值，是同一件事。（对于Node来说，这一条只对REPL环境适用，模块环境之中，全局变量必须显式声明成global对象的属性。）

// 这种规定被视为JavaScript语言的一大问题，因为很容易不知不觉就创建了全局变量。ES6为了改变这一点，一方面规定，var命令和function命令声明的全局变量，依旧是全局对象的属性；另一方面规定，let命令、const命令、class命令声明的全局变量，不属于全局对象的属性。

// var a = 1;
// 如果在Node的REPL环境，可以写成global.a
// 或者采用通用方法，写成this.a
// window.a // 1

// let b = 1;
// window.b // undefined
// 上面代码中，全局变量a由var命令声明，所以它是全局对象的属性；全局变量b由let命令声明，所以它不是全局对象的属性，返回undefined



