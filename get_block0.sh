#!/bin/bash
sleep 1
echo "dump_image blue_alias.bin 0x0 0x7FFFF"
echo "dump_image blue_flash.bin 0x08000000 0x7FFFF"
echo "dump_image blue_sys.bin 0x1FFF0000 0x77FF"
echo "dump_image blue_otp.bin 0x1FFF7800 0x20F"
echo "dump_image blue_op.bin 0x1FFFC000 0xF"
sleep 20