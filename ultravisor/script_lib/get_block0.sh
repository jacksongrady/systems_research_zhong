#!/bin/bash
sleep 1
echo "dump_image blue_alias.bin 0x0 0x80000"
echo "dump_image blue_flash.bin 0x08000000 0x80000"
echo "dump_image blue_sys.bin 0x1FFF0000 0x7800"
echo "dump_image blue_otp.bin 0x1FFF7800 0x210"
echo "dump_image blue_op.bin 0x1FFFC000 0x10"
sleep 20