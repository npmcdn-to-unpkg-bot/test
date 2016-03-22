var page = require('webpage').create(),
    system = require('system'),
    t, address;

if (system.args.length === 1) {
    console.log('Usage: capture-webpage.js <come URL>');
    phantom.exit();
}

t = Date.now();
address = system.args[1];

//viewportSize being the actual size of the headless browser
page.viewportSize = { width: 1920, height: 1080 };
//the clipRect is the portion of the page you are taking a screenshot of
page.clipRect = { top: 0, left: 0, width: 1920, height: 1080 };

page.open(address, function(status) {
    if (status !== 'success') {
        console.log('Fail to load the address:' + status);
    } else {
        t = Date.now() - t;
        console.log('Loading ' + address + ' with ' + t + ' msec');
        page.render('example.png');
    }
    phantom.exit();
});