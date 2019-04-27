#include "my_elf.h"

void print_shdr64(Elf64_Shdr *sh_table, char *name_table,
                uint16_t sh_num) {
    
    // allocat memory to store data to print.
    char *buf = malloc(sh_num * 128);
    if (buf == NULL)
        fatal("my_readelf: malloc: %s\n",strerror(errno));
    buf[0] = '\0';
    
    char tmp[32];
    for (int i = 0; i < sh_num; ++i) {
        // section name
        int str_index = sh_table[i].sh_name;
        sprintf(tmp, "%s ", &name_table[str_index]);
        strcat(buf, tmp);
        
        // section type
        const char *str = NULL;
        switch(sh_table[i].sh_type) {
        case SHT_NULL    : str = "NULL        "; break;
        case SHT_PROGBITS: str = "PROGRAMBITS "; break;
        case SHT_SYMTAB  : str = "SYMTAB      "; break;
        case SHT_STRTAB  : str = "STRTAB      "; break;
        default          : str = "OTHER       "; break;
        }
        
        // virtual address
        sprintf(tmp, "%016lx ", sh_table[i].sh_addr);
        strcat(buf, tmp);

        // offset of the section in the file image.
        sprintf(tmp, "%016lx ", sh_table[i].sh_offset);
        strcat(buf, tmp);

        // Size in bytes of the section in the file image. May be 0.
        sprintf(tmp, "%016lx ", sh_table[i].sh_size);
        strcat(buf, tmp);

        // the whole size
        sprintf(tmp, "%016lx\n", sh_table[i].sh_entsize);
        strcat(buf, tmp);
    }

    printf("%s", buf);

    free(buf);
}

void print_shdr32(Elf32_Shdr *sh_table, char *name_table,
                uint16_t sh_num) {
    
    // allocat memory to store data to print.
    char *buf = malloc(sh_num * 128);
    if (buf == NULL)
        fatal("my_readelf: malloc: %s\n",strerror(errno));
    buf[0] = '\0';
    
    char tmp[32];
    for (int i = 0; i < sh_num; ++i) {
        // section name
        int str_index = sh_table[i].sh_name;
        sprintf(tmp, "%s ", &name_table[str_index]);
        strcat(buf, tmp);
        
        // section type
        const char *str = NULL;
        switch(sh_table[i].sh_type) {
        case SHT_NULL    : str = "NULL        "; break;
        case SHT_PROGBITS: str = "PROGRAMBITS "; break;
        case SHT_SYMTAB  : str = "SYMTAB      "; break;
        case SHT_STRTAB  : str = "STRTAB      "; break;
        default          : str = "OTHER       "; break;
        }
        
        // virtual address
        sprintf(tmp, "%08x ", sh_table[i].sh_addr);
        strcat(buf, tmp);

        // offset of the section in the file image.
        sprintf(tmp, "%08x ", sh_table[i].sh_offset);
        strcat(buf, tmp);

        // Size in bytes of the section in the file image. May be 0.
        sprintf(tmp, "%08x ", sh_table[i].sh_size);
        strcat(buf, tmp);

        // the whole size
        sprintf(tmp, "%08x\n", sh_table[i].sh_entsize);
        strcat(buf, tmp);
    }

    printf("%s", buf);

    free(buf);
}
