'use strict'

var sleep = function(time) {
    return new Promise((resolve, reject) => {
        setTimeout(() => {
            resolve('timeout');
        }, time)
    });
}

async function sleep100() {
    console.log('start to sleep 100');
    await sleep(100);
    console.log('end to sleep 100');
    return new Promise((resolve, reject) => {
        resolve();
    });
}

function sleep1000() {
    return new Promise((resolve, reject) => {
        (async() => { // if no async, there will be error.
            console.log('start to sleep1000')
            await sleep(1000);
            console.log('end to sleep1000')

        })();
    });
}

// this is wrong.
// async function sleep1000() {
//     return new Promise((resolve, reject) => {
//             console.log('start to sleep1000')
//             await sleep(1000);
//             console.log('end to sleep1000')
//     });
// }

(async () => {
    await sleep100();
    await sleep100();

    await sleep1000();
})();

