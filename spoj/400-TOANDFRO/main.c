#include <stdio.h>

int main(void)
{
    int col_num;
    char msg[256];
    int msg_len;
    int i;
    int j;

    for(;;) {
        fgets(msg, sizeof(msg), stdin);
        col_num = 0;
        for (i = 0; i < (int)sizeof(msg) && (msg[i] & 0x30) == 0x30; ++i)
            col_num = col_num * 10 + (msg[i] & 0xF);
        if (col_num == 0)
            break;
        fgets(msg, sizeof(msg), stdin);
        for (i = 0; i < (int)sizeof(msg); ++i) {
            if ((msg[i] & 0x60) != 0x60)
                break;
        }
        msg_len = i;
        for (i = 0; i < col_num; ++i) {
            for (j = 0; j < msg_len; j += 2 * col_num) {
                fputc(msg[j + i], stdout);
                if (j + 2 * col_num - i - 1 >= msg_len)
                    break;
                fputc(msg[j + 2 * col_num - i - 1], stdout);
            }
        }
        fputc('\n', stdout);
    }

    return 0;
}
