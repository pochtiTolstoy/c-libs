#ifndef STRRCHR_DATA_H
#define STRRCHR_DATA_H
#include "../../s21_string.h"
const char *buffers[] = {
    "simpleexample",                   // Normal string
    "12345678901234567890",            // Numeric string
    "",                                // Empty string
    "shortstring",                     // Short string
    "longstringwithrepeatedchars",     // Long string with repeated characters
    "string\0withnull",                // Embedded null character
    "\0leadingnull",                   // Leading null character
    "aaaaaaaaaaa",                     // Repeated single character
    "special_characters:!@#",          // String with special characters
    "embedded\0nulltest",              // Null terminator within string
    "0123456789abcdef",                // Hex-like string
    "trailingspace   ",                // String with trailing spaces
    "middlenull\0padding",             // String with a null in the middle
    "this_is_a_test_string",           // Underscore-separated words
    "repeatedpatternrepeatedpattern",  // Repeated substring
    "nospaceshere",                    // No spaces
    "lastcharz",                       // Ends with target character
    "\0onlynull",                      // Single null character
    "hello",                           // Simple short string
    "endswithunderscore_",             // Ends with special character
};

// Characters to Search
// This array represents characters we want to search for in the corresponding
// buffer.
int search_chars[] = {
    'e',   // Last occurrence
    '5',   // Middle occurrence
    '\0',  // Null terminator
    's',   // Middle character
    'r',   // Repeated character
    'g',   // Before embedded null
    'l',   // After leading null
    'a',   // Repeated character
    ':',   // Special character
    'e',   // Character after embedded null
    'f',   // Last occurrence
    ' ',   // Trailing space
    'n',   // After embedded null
    '_',   // Special character
    'r',   // Repeated character
    'z',   // Absent character
    'z',   // Present as last character
    '\0',  // Single null terminator
    'o',   // Middle occurrence
    '_',   // Special character
};
const s21_size_t size_buffers = sizeof(buffers) / sizeof(buffers[0]);
const s21_size_t size_search_chars =
    sizeof(search_chars) / sizeof(search_chars[0]);
s21_size_t test_num = 0;
#endif