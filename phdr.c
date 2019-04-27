#include "my_elf.h"

void print_phdr64(Elf64_Phdr *phdr_table, uint16_t phdr_num) {
    char *tmp, *buf = NULL;
    
    // allocat buffer size to print phdr data.
    buf = (char *)malloc(phdr_num * 128);
    buf[0] = '\0';
    
    char flag[5] = {[4] = '\0',};
    for (int i = 0; i < phdr_num; ++i) {
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
}

void print_phdr32(Elf32_Phdr *phdr_table, uint16_t phdr_num) {
    char *tmp, *buf = NULL;
    
    // allocat buffer size to print phdr data.
    buf = (char *)malloc(phdr_num * 128);
    buf[0] = '\0';
    
    char flag[5] = {[4] = '\0',};
    for (int i = 0; i < phdr_num; ++i) {
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
        sprintf(buf, "%s%08x ", buf, phdr_table[i].p_offset);

        // virtAddress
        sprintf(buf, "%s%08x ", buf, phdr_table[i].p_vaddr);

        // physicalAddress
        sprintf(buf, "%s%08x ", buf, phdr_table[i].p_vaddr);

        // file size
        sprintf(buf, "%s%08x ", buf, phdr_table[i].p_filesz);

        // memory size
        sprintf(buf, "%s%08x ", buf, phdr_table[i].p_memsz);

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
        sprintf(buf, "%s%x\n", buf, phdr_table[i].p_align);        
    }
    printf("%s", buf);
}    
    
