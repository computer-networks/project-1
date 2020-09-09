#!/usr/bin/env python

import socket

RESPONSE = 'HTTP/1.1 501 Not Implemented\r\nServer: Liso/1.0\r\nConnection: \
close\r\n\r\n'

server = socket.socket()
server.bind(('0.0.0.0',8080))
server.listen(5)

try:
    while True:
        try:
            (client_socket, client_information) = server.accept()
        except:
            server.close()
            break

        try:
            print client_socket.recv(4096)
            client_socket.sendall(RESPONSE)
            continue
        except:
            pass
        finally:
            client_socket.close()
finally:
    server.close()