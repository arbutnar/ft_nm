#include "ft_nm.h"

extern t_elf_file g_elf_file;

int print_error(char *error) {
    fprintf(stderr, "ft_nm: '%s': %s\n", g_elf_file.path, error);
    return (1);
}

char    *extract_fom_content(unsigned long offset) {
    if (offset == 0 || offset >= g_elf_file.size)
        return NULL;
    return g_elf_file.content;
}