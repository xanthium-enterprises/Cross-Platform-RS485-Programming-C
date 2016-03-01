
	//====================================================================================================//
	// USB to RS485 conversion  using USB2SERIAL (Write) (Transmitter Side) (WIN32 API)                   //
	//----------------------------------------------------------------------------------------------------//
	// The Program runs on the PC side and uses Win32 API to communicate with USB2SERIAL hardware board-  //
	// -which converts the USB signals to RS485.                                                          //       
	//----------------------------------------------------------------------------------------------------//
	// Program runs on the PC side (Windows) and transmits a single character.                            //            
	// Program uses CreateFile() function to open a connection serial port(COMxx).                        //
	// Program then sets the parameters of Serial Comm like Baudrate,Parity,Stop bits in the DCB struct.  //
	// EsapeCommFunction() is used to control DTR and RTS and to set the direction of MAX485 chip         //
	// After setting the Time outs,the Program writes a character to COMxx using WriteFile().             //
        //----------------------------------------------------------------------------------------------------// 
	// BaudRate     -> 9600                                                                               //
	// Data formt   -> 8 databits,No parity,1 Stop bit (8N1)                                              //
	// Flow Control -> None                                                                               //
	//====================================================================================================//

	/*====================================================================================================*/
	/* www.xanthium.in										      */
	/* Copyright (C) 2014 Rahul.S                                                                         */
	/*====================================================================================================*/

	//====================================================================================================//
	//                                                                                                    //
	//  |------------|                                                                                    //
	//  | RS485      |                                               +---------+     +-----------+        //
	//  | Write.exe  |             USB2SERIAL V2.0                   |		 RO|---->|P1.1(RXD)  |        //
	//  |------------|            +--------------+                   |      ~RE|-----|P2.1       |        //
	//   \ [][][][][] \===========| USB -> RS485 |~~~~~~~~~~~~~~~~~~~|A,B      |     |           |        //
	//    \------------\   USB    +--------------+      Twisted      |       DE|-----|P2.0       |        //
	//        Laptop                                     Pair        |	     DI|<----|P1.2(TXD)  |        //
	//                                                               +---------+     +-----------+        //
	//                              						            MAX485        MSP430G2553         //
	//                                                                                                    //
	//      [Transmitter] --------------------------------------->   [--------Reciever-----------]        //
	//                            direction of data                                                       //
	//====================================================================================================//
	// Pin Configuration for  USB2SERIAL V2.0 Board                                                       //
	//                                                                                                    //
	//  		+==========================================================+                              //
	//			|	 +-----------+               +---------+               |                              //
	//  		|    |   	  TXD|-------------->|DI       |               |                              //
	// 	 	 +--|	 |        RXD|---------------|RO      A|------+        |                              //
	//	USB	 |	     |USB        |               |         |      |        |                              //
	// 	     +--|    |       ~RTS|-------------->|~RE     B|------|--+     |                              //
	//  		|    |	     ~DTR|-------------->|DE       |      |  |     |                              //
	//  		|    +-----------+               +---------+      |  |     |                              //
	//			|		FT232RL                    MAX485         |  |     |                              //
	//  		+================================================[A]=[B]===+                              //
	//                                                             RS485                                  //
	//                                                                                                    //
	//			                                                                                          //
	//====================================================================================================//
	// Compiler/IDE  :	Microsoft Visual Studio Express 2013 for Windows Desktop(Version 12.0)            //
	//               :  gcc 4.8.1 (MinGW)   
	// Library       :  Win32 API,windows.h,                                                              //
	// Commands      :  gcc -o USB2SERIAL_RS485_Write_W32 USB2SERIAL_RS485_Write_W32.c -std=c99                                                                              //
	// OS            :	Windows(Windows 7)                                                                //
	// Programmer    :	Rahul.S                                                                           //
	// Date	         :	30-November-2014                                                                  //
	//====================================================================================================//

	//====================================================================================================//
	// Sellecting the COM port Number                                                                     //
    //----------------------------------------------------------------------------------------------------//
    // Use "Device Manager" in Windows to find out the COM Port number allotted to USB2SERIAL converter-  // 
    // -in your Computer and substitute in the  "ComPortName[]" array.                                    //
	//                                                                                                    //
	// for eg:-                                                                                           //
	// If your COM port number is COM32 in device manager(will change according to system)                //
	// then                                                                                               //
	//			char   ComPortName[] = "\\\\.\\COM32";                                                    //
	//====================================================================================================//

	#include <Windows.h>
	#include <stdio.h>
	#include <string.h>
	void main(void)
	{
		
		HANDLE hComm;                          // Handle to the Serial port
		char   ComPortName[] = "\\\\.\\COM46"; // Name of the Serial port(May Change) to be opened,
		BOOL   Status;
		char   lpBuffer[] = "A";		       // lpBuffer should be  char or byte array, otherwise write wil fail
		DWORD  dNoOFBytestoWrite;              // No of bytes to write into the port
		DWORD  dNoOfBytesWritten = 0;          // No of bytes written to the port
		
		printf("\n\n +==========================================+");
		printf("\n |  RS485 Mode - Transmission (Win32 API)   |");
		printf("\n +==========================================+\n");
		/*----------------------------------- Opening the Serial Port --------------------------------------------*/

		hComm = CreateFile( ComPortName,                       // Name of the Port to be Opened
							GENERIC_READ | GENERIC_WRITE,      // Read/Write Access
							0,                                 // No Sharing, ports cant be shared
							NULL,                              // No Security
							OPEN_EXISTING,                     // Open existing port only
							0,                                 // Non Overlapped I/O
							NULL);                             // Null for Comm Devices

		if (hComm == INVALID_HANDLE_VALUE)
			printf("\n   Error! - Port %s can't be opened", ComPortName);
		else 
			printf("\n   Port %s Opened\n ", ComPortName);

		
		/*------------------------------- Setting the Parameters for the SerialPort ------------------------------*/

		DCB dcbSerialParams = { 0 };                        // Initializing DCB structure
		dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
		
		Status = GetCommState(hComm, &dcbSerialParams);     //retreives  the current settings

		if (Status == FALSE)
			printf("\n   Error! in GetCommState()");

		dcbSerialParams.BaudRate = CBR_9600;      // Setting BaudRate = 9600
		dcbSerialParams.ByteSize = 8;             // Setting ByteSize = 8
		dcbSerialParams.StopBits = ONESTOPBIT;    // Setting StopBits = 1
		dcbSerialParams.Parity   = NOPARITY;      // Setting Parity = None 

		Status = SetCommState(hComm, &dcbSerialParams);  //Configuring the port according to settings in DCB 

		if (Status == FALSE)
			{
				printf("\n   Error! in Setting DCB Structure");
			}
		else
			{
				printf("\n   Setting DCB Structure Successfull\n");
				printf("\n       Baudrate = %d", dcbSerialParams.BaudRate);
				printf("\n       ByteSize = %d", dcbSerialParams.ByteSize);
				printf("\n       StopBits = %d", dcbSerialParams.StopBits);
				printf("\n       Parity   = %d", dcbSerialParams.Parity);
			}
		
		/*------------------------------------ Setting Timeouts --------------------------------------------------*/
		
		COMMTIMEOUTS timeouts = { 0 };

		timeouts.ReadIntervalTimeout         = 50;
		timeouts.ReadTotalTimeoutConstant    = 50;
		timeouts.ReadTotalTimeoutMultiplier  = 10;
		timeouts.WriteTotalTimeoutConstant   = 50;
		timeouts.WriteTotalTimeoutMultiplier = 10;

		if (SetCommTimeouts(hComm, &timeouts) == FALSE)
			printf("\n   Error! in Setting Time Outs");
		else
			printf("\n\n   Setting Serial Port Timeouts Successfull");

		/*------------------------- Putting MAX485 chip in USB2SERIAL in Transmit Mode ---------------------------*/
		//                                                                                                        //
		//	----+			+-----------+              H  +-----------+                                           //
	    //		|			| 	    ~RTS| --------------> |~RE        |                                           //
		//	 PC |==========>| FT232     |                 |   MAX485  +(A,B)~~~~~~~~~~~~~~~>Data out(RS485)       //
		//	    |    USB    |       ~DTR| --------------> | DE        |        Twisted Pair                       //
		//  ----+			+-----------+              H  +-----------+                                           //
		//                                                                                                        //
		//--------------------------------------------------------------------------------------------------------//
		//TxMode - DE->High,~RE -> High
		
		
		Status = EscapeCommFunction(hComm, CLRDTR);// CLRDTR will make FT232 DTR  high (inverted),DE is HIGH for Transmission

		if (Status == TRUE)
			printf("\n\n    DE of MAX485 is High (Transmit Mode)");
		else
			printf("\n\n   Error! in EscapeCommFunction(hComm, CLRDTR)");

		Status = EscapeCommFunction(hComm, CLRRTS);// CLRRTS will make FT232 RTS  high (inverted)~RE is HIGH for Transmission

		if (Status == TRUE)
			printf("\n   ~RE of MAX485 is High (Transmit Mode)");
		else
			printf("\n   Error! in EscapeCommFunction(hComm, CLRRTS)");

		/*----------------------------- Writing a Character to Serial Port Continously----------------------------------------*/
		while(1)
		{
			dNoOFBytestoWrite = sizeof(lpBuffer); // Calculating the no of bytes to write into the port

			Status = WriteFile(hComm,               // Handle to the Serialport
							   lpBuffer,            // Data to be written to the port 
						       dNoOFBytestoWrite,   // No of bytes to write into the port
						       &dNoOfBytesWritten,  // No of bytes written to the port
						       NULL);
		
			if (Status == TRUE)
				printf("\n\n    %s - Written to %s", lpBuffer, ComPortName);
			else
				printf("\n\n   Error %d in Writing to Serial Port",GetLastError());
			
		int j= 0;
		for(j=0;j<99999999;j++);
		for(j=0;j<99999999;j++);
		}
		CloseHandle(hComm);//Closing the Serial Port
		printf("\n ==========================================\n");
		_getch();
	}
