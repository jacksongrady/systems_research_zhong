#!/bin/bash
sleep 1
echo "load_image blue_alias.bin 0x0"
echo "load_image blue_flash.bin 0x08000000"
echo "load_image blue_sys.bin 0x1FFF0000"
echo "load_image blue_otp.bin 0x1FFF7800" 
echo "load_image blue_op.bin 0x1FFFC000"
sleep 20