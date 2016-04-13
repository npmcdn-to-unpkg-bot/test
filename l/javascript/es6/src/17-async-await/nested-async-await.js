
function log(msg) {
    console.log(`[${new Date()}] ${msg}`)
}

var sleep = function(time) {
    return new Promise(function(resolve, reject) {
        setTimeout(() => {
            resolve('timeout');
        }, time)
    });
}

async function sleep1000() {
    log('start to sleep1000');
    let r = await sleep(1000);
    log('sleep1000 ' + r);
};

async function sleep2000() {
    log('start to sleep2000');
    sleep1000();  // these two runs async, so you only sleep 1000, not 2000.
    sleep1000();
    log('sleep2000 timeout');
}



// -----------

async function sleep1000Promise() {
    log('start to sleep1000Promise');
    let r = await sleep(1000);
    log('sleep1000Promise ' + r);
    return new Promise(function(resolve, reject) {
        resolve();
    });
}

async function sleep2000Promise() {
    log('start to sleep2000Promise');
    await sleep1000();  // these two runs async, so you only sleep 1000, not 2000.
    await sleep1000();
    log('sleep2000Promise timeout');
}

sleep2000();

setTimeout(()=> {
    console.log('\n');
    sleep2000Promise();
}, 3000)

// [Wed Apr 13 2016 15:42:54 GMT+0800 (CST)] start to sleep2000
// [Wed Apr 13 2016 15:42:54 GMT+0800 (CST)] start to sleep1000
// [Wed Apr 13 2016 15:42:54 GMT+0800 (CST)] start to sleep1000
// [Wed Apr 13 2016 15:42:54 GMT+0800 (CST)] sleep2000 timeout
// [Wed Apr 13 2016 15:42:55 GMT+0800 (CST)] sleep1000 timeout
// [Wed Apr 13 2016 15:42:55 GMT+0800 (CST)] sleep1000 timeout


// [Wed Apr 13 2016 15:42:57 GMT+0800 (CST)] start to sleep2000Promise
// [Wed Apr 13 2016 15:42:57 GMT+0800 (CST)] start to sleep1000
// [Wed Apr 13 2016 15:42:58 GMT+0800 (CST)] sleep1000 timeout
// [Wed Apr 13 2016 15:42:58 GMT+0800 (CST)] start to sleep1000
// [Wed Apr 13 2016 15:42:59 GMT+0800 (CST)] sleep1000 timeout
// [Wed Apr 13 2016 15:42:59 GMT+0800 (CST)] sleep2000Promise timeout