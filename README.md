# ainsuMtxd51

# NEWS

CamelForth is now embedded into this forth-like interpreter!

  'forth' starts CamelForth.  Please use ALL CAPS when
addressing CamelForth.

  There is no exit (just reboot to get out of CamelForth).

http://camelforth.com/news.php

CamelForth in C!
Misc: Brad R @ Friday 15 December 2017 - 14:38:49

# Status

Working small, Forth-like interpreter (type 'words' for help).

    On branch KM_converser_d51

For SAMD51 (here) and SAMD21 (elsewhere; similarly-named repository)

Most recent work is here.  SAMD21 repository is lagging behind quite a bit.

# Intent

This is a working, USART-tethered interpreter that exhibits a very small
number of behaviors reminiscent of forth.

It can execute arbitrary functions coded in C, through a pleasant tty
(typewriter-like) interface at 38400 bps.

Intent is to use this primitive environment as a way 'in' .. as a debug
monitor running on the hardware itself -- to try to do something a bit
more interesting there.

# Build Environment

This is an Atmel Start based project for Atmel ATSAMD51J19A,
and runs on the Adafruit Metro M4 Express target board.

Pinmuxing is for that specific board.

The program leverages the USART on the SAMD51, and talks to
a host PC running Linux, via USB to UART gateway chip from
Silabs (CP2104) - the Adafruit PiUART, in this instance.

It takes three wires to do so (TX, RX and ground).

Host system is any host that can talk to the PiUART (which
was designed for Raspberry Pi users to gain a serial console
on a getty).

Should be no problem to connect any serial terminal with 3.3v
logic levels directly to the Metro M4 Express TX and RX pins,
and talk that way.  The PiUART is a convenience, only (it allows
the host PC to leverage its USB port to talk to the Metro M4's
USART).

This firmware is built on Debian Linux 9.5 (Linux kernel
4.9.0-7-amd64).

Toolchain is the usual ARM gcc - same exact build environment as
Adafruit's CircuitPython.

Makefile is a modification of Atmel Start's version, with which
it is fundamentally compatible, except for the way the bootloader
is handled:

  $ cat ../ainsuMtxd51-exp/gcc/Makefile | egrep bootl
-T"../gcc/gcc/samd51j19a_flash_with_bootloader.ld" \

 $ cat ../ainsuMtxd51-exp/gcc/gcc/samd51j19a_flash_with_bootloader.ld | sed 46q | tail -12

/* Memory Spaces Definitions */
MEMORY
{
  rom      (rx)  : ORIGIN = 0x00004000, LENGTH = 0x00080000-0x4000
  ram      (rwx) : ORIGIN = 0x20000000, LENGTH = 0x00030000
  bkupram  (rwx) : ORIGIN = 0x47000000, LENGTH = 0x00002000
  qspi     (rwx) : ORIGIN = 0x04000000, LENGTH = 0x01000000
}

/* The stack size used by the application. NOTE: you need to adjust according to your application. */
STACK_SIZE = DEFINED(STACK_SIZE) ? STACK_SIZE : DEFINED(__stack_size__) ? __stack_size__ : 0xC000;

# Flashing the Firmware

This is done using bossac, from the command line.

A Makefile target called 'install' runs a shell script on 
the host Linux PC that launches bossac (reuses the existing
Arduino IDE bossac, which already works fine with SAMD51).

 $ ./scripts/_bossac_local.sh ./AtmelStart.bin (is what's in the Makefile)

 $ cat ../ainsuMtxd51-exp/gcc/scripts/_bossac_local.sh  (excerpt):

Call with one argument - the path/file.bin (not .uf2) to upload using bossac

if ! [ $1 ]; then
   echo no args.  Exiting; fi
   ~/.arduino15/packages/arduino/tools/bossac/1.8.0-48-gb176eee/bossac \
    -i -d --port=/dev/ttyACM0 -U -i --offset=0x4000 -e -w -v ${1} -R  # .bin not .elf

The  --offset is specific to Adafruit SAMD51 boards (to skip
over the bootloader).

Bossac may be in more than one version in the Arduino IDE
sub-tree; 1.8.0-48 was present and was used, here.

# Lineage:

# samd51_USART_basic
   * clocks and very basic USART support

# ainsuMtxd21
  * more recent work on the command processor/interpreter loop code

Sun Sep  2 05:11:12 UTC 2018
On branch zKM_converser_d51-aa-

 $ cat cat ./README.md | sed 65q | md5sum

ef128a300f16137485b9ace186131999
