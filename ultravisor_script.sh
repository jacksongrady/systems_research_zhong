#!/bin/bash
while true
do
    sleep 5
    echo "halt"
    echo "write_memory 0x40020C14 16 100000000"
    echo "resume"
    sleep 5
    echo "halt"
    echo "write_memory 0x40020C14 16 0"
    echo "resume"
done