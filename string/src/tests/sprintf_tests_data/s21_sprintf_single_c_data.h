#ifndef S21_SPRINTF_SINGLE_C_DATA_H
#define S21_SPRINTF_SINGLE_C_DATA_H
#include "../include/string.h"
char s21_buff[1024];
char orig_buff[1024];
char symbs[256];
wchar_t wide_chars[] = {L'𝄞', L'∂', L'Ω', L'∑', L'π', L'№', L'ж', L'د',
                        L'خ', L'צ', L'ש', L'ك', L'∞', L'≠', L'±', L'€',
                        L'♥', L'♠', L'♦', L'♣', L'✓', L'✔', L'✘', L'✿',
                        L'☯', L'☮', L'☀', L'★', L'♩', L'♪'};
const char* formats[] = {
    "%c",       //
    "%0c",      //
    "%10c",     //
    "%10.c",    //
    "%10.5c",   //
    "%0.0c",    //
    "%-10.0c",  //
    "%+10.0c",  //
    "%+c",      //
    "% c",      //
    "%lc",      //
    "%hc",      //
    "%-2c",     //
    "%2c",      //
    "%-c"       //
};
const char* wide_formats[] = {
    "%lc",       //
    "%0lc",      //
    "%10lc",     //
    "%10.lc",    //
    "%10.5lc",   //
    "%0.0lc",    //
    "%-10.0lc",  //
    "%+10.0lc",  //
    "%+lc",      //
    "% lc",      //
    "%lc",       //
    "%hc",       //
    "%c",        //
    "%0c",       //
    "%10c",      //
    "%10.c",     //
    "%10.5c"     //
};

const int size_formats = sizeof(formats) / sizeof(formats[0]);
const int size_wide_formats = sizeof(wide_formats) / sizeof(wide_formats[0]);
const int size_symbs = sizeof(symbs) / sizeof(symbs[0]);
const int size_wide_chars = sizeof(wide_chars) / sizeof(wide_chars[0]);

#endif /* S21_SPRINTF_SIGNLE_C_DATA_H */
