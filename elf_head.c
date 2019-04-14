#include <elf.h>
#include <stdio.h>
#include <string.h>
#define HEAD_FORMAT "\n  %s %s"

void elf_head(const Elf64_Ehdr *elf) {
    char buf[512], tmp[64];
    /* show the magic number */
    strcpy(buf, "ELF Header:   " "\n  Magic:");
    for (int i = 0; i < EI_NIDENT; ++i) {
        sprintf(tmp, "%2x ", elf->e_ident[i]);
        strcat(buf, tmp);
    }
    
    /* signify 32- or 64 bit */
    switch (elf->e_ident[EI_CLASS]) {
    case ELFCLASS32:
        sprintf(tmp, HEAD_FORMAT, "Class:", "ELF32");
    case ELFCLASS64:
        sprintf(tmp, HEAD_FORMAT, "Class:", "ELF64");
    }
    strcat(buf, tmp);

    /* signify little endian or big endian */

    puts(buf);
}
