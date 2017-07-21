const express = require('express');
const http = require('http');
const url = require('url');
const WebSocket = require('ws');
const ArduinoFirmata = require('arduino-firmata');

const app = express();

app.use(function (req, res) {
  res.send({ msg: "hello" });
})
//websocket server initialization
const server = http.createServer(app);
const wss = new WebSocket.Server({ server });


// websocket connection 
wss.on('connection', function connection(ws, req) {
  
  
  ws.on('message', function incoming(message) {
    console.log('received: %s', message);
  });
//test ping to client
  ws.send('ping');
});

server.listen(8080, function listening() {
  console.log('Listening on %d', server.address().port);
});


// firmata 
const arduino = new ArduinoFirmata();

// device connection 
arduino.connect('/dev/cu.usbmodem3387561');
//divice 
arduino.on('connect', function(){
 
  console.log("board version"+ arduino.boardVersion);
  // your-code-here 
 
});





module.exports = app;
