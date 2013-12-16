#include <stdlib.h>

int main(int argc, char *argv[])
{
    sync();

    if (reboot(0x01234567) < 0) exit(1);

    return 0;
}
