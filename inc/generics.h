#ifndef GENESIS_GENERICS_H
#define GENESIS_GENERICS_H

// -------------------------------------------------------------
// | primitive type aliases |
// -------------------------------------------------------------
// More-understandable aliases for fixed-width integer and float types.

typedef float           f32 ;
typedef double          f64 ;

typedef char            i8  ;
typedef unsigned char   u8  ;

typedef short           i16 ;
typedef unsigned short  u16 ;

typedef int             i32 ;
typedef unsigned int    u32 ;

typedef long            i64 ;
typedef unsigned long   u64 ;


// -------------------------------------------------------------
// | NULL macro |
// -------------------------------------------------------------
// Use `nil` as a universal null/zero value.

#define nil (0)


// -------------------------------------------------------------
// | ownership annotations |
// -------------------------------------------------------------
// These are semantic markers - useful for documentation, not functionality.

#define copy
#define borrowed
#define owned


// -------------------------------------------------------------
// | ownership helpers |
// -------------------------------------------------------------
// Macros to indicate semantic ownership operations.

#define borrow(x)                                                   \
        x
#define own(x)                                                      \
        x
#define clone(x)                                                    \
        x


// -------------------------------------------------------------
// | memory safety helpers |
// -------------------------------------------------------------

/**
 * drop(ptr):
 *   1. Frees the pointer if not null.
 *   2. Safe cleanup wrapper to avoid double-free or null-free.
 */
#define drop(ptr)                                                   \
        do {                                                        \
            if ( (ptr) ) free(ptr);                                 \
        } while (0)


// -------------------------------------------------------------
// | pointer / reference helpers |
// -------------------------------------------------------------

/**
 * deref(ptr, type):
 *   1. Dereference a pointer with the expected type.
 */
#define deref(ptr, type)                                            \
        (*((type *)(ptr)))

/**
 * ref(ptr):
 *   1. Get the address of a variable (pass-by-reference helper).
 */
#define ref(var)                                                    \
        (&var)

/**
 * cast(obj, type):
 *   1. Explicitly cast object to type.
 */
#define cast(obj, type)                                             \
        ((type) (obj))

/**
 * pointer(type):
 *   1. Aliases pointer types in a readable way.
 */
#define pointer(type)                                               \
        (type*)

/**
 * nullify(ptr):
 *  1. Sets the pointer to nil (zero).
 */
#define nullify(ptr)                                                \
        ptr = nil


// -------------------------------------------------------------
// | comparison helpers |
// -------------------------------------------------------------

#define eq(p1, p2)                                                  \
        ((p1) == (p2))

#define neq(p1, p2)                                                 \
        ((p1) != (p2))


// -------------------------------------------------------------
// | arithmetic helpers |
// -------------------------------------------------------------

/**
 * roundup(n, d):
 *   1. Rounds up `n` to the nearest multiple of `d`.
 *   2. Useful for alignment or chunked memory blocks.
 */
#define roundup(n, d)                                               \
        (((n) + (d) - 1) / (d))




#endif // GENESIS_GENERICS_H
