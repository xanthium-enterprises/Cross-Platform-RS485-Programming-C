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
  - <img src = "http://s25.postimg.org/ru7bl7pnj/rs485_data_reception_wait.jpg" />

- **Linux**

   - You can find the **Linux** Sourcecode for RS485 communication under the **Linux** Folder.
   
   - The Code uses **termios API** and **ioctl calls** to open a connection and communicates with the <a href="http://xanthium.in/USB-to-Serial-RS232-RS485-Converter">USB to RS485 Converter</a> to transmit and Receive the Data send from the Microcontroller (here MSP430 Launchpad).
    
   - The code can be **compiled** using Opensource **GCC** on any Linux System.
   
   - Code is tested on **Linux 3.x** Kernel on Ubuntu,Linux Mint and Lubuntu
   - <img src = "http://s25.postimg.org/8sxvrpggv/rs485_data_reception_linux.jpg" />
    
- **References**
 
  -  To Know more about **Win32 API for Serial Communication**,  <a href="http://xanthium.in/Serial-Port-Programming-using-Win32-API">Check this Tutorial</a>.
   
  -  To Know more about **termios API** (Linux), <a href ="http://xanthium.in/Serial-Port-Programming-on-Linux"> Check this Tutorial</a>.
    
  -  To Know more about  **ioct calls on Linux**,<a href ="http://xanthium.in/Controlling-RTS-and-DTR-pins-SerialPort-in-Linux">Check this Tutorial</a>.
    
  -  To Know more about USB to RS485 Converter,<a href="http://xanthium.in/USB-to-Serial-RS232-RS485-Converter">Check this Tutorial</a>.
