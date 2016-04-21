const fs = require('fs');
fs.readFile('a file that does not exist', (err, data) => {
  if (err) {
    console.error('There was an error reading the file!', err);
    console.log('--------')
    console.log(err);
    err.stack()
    return;
  }
  // Otherwise handle the data
});