# _Serial Port_

Serial Port Driver Application for UNIX system. Use `init_serialPort` function to initialize the serial port, `write_serialPort` to Send data to the Port and Impliment your own handler for Read the data from the port useing `read_serialPort` which actually returns the byte by byte data. Example Application require two arguments, first one is baudrate and second one is the port as follows,
 >```~$: <Build dir>/SERIAL_PORT_APP 115200 /dev/ttyUSB0```

### Build & Run

```sh
~$: make

~$: make run
```

[**CHANGELOG**](CHANGELOG.md)

### LICENCE

[**MIT**](LICENSE)

#### Contact,

<p align="left"><img src="markdownSrc/DK_Logo.jpg" alt="Mark Text" width="40"></p>

dhanushsandy91@gmail.com | Dhanush.K