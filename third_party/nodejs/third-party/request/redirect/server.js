var express = require('express');
var app = express();

app.get('/', function (req, res) {
  res.redirect('/redirect1');
});

app.get('/redirect1', function (req, res) {
  res.redirect('/redirect2');
});

app.get('/redirect2', function (req, res) {
  res.redirect(304, '/redirect3');
});

app.get('/redirect3', function (req, res) {
  res.send('this is the redirect 3 page');
});


app.post('/', function (req, res) {
  res.redirect('/redirect1');
});

app.get('/redirect1', function (req, res) {
  res.redirect('/redirect2');
});

app.get('/redirect2', function (req, res) {
  res.redirect(304, '/redirect3');
});

app.get('/redirect3', function (req, res) {
  res.send('this is the redirect 3 page');
});

var server = app.listen(3000, function () {
    var host = server.address().address;
    var port = server.address().port;
    console.log('Example app listening at http://127.0.0.1:3000');
});

