#!/bin/bash
sleep 1
echo "dump_image blue_APB1.bin 0x40000000 0x7400"
echo "dump_image blue_APB2.bin 0x40010000 0x5400"
echo "dump_image blue_AHB1_1.bin 0x40020000 0x1400"
echo "dump_image blue_AHB1_2.bin 0x40021C00 0x400"
echo "dump_image blue_AHB1_3.bin 0x40023000 0x400"
echo "dump_image blue_AHB1_4.bin 0x40023800 0x800"
echo "dump_image blue_AHB1_5.bin 0x40026000 0x800"
echo "dump_image blue_AHB2.bin 0x50000000 0x40000 "
echo "dump_image blue_cortex_periph.bin 0xE0000000 0x100000"
sleep 20