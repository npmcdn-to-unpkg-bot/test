'use strict';

const path = require('path');
const fs = require('fs')

function mkdirsSync(dir) {
    let absPath = dir;
    if (!path.isAbsolute(absPath)) {
        absPath = path.join(__dirname, absPath);
    }

    let currentPath = '';
    for (let p of absPath.split('/')) {
        if (p === '') {
            continue;
        }

        currentPath += '/' + p;

        if (!fs.existsSync(currentPath)) {
            fs.mkdirSync(currentPath);
        }
    }
}


mkdirsSync('a/b/c/d/e/f/g/')
mkdirsSync('./b/c/d')
mkdirsSync('/tmp/a/b/c/d')