#!/bin/bash

./hub.out "$1" > hub.txt &
./probeA.out "$1" > probeA.txt &
./probeB.out "$1" > probeB.txt &
