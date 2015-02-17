#!/usr/bin/ python
# -*- coding: utf-8 -*-

import os, sys
from Communicator import Communicator
from argparse import ArgumentParser
from datetime import datetime, timedelta
from serial import SerialException

# Parse arguments
def buildArgumentParser():
    parser = ArgumentParser(description="Python serial messenger")
    parser.add_argument('-p', '--port', 
        help="select a port to communicate with (e.g. /dev/tty0)")
    parser.add_argument('-b', '--baud', default=9600,
        help='select baudrate (e.g. 9600)')
    parser.add_argument('-t', '--timeout', default=1, 
        help='set a timeout')
    return parser

def main():
    args = buildArgumentParser().parse_args()
    baud = args.baud
    timeout = args.timeout
    if args.port:
        port = args.port
    else:
        ports = Communicator.find_ports()
        print "#        Port"
        print "--------------------------------"
        for p in ports:
            print "{}       {}".format(ports.index(p), p)
        s = int(raw_input("Please select a port: "))
        port = ports[s]
    try:
        com = Communicator(port, baudrate=9600, timeout=1)
    except SerialException:
        sys.exit("There was a problem connecting to the port. Please make sure the device is ready.")
    if com.ser.isOpen():
        print "Serial port initialized at {}".format(com.ser.name)
    delta = int(raw_input("Length of time to record[min]: "))
    rate = int(raw_input("Input sample rate[s]: "))
    
    com.capture(delta=delta, rate=rate, filename="{}.csv".format(datetime.now().strftime("%Y-%m-%d-%H:%M")))

if __name__ == '__main__':
    main()
