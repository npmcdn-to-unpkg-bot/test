var Crawler = require("simplecrawler");
var url = require("url");
var fs = require("fs");


var myCrawler = new Crawler("www.baidu.com");
myCrawler.initialPath = '/';
myCrawler.initialPort = 80;
myCrawler.initialProtocol = "http";
// myCrawler.interval = 10000; // 1000 = 1 seconds
myCrawler.maxConcurrency = 10;
myCrawler.maxDepth = 1;
myCrawler
.on("fetchcomplete", function(queueItem, responseBuffer, response) {
	console.log("--------------------------------")
	console.log("I just received %s (%d bytes)", queueItem.url, responseBuffer.length);
    console.log("It was a resource of type %s", response.headers['content-type']);
})
.on("crawlstart", function() {
	console.log("Crawler starts to work...");
})
.on("fetchheaders", function(queueItem, response) {
	console.log("fetchheaders");
})
.on("queueadd", function(queueItem) {
	console.log("queueadd");
})
.on("queueduplicate", function(url) {
	console.log("queueduplicate");
})
.on("queueerror", function(error, url) {
	console.log("queueerror");
})
.on("cookieerror", function(queueItem, error, setCookieHeader) {
	console.log("cookieerror:" + error);
})
.on("fetchdataerror", function(queueItem, response) {
	console.log("fetchdataerror");
})
.on("fetchredirect", function(queueItem, url, response) {
	console.log("fetchredirect");
})
.on("fetch404", function(queueItem, response) {
	console.log("404 received:" + queueItem.url);
})
.on("fetch410", function(queueItem, response) {
	console.log("410 received:" + queueItem.url);
})
.on("fetcherror", function(queueItem, response) {
	console.log("fetcherror");
})
.on("fetchtimeout", function(queueItem, crawlerTimeoutValue) {
	console.log("fetchtimeout:" + crawlerTimeoutValue);
})
.on("fetchclienterror", function(queueItem, error) {
	console.log("fetchclienterror:" + error);
})
.on("discoverycomplete", function(queueItem, resources) {
	console.log("discoverycomplete");
})
.on("complete", function() {
	console.log("all complete...");
})

myCrawler.start()

// Crawler.crawl(, function(queueItem) {
// 	console.log("Completed fetching resource:", queueItem.url);
// 	var parsed_url = url.parse(queueItem.url)
// 	// console.log(parsed_url)
// 	if (parsed_url.host != "www.baidu.com") {
// 		console.log("unmatched host " + parsed_url)
// 		return
// 	}

// 	var path = parsed_url.path.substring(1)
// 	console.log(queueItem)

// });
