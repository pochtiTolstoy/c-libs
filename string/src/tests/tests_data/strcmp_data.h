#ifndef STRNCMP_DATA_H
#define STRNCMP_DATA_H
#include "../../s21_string.h"
const char *strbuff1[] = {
    "abcdef",          // Identical strings
    "hello",           // Different strings, first difference at the first char
    "world",           // Different strings, first difference later
    "foo\0bar",        // Embedded nulls, same prefix
    "foo\0baz",        // Embedded nulls, different suffix
    "",                // Empty string
    "a",               // Single character
    "substring",       // Strings with subset relationships
    "substringextra",  // Longer version of the above
    "commonprefix",    // Common prefix but different suffix
    "commonprefixother",
    "abcdefghijk",  // Strings of different lengths
    "abcd",         // Shorter string compared with longer
    "aaaaa",        // Strings with repeated characters
    "aaaab",        // Same repeated pattern, one difference
    "\0\0\0\0\0",   // Strings of only null characters
    "\0\0\0\0\1",   // Strings of nulls with a different last character
    "short",        // A shorter string compared fully
    "shortend",     // A different but longer string
    "sameuntilnull\0different"  // Null terminator cuts comparison
};

const char *strbuff2[] = {
    "abcdef",           // Identical strings
    "jello",            // Different strings, first difference at the first char
    "worry",            // Different strings, first difference later
    "foo\0baz",         // Embedded nulls, different suffix
    "foo\0baz",         // Same as above
    "",                 // Empty string
    "b",                // Single character, different
    "subs",             // Strings with subset relationships
    "substringextra",   // Identical
    "commonprefixend",  // Common prefix but different suffix
    "commonprefixother",  // Identical
    "abcdefghijkx",       // Strings of different lengths, one extra char
    "abcdxyz",            // Shorter string with extra suffix
    "aaaaa",              // Identical
    "aaaac",              // Same repeated pattern, one difference
    "\0\0\0\0\0",         // Strings of only null characters
    "\0\0\0\0\2",         // Strings of nulls with a different last character
    "short",              // Identical
    "shortadd",           // Different but longer string
    "sameuntilnull\0differentstuff"  // Null terminator cuts comparison
};

s21_size_t lenbuff[] = {
    6,   // Compare full length
    5,   // Compare up to the last char
    5,   // Compare full length
    7,   // Compare beyond the null terminator
    7,   // Compare beyond the null terminator
    0,   // Compare zero bytes (edge case)
    1,   // Compare single character
    4,   // Compare partial length
    16,  // Compare full length
    13,  // Compare full length
    16,  // Compare full length
    12,  // Compare full length
    4,   // Compare up to the shorter string
    5,   // Compare full length
    5,   // Compare full length
    5,   // Compare nulls
    5,   // Compare nulls with different last character
    5,   // Compare full length
    7,   // Compare full length
    20   // Compare beyond the null terminator
};

const s21_size_t size_strbuff1 = sizeof(strbuff1) / sizeof(strbuff1[0]);
const s21_size_t size_strbuff2 = sizeof(strbuff2) / sizeof(strbuff2[0]);
const s21_size_t size_len_buff = sizeof(lenbuff) / sizeof(lenbuff[0]);
s21_size_t tests_num = 0;
#endif