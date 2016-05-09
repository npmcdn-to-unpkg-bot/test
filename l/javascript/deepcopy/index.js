'use strict';


function deepCopy(obj) {
    return JSON.parse(JSON.stringify(obj))
}

function change(v) {
    v.value = v.value + v.value;
}

let a = {
    type: 'aaa',
    value: 'aaaaa',
}

let b = a;
let c = deepCopy(a);

console.log(`a:${JSON.stringify(a)}`)
console.log(`b:${JSON.stringify(b)}`)
console.log(`c:${JSON.stringify(c)}`)
change(a);
console.log(`a:${JSON.stringify(a)}`)
console.log(`b:${JSON.stringify(b)}`)
console.log(`c:${JSON.stringify(c)}`)