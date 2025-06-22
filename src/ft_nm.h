#ifndef FT_NM_H
# define FT_NM_H

# include <elf.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/mman.h>
# include <unistd.h>

typedef struct {
    char    *path;
    char    *content;
    size_t  size;
    int     class;
    int     endian;
} t_elf_file;

typedef struct {
    char            type;
    unsigned long   value;
    char            *name;
} t_symbol;

int print_error(char *error);

int process_elf32(char* content);
int process_elf64();

char    *extract_fom_content(unsigned long offset);

#endif /* FT_NM_H */