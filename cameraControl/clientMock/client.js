//client.js
var PORT = 3001;
var HOST = '127.0.0.1';

var dgram = require('dgram');
var message = new Buffer('x:10,y:10,k:0');

var client = dgram.createSocket('udp4');

//Send a message [message variable] to the host and port configured in the first two lines,
//logging as appropriate.
client.send(message, 0, message.length, PORT, HOST, function (err, bytes) {
	if (err)
		throw err;
	console.log('UDP message sent to ' + HOST + ':' + PORT);
process.exit(0);
});