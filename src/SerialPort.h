/**************************************************************************************************************************/
/* H SOURCE FILE                                                                                                          */
/**************************************************************************************************************************/
/* Project    : Serial Port
 * File Name  : SerialPort.h
 * Author     : Dhanush.K (dhanushsandy98@gmail.com)
 * Date       : 30/11/2021
 * 
 * Revised on : 30/11/2021
 * Version    : V0.0.1
 * 
 * Brief      : Serial Port Communication (RS232) for UNIX envernment.
 * 
 * Reference  : -> https://www.cmrr.umn.edu/~strupp/serial.html#basics
 * 
 */
/**************************************************************************************************************************/
/* Licence    : MIT
 * Copyright (c) 2021 Dhanush.K
 */
/**************************************************************************************************************************/
#ifndef _SERIALPORT_H_
#define _SERIALPORT_H_

/**************************************************************************************************************************/
/* Macro Declarations                                                                                                     */
/**************************************************************************************************************************/
#define MAX_BUFF 1024   // 1KB Data we can Transmit. Modify here to increase the size.

/**************************************************************************************************************************/
/* Typedef, Enums, Structures and Union Declarations                                                                      */
/**************************************************************************************************************************/
typedef unsigned char BYTE;

/**************************************************************************************************************************/
/* Global Variable Declarations                                                                                           */
/**************************************************************************************************************************/

/**************************************************************************************************************************/
/* Function Declarations                                                                                                  */
/**************************************************************************************************************************/
/**
 * @brief Initialize the serial port.
 * 
 * @param port      -> Serial port no. eg., /dev/ttyUSB0.
 * @param baudrate  -> Baudrate for the port.
 * @return int      -> File descriptor for the port.
 */
int init_serialPort(char *port, int baudrate);

/**
 * @brief Write data into the given serial port. Returns the no of bytes write into the serial port.
 *
 * @param fd        -> File descriptor for the port.
 * @param buffer    -> Message Buffer.
 * @return int      -> No of Bytes.
 */
int write_serialPort(int fd, char *buffer);

/**
 * @brief Read byte data from the given serial port.
 * 
 * @param fd        -> File descriptor for the port.
 * @return BYTE     -> Byte data from the serial port.
 */
BYTE read_serialPort(int fd);

#endif // _SERIALPORT_H_
/**************************************************************************************************************************/
/* End of File                                                                                                            */
/**************************************************************************************************************************/