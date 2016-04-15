'use strict'

var sleep = function(time) {
    return new Promise(function(resolve, reject) {
        setTimeout(() => {
            resolve('timeout');
        }, time)
    });
}

function log(msg) {
    console.log(`[${new Date()}] ${msg}`)
}


class A {
    constructor() {
        this.x = 1;
        this.y = 1;
    }

    async step() {
        await sleep(1);
        return 'ok';
    }

    async s() {
        await sleep(1);
        return new Promise(function(resolve, reject) {
            resolve('ok');
        });
    }

    async step1() {
        log(`Start step1...(${this.x}, ${this.y})`);
        await sleep(1000);
        log(`end step1...(${this.x}, ${this.y})`);
        return true;
    }

    async step2() {
        log(`Start step2...(${this.x}, ${this.y})`);
        await sleep(1000);
        log(`end step2...(${this.x}, ${this.y})`);
    }

    async s1() {
        log(`Start S1...(${this.x}, ${this.y})`);
        await sleep(1000);
        log(`end S1...(${this.x}, ${this.y})`);

        var that = this;
        return new Promise(function(resolve, reject) {
            // log(`Start S1...(${that.x}, ${that.y})`);
            // await sleep(1000); // WHY can't write here???
            // log(`end S1...(${that.x}, ${that.y})`);

            // this doesn't exsits 
            // resolve({r:true, x: this.x, y: this.y});
            resolve({r:true, x: that.x, y: that.y});
        })
    }

    async s2() {
        log(`Start S2...(${this.x}, ${this.y})`);
        await sleep(1000);
        log(`end S2...(${this.x}, ${this.y})`);

        return new Promise(function(resolve, reject) {
            resolve(true);
        })
    }

}

let a = new A();

(async ()=>{
    console.log('step() return:');
    console.log(a.step());  // step return is a Promise()
    await sleep(10);

    console.log('s() return:');
    let r = await a.s(); // s return is 'ok'
    console.log(r);

    await sleep(10);

    if (a.step1()) {
        a.step2();
    }
    await sleep(2000);
    console.log('\n');

    let r1 = await a.s1();
    console.log(`=====>> s1 await return:`);
    console.log(r1);
    if (r1.r === true) {
        a.s2();
    }
})();

