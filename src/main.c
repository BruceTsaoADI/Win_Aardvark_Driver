#include "aardvark.h"
#include <stdio.h>

int main()
{
    u16 ports[16];
    int num = aa_find_devices(16, ports);
    if (num <= 0)
    {
        printf("No Aardvark adapters found.\n");
        return 1;
    }
    printf("Found %d Aardvark adapter(s).\n", num);

    int handle = aa_open(ports[0]);
    if (handle <= 0)
    {
        printf("Unable to open Aardvark adapter: %d\n", handle);
        return 1;
    }
    printf("Aardvark adapter opened successfully, handle=%d\n", handle);

    // 設定為I2C主機模式
    aa_configure(handle, AA_CONFIG_SPI_I2C);   // 啟用I2C
    aa_i2c_pullup(handle, AA_I2C_PULLUP_BOTH); // 開啟內建上拉
    aa_i2c_bitrate(handle, 100);               // 設定I2C時脈為100kHz

    // 要送出的資料
    u08 data_out[3] = {0x71, 0xA4, 01};
    // I2C slave address（7-bit）
    u16 slave_addr = 0x20;

    // 寫入資料
    int count = aa_i2c_write(handle, slave_addr, AA_I2C_NO_FLAGS, 3, data_out);
    if (count < 0)
    {
        printf("I2C寫入錯誤，錯誤碼: %d\n", count);
    }
    else if (count == 0)
    {
        printf("I2C寫入失敗，沒有任何byte被寫入。\n");
    }
    else
    {
        printf("I2C成功寫入 %d bytes。\n", count);
    }

    aa_close(handle);
    return 0;
}
