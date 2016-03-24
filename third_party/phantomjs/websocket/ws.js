var page = require('webpage').create(),
    system = require('system'),
    address, output, size;

var ws = new WebSocket("ws://127.0.0.1:9527/socket");
