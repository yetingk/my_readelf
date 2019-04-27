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
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define fatal(...)                    \
    do {                              \
        fprintf(stderr, __VA_ARGS__); \
        exit(EXIT_FAILURE);           \
    } while(0)
void elf_head (Elf64_Ehdr *);
void print_phdr64(Elf64_Phdr *, uint16_t);
void print_phdr32(Elf32_Phdr *, uint16_t);
void print_shdr64(Elf64_Shdr *, char *, uint16_t);
void print_shdr32(Elf32_Shdr *, char *, uint16_t);
bool valid_ELF(const Elf64_Ehdr *);
#endif /* MY_ELF_H */
