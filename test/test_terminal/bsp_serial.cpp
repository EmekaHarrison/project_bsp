#include <string.h>
#include "bsp_serial.h"

#define IOBUF_SIZE 64

static char output[IOBUF_SIZE] = "";
static bool serial_init = false;
static char user_input = 0;

void bsp_serial_begin(void)
{
    serial_init = true;
}

int bsp_serial_available(void)
{
    return ((user_input == 0) ? 0 : 1);
}

char bsp_serial_read(void)
{
    char ch = user_input;
    user_input = 0;
    return ch;
}

void bsp_serial_print(const char *str)
{
    size_t len = strlen(str);

    for (size_t i = 0; i < sizeof(output); i++)
    {
        output[i] = (i < len) ? str[i] : 0;
    }
}

void bsp_set_user_input(char chr)
{
    user_input = chr;
}

bool bsp_get_serial_init(void)
{
    return serial_init;
}

char *bsp_get_serial_output(void)
{
    static char temp[IOBUF_SIZE] = "";

    strcpy(temp, output);
    memset(output, 0, sizeof(output));
    return temp;
}
