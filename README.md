# DAP405 firmware for STM32F446

This firmware is intended for the high performance JTAG/SWD debugger DAP405v2,
which features a STM32F446 microcontroller at its heart.

## What is DAP405

DAP405 is a CMSIS-DAP compatible JTAG and SWD debugger for ARM Cortex-M based
microcontrollers. It is one of the few debuggers that features USB 2.0 Hi-Speed
connection to a host PC, allowing fast access to the target processor.

The name is held over from a previous project with a similar design goal, which
did use STM32F405 as the main processor. This revision upgraded the processor
to STM32F446 to allow the use of a more advanced ULPI transceiver, eliminating
one of the two clock crystals, and features a slightly faster CPU.

## How to use this repository

This repository is formed as an Eclipse workspace. You need the latest Eclipse
CDT, as well as GNU MCU Eclipse and its dependencies to build this project.

The code is written without the ue of an RTOS, STM32CubeMX or libopencm3. The
only dependencies are STM32 CMSIS device headers and libusb\_stm32. All of the
dependencies, at their correct revisions, are referenced in this repositories
as git submodules.

## License

This project is open source software under [3-clause BSD license](LICENSE.md).
