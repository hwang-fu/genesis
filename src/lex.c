#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lex.h"
#include "generics.h"
#include "token.h"
#include "assertf.h"
#include "utility.h"

static const char * const Keywords[] = {
    "",

    "program",
    "unit",
    "begin",
    "end",

    "var",
    "variable",

    "const",
    "constant",

    "forward",
    "func",
    "function",
    "proc",
    "procedure",
    "return",

    "structure",
    "enumeration",

    "implementation",
    "type",
    "as",
    "array",
    "tuple",
    "of",

    "if",
    "else",
    "do",
    "while",
    "for",
    "until",
    "loop",
    "repeat",
    "to",
    "downto",
    "in",
    "then",
    "break",
    "continue",
    "goto",

    "i8",
    "i16",
    "i32",
    "i64",

    "u8",
    "u16",
    "u32",
    "u64",

    "f32",
    "f64",

    "",
};

static const char * const Operators[] = {
    "",

    ":=",
    "+=",
    "-=",
    "*=",
    "/=",
    "%=",
    "&=",
    "!=",
    "^=",

    "&&",
    "||",
    "!=",
    "<>",
    "><",
    "->",
    "=>",

    "<=",
    ">=",
    "<<",
    ">>",
    "==",

    "::",

    "//",
    "(*",
    "*)",

    "`",
    "~",
    "!",
    "@",
    "#",
    "$",
    "%",
    "^",
    "&",
    "*",

    "(",
    ")",

    "-",
    "=",
    "+",

    "[",
    "]",
    "{",
    "}",

    "\\",
    "|",
    ";",
    ":",
    "\'",
    "\"",

    ",",
    ".",
    "<",
    ">",
    "/",
    "?",

    "",
};


static void lex_line_comment(borrowed char ** rest, borrowed char * start) {
    pforward(start, 2);
    while (deref(start, char) != '\n') {
        pforward(start, 1);
    }
    pforward(start, 1);
    deref(rest, char*) = start;
}

static void lex_multi_comment(borrowed char ** rest, borrowed char * start) {
    pforward(start, 2);
    while (!s_startswith(start, "*)")) {
        pforward(start, 1);
    }
    pforward(start, 2);
    deref(rest, char*) = start;
}

static owned Token * lex_bdigit(borrowed char ** rest, borrowed char * start) {
    owned char * integer = s_copy("0b");
    while (is_c_digit(deref(start, char))) {
        integer = s_insert_c_end(integer, *start++);
    }
    deref(rest, char*) = start;
    return tk_ctor_owned(TOKEN_INTEGER, integer);
}

static owned Token * lex_odigit(borrowed char ** rest, borrowed char * start) {
    owned char * integer = s_copy("0o");
    while (is_c_digit(deref(start, char))) {
        integer = s_insert_c_end(integer, *start++);
    }
    deref(rest, char*) = start;
    return tk_ctor_owned(TOKEN_INTEGER, integer);
}

static owned Token * lex_xdigit(borrowed char ** rest, borrowed char * start) {
    owned char * integer = s_copy("0x");
    while (is_c_digit(deref(start, char))) {
        integer = s_insert_c_end(integer, *start++);
    }
    deref(rest, char*) = start;
    return tk_ctor_owned(TOKEN_INTEGER, integer);
}

static owned Token * lex_digit(borrowed char ** rest, borrowed char * start) {
    if (s_startswith(start, "0b") || s_startswith(start, "0B")) {
        return lex_bdigit(rest, start + 2);
    }
    else if (s_startswith(start, "0o") || s_startswith(start, "0O")) {
        return lex_odigit(rest, start + 2);
    }
    else if (s_startswith(start, "0x") || s_startswith(start, "0X")) {
        return lex_xdigit(rest, start + 2);
    }
    else {
        owned char * integer = nil;
        while (is_c_digit(deref(start, char))) {
            integer = s_insert_c_end(integer, *start++);
        }
        deref(rest, char*) = start;
        return tk_ctor_owned(TOKEN_INTEGER, integer);
    }
}

static copy Bool is_s_keyword(borrowed const char * s) {
    int count = TOKEN_KEYWORD_END - TOKEN_KEYWORD_START;
    for (int i = 0; i < count; i++) {
        if (s_compare(s, Keywords[i], 0)) {
            return TOKEN_KEYWORD_START + i;;
        }
    }
    return -1;
}

static owned Token * lex_op(borrowed char ** rest, borrowed char * start) {
    int count = TOKEN_OPERATOR_END - TOKEN_OPERATOR_START;
    for (int i = 0; i < count; i++) {
        if (s_startswith(start, Operators[i])) {
            deref(rest, char*) = start + strlen(Operators[i]);
            return tk_ctor_owned(TOKEN_OPERATOR_START + i, nil);
        }
    }
    logging(LOG_ERROR, "failed to find operator token starts with ASCII [%d].", *start);
    return nil;
}

static owned Token * lex_ident(borrowed char ** rest, borrowed char * start) {
    owned char * value = nil;
    while (is_c_alnum(deref(start, char))) {
        value = s_insert_c_end(value, *start++);
    }
    deref(rest, char*) = start;
    int tt = is_s_keyword(value);
    if (eq(-1, tt)) {
        return tk_ctor_owned(TOKEN_IDENT, value);
    }
    else {
        return tk_ctor_owned(tt, value);
    }
}

owned TKs * scan(owned char * content) {
    if (eq(nil, content)) {
        return nil;
    }

    owned TKs * tks = tks_new();

    borrowed char * p = content;
    while (deref(p, char)) {
        copy char c = deref(p, char);
        if (is_c_whitespace(c)) {
            pforward(p, 1);
            continue;
        }
        if (s_startswith(p, "//")) {
            lex_line_comment(ref(p), p);
            continue;
        }
        if (s_startswith(p, "(*")) {
            lex_multi_comment(ref(p), p);
            continue;
        }
        if (is_c_digit(c)) {
            owned Token * tk = lex_digit(ref(p), p);
            vec_pushback(tks, tk);
            continue;
        }
        if (is_c_op(c)) {
            owned Token * tk = lex_op(ref(p), p);
            vec_pushback(tks, tk);
            continue;
        }
        if (is_c_alpha(c)) {
            owned Token * tk = lex_ident(ref(p), p);
            vec_pushback(tks, tk);
            continue;
        }

        logging(LOG_ERROR, "unknown char occurred at lexer: ASCII [%d]. ", c);
    }

    return tks;
}

owned TKs * lex(borrowed const char * filename) {
    if (eq(nil, filename)) {
        logging(LOG_ERROR, "please specify the file name to be lexed.");
    }

    owned    FILE  * fp         = nil;
    owned    FILE  * memstream  = nil;
    owned    char  * buf        = nil;
    copy     size_t  sizep      = 0;
    borrowed char    line[4096] = { 0 };

    fp = fopen(filename, "r"); 
    scp(fp);

    memstream = open_memstream(&buf, &sizep);
    scp(memstream);

    while (fgets(line, sizeof(line), fp)) {
        fputs(line, memstream);
    }
    fflush(memstream);
    fputc('\0', memstream);

    cassert(eq(0, fclose(memstream)));
    cassert(eq(0, fclose(fp)));

    return scan(buf);
}

