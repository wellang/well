#pragma once

// Only header data of elf //

// Program header
typedef struct {
    char[4] p_type;
    char[4] p_offset;
    char[4] p_vaddr;
    char[4] p_paddr;
    char[4] p_filesz;
    char[4] p_memsz;
    char[4] p_flags;
    char[4] p_fill;
} elf_header_program_t;

typedef struct {
    char[4] ei_mag;
    char    ei_class; char ei_data; // 2 bytes for both
    char[4] ei_version;
    char[6] ei_fill;
} elf_header_e_ident_t;

// ELF data
typedef struct { // 84 bytes size of all items of header
    elf_header_e_ident_t* e_ident;
    char[2]               e_type;
    char[2]               e_machine;
    char[4]               e_version;
    char[4]               e_entry;
    char[4]               e_phoff;
    char[4]               e_shoff;
    char[4]               e_fill;
    char[2]               e_ehsize;
    char[2]               e_phentsize;
    char[2]               e_phnum;
    char[2]               e_shentsize;
    char[2]               e_shnum;
    char[2]               e_shstrndx;
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
char* join_elf_header(elf_header_t* elf_header);
void remove_elf_header(elf_header_t* elf_header);
