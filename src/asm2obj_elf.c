#include <stdlib.h>

#include "asm2obj_elf.h"

// Create new elf header in zeros 'nulls'
elf_header_t* new_elf_header() {
    elf_header_t* elf_header = (elf_header_t*)calloc(1, sizeof(elf_header_t));
    // Ident
    elf_header->e_ident = (elf_header_e_ident_t*)calloc(1, sizeof(elf_header_e_ident_t));
    elf_header->e_ident->ei_mag[0] = (char)0x7F;
    elf_header->e_ident->ei_mag[1] = 'E';
    elf_header->e_ident->ei_mag[2] = 'L';
    elf_header->e_ident->ei_mag[3] = 'F';

    // Program headers
    elf_header->header_program = (elf_header_program_t*)calloc(1, sizeof(elf_header_program_t));

    return elf_header;
}

// Join the 84 bytes of info of header (elf)
void join_elf_header(elf_header_t* elf_header, char elf_header_bytes[ELF_HEADER_SIZE]) {
    int i = 0;
    // Reset with zeros ('nulls')
    for (int i = 0; i < ELF_HEADER_SIZE; ++i) {
        elf_header_bytes[i] = 0;
    }

    // Join ident
    elf_header_bytes[i++] = elf_header->e_ident->ei_mag[0];
    elf_header_bytes[i++] = elf_header->e_ident->ei_mag[1];
    elf_header_bytes[i++] = elf_header->e_ident->ei_mag[2];
    elf_header_bytes[i++] = elf_header->e_ident->ei_mag[3];

    elf_header_bytes[i++] = elf_header->e_ident->ei_class;
    elf_header_bytes[i++] = elf_header->e_ident->ei_data;

    elf_header_bytes[i++] = elf_header->e_ident->ei_version[0];
    elf_header_bytes[i++] = elf_header->e_ident->ei_version[1];
    elf_header_bytes[i++] = elf_header->e_ident->ei_version[2];
    elf_header_bytes[i++] = elf_header->e_ident->ei_version[3];

    // Others
    elf_header_bytes[i++] = elf_header->e_type[0];
    elf_header_bytes[i++] = elf_header->e_type[1];

    elf_header_bytes[i++] = elf_header->e_machine[0];
    elf_header_bytes[i++] = elf_header->e_machine[1];

    elf_header_bytes[i++] = elf_header->e_version[0];
    elf_header_bytes[i++] = elf_header->e_version[1];
    elf_header_bytes[i++] = elf_header->e_version[2];
    elf_header_bytes[i++] = elf_header->e_version[3];

    elf_header_bytes[i++] = elf_header->e_entry[0];
    elf_header_bytes[i++] = elf_header->e_entry[1];
    elf_header_bytes[i++] = elf_header->e_entry[2];
    elf_header_bytes[i++] = elf_header->e_entry[3];

    elf_header_bytes[i++] = elf_header->e_phoff[0];
    elf_header_bytes[i++] = elf_header->e_phoff[1];
    elf_header_bytes[i++] = elf_header->e_phoff[2];
    elf_header_bytes[i++] = elf_header->e_phoff[3];

    elf_header_bytes[i++] = elf_header->e_shoff[0];
    elf_header_bytes[i++] = elf_header->e_shoff[1];
    elf_header_bytes[i++] = elf_header->e_shoff[2];
    elf_header_bytes[i++] = elf_header->e_shoff[3];

    elf_header_bytes[i++] = elf_header->e_ehsize[0];
    elf_header_bytes[i++] = elf_header->e_ehsize[1];

    elf_header_bytes[i++] = elf_header->e_phentsize[0];
    elf_header_bytes[i++] = elf_header->e_phentsize[1];

    elf_header_bytes[i++] = elf_header->e_phnum[0];
    elf_header_bytes[i++] = elf_header->e_phnum[1];

    elf_header_bytes[i++] = elf_header->e_shentsize[0];
    elf_header_bytes[i++] = elf_header->e_shentsize[1];

    elf_header_bytes[i++] = elf_header->e_shnum[0];
    elf_header_bytes[i++] = elf_header->e_shnum[1];

    elf_header_bytes[i++] = elf_header->e_shstrndx[0];
    elf_header_bytes[i++] = elf_header->e_shstrndx[1];

    // Program headers
    elf_header_bytes[i++] = elf_header->header_program->p_type[0];
    elf_header_bytes[i++] = elf_header->header_program->p_type[1];
    elf_header_bytes[i++] = elf_header->header_program->p_type[2];
    elf_header_bytes[i++] = elf_header->header_program->p_type[3];

    elf_header_bytes[i++] = elf_header->header_program->p_offset[0];
    elf_header_bytes[i++] = elf_header->header_program->p_offset[1];
    elf_header_bytes[i++] = elf_header->header_program->p_offset[2];
    elf_header_bytes[i++] = elf_header->header_program->p_offset[3];

    elf_header_bytes[i++] = elf_header->header_program->p_vaddr[0];
    elf_header_bytes[i++] = elf_header->header_program->p_vaddr[1];
    elf_header_bytes[i++] = elf_header->header_program->p_vaddr[2];
    elf_header_bytes[i++] = elf_header->header_program->p_vaddr[3];

    elf_header_bytes[i++] = elf_header->header_program->p_paddr[0];
    elf_header_bytes[i++] = elf_header->header_program->p_paddr[1];
    elf_header_bytes[i++] = elf_header->header_program->p_paddr[2];
    elf_header_bytes[i++] = elf_header->header_program->p_paddr[3];

    elf_header_bytes[i++] = elf_header->header_program->p_filesz[0];
    elf_header_bytes[i++] = elf_header->header_program->p_filesz[1];
    elf_header_bytes[i++] = elf_header->header_program->p_filesz[2];
    elf_header_bytes[i++] = elf_header->header_program->p_filesz[3];

    elf_header_bytes[i++] = elf_header->header_program->p_memsz[0];
    elf_header_bytes[i++] = elf_header->header_program->p_memsz[1];
    elf_header_bytes[i++] = elf_header->header_program->p_memsz[2];
    elf_header_bytes[i++] = elf_header->header_program->p_memsz[3];

    elf_header_bytes[i++] = elf_header->header_program->p_flags[0];
    elf_header_bytes[i++] = elf_header->header_program->p_flags[1];
    elf_header_bytes[i++] = elf_header->header_program->p_flags[2];
    elf_header_bytes[i++] = elf_header->header_program->p_flags[3];
}

void remove_elf_header(elf_header_t* elf_header) {
    free((void*)elf_header->e_ident); free((void*)elf_header->header_program);
    free((void*)elf_header);
}
