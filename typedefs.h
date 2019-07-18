#ifndef _TYPEDEFS_H_
#define _TYPEDEFS_H_

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
#define EXTERN_C_BEGIN extern "C" {
#define EXTERN_C_END }
#else
#define EXTERN_C_BEGIN
#define EXTERN_C_END
#endif

#ifndef CONCAT
#define CONCAT(prefix, name) prefix ## name
#endif

#ifndef UNUSED
#define UNUSED(x) ((void)x);
#endif

#define ASSERT(cond)                                                   \
    if (!(cond)) {                                                     \
        fprintf(stderr, "Fatal error condition occurred in %s:%d: %s " \
                        "Exiting application\n",                       \
            __FILE__, __LINE__, #cond);                                \
    }

#define FATAL_ASSERT(cond)                                             \
    if (!(cond)) {                                                     \
        fprintf(stderr, "Fatal error condition occurred in %s:%d: %s " \
                        "Exiting application\n",                       \
            __FILE__, __LINE__, #cond);                                \
        abort();                                                       \
    }

#ifndef ARRAYSIZE
#define ARRAYSIZE(x) (sizeof(x) / sizeof(x[0]))
#endif
#ifndef NELEM
#define NELEM(array) ARRAYSIZE(array)
#endif

#ifndef MIN 
#define MIN(a, b) ((a) <= (b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b) ((a) >= (b) ? (a) : (b))
#endif

#ifndef __packed
#define __packed __attribute__((packed))
#endif

#ifndef __constructor
#define __constructor __attribute__((constructor))
#endif

#ifndef __destructor
#define __destructor __attribute__((destructor))
#endif

//
// General operation and error code definition
//
#define OPCODE_SUCCESS 0
#define OPCODE_FAILURE -1

#endif // _TYPEDEFS_H_
