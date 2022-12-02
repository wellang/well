#pragma once

#define ELF_HEADER_SIZE (84)

// Only header data of elf //

// Program header
typedef struct {
    char p_type[4];
    char p_offset[4];
    char p_vaddr[4];
    char p_paddr[4];
    char p_filesz[4];
    char p_memsz[4];
    char p_flags[4];
    char p_fill[4];
} elf_header_program_t;

typedef struct {
    char ei_mag[4];
    char ei_class; char ei_data; // 2 bytes for both
    char ei_version[4];
    char ei_fill[6];
} elf_header_e_ident_t;

// ELF data
typedef struct { // 84 bytes size of all items of header
    elf_header_e_ident_t* e_ident;
    char                  e_type[2];
    char                  e_machine[2];
    char                  e_version[4];
    char                  e_entry[4];
    char                  e_phoff[4];
    char                  e_shoff[4];
    char                  e_fill[4];
    char                  e_ehsize[2];
    char                  e_phentsize[2];
    char                  e_phnum[2];
    char                  e_shentsize[2];
    char                  e_shnum[2];
    char                  e_shstrndx[2];
    elf_header_program_t* header_program;
} elf_header_t;

// Only code of program (in elf) //

typedef struct {
} elf_sections_t;

// Only data for linker (in elf) //

typedef struct {
} elf_linker_data_t;

// Error data (for 1 file '.o') //

typedef struct {
    elf_header_t*      header;
    elf_sections_t*    sections;
    elf_linker_data_t* linker_data;
} elf_t;

elf_header_t* new_elf_header(); // Create new elf header in zeros 'nulls'
void join_elf_header(elf_header_t* elf_header, char elf_header_bytes[ELF_HEADER_SIZE]);
void remove_elf_header(elf_header_t* elf_header);
