#include <stdlib.h>
#include <stdint.h>

int64_t extract(int64_t value, int bit, int length) {
    int64_t res = (value >> bit);
    int64_t mask = 1;

    for (int i = 0; i < length; i++) {
        mask <<= 1;
        mask += 1;
    }
    res &= mask;

    length -= 1;
    int64_t some = (res >> length) & 1;

    if (some == 0) {
        return res;
    }
    mask >>= 1;
    mask = ~mask;

    res |= mask;

    return res;
}
