var Dummy = require('./dummy-babel/dummy');

process.on('uncaughtException', function (err) {
    console.log(err);
});

// http://stackoverflow.com/questions/30649994/can-i-catch-an-error-from-async-without-using-await
// https://nodejs.org/docs/latest/api/process.html#process_event_unhandledrejection
process.on('unhandledRejection', function(reason, p) {
    console.log("Unhandled Rejection at: Promise ", p, " reason: ", reason);
    // application specific logging, throwing an error, or other logic here
    console.log(reason.stack)
});



var d = new Dummy();
try {
    d.pp();
} catch (e) {
    console.log(e);
}