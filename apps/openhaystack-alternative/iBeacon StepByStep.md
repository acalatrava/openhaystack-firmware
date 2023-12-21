# All tools and software used: 
* iBeacons NRF51822: https://aliexpress.com/item/32917064741.html
* Batteries CR2477: https://aliexpress.com/item/1005004906609217.html 
* Programmer: ST-LINK V2: https://aliexpress.com/item/1005003575620794.html
* OpenOCD v20231002 https://gnutoolchains.com/arm-eabi/openocd/
* Drivers for ST-LINK for Win10 are inside openocd: openocd-20231002\OpenOCD-20231002-0.12.0\drivers\ST-Link
* Firmware Upgrade for ST-Link: STSW-LINK007 https://www.st.com/en/development-tools/stsw-link007.html 
* macOS 11.7.10 BigSur with [OpenHaystack](https://github.com/seemoo-lab/openhaystack)
* Windows 10

Firmware iBeacon: https://github.com/acalatrava/openhaystack-firmware
With preexisting files from apps/openhaystack-alternative/compiled 

## Software
1. Install Drivers for ST-Link from OpenOCD directory
2. Upgrade Firmware for ST-Link
3. Install OpenHaystack on macOS machine

## Soldering
Solder wires according to layout and attach to ST-LINK accordingly  
SWDCLK, SWDIO, GND, VDD(=3.3 V) - use only one GND - I used the bottom one.  
![Board layout](/apps/openhaystack-alternative/layout.jpg)

## Generate Advertisement Key
In Openhaystack:  
Create New Device  
Copy Advertisement Key->Base64

## Creating patched firmware
In Terminal in MacOS navigate into /apps/openhaystack-alternative and type:
```
NRF_MODEL=nrf51 ADV_KEY_BASE64=[YOUR_ADVERTISEMENT_KEY] make patch
```
This creates "nrf51_firmware_patched.bin" in /compiled folder

## Flashing Device
Copy "nrf51_firmware_patched.bin" to a Win10 machine  
(This step is obviously optional but I coouldn't make it work on macOS somehow, maybe ST-LINK is not compatible)
into the OpenOCD-Folder.

In cmd Windows 10:
Navigate into OPenOCD folder (the one that contains folders bin, drivers, share) and type:
```
bin\openocd.exe -f share\openocd\scripts\interface\stlink.cfg -f share\openocd\scripts\target\nrf51.cfg -c "init; halt; nrf51 mass_erase; program nrf51_firmware_patched.bin; reset; exit;"
```
Result should look like this, takes about one second:

```
Open On-Chip Debugger 0.12.0 (2023-10-02) [https://github.com/sysprogs/openocd]
Licensed under GNU GPL v2
libusb1 09e75e98b4d9ea7909e8837b7a3f00dda4589dc3
For bug reports, read
        http://openocd.org/doc/doxygen/bugs.html
Info : auto-selecting first available session transport "hla_swd". To override use 'transport select <transport>'.
Info : The selected transport took over low-level target control. The results might differ compared to plain JTAG/SWD
Info : clock speed 1000 kHz
Info : STLINK V2J43S7 (API v2) VID:PID 0483:3748
Info : Target voltage: 3.274766
Info : [nrf51.cpu] Cortex-M0 r0p0 processor detected
Info : [nrf51.cpu] target has 4 breakpoints, 2 watchpoints
Info : starting gdb server for nrf51.cpu on 3333
Info : Listening on port 3333 for gdb connections
Warn : target was in unknown state when halt was requested
[nrf51.cpu] halted due to debug-request, current mode: Thread
xPSR: 0x61000000 pc: 0x00011480 msp: 0x20003550
Info : nRF51822-QFAA(build code: H0) 256kB Flash, 16kB RAM
Info : Mass erase completed.
Info : A reset or power cycle is required if the flash was protected before.
[nrf51.cpu] halted due to debug-request, current mode: Thread
xPSR: 0xc1000000 pc: 0xfffffffe msp: 0xfffffffc
** Programming Started **
Warn : Adding extra erase range, 0x0001cc70 .. 0x0001cfff
** Programming Finished **
```
In OpenHaystack:  
Mark Device as deployed  

Unsolder Wires, insert Battery and you are done.
