var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);

app.get('/', function(req, res) {
    res.sendFile(__dirname + '/index.html');
});

app.get('/control', function(req, res) {
    res.sendFile(__dirname + '/control.html')
});

io.on('connection', function(socket) {
    console.log('a user connected');
    socket.on('control', function(data) {
        io.emit('worker', data);
    });
    socket.on('worker', function(data) {
        io.emit('control', data);
    })
    socket.on('disconnect', function() {
        console.log('user disconnect');
    });
});

http.listen(3333, function() {
    console.log('listening on http://127.0.0.1:3333');
});