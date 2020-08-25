#!/usr/bin/python

from socket import *
import sys
import random
import os
import time

if len(sys.argv) < 6:
    sys.stderr.write('Usage: %s <ip> <port> <#trials>\
            <#writes and reads per trial>\
            <#connections> \n' % (sys.argv[0]))
    sys.exit(1)

serverHost = gethostbyname(sys.argv[1])
serverPort = int(sys.argv[2])
numTrials = int(sys.argv[3])
numWritesReads = int(sys.argv[4])
numConnections = int(sys.argv[5])

if numConnections < numWritesReads:
    sys.stderr.write('<#connections> should be greater than or equal to <#writes and reads per trial>\n')
    sys.exit(1)

socketList = []

RECV_TOTAL_TIMEOUT = 0.1
RECV_EACH_TIMEOUT = 0.01

for i in xrange(numConnections):
    s = socket(AF_INET, SOCK_STREAM)
    s.connect((serverHost, serverPort))
    socketList.append(s)


GOOD_REQUESTS = ['GET / HTTP/1.1\r\nUser-Agent: 441UserAgent/1.0.0\r\n\r\n']
BAD_REQUESTS = [
    'GET\r / HTTP/1.1\r\nUser-Agent: 441UserAgent/1.0.0\r\n\r\n', # Extra CR
    'GET / HTTP/1.1\nUser-Agent: 441UserAgent/1.0.0\r\n\r\n',     # Missing CR
    'GET / HTTP/1.1\rUser-Agent: 441UserAgent/1.0.0\r\n\r\n',     # Missing LF
]

BAD_REQUEST_RESPONSE = 'HTTP/1.1 400 Bad Request\r\n'

for i in xrange(numTrials):
    socketSubset = []
    randomData = []
    randomLen = []
    socketSubset = random.sample(socketList, numConnections)
    for j in xrange(numWritesReads):
        random_index = random.randrange(len(GOOD_REQUESTS) + len(BAD_REQUESTS))
        if random_index < len(GOOD_REQUESTS):
            random_string = GOOD_REQUESTS[random_index]
            randomLen.append(len(random_string))
            randomData.append(random_string)
        else:
            random_string = BAD_REQUESTS[random_index - len(GOOD_REQUESTS)]
            randomLen.append(len(BAD_REQUEST_RESPONSE))
            randomData.append(BAD_REQUEST_RESPONSE)
        socketSubset[j].send(random_string)

    for j in xrange(numWritesReads):
        data = socketSubset[j].recv(randomLen[j])
        start_time = time.time()
        while True:
            if len(data) == randomLen[j]:
                break
            socketSubset[j].settimeout(RECV_EACH_TIMEOUT)
            data += socketSubset[j].recv(randomLen[j])
            if time.time() - start_time > RECV_TOTAL_TIMEOUT:
                break
        if data != randomData[j]:
            sys.stderr.write("Error: Data received is not the same as sent! \n")
            sys.exit(1)

for i in xrange(numConnections):
    socketList[i].close()

print "Success!"
