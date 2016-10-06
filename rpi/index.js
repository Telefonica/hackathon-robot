var express = require('express');
var http = require('http');

var app = express();
var server = http.createServer(app);

// XXX a websocket connection could work

app.get('/move/:button', function(req, res) {
    console.log(req.params.button);
    res.send('ok');
});

app.listen(3000);
