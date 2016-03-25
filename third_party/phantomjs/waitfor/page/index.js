var app = require('express')();
var http = require('http').Server(app);

app.get('/', function(req, res) {
    res.sendFile(__dirname + '/index.html');
});



http.listen(3333, function() {
    console.log('listening on http://127.0.0.1:3333');
});