#include "my_elf.h"

void print_shdr(int fd, const Elf64_Ehdr *e) {
    Elf64_Shdr *shdr_table = NULL; 
    char *buf = NULL;
    const char *tmp = NULL;
    
    // allocat memory we needed.
    size_t size = 128 * e->e_shnum;
    if ((shdr_table = malloc(size)) == NULL)
        fatal("my_readelf: malloc: %s",strerror(errno));

    if ((buf = malloc(size)) == NULL) 
        fatal("my_readelf: malloc: %s",strerror(errno));
    
    // make sure strcat() can work correctly.
    buf[0] = '\0';
    
    // move to the program header table.
    lseek(fd, e->e_shoff, SEEK_SET);
    read(fd, shdr_table, e->e_shnum * sizeof(Elf64_Shdr));

    for (int i = 0; i < e->e_shnum; ++i) {
        printf("%d ", shdr_table[i].sh_name);
    }

    printf("\n");

    free(shdr_table);
    free(buf);
}
