#include "aardvark.h"
#include <stdio.h>

int main()
{
    u16 ports[16];
    int num = aa_find_devices(16, ports);
    if (num <= 0)
    {
        printf("No Aardvark adapters founddddd.\n");
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
    aa_close(handle);
    return 0;
}
