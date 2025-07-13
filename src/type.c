#include <stdlib.h>

#include "type.h"
#include "generics.h"
#include "utility.h"
#include "assertf.h"

owned Type * ty_new() {
    owned Type * ty      = new(sizeof(Type));
    ty->ty               = TYPE_UNKNOWN;
    ty->size             = 0;
    ty->align            = 0;
    ty->name             = nil;
    ty->base             = nil;
    ty->return_type      = nil;
    ty->parameters       = nil;
    ty->fields           = nil;
    ty->tuples           = nil;
    ty->length           = 0;
    ty->offset           = 0;
    ty->stack_frame_size = 0;
    ty->argument_space   = 0;
    return ty;
}

owned Type * ty_void() {
    static owned Type * ty = nil;
    if (!ty) {
        ty       = ty_new();
        ty->ty   = TYPE_VOID;
        ty->size = 0;
        ty->name = s_copy("void");
    }
    return ty;
}

owned Type * ty_i8() {
    static owned Type * ty = nil;
    if (!ty) {
        ty       = ty_new();
        ty->ty   = TYPE_I8;
        ty->size = 1;
        ty->name = s_copy("i8");
    }
    return ty;
}

owned Type * ty_i16() {
    static owned Type * ty = nil;
    if (!ty) {
        ty       = ty_new();
        ty->ty   = TYPE_I16;
        ty->size = 2;
        ty->name = s_copy("i16");
    }
    return ty;
}

owned Type * ty_i32() {
    static owned Type * ty = nil;
    if (!ty) {
        ty       = ty_new();
        ty->ty   = TYPE_I32;
        ty->size = 4;
        ty->name = s_copy("i32");
    }
    return ty;
}

owned Type * ty_i64() {
    static owned Type * ty = nil;
    if (!ty) {
        ty       = ty_new();
        ty->ty   = TYPE_I64;
        ty->size = 8;
        ty->name = s_copy("i64");
    }
    return ty;
}

owned Type * ty_u8() {
    static owned Type * ty = nil;
    if (!ty) {
        ty       = ty_new();
        ty->ty   = TYPE_U8;
        ty->size = 1;
        ty->name = s_copy("u8");
    }
    return ty;
}

owned Type * ty_u16() {
    static owned Type * ty = nil;
    if (!ty) {
        ty       = ty_new();
        ty->ty   = TYPE_U16;
        ty->size = 2;
        ty->name = s_copy("u16");
    }
    return ty;
}

owned Type * ty_u32() {
    static owned Type * ty = nil;
    if (!ty) {
        ty       = ty_new();
        ty->ty   = TYPE_U32;
        ty->size = 4;
        ty->name = s_copy("u32");
    }
    return ty;
}

owned Type * ty_u64() {
    static owned Type * ty = nil;
    if (!ty) {
        ty       = ty_new();
        ty->ty   = TYPE_U64;
        ty->size = 8;
        ty->name = s_copy("u64");
    }
    return ty;
}

owned Type * ty_f32() {
    static owned Type * ty = nil;
    if (!ty) {
        ty       = ty_new();
        ty->ty   = TYPE_F32;
        ty->size = 4;
        ty->name = s_copy("f32");
    }
    return ty;
}

owned Type * ty_f64() {
    static owned Type * ty = nil;
    if (!ty) {
        ty       = ty_new();
        ty->ty   = TYPE_F64;
        ty->size = 8;
        ty->name = s_copy("f64");
    }
    return ty;
}

owned Type * ty_bool() {
    static owned Type * ty = nil;
    if (!ty) {
        ty       = ty_new();
        ty->ty   = TYPE_BOOL;
        ty->size = 1;
        ty->name = s_copy("bool");
    }
    return ty;
}

owned Type * ty_char() {
    static owned Type * ty = nil;
    if (!ty) {
        ty       = ty_new();
        ty->ty   = TYPE_CHAR;
        ty->size = 1;
        ty->name = s_copy("char");
    }
    return ty;
}

owned Type * ty_pointer(borrowed Type * base) {
    scp(base);
    owned Type * ty = ty_new();
    ty->ty          = TYPE_PTR;
    ty->base        = base;
    //
    return ty;;
}

copy u64 ty_size(borrowed Type * ty) {
}

void ty_dtor(borrowed void * arg) {
    if (!arg) {
        return;
    }
    borrowed Type * ty = cast(arg, Type*);
    sfree(ty->name);
    switch (ty->ty) {
        case TYPE_VOID:
        case TYPE_BOOL:
        case TYPE_CHAR:
        case TYPE_I8:
        case TYPE_I16:
        case TYPE_I32:
        case TYPE_I64:
        case TYPE_U8:
        case TYPE_U16:
        case TYPE_U32:
        case TYPE_U64:
        case TYPE_F32:
        case TYPE_F64:
        {
        } break;
    }
}

void ty_destroy(owned void * arg) {
    if (!arg) {
        return;
    }
    ty_dtor(arg);
    free(arg);
}

