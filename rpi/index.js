var express = require('express');
var http = require('http');
var SerialPort = require('serialport');

var app = express();
var server = http.createServer(app);

// XXX a websocket connection could work better
var MOVES = {
    'up': '1',
    'left': '2',
    'right': '3',
    'down': '4'
};

app.use('/static', express.static(__dirname + '/../web/'));

app.use(function(req, res, next) {
    res.header("Access-Control-Allow-Origin", "*");
    res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
    next();
});

app.post('/move/:button', function(req, res) {
    var button = req.params.button;

    var move = MOVES[button];
    if (!move) {
        return res.status(400).send('fail wrong input');
    }

    serial.write(move, function(err) {
        if (err) {
            console.err('write to serial error', err);
            return res.status(500).send('fail communications');
        }

        res.send('ok ' + button);
    });
});

app.get('/status', function(req, res) {
    res.send('ok');
});

var serialDevice = process.env.SERIAL_DEVICE || '/dev/tty-usbserial1';
var serial = new SerialPort(serialDevice, {
    baudRate: 9600
});

serial.on('open', function() {
    console.log('serial port open');
});

serial.on('error', function(err) {
    console.error('serial port error', err);
});

process.on('uncaughtException', function (err) {
    console.error(err);
    process.exit(1);
});

app.listen(3000, '0.0.0.0');
