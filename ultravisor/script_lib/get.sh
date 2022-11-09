#!/bin/bash
./get_regs.sh | telnet localhost 4444 > regs.txt
./get_block0.sh | telnet localhost 4444
./get_block1.sh | telnet localhost 4444
./get_block2.sh | telnet localhost 4444