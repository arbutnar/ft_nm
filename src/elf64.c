#include "ft_nm.h"

extern t_elf_file g_elf_file;

Elf64_Shdr  *get_symtab(Elf64_Shdr *sections, size_t num_sections) {
    size_t i;

    for (i = 0; sections[i].sh_type != SHT_SYMTAB; i++)
        if (i == num_sections)
            return NULL;
    return &sections[i];
}

char get_type(Elf64_Sym symbol) {
    unsigned char bind = ELF64_ST_BIND(symbol.st_info);
    unsigned char type = ELF64_ST_TYPE(symbol.st_info);
    char c;

    switch (type) {
        case STT_NOTYPE:
            c = (symbol.st_shndx == SHN_UNDEF) ? 'U' : 'N';
            break;
        case STT_OBJECT:
            c = (symbol.st_shndx == SHN_COMMON) ? 'C' : 'D';
            break;
        case STT_FUNC:
            c = 'T';
            break;
        case STT_SECTION:
            c = 'S';
            break;
        case STT_FILE:
            c = 'F';
            break;
        default:
            c = '?';
    }
    if (bind == STB_LOCAL && c != '?') {
        c = c + ('a' - 'A');
    }

    return c;
}

t_symbol    translate_symbol(Elf64_Sym elf_symbol, char *names) {
    t_symbol symbol;

    symbol.value = elf_symbol.st_value;
    symbol.name = names[elf_symbol.st_name];

    return symbol;
}

t_symbol    *get_symbols(Elf64_Shdr strtab, Elf64_Shdr *symtab) {
    char        *names;
    Elf64_Sym   *elf_symbols;
    size_t      num_symbols;
    t_symbol    *symbols;

    names = extract_fom_content(strtab.sh_offset);
    if (names == NULL || names[0] == '\0')
        return NULL;
    elf_symbols = (Elf64_Sym *) extract_fom_content(symtab->sh_offset);
    if (elf_symbols == NULL)
        return NULL;
    num_symbols = symtab->sh_size / sizeof(Elf64_Sym);
    symbols = malloc(sizeof(t_symbol) * num_symbols);
    if (!symbols)
        return NULL;
    for (size_t i = 0, k = 0; i < num_symbols; i++) {
        t_symbol symbol = translate_symbol(elf_symbols[i], names);
        if (symbol.name == NULL)
            continue ;
        symbols[k] = symbol;
        k++;
        printf("%c %s\n", symbol.name);
    }
    return symbols;
}

int    process_elf64() {
    Elf64_Ehdr  *header;
    Elf64_Shdr  *sections;
    Elf64_Shdr  *symtab;
    t_symbol    *symbols;

    header = (Elf64_Ehdr *) g_elf_file.content;
    if (header->e_shoff + header->e_shnum * header->e_shentsize > g_elf_file.size)
        return 1;
    sections = (Elf64_Shdr *) extract_fom_content(header->e_shoff);
    if (sections == NULL)
        return 1;
    symtab = get_symtab(sections, header->e_shnum);
    if (!symtab) {
        printf("nm: %s: no symbols\n", g_elf_file.path);
        return 0;
    }
    if(symtab->sh_link >= header->e_shnum)
        return 1;
    symbols = get_symbols(sections[symtab->sh_link], symtab);
    
    return display_symbols(sections[symtab->sh_link], symtab);
}