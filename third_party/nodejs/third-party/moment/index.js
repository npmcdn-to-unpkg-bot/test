var moment = require('moment')

// api
// http://momentjs.com/docs/#/use-it


console.log(new Date())
console.log(moment().format())
console.log(moment().format('YYYY-MM-DD'))
console.log(moment().format('YYYYMMDD'))

console.log(moment({day: 1}).format('YYYY-MM-DD'))

console.log(moment().format('YYYY年MM月'))
console.log(moment().format('DD'))
console.log(moment({day:11}).format('D'))
console.log(moment({day:1}).format('D'))

// last day
console.log(moment().endOf('month').format('YYYYMMDD'))
console.log(moment().add(-1, 'months').endOf('month').format('YYYYMMDD'))
console.log(moment().endOf('year').format('YYYYMMDD'))
