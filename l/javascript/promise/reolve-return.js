'use strict';

let p1 = new Promise((resolve, reject) => {
    console.log('p1 starts to run...');
    resolve('resolve p1 result')
    console.log('p1 after resolve ...')
    reject('haha????')
});

p1.then(result => console.log(result))
.catch((e) => {
    console.log(e);
});
