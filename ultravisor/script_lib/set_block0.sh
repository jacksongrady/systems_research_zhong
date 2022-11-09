#!/bin/bash
sleep 1
echo "load_image blue_alias.bin 0x0"
echo "flash protect 0 0 7 off"
echo "flash write_image erase unlock blue_flash.bin 0x8000000 bin"
#st-flash write openocd-esp32/tcl/blue_flash.bin 0x8000000
sleep 4
echo "load_image blue_sys.bin 0x1FFF0000"
echo "load_image blue_otp.bin 0x1FFF7800" 
echo "load_image blue_op.bin 0x1FFFC000"
sleep 20