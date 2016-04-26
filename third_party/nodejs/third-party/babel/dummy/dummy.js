'use strict';

class Dummy {

    p() {
        // 这个可以正常提示
        console.log(`printing undefinedVar:` + undefinedVar)
    }

    // 这个不行，因为转换了 async
    pp() {
        (async () => {
            await 1;
            console.log(`printing undefinedVar:` + undefinedVar)
        })();
    }
}

module.exports = Dummy;
