// File: src/main.c
#include <stdio.h>
#include <stdlib.h>
#include "aardvark.h"
#define I2C_BITRATE 100
#define SLAVE_ADDR 0x50
int main(void)
{
    Aardvark handle = aa_open(0);
    if (handle <= 0)
    {
        fprintf(stderr, "Unable to open Aardvark adapter: %d\n", handle);
        return EXIT_FAILURE;
    }
    aa_configure(handle, AA_CONFIG_SPI_I2C);
    aa_i2c_pullup(handle, AA_I2C_PULLUP_BOTH);
    aa_i2c_bitrate(handle, I2C_BITRATE);
    unsigned char data_out[2] = {0x00, 0x00};
    int tx = aa_i2c_write(handle, SLAVE_ADDR, AA_I2C_NO_FLAGS, 2, data_out);
    if (tx < 0)
    {
        fprintf(stderr, "I2C write error: %d\n", tx);
        aa_close(handle);
        return EXIT_FAILURE;
    }
    aa_i2c_read(handle, SLAVE_ADDR, AA_I2C_NO_FLAGS, 0, data_out);
    unsigned char data_in[2];
    int rx = aa_i2c_read(handle, SLAVE_ADDR, AA_I2C_NO_FLAGS, 2, data_in);
    if (rx < 0)
    {
        fprintf(stderr, "I2C read error: %d\n", rx);
        aa_close(handle);
        return EXIT_FAILURE;
    }
    printf("Read %d bytes: 0x%02X 0x%02X\n", rx, data_in[0], data_in[1]);
    aa_close(handle);
    return EXIT_SUCCESS;
}