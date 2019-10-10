#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base64.h"

int main(int argc, char **argv)
{
    unsigned char src[] = {0x01, 0x02, 0x00, 0x00, 0x04, 0x08, 0x00};
    size_t len;

    unsigned char *cipher = base64_encode(src, sizeof(src), &len);

    printf("(%lu) %s\n", len, cipher);

    unsigned char *plain = base64_decode(cipher, len, &len);

    size_t i;
    printf("(%lu) ", len);
    for (i = 0; i < len; i++) {
        if (i == len - 1)
            printf("0x%02x\n", plain[i]);
        else
            printf("0x%02x, ", plain[i]);
    }

    free(cipher);
    free(plain);

    return 0;
}

