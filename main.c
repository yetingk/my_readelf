#include "my_elf.h"

int main (int argc, char * const * argv) {
    int fd = -1;
    void *file = NULL;
    char *file_name = NULL;
    Elf64_Ehdr *ehdr = NULL;
    
    for (int i = 0; i < argc; ++i) {
        if (argv[i][0] != '-') {
            file_name = argv[i];
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
    
    // get file size;
    struct stat st;
    stat(file_name, &st);
    
    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        fatal("my_readelf: open: %s\n", strerror(errno));

    file = mmap(0, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    ehdr = (Elf64_Ehdr *)file;
    
    /* check this file is ELF or not */
    if (!valid_ELF(ehdr)) {
        fatal("my_readelf: Error: Not an ELF file - it has the wrong magic bytes at the start\n");
    }
    
    if (elf) {
        elf_head(ehdr);
    }
    
    if (program) {
        void *ph_table = file + ehdr->e_phoff;
        switch (ehdr->e_ident[EI_CLASS]) {
        case ELFCLASS64:
            print_phdr64 ((Elf64_Phdr *)ph_table, ehdr->e_phnum);
            break;
        case ELFCLASS32:
            print_phdr32 ((Elf32_Phdr *)ph_table, ehdr->e_phnum);
            break;
        default:
            fatal("my_readelf: only support 32-bit and 64-bit format.\n");
        }
    }

    if (section) {
        void *sh_table = file + ehdr->e_shoff;
        char *name_table = NULL;
        switch (ehdr->e_ident[EI_CLASS]) {
        case ELFCLASS64:
            name_table = (char *)(file + ((Elf64_Shdr *) sh_table)[ehdr->e_shstrndx].sh_offset);
            print_shdr64((Elf64_Shdr *)sh_table, name_table, ehdr->e_shnum);
            break;
        case ELFCLASS32:
            name_table = (char *)(file + ((Elf32_Shdr *)sh_table)[ehdr->e_shstrndx].sh_offset);
            print_shdr32((Elf32_Shdr *)sh_table, name_table, ehdr->e_shnum);
            break;
        default:
            fatal("my_readelf: only support 32-bit and 64-bit format.\n");
        }
    }

    // free allocated resource.
    close(fd);
    munmap(file, st.st_size);
}

bool valid_ELF(const Elf64_Ehdr *elf) {
    return elf->e_ident[EI_MAG0] == 0x7f &&
           elf->e_ident[EI_MAG1] == 0x45 && 
           elf->e_ident[EI_MAG2] == 0x4c && 
           elf->e_ident[EI_MAG3] == 0x46;
}
