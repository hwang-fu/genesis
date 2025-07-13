#ifndef GENESIS_TYPE_H
#define GENESIS_TYPE_H

#include "generics.h"
#include "vector.h"

typedef enum TType TType;
enum TType {
    TYPE_VOID,
    TYPE_BOOL,
    TYPE_CHAR,

    TYPE_I8,
    TYPE_U8,
    TYPE_I16,
    TYPE_U16,
    TYPE_I32,
    TYPE_U32,
    TYPE_I64,
    TYPE_U64,

    TYPE_F32,
    TYPE_F64,

    TYPE_ENUMERATION,
    TYPE_STRUCTURE,

    TYPE_PTR,
    TYPE_ARRAY,
    TYPE_TUPLE,

    TYPE_FUNCTION,
    TYPE_PROCEDURE,

    TYPE_STR_LITERAL,

    TYPE_ALIAS,

    TYPE_UNKNOWN,
};

typedef struct Type Type;
struct Type {
    copy     TType    ty;
    copy     u64      size;
    copy     u64      align;
    owned    char   * name;

    borrowed Type   * base;
    borrowed Type   * return_type;
    owned    Vector * parameters;
    owned    Vector * fields;
    owned    Vector * tuples;
    copy     u64      length;
    copy     u64      offset;
    copy     u64      stack_frame_size;
    copy     u64      argument_space;
};

typedef struct Field Field;
struct Field {
    borrowed Type * tye;
    owned    char * name;
    copy     u64    offset;
};

owned Type * ty_new();
owned Type * ty_void();
owned Type * ty_i8();
owned Type * ty_i16();
owned Type * ty_i32();
owned Type * ty_i64();
owned Type * ty_u8();
owned Type * ty_u16();
owned Type * ty_u32();
owned Type * ty_u64();
owned Type * ty_f32();
owned Type * ty_f64();
owned Type * ty_char();
owned Type * ty_bool();
owned Type * ty_pointer(borrowed Type * base);

copy u64 ty_size(borrowed Type * ty);

void ty_dtor(borrowed void * arg);
void ty_destroy(owned void * arg);

#endif // GENESIS_TYPE_H
