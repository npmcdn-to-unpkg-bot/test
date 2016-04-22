var redis = require("redis");

var options = {
    host: '127.0.0.1',
    port: 6379
}
var client = redis.createClient(options);

// if you'd like to select database 3, instead of 0 (default), call
// client.select(3, function() { /* ... */ });

client.on("error", function (err) {
    console.log("Error " + err);
});

client.set("string key", "string val", redis.print);
client.hset("user:100", "name", "Bob", redis.print);
client.hset(["user:100", "email", "bob@bob.com"], redis.print);
client.hkeys("user:100", function (err, replies) {
    console.log(replies.length + " replies:");
    replies.forEach(function (reply, i) {
        console.log("    " + i + ": " + reply);
    });
    client.quit();
});