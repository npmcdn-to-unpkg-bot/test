'use strict';

function _asyncToGenerator(fn) { return function () { var gen = fn.apply(this, arguments); return new Promise(function (resolve, reject) { function step(key, arg) { try { var info = gen[key](arg); var value = info.value; } catch (error) { reject(error); return; } if (info.done) { resolve(value); } else { return Promise.resolve(value).then(function (value) { return step("next", value); }, function (err) { return step("throw", err); }); } } return step("next"); }); }; }

class Dummy {

    p() {
        // 这个可以正常提示
        console.log(`printing undefinedVar:` + undefinedVar);
    }

    // 这个不行，因为转换了 async
    pp() {
        _asyncToGenerator(function* () {
            yield 1;
            console.log(`printing undefinedVar:` + undefinedVar);
        })();
    }
}

module.exports = Dummy;