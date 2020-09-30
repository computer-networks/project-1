#!/usr/bin/env python
#
# This script serves as a simple TLSv1 client for 15-441
#
# Authors: Athula Balachandran <abalacha@cs.cmu.edu>,
#          Charles Rang <rang972@gmail.com>,
#          Wolfgang Richter <wolf@cs.cmu.edu>

import pprint
import socket
import ssl

# try a connection
sock = socket.create_connection(('localhost', 4949))
tls = ssl.wrap_socket(sock, cert_reqs=ssl.CERT_REQUIRED,
                            ca_certs='../certs/signer.crt',
                            ssl_version=ssl.PROTOCOL_TLSv1)

# what cert did he present?
pprint.pprint(tls.getpeercert())

tls.sendall('this is a test message')
print tls.recv(4096)
tls.close()



# try another connection!
sock = socket.create_connection(('localhost', 4949))
tls = ssl.wrap_socket(sock, cert_reqs=ssl.CERT_REQUIRED,
                            ca_certs='../certs/signer.crt',
                            ssl_version=ssl.PROTOCOL_TLSv1)

tls.sendall('this is a test message!!!')
print tls.recv(4096)
tls.close()

exit(0)
