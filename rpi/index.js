var express = require('express');
var http = require('http');
var SerialPort = require('serialport');

var app = express();
var server = http.createServer(app);

// XXX a websocket connection could work

var serialDevice = process.env.SERIAL_DEVICE || '/dev/tty-usbserial1';
var serial = new SerialPort(serialDevice, {
    baudRate: 9600
});

app.get('/move/:button', function(req, res) {
    var button = req.params.button;
    res.send('ok ' + button);
    serial.write(button);
});

process.on('uncaughtException', function (err) {
    console.error(err);
    process.exit(1);
});

app.listen(3000);
