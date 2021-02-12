#include <stdio.h>

int main(void)
{
    char line[64];
    char *p;
    int i;
    int base_in, base_out;
    unsigned int val;
    char out_str[8];
    int digit;

    out_str[7] = '\0';

    while ((p = fgets(line, sizeof line, stdin)) != NULL) {
        base_in = p[9] & 0xF;
        if (p[8] == 0x31)
            base_in += 10;
        base_out = p[12] & 0xF;
        if (p[11] == 0x31)
            base_out += 10;
        val = 0;
        for (i = 0; i <= 6; ++i) {
            val *= base_in;
            if (p[i] & 0x40)
                val += (p[i] & 0xF) + 9;
            else if ((p[i] & 0x30) == 0x30)
                val += p[i] & 0xF;
        }
        for (i = 6; i >= 0; --i) {
            digit = val % base_out;
            out_str[i] = digit < 10 ? (0x30 | digit) : (0x40 | (digit - 9));
            val /= base_out;
            if (val == 0)
                break;
        }
        while (--i >= 0)
            out_str[i] = ' ';
        if (val == 0)
            printf("%s\n", out_str);
        else
            printf("  ERROR\n");
    }

    return 0;
}
