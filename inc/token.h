#ifndef GENESIS_TOKEN_H
#define GENESIS_TOKEN_H

#include "generics.h"
#include "vector.h"

typedef Vector TKs;

typedef enum TToken TToken;
enum TToken {

    TOKEN_KEYWORD_START = 0,

    TOKEN_PROGRAM,      // program
    TOKEN_UNIT,         // unit
    TOKEN_BEGIN,        // begin
    TOKEN_END,          // end
    
    TOKEN_VAR,          // var
    TOKEN_VARIABLE,     // variable
    
    TOKEN_CONST,        // const
    TOKEN_CONSTANT,     // constant
    
    TOKEN_FORWARD,      // forward
    TOKEN_FUNC,         // func
    TOKEN_FUNCTION,     // function
    TOKEN_PROC,         // proc
    TOKEN_PROCEDURE,    // procedure
    TOKEN_RETURN,       // return
    
    TOKEN_STRUCTURE,    // structure
    TOKEN_ENUMERATION,  // enumeration

    TOKEN_IMPL,         // implementation
    TOKEN_TYPE,         // type
    TOKEN_AS,           // as
    TOKEN_ARRAY,        // array
    TOKEN_TUPLE,        // tuple
    TOKEN_OF,           // of

    TOKEN_IF,           // if
    TOKEN_ELSE,         // else
    TOKEN_DO,           // do
    TOKEN_WHILE,        // while
    TOKEN_FOR,          // for
    TOKEN_UNTIL,        // until
    TOKEN_LOOP,         // loop
    TOKEN_REPEAT,       // repeat
    TOKEN_TO,           // to
    TOKEN_DOWNTO,       // downto
    TOKEN_IN,           // in
    TOKEN_THEN,         // then
    TOKEN_BREAK,        // break
    TOKEN_CONTINUE,     // continue
    TOKEN_GOTO,         // goto

    TOKEN_I8,           // i8
    TOKEN_I16,          // i16
    TOKEN_I32,          // i32
    TOKEN_I64,          // i64

    TOKEN_U8,           // u8
    TOKEN_U16,          // u16
    TOKEN_U32,          // u32
    TOKEN_U64,          // u64

    TOKEN_F32,          // f32
    TOKEN_F64,          // f64

    TOKEN_KEYWORD_END,

    TOKEN_IDENT,
    TOKEN_INTEGER,
    TOKEN_FLOAT,
    TOKEN_NUMBER,
    TOKEN_CHAR,
    TOKEN_STR,

    TOKEN_OPERATOR_START,

    TOKEN_ASSIGNMENT,   // :=
    TOKEN_PLUS_ASSIGN,  // +=
    TOKEN_MINUS_ASSIGN, // -=
    TOKEN_MUL_ASSIGN,   // *=
    TOKEN_DIV_ASSIGN,   // /=
    TOKEN_MOD_ASSIGN,   // %=
    TOKEN_AND_ASSIGN,   // &=
    TOKEN_OR_ASSIGN,    // |=
    TOKEN_XOR_ASSIGN,   // ^=

    TOKEN_AND,          // &&
    TOKEN_OR,           // ||
    TOKEN_NOT_EQ,       // !=
    TOKEN_LT_GT,        // <>
    TOKEN_GT_LT,        // ><
    TOKEN_ARROW,        // ->
    TOKEN_THICK_ARROW,  // =>

    TOKEN_LT_EQ,        // <=
    TOKEN_GT_EQ,        // >=
    TOKEN_LSHIFT,       // <<
    TOKEN_RSHIFT,       // >>
    TOKEN_EQ_EQ,        // ==

    TOKEN_SCOPE,        // ::

    TOKEN_LINE_COMMENT,         // //
    TOKEN_L_BLK_COMMENT,        // (*
    TOKEN_R_BLK_COMMENT,        // *)

    TOKEN_BACKTICK,     // `
    TOKEN_TILDE,        // ~
    TOKEN_NOT,          // !
    TOKEN_AT,           // @
    TOKEN_HASH,         // #
    TOKEN_DOLLAR,       // $
    TOKEN_MOD,          // %
    TOKEN_CARET,        // ^
    TOKEN_AMPERSAND,    // &
    TOKEN_MUL,          // *

    TOKEN_L_PARENTHESES,// (
    TOKEN_R_PARENTHESES,// )

    TOKEN_MINUS,        // -
    TOKEN_EQ,           // =
    TOKEN_PLUS,         // +

    TOKEN_L_BRACKET,    // [
    TOKEN_R_BRACKET,    // ]
    TOKEN_L_BRACE,      // {
    TOKEN_R_BRACE,      // }

    TOKEN_SLASH,        // '\\'
    TOKEN_BAR,          // |
    TOKEN_SEMICOLON,    // ;
    TOKEN_COLON,        // :
    TOKEN_APOSTROPHE,   // '\''
    TOKEN_QUOTE,        // '\"'

    TOKEN_COMMA,        // ,
    TOKEN_PERIOD,       // .
    TOKEN_LT,           // <
    TOKEN_GT,           // >
    TOKEN_DIV,          // /
    TOKEN_QUESTION,     // ?

    TOKEN_OPERATOR_END,

    TOKEN_UNKNOWN,
};

typedef struct Token Token;
struct Token {
    copy  TToken tt;
    owned char * value;
};

owned Token * tk_new();
owned Token * tk_ctor(copy const TToken tt, borrowed const char * value);
owned Token * tk_ctor_owned(copy const TToken tt, owned char * value);
owned TKs   * tks_new();

void tk_dtor(borrowed void * arg);
void tk_destroy(owned void * arg);

#endif // GENESIS_TOKEN_H
