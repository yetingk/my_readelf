#ifndef MY_ELF_H
#define MY_ELF_H

#include <elf.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define fatal(...)                    \
	do {                              \
		fprintf(stderr, __VA_ARGS__); \
		exit(EXIT_FAILURE);           \
	} while(0)
void elf_head (const Elf64_Ehdr *elf);

#endif /* MY_ELF_H */
