'use strict';




function MyCustomErrorOld(message) {
 this.message = message;
 this.name = 'MyCustomErrorTypeNameOld';
 Error.captureStackTrace(this, MyCustomErrorOld); // in nodejs and v8
}
MyCustomErrorOld.prototype = Object.create(Error.prototype);
MyCustomErrorOld.prototype.constructor = MyCustomErrorOld;

class MyCustomErrorNew extends Error {
    constructor(message) {
        super();
        this.message = message;
        this.name = 'MyCustomErrorTypeNameNew';
    }
}


try {
    throw new MyCustomErrorOld('I am an old error');
} catch(e) {
    console.log(e);
};

try {
    throw new MyCustomErrorNew('I am a new error');
} catch(e) {
    console.log(e);
    console.log('----------------print stack of error--------------------')
    console.log(e.stack); // Print stack
};

throw new MyCustomErrorNew(`don't catch me`)