#!/usr/bin/env python

import socket
import ssl
import sys

CERTFILE = 'certs/python_server.crt'
KEYFILE = 'private/python_server.key'

server = socket.socket()
server.bind(('0.0.0.0',int(sys.argv[1])))
server.listen(5)

while True:
    newsock, address = server.accept()
    try:
        newsock = ssl.wrap_socket(newsock,
                                  server_side=True,
                                  certfile=CERTFILE,
                                  keyfile=KEYFILE,
                                  ssl_version=ssl.PROTOCOL_TLSv1)
    except ssl.SSLError:
        print 'exception in socket!'
        if newsock:
            newsock.shutdown(socket.SHUT_RDWR)
            newsock.close()
        continue
    data = newsock.read(8192)
    newsock.write('HTTP/1.1 200 OK\r\n\r\nTesting')
    newsock.shutdown(socket.SHUT_RDWR)
    newsock.close()