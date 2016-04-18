
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

