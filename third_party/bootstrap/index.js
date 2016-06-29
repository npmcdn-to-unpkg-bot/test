'use strict';

var render = require('./render');
var koa = require('koa');
var route = require('koa-route');
var app = koa();


app.use(route.get('/navigator', navigator));

function *navigator() {
	this.body = yield render('navigator');
}

app.listen(3000, ()=>{console.log(`listening on http://127.0.0.1:3000`)});