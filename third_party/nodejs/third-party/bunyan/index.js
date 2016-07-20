'use strict';


var bunyan = require('bunyan');
var log = bunyan.createLogger({name: 'myapp', src: false /*true会记录文件，行号等信息*/});
log.info('hi');
log.warn({lang: 'fr', ok: {a:1, b:2}, id: '12123123213'}, 'au revoir');
try {
    JSON.parse('aaa}');
} catch (e) {
    log.info(e)
    // ...
    // "err": {
    //   "message": "boom",
    //   "name": "TypeError",
    //   "stack": "TypeError: boom\n    at Object.<anonymous> ..."
    // },
    // "msg": "boom",
    // ...
}

log.info(null, 'prefix is null')
log.info({}, 'prefix is {}');

let log1 = log.child({username: 'Bob'})
let log2 = log1.child({password: 'xxxxxx'})
log1.info(`log1 print`)
log2.info(`log2 print`)
log.info(`log print`)