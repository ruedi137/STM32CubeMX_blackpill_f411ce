# serial-printf

provide a anlog for Arduinos SerialMonitor.printf 

blackpill has no UART to USB chip but uses USB pins in MCU

LED @ PC13
USB_OTG_FS_DM @ PA11
USB_OTG_FS_DM @ PA12

##STM32Cube/PlatformIO fusion project
- STM32Cube and PlatformIO located in same root
- All owe devel in PlatformIO layout: scr, include, ...
- Only minimal changes to STM32CubeMX code
- Configure git to pick only necessary code for buildable repo

Resources:
- https://stm32-base.org/boards/STM32F411CEU6-WeAct-Black-Pill-V2.0
