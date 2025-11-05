#include "ft_nm.h"

extern t_flags  g_flags;

void    close_fd(int *fd) {
    if (*fd > 0)
        close(*fd);
}

void    unmap_file(t_string *mapped_file) {
    if (mapped_file->content != NULL)
        munmap(mapped_file->content, mapped_file->size);
}

void    free_file_paths(char ***file_paths) {
    if (*file_paths != NULL)
        free(*file_paths);
}

void    free_symbols(t_sym_info ***symbols_info) {
    if (symbols_info == NULL || *symbols_info == NULL)
        return;
    for (int i = 0; (*symbols_info)[i] != NULL; i++) {
        free((*symbols_info)[i]->value);
        free((*symbols_info)[i]);
    }
    free(*symbols_info);
}

void    sort_symbols(t_sym_info **symbols_info) {
    t_sym_info  temp;
    int         diff;

    for (int i = 0; symbols_info[i] != NULL; i++) {
        for (int j = 0; symbols_info[j] != NULL; j++) {
            if (symbols_info[j + 1] == NULL)
                break;
            diff = ft_strcmp(symbols_info[j]->name, symbols_info[j + 1]->name);
            if ((diff > 0 && !g_flags.reverse_sort) || (diff < 0 && g_flags.reverse_sort)) {
                temp = *symbols_info[j + 1];
                *symbols_info[j + 1] = *symbols_info[j];
                *symbols_info[j] = temp;
            }
        }
    }
}
