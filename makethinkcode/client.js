
const WebSocket = require('ws');

let ws = new WebSocket('ws://localhost:8080');

ws.onopen = function() {
    ws.send('ping')
}

ws.on('message', function incoming(data) {
   console.log(data)
})
