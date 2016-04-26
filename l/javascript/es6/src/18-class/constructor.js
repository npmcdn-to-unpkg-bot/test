'use strict';

function add(x, y, ...args) { // babel
    console.log(args)
}

class A {
    constructor(x, y) {
        this.x = x;
        this.y = y;
    }
}

class B extends A {
    constructor(...args) { // 
        super(...args);
        this.z = 0;
    }
}

add(1,2)

let b = new B(1, 2);
console.log(b)