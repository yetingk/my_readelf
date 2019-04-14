#include "my_elf.h"

int main (int argc, char * const * argv) {
    Elf64_Ehdr elf;
    char *file_name;
    
    for (int i = 0; i < argc; ++i) {
        if (argv[i][0] != '-') {
            file_name = malloc(strlen(argv[i]) + 1);
            strcpy(file_name, argv[i]);
            break;
        }
    }
    
    /* check which flag is raised */
    bool head = false;
    int c;
    while ((c = getopt(argc, argv, "h")) != EOF) {
        switch (c) {
        case 'h':
            head = true;
            break;
        }
    }
    
    
    FILE *fp = fopen(file_name, "r");
    if (!fp)
        fatal("error: open\n");

    memset(elf.e_ident, 0, EI_NIDENT);
    fread(elf.e_ident, EI_NIDENT, 1, fp);
    fclose(fp);
    
    /* check this file is ELF or not */
    if (elf.e_ident[EI_MAG0] != 0x7f ||
        elf.e_ident[EI_MAG1] != 0x45 ||
        elf.e_ident[EI_MAG2] != 0x4c ||
        elf.e_ident[EI_MAG3] != 0x46) {
        fatal("my_readelf: Error: Not an ELF file - it has the wrong magic bytes at the start\n");
    }
    
    if (head) 
        elf_head(&elf);
}
