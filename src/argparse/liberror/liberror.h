/*
 * C-Ware License
 * 
 * Copyright (c) 2022, C-Ware
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * 3. Redistributions of modified source code must append a copyright notice in
 *    the form of 'Copyright <YEAR> <NAME>' to each modified source file's
 *    copyright notice, and the standalone license file if one exists.
 *
 * A "redistribution" can be constituted as any version of the source code
 * that is intended to comprise some other derivative work of this code. A
 * fork created for the purpose of contributing to any version of the source
 * does not constitute a truly "derivative work" and does not require listing.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef CWARE_LIBERROR_H
#define CWARE_LIBERROR_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CWARE_LIBERROR_VERSION  "1.0.0"

#define liberror_is_null(function_name, argument)                 \
do {                                                              \
    if((argument) != NULL)                                        \
        break;                                                    \
                                                                  \
    fprintf(stderr, "%s", #function_name ": argument '" #argument \
            "' cannot be NULL\n");                                \
    abort();                                                      \
} while(0)

#define liberror_in_range(function_name, argument, start, end)        \
do {                                                                  \
    if((argument) >= (start) && (argument) <= end)                    \
        break;                                                        \
                                                                      \
    fprintf(stderr, "%s: argument '%s' (%i) out of range (%i, %i)\n", \
            #function_name, #argument, (start), (end), argument);     \
    abort();                                                          \
} while(0)

#define liberror_buffer_is_full(function_name, argument, needed_size, length) \
do {                                                                          \
    if((needed_size) <= (length))                                             \
        break;                                                                \
                                                                              \
    fprintf(stderr, "%s: argument '%s' (%s) produces truncated buffer at "    \
            "runtime. maximum length is %i\n", #function_name, #argument,     \
            argument, length);                                                \
    abort();                                                                  \
} while(0)

#define liberror_is_number(function_name, argument, format, value)    \
do {                                                                  \
    if((argument) != (value))                                         \
        break;                                                        \
                                                                      \
    fprintf(stderr, "%s: argument '%s' cannot be value " format "\n", \
            #function_name, #argument, value);                        \
    abort();                                                          \
} while(0);

#define liberror_failure(function_name, function)                           \
do {                                                                        \
    if((errno) == 0)                                                        \
        break;                                                              \
                                                                            \
    fprintf(stderr, "%s: function '%s' failed with error code %i (%s) "     \
            "(%s:%i)\n", #function_name, #function, errno, strerror(errno), \
            __FILE__, __LINE__);                                            \
    abort();                                                                \
} while(0)

#define liberror_is_negative(function_name, argument)         \
do {                                                          \
    if((argument) >= 0)                                       \
        break;                                                \
                                                              \
    fprintf(stderr, "%s: argument '%s' cannot be negative\n", \
            #function_name, #argument);                       \
    abort();                                                  \
} while(0)

#define liberror_is_positive(function_name, argument)         \
do {                                                          \
    if((argument) <= 0)                                       \
        break;                                                \
                                                              \
    fprintf(stderr, "%s: argument '%s' cannot be positive\n", \
            #function_name, #argument);                       \
    abort();                                                  \
} while(0)

#define liberror_unhandled(function_name) \
    fprintf(stderr, "%s: unexpected error condition (errno %i: %s) "       \
            "(%s:%i)\n", #function_name, errno, strerror(errno), __FILE__, \
            __LINE__)

#endif
