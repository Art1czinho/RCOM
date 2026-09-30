// RCOM 2026/2027
//
// Link layer protocol implementation

#include "link_layer.h"
#include "serial_port.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

// MISC
#define _POSIX_SOURCE 1 // POSIX compliant source
#define BUF_SIZE 256
#define FLAG_VAL 0x7E
#define A_CMD    0x03 
#define C_SET    0x03
#define C_UA     0x07

////////////////////////////////////////////////
// LLOPEN
////////////////////////////////////////////////
int llOpenTx(LinkLayer llParameters)
{
    if (openSerialPort(llParameters.serialPort, llParameters.baudRate) < 0)
    {
        perror("openSerialPort");
        return -1;
    }
    printf("Serial port %s opened\n", llParameters.serialPort);
    
    // ENVIAR TRAMA SET
    unsigned char buf[5];
    buf[0] = FLAG_VAL;
    buf[1] = A_CMD;
    buf[2] = C_SET;
    buf[3] = buf[1] ^ buf[2];
    buf[4] = FLAG_VAL;

    int bytes = writeBytesSerialPort(buf, 5);
    printf("Sent SET frame (%d bytes)\n", bytes);

    // LER TRAMA UA
    unsigned char ua_buf[5];
    printf("Waiting for UA frame...\n");
    for (int i = 0; i < 5; i++) {
        readByteSerialPort(&ua_buf[i]);
    }
    printf("Received UA frame. Connection established.\n");

    sleep(1);

    // Close serial port (mantido aqui como no código base original)
    if (closeSerialPort() < 0)
    {
        perror("closeSerialPort");
        return -1;
    }
    printf("Serial port %s closed\n", llParameters.serialPort);

    return 0;
}

int llOpenRx(LinkLayer llParameters)
{
    if (openSerialPort(llParameters.serialPort, llParameters.baudRate) < 0)
    {
        perror("openSerialPort");
        return -1;
    }
    printf("Serial port %s opened\n", llParameters.serialPort);

    // LER TRAMA SET
    unsigned char set_buf[5];
    printf("Waiting for SET frame...\n");
    for (int i = 0; i < 5; i++) {
        readByteSerialPort(&set_buf[i]);
    }
    printf("Received SET frame.\n");

    // ENVIAR TRAMA UA
    unsigned char ua_buf[5];
    ua_buf[0] = FLAG_VAL;
    ua_buf[1] = A_CMD;
    ua_buf[2] = C_UA;
    ua_buf[3] = ua_buf[1] ^ ua_buf[2];
    ua_buf[4] = FLAG_VAL;

    int bytes = writeBytesSerialPort(ua_buf, 5);
    printf("Sent UA frame (%d bytes). Connection established.\n", bytes);

    // Close serial port (mantido aqui como no código base original)
    if (closeSerialPort() < 0)
    {
        perror("closeSerialPort");
        return -1;
    }
    printf("Serial port %s closed\n", llParameters.serialPort);

    return 0; 
}

////////////////////////////////////////////////
// LLSEND
////////////////////////////////////////////////
int llSend(const unsigned char *buf, int bufSize)
{
    // TODO: Implement this function
    return 0;
}

////////////////////////////////////////////////
// LLRECEIVE
////////////////////////////////////////////////
int llReceive(unsigned char *packet)
{
    // TODO: Implement this function
    return 0;
}

////////////////////////////////////////////////
// LLCLOSE
////////////////////////////////////////////////
int llCloseTx()
{
    // TODO: Implement this function
    return 0;
}

int llCloseRx()
{
    // TODO: Implement this function
    return 0;
}