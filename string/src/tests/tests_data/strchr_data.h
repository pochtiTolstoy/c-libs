#ifndef STRCHR_DATA_H
#define STRCHR_DATA_H
#include "../../s21_string.h"
const char *buffers[] = {
    "abcdefghijklmno",                      // Regular string
    "1234567890",                           // Numeric string
    "short",                                // Short string
    "longstringwithmorechars",              // Long string
    "\0\0\0\0\0",                           // Nulls only
    "fill this space",                      // Space-filled buffer
    "case_sensitive",                       // Mixed case
    "edge_case_buffer",                     // Arbitrary text
    "aaaaaaaaaaaaaaaaaaaa",                 // Repeated character
    "",                                     // Empty string
    "pre_filled_data",                      // Pre-filled buffer
    "\0\0\0test\0\0",                       // Nulls with embedded text
    "0123456789abcdef",                     // Hex-like pattern
    "buffer_with_trailing\0null",           // Text with a null terminator
    "bufferfull",                           // Small, fully used buffer
    "longbuffernearlyempty",                // Large buffer with little data
    "\0",                                   // Single null
    "123",                                  // Small data for partial search
    "findmehere",                           // Regular text
    "final_buffer_test",                    // Last buffer
    "-",                                    // Dash for test case
    "simpletextfortesting",                 // Simple text for basic testing
    "numerical1234567890",                  // Numeric characters
    "longertextwithspecialcharacters!@#$",  // Longer text with special chars
    "smallsizebuffer",                      // Smaller buffer for testing
    "repeatedcharactersaaaaaaaaaaaaaaaa",   // Repeated 'a' characters
    "onewordtest",                          // One word buffer
    "buffertestwithspacesinbetween",        // Test with spaces in between
    "underscore_test_case",                 // String with underscores
    "characterswithsymbols!#^",             // Characters with symbols
    "emptyspacebuffer       ",              // Buffer with trailing spaces
    "finalteststringwithnumbers123",        // Final test with mixed content
    "endofbuffertest",                      // End test case buffer
    "moretexttoworkwith",                   // Additional test string
    "thequickbrownfoxjumpsoverthelazydog",  // Long famous pangram
    "itwasagreatdayintheend",               // Another meaningful sentence
    "spacesandmore   ",             // String with multiple spaces at end
    "tabbed\ttext\tin\tbuffer",     // String with tabs inside
    "multiline\nbuffer\ntest",      // Multi-line text buffer
    "randomcharstestwithspaces",    // Random chars and spaces
    "anotherfinaltest",             // A last testing buffer
    "edgecaseempty\0buffer",        // Edge case with empty null buffer
    "testcasewithmultiplevalues",   // Test case with mixed values
    "longerstringwithtab\tsymbol",  // String with tab and symbol
    "doublespaceinmiddle  test"     // Test string with double spaces
};

int search_chars[] = {
    'a',   // Character present at the start
    '5',   // Character present in the middle
    '\0',  // Search for null terminator
    'g',   // Character in the middle of the string
    'A',   // Uppercase character not present
    ' ',   // Space character
    's',   // Character in the middle
    '_',   // Underscore
    'a',   // Repeated character
    'x',   // Character not in string
    'd',   // Character in the middle
    't',   // Character after embedded null
    '9',   // Last character
    'n',   // Character before null terminator
    'f',   // Repeated character
    'e',   // Last character in string
    '\0',  // Null terminator in a single-null buffer
    '2',   // Middle character in a small string
    'm',   // Middle character
    't',   // Last character
    'a',   // Another 'a'
    'b',   // First character of a new word
    'z',   // Last character
    '7',   // Numeric character from middle
    '!',   // Special symbol
    '#',   // Another special symbol
    '^',   // Another special character
    'x',   // Character that does not exist in the buffer
    '@',   // Special symbol for test
    'q',   // Character from the middle of long buffer
    't',   // Check for repeated 't'
    'y',   // Check for character 'y'
    'j',   // Testing an uncommon character
    'r',   // Check for lowercase 'r'
    'h',   // Check for lowercase 'h'
    'u',   // Uppercase character for case sensitivity
    'l',   // Check for lowercase 'l'
    'p',   // Character present in buffer
    '1',   // Numeric character in the string
    'o',   // Check for lowercase 'o'
    'w',   // Check for lowercase 'w'
    '0',   // Test for numeric 0
    'i',   // Another middle character to check
    'j',   // Another test character
    'n',   // Check null-terminated strings
    'c',   // Simple check
    'b',   // Check second position character
    'e',   // Check last character
    'v',   // Check for character 'v'
    'z',   // Another uncommon character
    'k',   // Check for 'k' character in the buffer
    'g',   // Test for character 'g'
    'd',   // Testing for 'd' in buffer
    'm',   // Another common character test
    'o',   // Another check for lowercase 'o'
    'q',   // Uncommon check for 'q'
    'r',   // Another middle test case
    'j',   // Another middle test case
    't',   // Another test of 't'
    'p',   // Character to test
};

const s21_size_t size_buffers = sizeof(buffers) / sizeof(buffers[0]);
const s21_size_t size_search_chars =
    sizeof(search_chars) / sizeof(search_chars[0]);
s21_size_t test_num = 0;
#endif