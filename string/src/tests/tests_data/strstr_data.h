#ifndef STRSTR_DATA_H
#define STRSTR_DATA_H
#include "../../s21_string.h"
const char *haystacks[] = {
    "simpleexample",              // Normal string
    "12345678901234567890",       // Numeric string
    "",                           // Empty string
    "shortstring",                // Short haystack
    "repeatedsubstringrepeated",  // Repeated substring
    "string\0withnull",           // Embedded null character
    "\0leadingnull",              // Leading null character
    "aaaaaaaaaaa",                // Repeated single character
    "special_characters:!@#",     // String with special characters
    "embedded\0nulltest",         // Null terminator within string
    "thisisateststring",          // Regular string
    "trailingspace   ",           // String with trailing spaces
    "substring\0withpadding",     // Null terminator within
    "this_is_a_test_string",      // Underscore-separated words
    "overlappingoverlapping",     // Overlapping substrings
    "nospaceshere",               // No spaces
    "longstringwithkeywords",     // Long string with embedded keywords
    "\0onlynull",                 // Single null character
    "hello",                      // Simple short string
    "endwithpatternpattern",      // Ends with repeated pattern
    "simpleexample",              // Repeated string
    "12345678901234567890",       // Repeated numeric string
    "",                           // Repeated empty string
    "shortstring",                // Repeated short haystack
    "repeatedsubstringrepeated",  // Repeated repeated substring
    "string\0withnull",           // Repeated embedded null character
    "\0leadingnull",              // Repeated leading null character
    "aaaaaaaaaaa",                // Repeated single character
    "special_characters:!@#",     // Repeated string with special characters
    "embedded\0nulltest",         // Repeated null terminator within string
    "thisisateststring",          // Repeated regular string
    "trailingspace   ",           // Repeated string with trailing spaces
    "substring\0withpadding",     // Repeated null terminator within
    "this_is_a_test_string",      // Repeated underscore-separated words
    "overlappingoverlapping",     // Repeated overlapping substrings
    "nospaceshere",               // Repeated no spaces
    "longstringwithkeywords",     // Repeated long string with embedded keywords
    "\0onlynull",                 // Repeated single null character
    "hello",                      // Repeated simple short string
    "endwithpatternpattern",      // Repeated ends with repeated pattern
};

const char *needles[] = {
    "example",    // Normal match
    "5678",       // Numeric substring
    "",           // Empty needle
    "short",      // Full haystack match
    "repeated",   // Repeated substring
    "null",       // Substring after null
    "null",       // Substring not found (after leading null)
    "aaa",        // Substring of repeated character
    "special_",   // Substring with special character
    "null",       // Substring after null
    "test",       // Substring in the middle
    "space",      // Substring near trailing space
    "substring",  // Substring before null
    "test",       // Substring within underscores
    "lap",        // Substring in overlapping sequence
    "here",       // Substring at the end
    "keywords",   // Substring at the end
    "\0",         // Null character
    "ell",        // Middle substring
    "pattern",    // Substring at the end
    "example",    // Repeated normal match
    "5678",       // Repeated numeric substring
    "",           // Repeated empty needle
    "short",      // Repeated full haystack match
    "repeated",   // Repeated substring
    "null",       // Repeated substring after null
    "null",       // Repeated substring not found (after leading null)
    "aaa",        // Repeated substring of repeated character
    "special_",   // Repeated substring with special character
    "null",       // Repeated substring after null
    "test",       // Repeated substring in the middle
    "space",      // Repeated substring near trailing space
    "substring",  // Repeated substring before null
    "test",       // Repeated substring within underscores
    "lap",        // Repeated substring in overlapping sequence
    "here",       // Repeated substring at the end
    "keywords",   // Repeated substring at the end
    "\0",         // Repeated null character
    "ell",        // Repeated middle substring
    "pattern",    // Repeated substring at the end
};
const s21_size_t size_buffers = sizeof(haystacks) / sizeof(haystacks[0]);
const s21_size_t size_needles = sizeof(needles) / sizeof(needles[0]);
s21_size_t tests_num = 0;
#endif