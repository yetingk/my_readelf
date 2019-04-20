#ifndef MY_ELF_H
#define MY_ELF_H

#include <elf.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define fatal(...)                    \
    do {                              \
        fprintf(stderr, __VA_ARGS__); \
        exit(EXIT_FAILURE);           \
    } while(0)
void elf_head (const Elf64_Ehdr *elf);
void print_phdr(int fd, const Elf64_Ehdr *elf);
void print_shdr(int fd, const Elf64_Ehdr *elf);
bool valid_ELF(const Elf64_Ehdr *e);
#endif /* MY_ELF_H */
