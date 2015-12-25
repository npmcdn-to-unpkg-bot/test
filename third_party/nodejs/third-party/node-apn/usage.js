"use strict";

// npm install apn
// npm install commander


var apn = require ("apn");
var args = require ('commander');
var fs = require ('fs');

var apns_conf = {
    certFile : process.env['CERT_FILE'],
    keyFile : process.env['KEY_FILE'],
    production : false,
    sendTimes : 1,
    tokens : []
};

var path_exists = function (path) {
    try {
        status = fs.accessSync(path, fs.F_OK);
    } catch (e) {
        if (e.errorno === -2) {
            console.log(e);
            return false;
        }
    }
    return true;
};

var token_list = function (val) {
    console.log(val)
    return val.split(' ');
};

args.version('0.0.1')
    .usage('token1 token2... [options]')
    .option('--production', 'Use production server')
    .option('--cert-file [path]', 'cert file for apns server')
    .option('--key-file [path]', 'private key file for apns server')
    .option('-n, --number <n>', 'How many times to send', parseInt)
    .parse(process.argv)

if (args.certFile) {
    apns_conf.certFile = args.certFile;
}
if (args.keyFile) {
    apns_conf.keyFile = args.keyFile;
}
if (args.production) {
    apns_conf.production = true;
}
if (args.number) {
    apns_conf.sendTimes = args.number;
}
if (!args.args.length) {
    console.log('  Need tokens ...');
    args.help();
    process.exit(-1);
}
// Unparsed args as tokens
apns_conf.tokens = apns_conf.tokens.concat(args.args);

if (!apns_conf.certFile || !apns_conf.keyFile) {
    console.log('Please export CERT_FILE=/path/to/cert-file');
    console.log('       export KEY_FILE=/path/to/key-file');
    console.log('Or use --cert-file=/path/to/cert-file');
    console.log('       --cert-file=/path/to/key-file');
    process.exit(-1);
}

if (!path_exists(apns_conf.certFile) || !path_exists(apns_conf.keyFile)) {
    process.exit(-1);
}


// Create a connection to the service using mostly default parameters.
var options = {
    cert : apns_conf.certFile,
    key : apns_conf.keyFile,
    production : apns_conf.production
};
var service = new apn.connection(options);

service.on("connected", function() {
    console.log("Connected");
});

service.on("transmitted", function(notification, device) {
    console.log("Notification transmitted to:" + device.token.toString("hex"));
});

service.on("transmissionError", function(errCode, notification, device) {
    console.error("Notification caused error: " + errCode + " for device ", device, notification);
    if (errCode === 8) {
        console.log("A error code of 8 indicates that the device token is invalid. This could be for a number of reasons - are you using the correct environment? i.e. Production vs. Sandbox");
    }
});

service.on("timeout", function () {
    console.log("Connection Timeout");
});

service.on("disconnected", function() {
    console.log("Disconnected from APNS");
});

service.on("socketError", console.error);


// If you plan on sending identical paylods to many devices you can do something like this.
function pushNotificationToMany(tokens) {
    console.log("Sending the same notification each of the devices with one call to pushNotification.");
    var note = new apn.notification();
    note.setAlertText("Hello, from node-apn!");
    note.badge = 1;

    service.pushNotification(note, tokens);
}


// If you have a list of devices for which you want to send a customised notification you can create one and send it to and individual device.
function pushSomeNotifications(tokens) {
    console.log("Sending a tailored notification to %d devices", tokens.length);
    tokens.forEach(function(token, i) {
        var note = new apn.notification();
        note.setAlertText("Hello, from node-apn! You are number: " + i);
        note.badge = i;

        service.pushNotification(note, token);
    });
}

function pushNotificationWithNumber(token, sendTimes) {
    sendTimes = arguments[1] ? arguments[1] : 1;
    for (var i=1; i<sendTimes+1; i++) {
        var note = new apn.notification();
        note.setAlertText('This is the ' + i + ' time to push ...');
        note.badge = i;

        service.pushNotification(note, token);
    }
}

pushNotificationWithNumber(apns_conf.tokens[0], apns_conf.sendTimes);