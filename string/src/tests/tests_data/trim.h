#ifndef TRIM_H
#define TRIM_H
#include "../../s21_string.h"
const char *input_string[] = {"   Hello World   ",
                              "Test String!!!",
                              "\tTabbed Line\t",
                              "---Dashes---",
                              "###Hash###Tag###",
                              "   Leading and Trailing Spaces   ",
                              "!!!Exclamation!!!",
                              "12345Numbers54321",
                              "   Mixed###Symbols!!!123   ",
                              "\t\nWhitespace Only\t\n",
                              "---Remove---Dashes---",
                              "     Spaces Everywhere     ",
                              "\t\nTabs and Newlines Only\n\t",
                              "***Stars***Around***",
                              "%%%Percent%%%Signs%%%",
                              "&&&Ampersands&&&",
                              "   Just Spaces   ",
                              "###Mixed---Symbols!!!",
                              "   Final Test Case   ",
                              "!!!Complex###String---\t"};

const char *trim_chars[] = {" ",     "!",   "\t",   "-",   "#", " ",    "!",
                            "12345", " #!", "\t\n", "-",   " ", "\t\n", "*",
                            "%",     "&",   " ",    "#-!", " ", "!#-\t"};

const char *output_string[] = {"Hello World",
                               "Test String",
                               "Tabbed Line",
                               "Dashes",
                               "Hash###Tag",
                               "Leading and Trailing Spaces",
                               "Exclamation",
                               "Numbers",
                               "Mixed###Symbols!!!123",
                               "Whitespace Only",
                               "Remove---Dashes",
                               "Spaces Everywhere",
                               "Tabs and Newlines Only",
                               "Stars***Around",
                               "Percent%%%Signs",
                               "Ampersands",
                               "Just Spaces",
                               "Mixed---Symbols",
                               "Final Test Case",
                               "Complex###String"};

const s21_size_t count_strings = sizeof(input_string) / sizeof(input_string[0]);
s21_size_t test_num = 0;

#endif