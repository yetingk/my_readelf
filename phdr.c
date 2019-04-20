#include "my_elf.h"

void print_phdr(int fd, const Elf64_Ehdr *e) {
    Elf64_Phdr *phdr_table = NULL; 
    char *buf = NULL;
    const char *tmp = NULL;
    
    // allocat memory we needed.
    size_t size = 128 * e->e_phnum;
    if ((phdr_table = malloc(size)) == NULL)
        fatal("my_readelf: malloc: %s",strerror(errno));

    if ((buf = malloc(size)) == NULL) 
        fatal("my_readelf: malloc: %s",strerror(errno));
    
    // make sure strcat() can work correctly.
    buf[0] = '\0';
    
    // move to the program header table.
    lseek(fd, e->e_phoff, SEEK_SET);
    read(fd, phdr_table, e->e_phnum * sizeof(Elf64_Phdr));
    
    char flag[5] = {[4] = '\0',};
    for (int i = 0; i < e->e_phnum; ++i) {
        switch (phdr_table[i].p_type) {
        case PT_NULL   : tmp = "NULL    "; break;
        case PT_LOAD   : tmp = "LOAD    "; break;
        case PT_DYNAMIC: tmp = "DYNAMIC "; break;
        case PT_INTERP : tmp = "INTERP  "; break;
        case PT_PHDR   : tmp = "PHDR    "; break;
        default        : tmp = "OTHER   "; break;
        }
        strcat(buf, tmp);
        
        // offset
        sprintf(buf, "%s%016lx ", buf, phdr_table[i].p_offset);

        // virtAddress
        sprintf(buf, "%s%016lx ", buf, phdr_table[i].p_vaddr);

        // physicalAddress
        sprintf(buf, "%s%016lx ", buf, phdr_table[i].p_vaddr);

        // file size
        sprintf(buf, "%s%016lx ", buf, phdr_table[i].p_filesz);

        // memory size
        sprintf(buf, "%s%016lx ", buf, phdr_table[i].p_memsz);

        // flag
        memset(flag, ' ', 4);
        int j = 0;
        if (phdr_table[i].p_flags & PF_X)
            flag[j] = 'X';
        ++j;
        if (phdr_table[i].p_flags & PF_W)
            flag[j] = 'W';
        ++j;
        if (phdr_table[i].p_flags & PF_R)
            flag[j] = 'R';
        strcat(buf, flag);

        // alignment
        sprintf(buf, "%s%lx\n", buf, phdr_table[i].p_align);        
    }
    printf("%s", buf);
    
    
    // free allocated space.
    free(buf);
    free(phdr_table);
}
