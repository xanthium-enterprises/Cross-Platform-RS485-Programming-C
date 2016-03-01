# Cross-Platform-RS485-Programming-C (Linux/Windows)
------------------------------------------------------------------------------------------------

<img src ="http://s25.postimg.org/miw3bhv33/launchpad_interface_usb2serial.jpg"/>

This Repo contains code for communicating with an x86 PC from a microcontroller Board (MSP430 Launchpad) using **RS485 Protocol**.

The codes are written in **C** for both **Windows** and **Linux** Platforms.

<a href="http://xanthium.in/Cross-Platform-RS485-Communication-using-USB-to-RS485-converter"> Detailed **explanation of the codes** along with the Hardware can be found here.</a>

--------------------------------------------------------------------------------------------------------------------------
###Source Code 

- **Windows**

  - You can find the **Windows** Sourcecode for RS485 communication under the **Win32** Folder.

  - The code uses Win32 API to open a connection and communicates with the <a href="http://xanthium.in/USB-to-Serial-RS232-RS485-Converter">USB to RS485 Converter</a> to transmit and Receive the Data send from the Microcontroller (here MSP430 Launchpad).

  - The code can be **compiled** using Opensource **GCC** or **Microsoft Visual Studio**.
  - Code is tested on Windows XP,Windows 7

- **Linux**
   - You can find the **Linux** Sourcecode for RS485 communication under the **Linux** Folder.
   
   - The Code uses **termios API** and **ioctl calls** to open a connection and communicates with the <a href="http://xanthium.in/USB-to-Serial-RS232-RS485-Converter">USB to RS485 Converter</a> to transmit and Receive the Data send from the Microcontroller (here MSP430 Launchpad).
    
   - The code can be **compiled** using Opensource **GCC** on any Linux System.
   
   - Code is tested on **Linux 3.x** Kernel on Ubuntu,Linux Mint and Lubuntu
