'use strict';
// promise是new之后立刻执行的，可以认为你new完后立刻去异步执行了。
// 但是，结果 是 在所有同步代码执行完之后才开始的，可以认为是eventloop的下一个for循环
// 看下面log日志

// p1 starts to run...   // run imediately
// p1 finished running... 
// before then
// after then
// out of the scope
// another scope
// this is the last sync code....  ###### all sync code finised
// resolve p1 result

{
    let p1 = new Promise((resolve, reject) => {
        console.log('p1 starts to run...');
        console.log('p1 finished running...')
        resolve('resolve p1 result')
    });
    console.log('before then')
    p1.then(result => console.log(result));
    console.log('after then')
}
console.log('out of the scope')
{
    console.log('another scope')
}

// resolve另外一个Promise
{
    let p1 = new Promise((resolve, reject) => {
        setTimeout(() => reject(new Error('fail')), 3000)
    });
    let p2 = new Promise((resolve, reject) => {
        setTimeout(() => resolve(p1), 100);
    });


    p2.then(result => console.log(result))
    p2.catch(error => {
        console.log(error)
        console.log(error.stack) // print stack....
    }) 
}

{
    // then方法返回的是一个新的Promise实例（注意，不是原来那个Promise实例）。因此可以采用链式写法，即then方法后面再调用另一个then方法
    let p1 = new Promise(resolve => resolve('ok'));

    function returnThen() {
        return p1.then(x => console.log(x));
    }

    console.log('----return then ----')
    console.log(returnThen())
}




console.log('this is the last sync code....')