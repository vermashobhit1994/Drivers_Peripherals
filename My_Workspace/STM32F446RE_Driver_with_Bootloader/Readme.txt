This is the minimum functionality bootloader.

In this the user application and bootloader is flashed separately by changing the sections in linker script.

First flash the user application by changing the sections to go to FLASH.

Then flash the bootloder by changing the sections to go to BOOTROM.

In user application the LED blinks while in bootloader mode the LED remains ON.

When we want to change the mode from application to bootloader mode just reset the board and then press and hold the user button until the LED glows.



