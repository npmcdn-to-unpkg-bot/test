"use strict"

var sleep = function(time) {
    return new Promise(function(resolve, reject) {
        setTimeout(()=> resolve(`time's up`), time);
    });
}

var start = async function() {
    console.log('start...');
    var result = await sleep(2000);
    console.log('end:' + result);
}

start();

console.log('doing something else..');

let [a, b] = [1,2]