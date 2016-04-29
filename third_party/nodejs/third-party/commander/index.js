// npm install commander

var program = require('commander');

program
  .version('0.0.1')
  .usage('[options] arg1 arg2')
  .option('-p, --peppers', 'Add peppers')
  .option('-P, --pineapple', 'Add pineapple')
  .option('-b, --bbq-sauce', 'Add bbq sauce')
  .option('-c, --cheese [type]', 'Add the specified type of cheese [marble]', 'marble')
  .parse(process.argv);

console.log('arg1:' + program.args[0]);
console.log('arg2:' + program.args[1]);
console.log('peppers', program.peppers);
console.log('pineapple', program.pineapple);
console.log('bbqSauce', program.bbqSauce);
console.log('cheese', program.cheese);

