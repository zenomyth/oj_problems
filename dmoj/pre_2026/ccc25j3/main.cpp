#include <cstdio>
#include <cctype>

using namespace std;

int main()
{
    int n;
    char code[1024];
    scanf("%d\n", &n);
    do {
        fgets(code, sizeof(code), stdin);
        int state = 0;
        int sign = 1;
        int t = 0;
        int num = 0;
        char upc[1024] = {'\0'};
        int idx_upc = 0;
        // printf("code is %s\n", code);
        for (int i = 0; i < (int)sizeof(code); ++i) {
            char c = code[i];
            if (c == '\0' || c == '\n')
                break;
            // printf("c=%c, state=%d\n", c, state);
            if (state == 1) {
                if (isdigit(c))
                    num = num * 10 + (c & 0xF);
                else {
                    t += num * sign;
                    sign = 1;
                    num = 0;
                    state = 0;
                }
            }
            if (state == 0) {
                if (c == '-') {
                    sign = -1;
                    state = 1;
                }
                else if (isupper(c))
                    upc[idx_upc++] = c;
                else if (isdigit(c)) {
                    num = c & 0xF;
                    state = 1;
                }
            }
        }
        upc[idx_upc] = '\0';
        if (state == 1)
            t += num * sign;
        printf("%s%d\n", upc, t);
    } while (--n > 0);
    return 0;
}
