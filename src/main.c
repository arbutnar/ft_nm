#include "ft_nm.h"

t_flags g_flags = { 0 };

int get_file_fd(char *file_path) {
    int fd;

    fd = open(file_path, O_RDONLY);
    if (fd < 0)
        ft_dprintf(STDERR_FILENO, "nm: '%s': No such file\n", file_path);
    return fd;
}

size_t   get_file_size(int fd, char *file_path) {
    struct stat file_info;

    if (fstat(fd, &file_info) < 0) {
        ft_dprintf(STDERR_FILENO, "nm: '%s': %s\n", file_path, strerror(errno));
        return 0;
    }
    if (S_ISDIR(file_info.st_mode)) {
        ft_dprintf(STDERR_FILENO, "nm: Warning: '%s' is a directory\n", file_path);
        return 0;
    }
    return file_info.st_size;
}

char    *get_file_content(int fd, size_t file_size) {
    void    *map;

    map = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (map == NULL || map == MAP_FAILED)
        return NULL;
    return (char *) map;
}

int check_content(t_string mapped_file) {
    char    *content = mapped_file.content;
    size_t  size = mapped_file.size;

    if (size < sizeof(Elf32_Ehdr) ||
        content[0] != 0x7f || content[1] != 'E' ||
        content[2] != 'L' || content[3] != 'F') {
        return 1;
    }
    if(content[EI_CLASS] != ELFCLASS32 && content[EI_CLASS] != ELFCLASS64)
        return 1;
    if (content[EI_CLASS] == ELFCLASS64 && size < sizeof(Elf64_Ehdr))
        return 1;
    if (content[EI_DATA] != ELFDATA2LSB && content[EI_DATA] != ELFDATA2MSB)
        return 1;
    if (content[EI_VERSION] != EV_CURRENT)
        return 1;
    return 0;
}

int ft_nm(char *file_path) {
    int         fd __attribute__ ((cleanup(close_fd)));
    t_string    mapped_file __attribute__ ((cleanup(unmap_file))) = { 0 };
    t_sym_info  **symbols_info __attribute__ ((cleanup(free_symbols))) = { 0 };

    fd = get_file_fd(file_path);
    if (fd < 0)
        return 1;

    mapped_file.size = get_file_size(fd, file_path);
    if (mapped_file.size == 0)
        return 1;
    mapped_file.content = get_file_content(fd, mapped_file.size);
    if (check_content(mapped_file)) {
        ft_dprintf(STDERR_FILENO, "nm: %s: file format not recognized\n", file_path, strerror(errno));
        return 1;
    }
    g_flags.endian_match = define_endianess(mapped_file.content[EI_DATA]);

    symbols_info = (mapped_file.content[EI_CLASS] == ELFCLASS32) ? 
       x32_get_symbols_info(mapped_file) : x64_get_symbols_info(mapped_file);
    if (symbols_info == NULL)
        return 1;
    if (symbols_info[0] == NULL) {
        ft_dprintf(STDERR_FILENO, "nm: %s: no symbols\n", file_path);
        return 0;
    }

    if (!g_flags.no_sort)
        sort_symbols(symbols_info);
    print_symbols_info(symbols_info, file_path, mapped_file.content[EI_CLASS]);
    return 0;
}

char    *handle_long_flag(char *flag) {
    char    *long_flags[] = {"--debug-syms", "--extern-only", "--undefined-only", "--reverse-sort", "--no-sort"};
    char    *short_flags[] = {"-a", "-g", "-u", "-r", "-p"};
    int     size, i;

    size = sizeof(long_flags) / sizeof(char *);
    for (i = 0; i < size; i++) {
        if (ft_strcmp(flag, long_flags[i]) == 0)
            return short_flags[i];
    }

    ft_dprintf(STDERR_FILENO, "nm: unrecognized option \'%s\'\n", flag);
    return NULL;
}

int     set_flags(char *flags) {
    for (int i = 1; flags[i] != '\0'; i++) {
        switch(flags[i]) {
            case '-':
                flags = handle_long_flag(flags);
                if (flags == NULL)
                    return 1;
                i = 0;
                break;
            case 'a':
                g_flags.all = 1; break;
            case 'g':
                g_flags.external = 1; break;
            case 'u':
                g_flags.undefined = 1; break;
            case 'r':
                g_flags.reverse_sort = 1; break;
            case 'p':
                g_flags.no_sort = 1; break;
            default:
                ft_dprintf(STDERR_FILENO, "nm: invalid option -- \'%c\'\n", flags[i]);
                return 1;
        }
    }
    return 0;
}

char    **process_arguments(int argc, char *argv[]) {
    char    **file_paths;
    int     end_of_options, k;

    k = 0;
    end_of_options = 0;
    file_paths = malloc(sizeof(char *) * (argc + 1));

    for (int i = 1; i < argc; i++) {
        if (!end_of_options && ft_strcmp(argv[i], "--") == 0)
            end_of_options = 1;
        else if (!end_of_options && (argv[i][0] == '-' && argv[i][1] != '\0')) {
            if (set_flags(argv[i]))
                return NULL;
        }
        else {
            file_paths[k] = argv[i];
            k++;
        }
    }
    if (k == 0)
        file_paths[k++] = "a.out";
    file_paths[k] = NULL;
    if (k > 1)
        g_flags.path = 1;

    return file_paths;
}

int main(int argc, char *argv[]) {
    int     exit_status = 0;
    char    **file_paths __attribute__((cleanup(free_file_paths)));

    file_paths = process_arguments(argc, argv);
    if (file_paths == NULL)
        return 1;
    for (int i = 0; file_paths[i] != NULL; i++)
        exit_status = ft_nm(file_paths[i]) || exit_status;

    return exit_status;
}
