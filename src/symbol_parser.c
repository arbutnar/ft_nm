#include "ft_nm.h"

extern t_elf_file g_elf_file;

char    *x_(get_value)(Elf_Sym symbol) {
    char        *str;
    const char  *hex_digits = "0123456789abcdef";
    Elf_Addr    st_value;

    str = malloc(Elf_Addr_len + 1);
    if (!str)
        return NULL;
    st_value = resolve_endianess(symbol.st_value);

    for (int i = Elf_Addr_len - 1; i >= 0; i--) {
        if (resolve_endianess(symbol.st_shndx) == SHN_UNDEF) {
            str[i] = ' ';
            continue;
        }
        str[i] = hex_digits[st_value & 0xF];
        st_value >>= 4;
    }
    str[Elf_Addr_len] = '\0';
    return str;
}

char x_(get_type)(Elf_Sym symbol, Elf_Shdr *sh_arr) {
    unsigned char   bind, type;
    uint16_t        st_shndx;
    Elf64_Xword     sh_flags, sh_type;
    char            c = '?';

    bind = ELF_ST_BIND(symbol.st_info);
    type = ELF_ST_TYPE(symbol.st_info);
    st_shndx = resolve_endianess(symbol.st_shndx);

    if (type == STT_SECTION || type == STT_FILE)
        return '\0';
    // if (type == STT_FILE)
    //     c = 'f';
    // else if (type == STT_SECTION)
    //     c = 's';
    if (st_shndx == SHN_UNDEF)
        c = (bind == STB_WEAK) ? 'w' : 'U';
    else if (st_shndx == SHN_ABS)
        c = 'A';
    else if (st_shndx == SHN_COMMON)
        c = 'C';
    else if (sh_arr && st_shndx < SHN_LORESERVE) {
        sh_flags = resolve_endianess(sh_arr[st_shndx].sh_flags);
        sh_type = resolve_endianess(sh_arr[st_shndx].sh_type);

        if (type == STT_FUNC || (type == STT_NOTYPE && sh_flags & SHF_EXECINSTR))
            c = 'T';
        else if (sh_type == SHT_NOBITS)
            c = 'B';
        else if (sh_flags & SHF_WRITE)
            c = 'D';
        else
            c = 'R';
    }

    if (bind == STB_WEAK && st_shndx != SHN_UNDEF)
        c = (c == 'T') ? 'V' : 'W';
    else if (bind == STB_LOCAL && c != 'U' && c != 'w')
        c += ('a' - 'A');
    return c;
}

char    *x_(get_name)(Elf_Sym symbol, char *names) {
    uint32_t    st_name;

    st_name = resolve_endianess(symbol.st_name);
    if (st_name == 0)
        return NULL;
    return names + st_name;
}

t_sym_info  *x_(get_symbols_info)(Elf_Sym *sym_arr, size_t *n_sym, Elf_Shdr *strtab, Elf_Shdr *sh_arr) {
    char        *names;
    t_sym_info  *sym_info_arr;
    size_t      j;

    names = g_elf_file.content + resolve_endianess(strtab->sh_offset);
    sym_info_arr = malloc(sizeof(t_sym_info) * (*n_sym));
    if (!sym_info_arr)
        return NULL;

    j = 0;
    for (size_t i = 1; i < *n_sym; i++) {
        t_sym_info sym_info;
        sym_info.type = x_(get_type)(sym_arr[i], sh_arr);
        int x = sym_arr[i].st_shndx;
        if (x < SHN_LORESERVE)
            printf("%c, %s\n", sym_info.type, sh_arr[x].sh_name);
        sym_info.name = x_(get_name)(sym_arr[i], names);
        if (sym_info.type == '\0' || !sym_info.name || sym_info.name[0] == '\0')
            continue;
        sym_info.value = x_(get_value)(sym_arr[i]);
        sym_info_arr[j++] = sym_info;
    }
    *n_sym = j;
    return sym_info_arr;
}
