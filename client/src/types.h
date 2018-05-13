#ifndef __COMMON_TYPES_H__
#define __COMMON_TYPES_H__

/*
 Se definen tipos de datos comunes al cliente y el servidor.
*/
typedef enum {
    push = '1',
    tag = '2',
    pull = '3'
} usage_t;

typedef unsigned char uchar;

#endif
