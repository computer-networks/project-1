################################################################################
# README                                                                       #
#                                                                              #
# Description: This file serves as a README and documentation for CP1 starter. #
#                                                                              #
# Authors: Athula Balachandran <abalacha@cs.cmu.edu>,                          #
#          Wolf Richter <wolf@cs.cmu.edu>                                      #
#                                                                              #
################################################################################




[TOC-1] Table of Contents
--------------------------------------------------------------------------------

        [TOC-1] Table of Contents
        [DES-2] Description of Files
        [RUN-3] How to Run




[DES-2] Description of Files
--------------------------------------------------------------------------------

Here is a listing of all files associated with checkpoint 1 and what their'
purpose is:

                    .../README              - Current document 
                    .../echo_client.c       - Simple echo network client
                    .../echo_server.c       - Simple echo network server
                    .../Makefile            - Contains rules for make
                    .../cp1_checker.py      - Simple python test script

                    .../example.c           - Example driver for parsing
                    .../lexer.l             - Lex/Yacc related logic           
                    .../parse.y
                    .../parse.c
                    .../parse.h

                    .../sample_request_simple    - Example HTTP requests
                    .../sample_request_realistic


[RUN-3] How to Run
--------------------------------------------------------------------------------

Note: We recommend building and testing on Andrew machines. 

i) Starter echo server

Executing the starter echo code should be very simple:

                    ./echo_server
                    ./echo_client localhost 9999

This should allow you to input characters on stdin which will be sent to the
echo server.  The echo server has a hard-coded serving port of 9999.  Any input
characters to stdin will be flushed to the server on return, and any bytes
received from the server will appear on stdout.

In addition, a telnet client may also be used in a similar fashion for
communicating with the server:

                    ./echo_server
                    telnet localhost 9999


ii) Starter parsing code

                    ./example <input>


iii) Test script

After you have done your checkpoint 1 implementations (select and HTTP parsing),
you could use provided test script to test your implementations. The provided 
test script is a subset of the tests we will use eventually on Autolab.

The test Python script takes a series of arguments and can be run as:

                    ./lisod
                    ./cp1_checker 127.0.0.1 9999 1000 10 500

with arguments as such:

                    <ip> <port> <# trials> <# writes and reads per trial> \
                    <# connections> 

