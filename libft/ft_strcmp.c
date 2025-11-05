#include "libft.h"

int ft_strcmp(const char *s1, const char *s2) {
    while (*s1 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }
    if (*s2 != '\0')
        return (-1);
    return (*s1 > *s2);
}
