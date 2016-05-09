'use strict';

class Fn {

    f1() {
        console.log('this is f1')
    }

    f2() {
        console.log('this is f2')
    }

    ext(extension) {
        if (!(extension instanceof FnExt)) return;

        this[extension.proName] = extension.proInstance;
    }
}

class FnExt {
    constructor(proName, proInstance) {
        this.proName = proName;
        this.proInstance = proInstance;
    }
}


let f = new Fn();
f.f1();
f.f2();

let log = {
    info: function(msg) {
        console.log(`info:` + msg);
    }
}
let ext1 = new FnExt('log', log );
f.ext(ext1);

f.log.info('aaaa')