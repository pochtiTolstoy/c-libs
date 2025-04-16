#ifndef MEMCHR_DATA_H
#define MEMCHR_DATA_H
#include "../../s21_string.h"
const char* srcbuff[] = {
    "",                                   // Empty string
    "abc\nabc",                           // String with newline
    "abcabc",                             // Repeated pattern
    "Hello world!",                       // Standard string
    "This is the end\n of the line",      // Multiline string
    "\tThis is tab test",                 // String with tab
    "oh,\0&here we go again",             // Embedded null character
    "18880 inhales",                      // Numeric in string
    "give me 0xaf1ae3b2 apples, please",  // Hexadecimal in string
    "just a normal string here",          // Regular text
    "\n\n\n",                             // Multiple newlines
    "\t\t\t",                             // Multiple tabs
    "\0\0\0\0",                           // Multiple null characters
    "\a\b\f\n\r\t\v",                     // Escape sequences
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ",         // Uppercase alphabet
    "abcdefghijklmnopqrstuvwxyz",         // Lowercase alphabet
    "0123456789",                         // Digits
    "!"
    "#$%&'()*+,-./:;<=>?@[\\]^_`{|}~",              // Special characters
    "The quick brown fox jumps over the lazy dog",  // Pangram
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
    "Sed do eiusmod tempor incididunt ut labore et dolore magna "
    "aliqua.",                                          // Long
                                                        // text
    "Binary data:\x01\x02\x03\x04\xFF\xFE\xFD",         // Binary-like data
    "Repeated char aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",  // Repeated
                                                        // single char
    "Mix of patterns: \t\n\0abcABC123!@#",              // Mixed patterns
    "End with null char\0",  // Ends with null character
    "A string that's longer than the typical buffer size to test large "
    "inputs, "
    "which might break certain assumptions about memory usage.",  // Large
                                                                  // input
    // Additional entries for doubling the array
    "Random test string with symbols !@#$%^&*()",  // Symbols mixed in
    "Another one bites the dust.",                 // Regular sentence
    "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09",    // Sequence of control
                                                   // bytes
    "Strings with emojis 😊👍🔥💻",                // Unicode emojis
    "Text ending abruptly...\n",                   // Unusual termination
    "12345\0hidden part of string",                // Null in the middle
    "Different cases: UPPER lower MiXeD",          // Mixed case
    "An exceptionally long string to test performance and edge cases, "
    "ensuring that any bottleneck or limitation in the function is "
    "exposed "
    "through comprehensive testing methodology.",      // Another large
                                                       // input
    "Unique bytes: \x10\x20\x30\x40\x50\x60\x70\x80",  // Arbitrary hex
                                                       // bytes
    "Padding with spaces      ",                       // Trailing spaces
    "\n\n\n\n\n\n\n\n",                                // Many newlines
    "\t\t\t\t\t\t\t\t",                                // Many tabs
    "Short",                                           // Single word
    "SpEcIaLcHaRs:~`<>[]{}\\|_^",                      // Unusual characters
    "Trailing null char in this string\0",       // Explicitly ends with \0
    "\xFF\xFE\xFD\xFC\xFB\xFA",                  // High ASCII/hex
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",  // Repeated uppercase
    "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ",   // Different repeated
                                                 // char
    "More escape sequences: \n\r\f\t\b\a\v",     // Complex escape cases
};
s21_size_t size_srcbuff = sizeof(srcbuff) / sizeof(srcbuff[0]);

const char symbbuff[] = "\0&0xaf,\n\t.A!H8";
s21_size_t size_symbbuff = sizeof(symbbuff) / sizeof(symbbuff[0]);

/* do not pass greater number than smallest strlen of srcbuff string */
const s21_size_t nbuff[] = {0, 1, 2, 3, 4, 5};
s21_size_t size_nbuff = sizeof(nbuff) / sizeof(nbuff[0]);
s21_size_t tests_num = 0;
#endif
