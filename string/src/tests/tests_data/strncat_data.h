#ifndef STRNCAT_DATA_H
#define STRNCAT_DATA_H
#include "../../s21_string.h"
const char *destbuff[] = {
    "Hello, ",             // Normal string
    "",                    // Empty string
    "Initial ",            // Prefixed string
    "some text",           // Regular text
    "string\0 with zero",  // Embedded null character
    "\0text",              // Starts with a null character
    "12345",               // Numeric string
    "Punctuation:",        // Ends with punctuation
    "Spaces at end ",      // Ends with space
    "Tabs\tin\tdest",      // Contains tabs
    "New\nlines",          // Contains newlines
    "Special$Chars!",      // Special characters
    "Mix123Alpha",         // Alphanumeric mix
    "CaseSensitive",       // Mixed case
    "Trailing spaces   ",  // Trailing spaces
    "PrefixOnly",          // No overlapping with srcbuff
    "LongDestinationStringWithNoSpaces",
    "Short",                // Short destination string
    "Contains,Delimiters",  // Delimiters
    ""                      // Another empty string
};

const char *srcbuff[] = {
    "world!",               // Normal string
    "",                     // Empty string
    "non-empty string",     // Regular string
    "",                     // Another empty string
    "src\0 with zero",      // Embedded null character
    "\nbyte\t0",            // Contains newlines and tabs
    "67890",                // Numeric string
    "!EndWithExclaim",      // Ends with punctuation
    "LeadingSpaces",        // Leading spaces
    "Tabs\tand\nSpaces",    // Tabs and spaces
    "AlphaBeta123",         // Alphanumeric mix
    "Special#Symbols",      // Special symbols
    "CaseSensitiveSrc",     // Mixed case
    "OverlappingDest",      // Potential overlap
    "ExactMatchTest",       // Matches part of destbuff
    "UnicodeTest™",         // Contains Unicode
    "Short",                // Short source string
    "MoreDelimiters,,,",    // Delimiters
    "TrailingWhitespace ",  // Ends with a space
    "FinalSRC"              // Final test case
};

const s21_size_t lenbuff[] = {
    6,   // Normal length
    6,   // Length for empty destbuff
    9,   // Partial concatenation
    1,   // Append one character
    8,   // Includes null character
    7,   // Mix of tabs and newlines
    5,   // Exact length of srcbuff
    10,  // Longer than srcbuff
    15,  // Includes leading spaces
    8,   // Includes tabs and spaces
    12,  // Full concatenation
    4,   // Partial special characters
    6,   // Case-sensitive substring
    9,   // Overlapping part
    14,  // Full match length
    8,   // Unicode test length
    2,   // Short srcbuff
    18,  // Delimiters with whitespace
    20,  // Beyond srcbuff length
    0    // No concatenation
};
const s21_size_t size_destbuff = sizeof(destbuff) / sizeof(destbuff[0]);
const s21_size_t size_srcbuff = sizeof(srcbuff) / sizeof(srcbuff[0]);
const s21_size_t size_lenbuff = sizeof(lenbuff) / sizeof(lenbuff[0]);

s21_size_t tests_num = 0;
#endif