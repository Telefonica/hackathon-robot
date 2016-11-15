var PORT = 3000;
var HOST = '0.0.0.0';

var dgram = require('dgram');
var SerialPort = require("serialport");
var serialport = new SerialPort("COM7", {
         baudRate: 115200
     });

var server = dgram.createSocket('udp4');

//As soon as the server is ready to receive messages, handle it with this handler
server.on('listening', function () {
	var address = server.address();
	console.log('UDP Server listening on ' + address.address + ":" + address.port);
});
serialport.on('open', function () {

	console.log('Serial port Open');
});
//When getting a message, handle it like so:
server.on('message', function (message, remote) {
	//parse request
	var msg = ''+message;
	var arr = msg.split(",");
	serialport.write(arr[0]+','+arr[1]+'\r\n', function (err) {
		if (err) {
			return console.log('Error on write: ', err.message);
		}
		console.log('message x written');
	});
	
	//print out the message	
	console.log(remote.address + ':' + remote.port + ' - ' + message);
});

server.bind(PORT, HOST);
