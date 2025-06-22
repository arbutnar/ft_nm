#include "ft_nm.h"

extern t_elf_file g_elf_file;

int set_content(void *map) {
    char *content;

    content = (char *) map;
    if (g_elf_file.size < sizeof(Elf32_Ehdr) ||
        content[0] != 0x7f || content[1] != 'E' ||
        content[2] != 'L' || content[3] != 'F') {
        return 1;
    }
    if(content[EI_CLASS] != ELFCLASS32 && content[EI_CLASS] != ELFCLASS64)
        return 1;
    if (content[EI_CLASS] == ELFCLASS64 && g_elf_file.size < sizeof(Elf64_Ehdr))
        return 1;
    if (content[EI_DATA] != ELFDATA2LSB && content[EI_DATA] != ELFDATA2MSB)
        return 1;
    if (content[EI_VERSION] != EV_CURRENT)
        return 1;
    g_elf_file.content = content;
    g_elf_file.class = content[EI_CLASS];
    g_elf_file.endian = content[EI_DATA];
    return 0;
}

void    *map_file(char *file_path) {
    int     fd;
    struct  stat file_info;
    void    *map;

    g_elf_file.path = file_path;
    fd = open(file_path, O_RDONLY);
    if (fd == -1)
        return NULL;
    if (fstat(fd, &file_info) < 0)
        return NULL;
    if (S_ISDIR(file_info.st_mode))
        return NULL;
    g_elf_file.size = file_info.st_size;
    map = mmap(NULL, file_info.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    return map;
}

int ft_nm(char *file_path) {
    void    *map;
    int     ret;

    map = map_file(file_path);
    if (map == MAP_FAILED)
        return print_error("can't be mapped");
    if (set_content((char *) map)) {
        munmap(map, g_elf_file.size);
        return print_error("file format not recognized");
    }
    ret = process_elf64();
    munmap(map, g_elf_file.size);
    return ret;
}

int main(int argc, char *argv[]) {
    int exit_status = 0;

    if (argc < 2)
        return ft_nm("a.out");
    for (int i = 1; i < argc; i++)
        exit_status = ft_nm(argv[i]) || exit_status;

    return exit_status;
}