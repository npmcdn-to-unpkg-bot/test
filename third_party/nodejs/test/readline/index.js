const readline = require('readline');

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdin,
});

rl.question(`what is this?`, (answer) => {
    console.log('this is your answer:' + answer);
    rl.close();
}); 

