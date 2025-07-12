#ifndef GENESIS_CRAYON_H
#define GENESIS_CRAYON_H

#define BOLD                "\033[1m"
#define DIM                 "\033[2m"
#define ITALIC              "\033[3m"
#define UNDERLINE           "\033[4m"
#define BLINK               "\033[5m"
#define REVERSED            "\033[7m"
#define STRIKETHRU          "\033[9m"

#define BLACK               "\033[30m"
#define RED                 "\033[31m"
#define GREEN               "\033[32m"
#define YELLOW              "\033[33m"
#define BLUE                "\033[34m"
#define MAGENTA             "\033[35m"
#define CYAN                "\033[36m"
#define WHITE               "\033[37m"
#define GRAY                "\033[90m"

#define FOREGROUND_BLACK    "\033[30m"
#define FOREGROUND_RED      "\033[31m"
#define FOREGROUND_GREEN    "\033[32m"
#define FOREGROUNDYELLOW    "\033[33m"
#define FOREGROUNDBLUE      "\033[34m"
#define FOREGROUNDMAGENTA   "\033[35m"
#define FOREGROUNDCYAN      "\033[36m"
#define FOREGROUNDWHITE     "\033[37m"
#define FOREGROUNDGRAY      "\033[90m"

#define BACKGROUND_BLACK    "\033[40m"
#define BACKGROUND_RED      "\033[41m"
#define BACKGROUND_GREEN    "\033[42m"
#define BACKGROUND_YELLOW   "\033[43m"
#define BACKGROUND_BLUE     "\033[44m"
#define BACKGROUND_WHITE    "\033[47m"
#define BACKGROUND_GRAY     "\033[100m"

#define ENDCRAYON            "\033[0m"

#define crayon_to_bold(x)           BOLD        x ENDCRAYON
#define crayon_to_dim(x)            DIM         x ENDCRAYON
#define crayon_to_italic(x)         ITALIC      x ENDCRAYON
#define crayon_to_underline(x)      UNDERLINE   x ENDCRAYON
#define crayon_to_blink(x)          BLINK       x ENDCRAYON
#define crayon_to_reversed(x)       REVERSED    x ENDCRAYON
#define crayon_to_strikethru(x)     STRIKETHRU  x ENDCRAYON

#define crayon_to_black(x)          BLACK       x ENDCRAYON
#define crayon_to_red(x)            RED         x ENDCRAYON
#define crayon_to_green(x)          GREEN       x ENDCRAYON
#define crayon_to_yellow(x)         YELLOW      x ENDCRAYON
#define crayon_to_blue(x)           BLUE        x ENDCRAYON
#define crayon_to_magenta(x)        MAGENTA     x ENDCRAYON
#define crayon_to_cyan(x)           CYAN        x ENDCRAYON
#define crayon_to_white(x)          WHITE       x ENDCRAYON
#define crayon_to_gray(x)           GRAY        x ENDCRAYON

#define crayon_no_effect(x)         ENDCRAYON   x ENDCRAYON

#endif // GENESIS_CRAYON_H

