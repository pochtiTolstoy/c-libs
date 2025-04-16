#ifndef STRLEN_DATA_H
#define STRLEN_DATA_H
#include "../../s21_string.h"
const char* stack_str_buff[] = {
    "null\0terminated",              // Embedded null character
    "",                              // Empty string
    ".",                             // Single character
    "\t",                            // Tab
    "\n",                            // Newline
    "\t\t",                          // Multiple tabs
    "\t\n",                          // Mixed tab and newline
    "Hello, world!",                 // Standard string
    "How are you today?",            // Question
    "A single character",            // Normal sentence
    "Special$Chars@Example#Test",    // Special characters
    "Mix123andWords456",             // Numbers mixed with text
    "CaseInsensitiveCHECK",          // Mixed case
    "Multiple spaces   between",     // Multiple spaces
    "Two,,Delimiters,Here",          // Consecutive delimiters
    "Extra ,spaces ,with ,commas",   // Delimiters with spaces
    ",,,",                           // Only commas
    ".,!?:;",                        // Only punctuation
    "Short",                         // Short string
    "12345",                         // Numbers only
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ",    // Uppercase letters
    "abcdefghijklmnopqrstuvwxyz",    // Lowercase letters
    "MixedCASE1234567890",           // Mixed case with digits
    "   Leading spaces",             // Leading spaces
    "Trailing spaces   ",            // Trailing spaces
    "Spaces   inside  text",         // Internal multiple spaces
    "Special characters: @#$^&*()",  // Special characters with punctuation
    "Math symbols: +-=*/",           // Math symbols
    "Random, punctuation; marks!",   // Mixed punctuation
    "Tab\tseparated",                // Tab-separated words
    "New\nline",                     // Newline within text
    "\0embedded\0nulls",             // Multiple embedded nulls
    "Escape \\ backslash",           // Escape sequence
    "Quotes 'single' \"double\"",    // Mixed quotes
    "Longer string for testing purposes, just to make sure it handles longer "
    "inputs correctly.",                           // Long string
    "Short one",                                   // Another short string
    "Repeating pattern: abcabcabcabc",             // Repeated pattern
    "Numbers only: 1234567890",                    // Only numbers
    "Binary data: 0101010101",                     // Binary-like data
    "Hexadecimal: 0xDEADBEEF",                     // Hexadecimal
    "Paths: /usr/local/bin/",                      // File paths
    "URLs: https://example.com",                   // URL
    "Emails: user@example.com",                    // Email address
    "JSON: {\"key\": \"value\"}",                  // JSON format
    "XML: <tag>value</tag>",                       // XML format
    "SQL: SELECT * FROM table;",                   // SQL query
    "Programming: printf(\"Hello, world!\\n\");",  // Code snippet
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit.",  // Lorem Ipsum
    "More numbers: 9876543210",            // Another set of numbers
    "Repeating char: aaaaaaaaaaaaaaaaaa",  // Repeated character
    "Unicode: 💻✨🚀",                     // Unicode characters
    "Control chars: \x01\x02\x03\x04",     // Control characters
    "Empty spaces:          ",             // Many spaces
    "Long whitespace\t\n\t\n",             // Mixed whitespace
    "Newline and tab combo\n\t\n\t",       // Alternating newline and tab
    "Multiline:\nLine1\nLine2\nLine3",     // Multiline text
    "Delimiters;;;,,;;",                   // Repeated delimiters
    "Only commas,,,,",                     // Only commas
    "Only periods....",                    // Only periods
    "Only spaces         ",                // Only spaces
    "Only tabs\t\t\t\t",                   // Only tabs
    "Lorem Ipsum Repeated: Lorem ipsum lorem ipsum lorem ipsum.",  // Repeated
                                                                   // text
    "Palindrome: abccba",                                          // Palindrome
    "Not a palindrome: abcba",                 // Near palindrome
    "Odd length palindrome: abcba",            // Palindrome with odd length
    "Even length palindrome: abba",            // Palindrome with even length
    "Math equation: 2 + 2 = 4",                // Math expression
    "Greetings: Hi, hello, hey!",              // Greetings
    "Multilingual: Привет, こんにちは, 你好",  // Multilingual text
    "Zero byte test\0\0\0",                    // Multiple consecutive nulls
    "\0",                                      // Single null character
    "Trailing null char\0after",               // Null at end of visible string
    "Special escape: \n\t\0",  // Combination of escape sequences
    "Maximum string length "   // Long repeated string to test limits
    "abcdefghijklmnopqrstuvwxyz"
    "abcdefghijklmnopqrstuvwxyz"
    "abcdefghijklmnopqrstuvwxyz",
    "Invisible control: \x01\x7F\x80\xFF"  // Edge control characters and
                                           // extended ASCII
};

const s21_size_t size_stack_buff =
    sizeof(stack_str_buff) / sizeof(stack_str_buff[0]);
s21_size_t tests_num = 0;
#endif