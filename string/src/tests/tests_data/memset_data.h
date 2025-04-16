#ifndef MEMSET_DATA_H
#define MEMSET_DATA_H
#include "../../s21_string.h"
char *buffers[] = {
    "abcdefghijklmno",             // Regular buffer
    "1234567890",                  // Numeric string
    "short",                       // Short string
    "longstringwithmorechars",     // Long string
    "\0\0\0\0\0",                  // Nulls only
    "fill this space",             // Space-filled buffer
    "case_sensitive",              // Mixed case
    "edge_case_buffer",            // Arbitrary text
    "aaaaaaaaaaaaaaaaaaaa",        // Repeated character
    "",                            // Empty string
    "pre_filled_data",             // Pre-filled buffer
    "\0\0\0test\0\0",              // Nulls with embedded text
    "0123456789abcdef",            // Hex-like pattern
    "buffer_with_trailing\0null",  // Text with a null terminator
    "bufferfull",                  // Small, fully used buffer
    "longbuffernearlyempty",       // Large buffer with little data
    "\0",                          // Single null
    "123",                         // Small data for partial fill
    "memsettest",                  // Regular text
    "final_buffer_test",           // Last buffer
};

// Fill characters for memset
int fill_chars[] = {
    'X',   // Regular character fill
    '0',   // Numeric character fill
    '\0',  // Fill with null
    '*',   // Special character
    'A',   // Uppercase alphabet
    ' ',   // Space character
    'z',   // Lowercase alphabet
    '@',   // Special character
    '-',   // Dash
    '!',   // Exclamation mark
    '_',   // Underscore
    '\n',  // Newline character
    '\t',  // Tab character
    '1',   // Numeric character
    'y',   // Lowercase alphabet
    'M',   // Uppercase alphabet
    'o',   // Lowercase alphabet
    '%',   // Percent sign
    'k',   // Lowercase alphabet
    '#',   // Hash
};

// Number of bytes to fill
s21_size_t fill_sizes[1024] = {
    5,   // Partial fill
    10,  // Full fill
    0,   // Zero bytes (edge case)
    20,  // Fill up to buffer size
    3,   // Small fill
    15,  // Partial fill
    7,   // Partial fill
    17,  // Partial fill
    16,  // Full buffer fill
    0,   // Edge case: no fill
    12,  // Partial fill
    6,   // Partial fill with embedded nulls
    8,   // Fill up to half the buffer
    25,  // Fill past the null terminator
    10,  // Partial fill
    10,  // Partial fill
    1,   // Single-byte fill
    2,   // Tiny fill
    8,   // Partial fill
    18   // Fill the entire buffer
};

const s21_size_t size_buffers = sizeof(buffers) / sizeof(buffers[0]);
const s21_size_t size_fill_chars = sizeof(fill_chars) / sizeof(fill_chars[0]);
s21_size_t tests_num = 0;
#endif