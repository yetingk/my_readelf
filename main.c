#include "my_elf.h"

int main (int argc, char * const * argv) {
    Elf64_Ehdr ehdr;
    char *file_name;
    
    for (int i = 0; i < argc; ++i) {
        if (argv[i][0] != '-') {
            file_name = malloc(strlen(argv[i]) + 1);
            strcpy(file_name, argv[i]);
            break;
        }
    }
    
    /* check which flag is raised */
    bool elf = false;
    bool program = false;
    bool section = false;
    int c;
    while ((c = getopt(argc, argv, "hlS")) != EOF) {
        switch (c) {
        case 'h':
            elf = true;
            break;
        case 'l':
            program = true;
            break;
        case 'S':
            section = true;
            break;
        }
    }
    
    
    int fd = open(file_name, O_RDONLY);
    if (fd < 0)
        fatal("error: open\n");

    read(fd, &ehdr, sizeof(Elf64_Ehdr));
    //close(fd);
    
    /* check this file is ELF or not */
    if (!valid_ELF(&ehdr)) {
        fatal("my_readelf: Error: Not an ELF file - it has the wrong magic bytes at the start\n");
    }
    
    if (elf) 
        elf_head(&ehdr);

    if (program)
        print_phdr(fd, &ehdr);

    if (section)
        print_shdr(fd, &ehdr);

    close(fd);
}

bool valid_ELF(const Elf64_Ehdr *elf) {
    return elf->e_ident[EI_MAG0] == 0x7f &&
           elf->e_ident[EI_MAG1] == 0x45 && 
           elf->e_ident[EI_MAG2] == 0x4c && 
           elf->e_ident[EI_MAG3] == 0x46;
}
