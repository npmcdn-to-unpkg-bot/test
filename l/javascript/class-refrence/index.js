'use strict';

class A {
    constructor(d) {
        this.d = d;
    }
}

class B {
    constructor(d) {
        this.d = d;
    }
}


let data = { name: 'data', data: 11}
let a = new A(data)
let b = new B(data)
a.d.data = 100;
b.d.data = 200;
console.log(`data:${JSON.stringify(data)}, a:${JSON.stringify(a.d)}, b:${JSON.stringify(a.d)}`)
// 结果都是200，所以是引用