

var s = `haha为了获取`
var encoded = encodeURIComponent(s);
console.log(encoded);


var decoded = decodeURIComponent(encoded)
console.log(decoded)