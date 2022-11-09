#!/bin/bash
(sleep 1; python3 set_regs.py; sleep 2) | telnet localhost 4444
./set_block0.sh | telnet localhost 4444
./set_block1.sh | telnet localhost 4444
./set_block2.sh | telnet localhost 4444
#./get_block7.sh | telnet localhost 4444