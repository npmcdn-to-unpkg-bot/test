
var s = `
                <tr>
                    <td>1</td>
                    <td>被叫</td>
                    <td>本地</td>
                    <td>北京</td>
                    <td>18011111111</td>
                    <td>2016-04-15 17:38:53</td>
                    <td>0.00</td>
                    <td>0.00</td>
                    <td>7</td>
                    <td>0.00</td>
                </tr>

                <tr>
                    <td>2</td>
                    <td>被叫</td>
                    <td>本地</td>
                    <td>北京</td>
                    <td>18022222222</td>
                    <td>2016-04-15 17:38:53</td>
                    <td>0.00</td>
                    <td>0.00</td>
                    <td>7</td>
                    <td>0.00</td>
                </tr>

                <tr>
                    <td>2</td>
                    <td>被叫</td>
                    <td>本地</td>
                    <td>北京</td>
                    <td>18033333333</td>
                    <td>2016-04-15 17:38:53</td>
                    <td>0.00</td>
                    <td>0.00</td>
                    <td>7</td>
                    <td>0.00</td>
                </tr>
`


var tr = new RegExp('<tr>((\\s*<td>.*</td>\\s*){10})</tr>', 'ig');
var td = new RegExp('<td>(.*)</td>', 'ig');
var r = null;

while (r = tr.exec(s)) {
    console.log('-------------------------')
    // console.log(r[1]);
    var d = null;
    while (d = td.exec(r[1])) {
        console.log(d[1])
    }
}

// while (r = td.exec(s)) {
//     console.log(r[1]);
// }


console.log('-------------------------')
var s1 = `'1234', "345"`;
var re1 = /\'[\d]{4}\'.*/;
console.log(re1.exec(s1))

console.log('-------------------------')
// 不知道这种应该咋写
var re2 = new RegExp("\\\'[\\d]{4}\\\'.*/")
console.log(re2.exec(s1))

console.log('-------------------------')
var re3 = new RegExp(/\'[\d]{4}\'.*/)
console.log(re3.exec(s1))

//惰性匹配,匹配最小的
// 惰性模式的语法很简单，即是在贪婪模式后面加上一个“?”即可
// * –> *?
// + –> +?
// {n,} –> {n,}?
console.log('-------------------------')
var s2 = `<html>
    <p>aaa</p><p>bbb</p><p>ccc</p>
<html>`
var re4 = /<p>(.*)<\/p>/;
console.log(re4.exec(s2)[1]);
console.log('-------------------------')
var re5 = /<p>(.*?)<\/p>/;
console.log(re5.exec(s2)[1]);

