#include <elf.h>
#include <stdio.h>
#include <string.h>

void elf_head(const Elf64_Ehdr *elf) {
    char buf[1024], mbuf[32];
    const char *tmp;
    /* show the magic number */
    strcpy(buf, "ELF Header:   " "\n  Magic:");
    for (int i = 0; i < EI_NIDENT; ++i) {
        sprintf(mbuf, "%02x ", elf->e_ident[i]);
        strcat(buf, mbuf);
    }
    
    /* signify 32- or 64 bit */
    switch (elf->e_ident[EI_CLASS]) {
    case ELFCLASS32:
        tmp = "\n  Class: ELF32";
        break;
    case ELFCLASS64:
        tmp = "\n  Class: ELF64";
        break;
    }
    strcat(buf, tmp);

    // signify little endian or big endian
    switch (elf->e_ident[EI_DATA]) {
    case ELFDATA2LSB:
        tmp = "\n  Data: 2's complement, little endian";
        break;
    case ELFDATA2MSB: 
        tmp = "\n  Data: 2's complement, big endian";
        break;
    }
    strcat(buf, tmp);

    // signify version 
    switch (elf->e_ident[EI_VERSION]) {
    case EV_NONE:
        tmp = "\n  Version: 0 (invalid)";
        break;
    case EV_CURRENT:
        tmp = "\n  Version: 1 (current)";
        break;
    }
    strcat(buf, tmp);
   
    // signify ABI
    switch (elf->e_ident[EI_OSABI]) {
    case ELFOSABI_SYSV: 
        tmp = "\n  OS/ABI: UNIX System V ABI";
        break;
    case ELFOSABI_HPUX: 
        tmp = "\n  OS/ABI: HP-UX ABI";
        break;
    case ELFOSABI_NETBSD: 
        tmp = "\n  OS/ABI: NetBSD ABI";
        break;
    case ELFOSABI_LINUX: 
        tmp = "\n  OS/ABI: Linux ABI";
        break;
    case ELFOSABI_SOLARIS: 
        tmp = "\n  OS/ABI: Solaris ABI";
        break;
    case ELFOSABI_IRIX: 
        tmp = "\n  OS/ABI: IRIX ABI";
        break;
    case ELFOSABI_FREEBSD:  
        tmp = "\n  OS/ABI: FreeBSD ABI";
        break;
    case ELFOSABI_TRU64: 
        tmp = "\n  OS/ABI: TRU64 UNIX ABI";
        break;
    case ELFOSABI_ARM: 
        tmp = "\n  OS/ABI: ARM architecture ABI";
        break;
    case ELFOSABI_STANDALONE: 
        tmp = "\n  OS/ABI: Stand-alone (embedded) ABI";
        break;
    }
    strcat(buf, tmp);

    puts(buf);
}
