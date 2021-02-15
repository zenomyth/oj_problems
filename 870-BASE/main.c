#include <stdio.h>

int main(void)
{
    char line[64];
    char *p;
    int i;
    int num[64];
    int weight;
    int base_in, base_out;
    unsigned int val;
    char out_str[8];
    int digit;

    out_str[7] = '\0';

    while ((p = fgets(line, sizeof line, stdin)) != NULL) {
        for (i = 0; p[i] != '\0'; ++i) {
            if (p[i] & 0x40)
                num[i] = (p[i] & 0xF) + 9;
            else if ((line[i] & 0x30) == 0x30)
                num[i] = p[i] & 0xF;
            else
                num[i] = -1;
        }
        --i;
        while (num[i] == -1)
            --i;
        base_out = 0;
        weight = 1;
        while (num[i] != -1) {
            base_out += num[i] * weight;
            weight *= 10;
            --i;
        }
        while (num[i] == -1)
            --i;
        base_in = 0;
        weight = 1;
        while (num[i] != -1) {
            base_in += num[i] * weight;
            weight *= 10;
            --i;
        }
        while (num[i] == -1)
            --i;
        val = 0;
        weight = 1;
        while (i >= 0 && num[i] != -1) {
            val += num[i] * weight;
            weight *= base_in;
            --i;
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
