'use strict';

var s = `
  
  
  <script>
    doQuery('15350690825','183','1402714','aaaa','8','968199696');
  </script>
  
  
  
`

console.log('--------------------------------')
let r = new RegExp('<script>.*</script>');
console.log(r.exec(s));
console.log('--------------------------------')

let r1 = new RegExp('<script>[\\s\\S]*</script>');
console.log(r1.exec(s));