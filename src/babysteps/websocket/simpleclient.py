#!/usr/bin/env python

# references
#  https://github.com/websocket-client/websocket-client
#  apt install python-websocket

import websocket,socket,sys

ws = websocket.create_connection("ws://192.168.0.159:81/")
ws.settimeout(0.1)
while True:
    try:
        print ws.recv()
    except websocket._exceptions.WebSocketTimeoutException:
        print ".",
        sys.stdout.flush()
    except KeyboardInterrupt:
        break

