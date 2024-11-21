#include <string.h>

#include "../include/utils.h"

void ModifyString(char *str) {
    char *dst = str;
    while (*str) {
        if (*str != 'a' && *str != 'e' && *str != 'i' && *str != 'o' && *str != 'u' &&
            *str != 'A' && *str != 'E' && *str != 'I' && *str != 'O' && *str != 'U') {
            *dst++ = *str;
        }
        str++;
    }
    *dst = '\0';
}