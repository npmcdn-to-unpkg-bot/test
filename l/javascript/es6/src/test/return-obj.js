"use strict"

function p() {
    let [left, right, top, bottom] = [1, 2, 3, 4];
    return {left, right, top, bottom};
}

const a = p();
console.log(a);

const {left, right, top, bottom} = p();
console.log(`left:${left}, right:${right}, top:${top}, bottom:${bottom}`);