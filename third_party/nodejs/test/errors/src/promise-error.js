'use strict';

function a() {
    return new Promise((resolve, reject) => {
        reject(new Error('this is an error'));
    });
}
function b() {
    return new Promise((resolve, reject) => {
        return reject('this is an error');
    });
}

function c() {
    return new Promise((resolve, reject) => {
        return reject({
            code: 1,
            msg: 'this is an error'}
            );
    });
}

(async () => {
    try {
        let i = await a();
    } catch(e) {
        console.log(e)
    }

    try {
        let i = await b();
    } catch(e) {
        console.log(e)
    }

    try {
        let i = await c();
    } catch(e) {
        console.log(e)
    }
})();