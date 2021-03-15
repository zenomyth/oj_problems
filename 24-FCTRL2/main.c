#include <stdio.h>
#include <stdlib.h>

struct {
    char payload[20000];
    int len;
} stream;
struct {
    char *start;
    int len;
} result[100];
struct {
    int payload[30];
    int len;
} num;

void multiply(int n)
{
    int i, j;
    int carry = 0;
    int temp;
    for (i = 0; i < num.len; ++i) {
        num.payload[i] = num.payload[i] * n + carry;
        carry = num.payload[i] / 10000000;
        num.payload[i] %= 10000000;
    }
    if (carry > 0)
        num.payload[num.len++] = carry;
    result[n].len = 0;
    result[n].start = &stream.payload[stream.len];
    for (i = 0; i < num.len; ++i) {
        temp = num.payload[i];
        for (j = 0; j < 7; ++j) {
            stream.payload[stream.len++] = 0x30 + temp % 10;
            ++result[n].len;
            temp /= 10;
            if (i == num.len - 1 && temp == 0)
                break;
        }
    }
}

void print(int n)
{
    int i;
    for (i = result[n].len - 1; i >= 0; --i)
        putc(result[n].start[i], stdout);
    putc('\n', stdout);
}

int main(int argc, char *argv[])
{
    int i;
    int t;
    int n;
    num.len = 1;
    num.payload[0] = 1;
    for (i = 1; i <= 100; ++i)
        multiply(i);
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        print(n);
    }
    exit(0);
}