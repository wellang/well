#include <stdlib.h>
#include <string.h>

// Assign string ('=')
char* salloc(char* string) {
    char* address = (char*)malloc(strlen(string)+1);

    int i = 0;
    for (; string[i] != '\0'; ++i) {
        address[i] = string[i];
    } address[i] = '\0';

    return address;
}

// Append string ('+=')
char* resalloc(char* address, char* string) {
    int size_address = strlen(address);
    address = (char*)realloc(address, size_address + strlen(string)+1);

    int i = size_address;
    for (int i2 = 0; string[i2] != '\0'; ++i, ++i2) {
        address[i] = string[i2];
    } address[i] = '\0';

    return address;
}

// Clean string
#define unsalloc(_address_) free((void*)(_address_))
