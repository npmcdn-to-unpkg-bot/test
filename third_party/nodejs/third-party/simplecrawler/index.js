var Crawler = require("simplecrawler");
var url = require("url");
var fs = require("fs");

// parsedURL == >
// {
//     protocol: "http",
//     host: "example.com",
//     port: 80,
//     path: "/search?q=hello",
//     uriPath: "/search",
//     depth: 2
// }

// Queue items   https://github.com/cgiffard/node-simplecrawler#queue-items

var queueItemToString = function(queueItem) {
    return "[" + queueItem.url + "][" + queueItem.depth + "]";
};

var myConditions = []
var myCrawler = new Crawler("www.baidu.com");
myCrawler.initialPath = '/';
myCrawler.initialPort = 80;
myCrawler.initialProtocol = "http";
// myCrawler.interval = 10000; // 1000 = 1 seconds
myCrawler.maxConcurrency = 10;
myCrawler.maxDepth = 2;
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
    console.log("fetchheaders **** " + queueItemToString(queueItem));
})
.on("queueadd", function(queueItem) {
    console.log("queueadd <= " + queueItemToString(queueItem));
})
.on("queueduplicate", function(parsedURL) {
    console.log("queueduplicate X [" + parsedURL.host + parsedURL.path + "]");
})
.on("queueerror", function(error, parsedURL) {
    console.log("queueerror:" + parsedURL.host + parsedURL.path + ", error:" + error);
})
.on("cookieerror", function(queueItem, error, setCookieHeader) {
    console.log("cookieerror:" + error);
})
.on("fetchdataerror", function(queueItem, response) {
    console.log("fetchdataerror: "+ queueItemToString(queueItem));
})
.on("fetchredirect", function(queueItem, parsedURL, response) {
    console.log("fetchredirect: " + queueItemToString(queueItem) + " ==> [" + parsedURL.host + parsedURL.path + "]");
    // console.log(response);
})
.on("fetch404", function(queueItem, response) {
    console.log("404 received:" + queueItemToString(queueItem));
})
.on("fetch410", function(queueItem, response) {
    console.log("410 received:" + queueItemToString(queueItem));
})
.on("fetcherror", function(queueItem, response) {
    console.log("fetcherror:" + queueItemToString(queueItem));
})
.on("fetchtimeout", function(queueItem, crawlerTimeoutValue) {
    console.log("fetchtimeout:" + queueItemToString(queueItem) + ", default timeout value:" + crawlerTimeoutValue);
})
.on("fetchclienterror", function(queueItem, error) {
    console.log("fetchclienterror:" + queueItemToString(queueItem) + ", error:" + error);
})
.on("discoverycomplete", function(queueItem, resources) {
    console.log("discoverycomplete:" + queueItemToString(queueItem));
})
.on("complete", function() {
    console.log("all is completed...");
    report(this);
})

// add condition to prevent downloading some url
var conditionId = myCrawler.addFetchCondition(function(parsedURL, queueItem) {
    if (parsedURL.path.match(/\.png$/i)) {
        console.log(" __prevent downloading [" + parsedURL.host + parsedURL.path + "]");
        return false
    }

    return true
});
myConditions.push(conditionId);

var report = function(crawler) {
    crawler.queue.max("requestTime", function (error, max) {
        console.log("The maximum request time was %dms.", max);
    });
    crawler.queue.min("requestTime", function (error, min) {
        console.log("The minimum request time was %dms.", min);
    });
    crawler.queue.avg("requestTime", function (error, avg) {
        console.log("The average request time was %dms.", avg);
    });

    crawler.queue.max("requestLatency", function (error, max) {
        console.log("The maximum requestLatency was %dms.", max);
    });
    crawler.queue.min("requestLatency", function (error, min) {
        console.log("The minimum requestLatency was %dms.", min);
    });
    crawler.queue.avg("requestLatency", function (error, avg) {
        console.log("The average requestLatency was %dms.", avg);
    });

    crawler.queue.max("downloadTime", function (error, max) {
        console.log("The maximum downloadTime was %dms.", max);
    });
    crawler.queue.min("downloadTime", function (error, min) {
        console.log("The minimum downloadTime was %dms.", min);
    });
    crawler.queue.avg("downloadTime", function (error, avg) {
        console.log("The average downloadTime was %dms.", avg);
    });

    crawler.queue.max("contentLength", function (error, max) {
        console.log("The maximum contentLength was %d", max);
    });
    crawler.queue.min("contentLength", function (error, min) {
        console.log("The minimum contentLength was %d", min);
    });
    crawler.queue.avg("contentLength", function (error, avg) {
        console.log("The average contentLength was %d", avg);
    });

    crawler.queue.max("actualDataSize", function (error, max) {
        console.log("The maximum actualDataSize was %d", max);
    });
    crawler.queue.min("actualDataSize", function (error, min) {
        console.log("The minimum actualDataSize was %d", min);
    });
    crawler.queue.avg("actualDataSize", function (error, avg) {
        console.log("The average actualDataSize was %d", avg);
    });

    crawler.queue.countWithStatus("redirected", function (error, redirectCount) {
        console.log("The redirect count is %d", redirectCount);
    });

    crawler.queue.getWithStatus("failed", function (error, failedItems) {
        if (failedItems) {
            failedItems.forEach(function(queueItem) {
                console.log("Whoah, the request for %s failed!", queueItem.url);
            });
        }
    });
}

myCrawler.start()

// var schedule = require("node-schedule");
// var rule = new schedule.RecurrenceRule();
//     var times = [];
//     for(var i=1; i<60; i++){
//         times.push(i);
//     }
// rule.second = times;

// var j = schedule.scheduleJob(rule, function(){
//     report(myCrawler);
// });


// Crawler.crawl(, function(queueItem) {
//  console.log("Completed fetching resource:", queueItem.url);
//  var parsed_url = url.parse(queueItem.url)
//  // console.log(parsed_url)
//  if (parsed_url.host != "www.baidu.com") {
//      console.log("unmatched host " + parsed_url)
//      return
//  }

//  var path = parsed_url.path.substring(1)
//  console.log(queueItem)

// });
