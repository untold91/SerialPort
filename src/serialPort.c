/**************************************************************************************************************************/
/* C SOURCE FILE                                                                                                          */
/**************************************************************************************************************************/
/* Project    : Serial Port
 * File Name  : SerialPort.c
 * Author     : Dhanush.K (dhanushsandy98@gmail.com)
 * Date       : 30/11/2021
 *
 * Revised on : 30/11/2021
 * Version    : V0.0.1
 *
 * Brief      : Serial Port Communication (RS232) for UNIX environment.
 *
 * Reference  : -> https://www.cmrr.umn.edu/~strupp/serial.html#basics
 *
 */
/**************************************************************************************************************************/
/* Licence    : MIT
 * Copyright (c) 2021 Dhanush.K
 */
/**************************************************************************************************************************/
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

#include "serialPort.h"

// #define DEBUGPRINT

#ifdef DEBUGPRINT
#include <stdarg.h>
#endif

#define CFILE "SERIAL.C"

/**************************************************************************************************************************/
/* Macro Declarations                                                                                                     */
/**************************************************************************************************************************/
#define ZERO 0
#define NUL 0
#define ONE 1

/**************************************************************************************************************************/
/* Typedef, Enums, Structures and Union Declarations                                                                      */
/**************************************************************************************************************************/

/**************************************************************************************************************************/
/* Global Variable Declarations                                                                                           */
/**************************************************************************************************************************/

/**************************************************************************************************************************/
/* Function Declarations                                                                                                  */
/**************************************************************************************************************************/
int open_serialPort(char *port);
void config_serialPort(int fd, int baudrate);
int convert_baudrate(int baudrate);

static void logger(const char *format, ...);

/**************************************************************************************************************************/
/* Main Program                                                                                                           */
/**************************************************************************************************************************/

// Nothing to Do.

/**************************************************************************************************************************/
/* Function Definations                                                                                                   */
/**************************************************************************************************************************/
/**
 * @brief Initialize the serial port.
 *
 * @param port      -> Serial port no. eg., /dev/ttyUSB0.
 * @param baudrate  -> Baudrate for the port.
 * @return int      -> File descriptor for the port.
 */
int init_serialPort(char *port, int baudrate)
{
    logger("Initializing the serial port.\n");

    // Open Serial Port
    int fd = open_serialPort(port);

    if (fd != SERIAL_PORT_FAILED)
        // Config Serial Port
        config_serialPort(fd, baudrate);

    return fd;
}

/**
 * @brief Open given serial port. Returns the file descriptor on success or -1 on error.
 *
 * @param port      -> Serial port no. eg., /dev/ttyUSB0.
 * @return int      -> File descriptor for the port.
 */
int open_serialPort(char *port)
{
    int fd; /* File descriptor for the port */

    fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == SERIAL_PORT_FAILED)
    {
        // Could not open the port.
        logger("open_port: Unable to open %s - \n", port);
    }
    else
    {
        logger("Serial Port Opened.\n");

        // Setting up the Receive port till the complete byte receive.
        fcntl(fd, F_SETFL, ZERO);
    }

    return fd;
}

/**
 * @brief Open given serial port.
 *
 * @param fd        -> File descriptor for the port.
 * @param baudrate  -> Baudrate for the port.
 */
void config_serialPort(int fd, int baudrate)
{
    logger("Configuring the serial port.\n");

    // Setting up the serial port options...
    struct termios options;

    // Get the current options for the port...
    tcgetattr(fd, &options);

    // ***Set the given baud rates...
    int BRate = convert_baudrate(baudrate);
    cfsetispeed(&options, BRate);
    cfsetospeed(&options, BRate);

    // ***Enable the receiver and set local mode...
    options.c_cflag |= (CLOCAL | CREAD);

    // Setting the Character Size...
    options.c_cflag &= ~CSIZE; /* Mask the character size bits */
    options.c_cflag |= CS8;    /* Select 8 data bits */

    // Setting Parity Checking...
    // No parity (8N1)
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;

    // Setting Hardware Flow Control...
    options.c_cflag &= ~CRTSCTS; // Disable Hardware Control Flow.

    // ***Set the new options for the port...
    tcsetattr(fd, TCSANOW, &options);
}

/**
 * @brief Write data into the given serial port. Returns the no of bytes write into the serial port.
 *
 * @param fd        -> File descriptor for the port.
 * @param buffer    -> Message Buffer.
 * @return int      -> No of Bytes.
 */
int write_serialPort(int fd, char *buffer)
{
    int bytes;
    int len = strlen(buffer);

    if (len <= MAX_BUFF)
    {
        bytes = write(fd, buffer, len);
        if (bytes < ZERO)
        {
            // Could not write into the port.
            logger("Error Writing the %d Bytes!\n", len);
        }
        else
        {
            logger("%d Bytes Write into the Port Successfully.\n", len);
        }
        return bytes;
    }
    else
    {
        logger("Buffer Overloaded %d Bytes!, Max Buff Size is: %d Bytes\n", len, MAX_BUFF);
        return SErIAL_BUFF_OVERLOAD;
    }
}

/**
 * @brief Read byte data from the given serial port.
 *
 * @param fd        -> File descriptor for the port.
 * @return BYTE     -> Byte data from the serial port.
 */
BYTE read_serialPort(int fd)
{
    int bytes;
    BYTE rxByte;

    bytes = read(fd, &rxByte, ONE);

    if (bytes <= ZERO)
    {
        // Could not read the port.
        logger("Error Reading the Bytes!\n");
        return NUL;
    }
    else
    {
        return rxByte;
    }
}

/**
 * @brief Returns the actual macro for the given Baudrate.
 *
 * @param baudrate  -> Baudrate in Decimal.
 * @return int      -> Actual baudrate Macro.
 */
int convert_baudrate(int baudrate)
{
    int BRate;
    switch (baudrate)
    {
    case 4800:
        BRate = B4800;
        break;

    case 9600:
        BRate = B9600;
        break;

    case 19200:
        BRate = B19200;
        break;

    case 38400:
        BRate = B38400;
        break;

    case 57600:
        BRate = B57600;
        break;

    case 115200:
        BRate = B115200;
        break;

    case 230400:
        BRate = B230400;
        break;

    default:
        BRate = B0;
        break;
    }
    return BRate;
}

/*-------------------------------------------------------------------------------------------------*/
/**
 * @brief Debug log function
 *
 * @param format    -> Print data format based on standard stdio.
 * @param ...
 */
static void logger(const char *format, ...)
{
#ifdef DEBUG
    printf("[%s]", "DBUG");

    va_list arg;
    va_start(arg, format);
    vprintf(format, arg);
    va_end(arg);

    printf("\r\n");
#endif
}
/**************************************************************************************************************************/
/* End of File                                                                                                            */
/**************************************************************************************************************************/