const readline = require('readline');

const rl = readline.createInterface(process.stdin, process.stdout);

rl.on('line', (line) => {
    console.log('you type:' + line);
})