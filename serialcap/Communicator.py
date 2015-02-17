#!/usr/bin/ python
# -*- coding: utf-8 -*-
import csv, serial, time, struct
from serial.tools import list_ports
from datetime import datetime, timedelta

class Communicator(object):

    def __init__(self, port, baudrate=9600, timeout=1):
        self.port = port
        self.baudrate = baudrate
        self.timeout = timeout
        self.ser = serial.Serial(
            port = self.port,
            baudrate = self.baudrate,
            timeout = self.timeout)
        self.requestPacket = "~"

    # Find all available ports
    @staticmethod
    def find_ports():
        return [port[0] for port in list_ports.comports()]

    def readData(self):
        self.requestData()
        raw = self.ser.readline().rstrip()
        if raw:
            return float(raw)

    def requestData(self):
        self.ser.write(self.requestPacket)
        print "Request Packet Sent"

    def capture(self, delta, rate, filename):
        end_time = datetime.now() + timedelta(minutes=delta)
        while datetime.now() < end_time:
            try:
                with open(filename, "a") as csv_file:
                    w = csv.writer(csv_file, dialect="excel")
                    w.writerow([datetime.now(), self.readData()])
            except csv.Error, e:
                print "Error writing CSV: {}".format(e)
            time.sleep(rate)
