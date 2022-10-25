#!/bin/bash
sleep 1
echo "load_image blue_APB1.bin 0x40000000"
echo "load_image blue_APB2.bin 0x40010000"
echo "load_image blue_AHB1_1.bin 0x40020000"
echo "load_image blue_AHB1_2.bin 0x40021C00"
echo "load_image blue_AHB1_3.bin 0x40023000"
echo "load_image blue_AHB1_4.bin 0x40023800"
echo "load_image blue_AHB1_5.bin 0x40026000"
echo "load_image blue_AHB2.bin 0x50000000"
echo "load_image blue_cortex_periph.bin 0xE0000000"
sleep 20