#include <cstdio>
#include <cstdint>
#include <cinttypes>
#include <cctype>

using namespace std;

int64_t get_uncompressed_str_len(const char *rle_str)
{
    int64_t len = 0, sub_len = 0;
    for (int i = 0; rle_str[i] != '\n' && rle_str[i] != '\0'; ++i) {
        if (islower(rle_str[i])) {
            len += sub_len;
            sub_len = 0;
        }
        else if (isdigit(rle_str[i]))
            sub_len = sub_len * 10 + (rle_str[i] & 0x0F);
    }
    return len + sub_len;
}

char char_at_pos(const char *rle_str, int64_t pos)
{
    int64_t len = 0, sub_len = 0;
    char cur_char = '\0';
    for (int i = 0; rle_str[i] != '\n' && rle_str[i] != '\0'; ++i) {
        if (islower(rle_str[i])) {
            len += sub_len;
            sub_len = 0;
            if (len > pos)
                return cur_char;
            cur_char = rle_str[i];
        }
        else if (isdigit(rle_str[i]))
            sub_len = sub_len * 10 + (rle_str[i] & 0x0F);
    }
    return cur_char;
}

int main()
{
    static char rle_str[200002];
    int64_t c;
    fgets(rle_str, sizeof(rle_str), stdin);
    scanf("%" SCNd64, &c);
    int64_t len = get_uncompressed_str_len(rle_str);
    // printf("%" PRId64 "\n", len);
    int64_t pos = c % len;
    // printf("%" PRId64 "\n", pos);
    char result = char_at_pos(rle_str, pos);
    printf("%c\n", result);
    return 0;
}
