        /*====================================================================================================*/
        /* USB to RS485 conversion  using USB2SERIAL (Write) (Transmitter Side) (Linux API)                   */
	/* using termios and ioctl() system call                                                              */
	/* Non Cannonical mode                                                                                */
	/*====================================================================================================*/

	/*====================================================================================================*/
	/* www.xanthium.in										      */
	/* Copyright (C) 2014 Rahul.S                                                                         */
	/*====================================================================================================*/

        /*====================================================================================================*/
	//                                                                                                    //
	//  |------------|                                                                                    //
	//  | RS485      |                                               +---------+     +-----------+        //
	//  | Write.exe  |             USB2SERIAL V2.0                   |       RO|---->|P1.1(RXD)  |        //
	//  |------------|            +--------------+                   |      ~RE|-----|P2.1       |        //
	//   \ [][][][][] \===========| USB -> RS485 |~~~~~~~~~~~~~~~~~~~|A,B      |     |           |        //
	//    \------------\   USB    +--------------+      Twisted      |       DE|-----|P2.0       |        //
	//        Laptop                                     Pair        |	 DI|<----|P1.2(TXD)  |        //
	//                                                               +---------+     +-----------+        //
	//                                                                  MAX485        MSP430G2553         //
	//                                                                                                    //
	//      [Transmitter] --------------------------------------->   [--------Reciever-----------]        //
	//                            direction of data                                                       //
	//====================================================================================================//
	// Pin Configuration for  USB2SERIAL V2.0 Board                                                       //
	//                                                                                                    //
	//  		+==========================================================+                          //
	//		|    +-----------+               +---------+               |                          //
	//  		|    |        TXD|-------------->|DI       |               |                          //
	// 	     +--|    |        RXD|---------------|RO      A|------+        |                          //
	//	USB  |	     |USB        |               |         |      |        |                          //
	// 	     +--|    |       ~RTS|-------------->|~RE     B|------|--+     |                          //
	//  		|    |	     ~DTR|-------------->|DE       |      |  |     |                          //
	//  		|    +-----------+               +---------+      |  |     |                          //
	//		|	FT232RL                    MAX485         |  |     |                          //
	//  		+================================================[A]=[B]===+                          //
	//                                                             RS485                                  //
	//                                                                                                    //
	//			                                                                              //
	//====================================================================================================//

	/*====================================================================================================*/
        /* Program writes a character to the serial port at 9600 bps 8N1 format                               */
	/* Baudrate - 9600                                                                                    */
	/* Stop bits -1                                                                                       */
	/* No Parity                                                                                          */
        /*----------------------------------------------------------------------------------------------------*/
	/* Compiler/IDE  : gcc 4.6.3                                                                          */
	/* Library       :                                                                                    */
	/* Commands      : gcc -o USB2SERIAL_RS485_Write_UX USB2SERIAL_RS485_Write_UX.c                       */
	/* OS            : Linux(x86) (Linux Mint 13 Maya)(Linux Kernel 3.x.x)                                */                              
	/* Programmer    : Rahul.S (c)                                                                        */
	/* Date	         : 31-December-2014                                                                   */
	/*====================================================================================================*/
	
	/*====================================================================================================*/
	/* Running the executable                                                                             */
	/* ---------------------------------------------------------------------------------------------------*/ 
	/* 1) Compile the USB2SERIAL_RS485_Write_UX.c  file using gcc on the terminal (without quotes)        */
        /*                                                                                                    */
	/*	" gcc -o USB2SERIAL_RS485_Write_UX USB2SERIAL_RS485_Write_UX.c "                              */
	/*                                                                                                    */
        /* 2) Linux will not allow you to access the serial port from user space,you have to be root.So use   */
        /*    "sudo" command to execute the compiled binary as super user.                                    */
        /*                                                                                                    */
        /*       "sudo ./USB2SERIAL_RS485_Write_UX"                                                           */
	/*                                                                                                    */
	/*====================================================================================================*/

	/*====================================================================================================*/
	/* Sellecting the Serial port Number on Linux                                                         */
	/* ---------------------------------------------------------------------------------------------------*/ 
	/* /dev/ttyUSBx - when using USB to Serial Converter, where x can be 0,1,2...etc                      */
	/* /dev/ttySx   - for PC hardware based Serial ports, where x can be 0,1,2...etc                      */
        /*====================================================================================================*/
	
	/*-------------------------------------------------------------*/
    	/* termios structure -  /usr/include/asm-generic/termbits.h    */ 
	/* use "man termios" to get more info about  termios structure */
	/*-------------------------------------------------------------*/

	/*==================================*/
	/*       MODEM bits                 */
	/*------------------- --------------*/
	/*   TIOCM_DTR --- DTR Line         */
	/*   TIOCM_RTS --- RTS Line         */
	/*==================================*/

    	#include <stdio.h>
    	#include <fcntl.h>       /* File Control Definitions           */
    	#include <termios.h>     /* POSIX Terminal Control Definitions */
    	#include <unistd.h>      /* UNIX Standard Definitions 	       */ 
    	#include <errno.h>       /* ERROR Number Definitions           */
	#include <sys/ioctl.h>   /* ioctl()                            */

    	void main(void)
    	{
        	int fd;/*File Descriptor*/
		
		printf("\n +----------------------------------+");
		printf("\n |        USB To RS485 Write        |");
		printf("\n +----------------------------------+");

		/*------------------------------- Opening the Serial Port -------------------------------*/

		/* Change /dev/ttyUSB0 to the one corresponding to your system */

        	fd = open("/dev/ttyUSB0",O_RDWR | O_NOCTTY);	/* ttyUSB0 is the FT232 based USB2SERIAL Converter   */
			   						/* O_RDWR Read/Write access to serial port           */
									/* O_NOCTTY - No terminal will control the process   */
									                                
									
        	if(fd == -1)						/* Error Checking */
            	   printf("\n  Error! in Opening ttyUSB0  ");
        	else
            	   printf("\n  ttyUSB0 Opened Successfully ");

	
		/*---------- Setting the Attributes of the serial port using termios structure --------- */
		
		struct termios SerialPortSettings;	/* Create the structure                          */

		tcgetattr(fd, &SerialPortSettings);	/* Get the current attributes of the Serial port */

		cfsetispeed(&SerialPortSettings,B9600); /* Set Read  Speed as 9600                       */
		cfsetospeed(&SerialPortSettings,B9600); /* Set Write Speed as 9600                       */

		SerialPortSettings.c_cflag &= ~PARENB;   /* Disables the Parity Enable bit(PARENB),So No Parity   */
		SerialPortSettings.c_cflag &= ~CSTOPB;   /* CSTOPB = 2 Stop bits,here it is cleared so 1 Stop bit */
		SerialPortSettings.c_cflag &= ~CSIZE;	 /* Clears the mask for setting the data size             */
		SerialPortSettings.c_cflag |=  CS8;      /* Set the data bits = 8                                 */
	
		SerialPortSettings.c_cflag &= ~CRTSCTS;       /* No Hardware flow Control                         */
		SerialPortSettings.c_cflag |= CREAD | CLOCAL; /* Enable receiver,Ignore Modem Control lines       */ 
		
		
		SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY);          /* Disable XON/XOFF flow control both i/p and o/p */
		SerialPortSettings.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);  /* Non Cannonical mode                            */

		SerialPortSettings.c_oflag &= ~OPOST;/*No Output Processing*/

		if((tcsetattr(fd,TCSANOW,&SerialPortSettings)) != 0) /* Set the attributes to the termios structure*/
		    printf("\n  ERROR ! in Setting attributes");
		else
                    printf("\n  BaudRate = 9600 \n  StopBits = 1 \n  Parity   = none");

		/*---------------------------------------- Controlling RTS and DTR Pins --------------------------------------*/
		/* ~RTS(USB2SERIAL) ---> ~RE(MAX485) */
		/* ~DTR(USB2SERIAL) --->  DE(MAX485) */
		
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

		int RTS_flag,DTR_flag;

		RTS_flag = TIOCM_RTS;	/* Modem Constant for RTS pin */
		DTR_flag = TIOCM_DTR;	/* Modem Constant for DTR pin */

		ioctl(fd,TIOCMBIC,&RTS_flag);/* ~RTS = 1,So ~RE pin of MAX485 is HIGH                       */
		ioctl(fd,TIOCMBIC,&DTR_flag);/* ~DTR = 1,So  DE pin of MAX485 is HIGH,Transmit Mode enabled */ 

	        /*------------------------------- Write data to serial port -----------------------------*/

		char write_buffer[] = "A";	/* Buffer containing characters to write into port	     */	
		int  bytes_written  = 0;  	/* Value for storing the number of bytes written to the port */ 

		bytes_written = write(fd,write_buffer,sizeof(write_buffer));/* use write() to send data to port                                            */
									     /* "fd"                   - file descriptor pointing to the opened serial port */
									     /*	"write_buffer"         - address of the buffer containing data	            */
									     /* "sizeof(write_buffer)" - No of bytes to write                               */	
		printf("\n  %s written to ttyUSB0",write_buffer);
		printf("\n  %d Bytes written to ttyUSB0", bytes_written);
		printf("\n +----------------------------------+\n\n");

		close(fd);/* Close the Serial port */

    	}

