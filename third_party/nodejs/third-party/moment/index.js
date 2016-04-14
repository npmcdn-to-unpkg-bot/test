var moment = require('moment')

console.log(new Date())
console.log(moment().format())
console.log(moment().format('YYYY-MM-DD'))
console.log(moment().format('YYYYMMDD'))

console.log(moment({day: 1}).format('YYYY-MM-DD'))