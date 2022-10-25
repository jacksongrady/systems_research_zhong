#!/bin/bash
sleep 1
echo "dump_image blue_APB1.bin 0x40000000 0x73FF"
echo "dump_image blue_APB2.bin 0x40010000 0x4BFF"
echo "dump_image blue_AHB1_1.bin 0x40020000 0x13FF"
echo "dump_image blue_AHB1_2.bin 0x40021C00 0x3FF"
echo "dump_image blue_AHB1_3.bin 0x40023000 0x3FF"
echo "dump_image blue_AHB1_4.bin 0x40023800 0x7FF"
echo "dump_image blue_AHB1_5.bin 0x40026000 0x7FF"
echo "dump_image blue_AHB2.bin 0x50000000 0x3FFFF"
echo "dump_image blue_cortex_periph.bin 0xE0000000 0xFFFFF"
sleep 20