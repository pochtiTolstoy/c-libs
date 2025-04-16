#ifndef STRPBRK_DATA_H
#define STRPBRK_DATA_H
#include "../../s21_string.h"
const char* strbuff1[] = {
    "1234567890",                // Number string
    "abcdefgh",                  // Characters string
    "Hello\n\t, world!\0",       // String with special symbols
    "Hello\0, world!",           // String with null terminator
    "",                          // Empty string
    "!@#$%^&*",                  // Symbols string
    "!@#$%^&*",                  // Symbols string
    "!@#$%^&*",                  // Symbols string
    "!@#$%^&*1",                 // Symbols string
    "!@#$%^&*1",                 // Symbols string
    "!@#$%^&*1",                 // Symbols string
    "a",                         // Single character string
    "b",                         // Single character string
    "\0\0\0\0 0",                // NULL terminated string
    "xyz",                       // NULL terminated string
    "xyz",                       // NULL terminated string
    "123abc456def",              // Mixed number and letters
    "Alphabet123456",            // Letters and numbers with different order
    "TestStringWithSpaces",      // String with spaces
    "Multiple\nNewlines\nHere",  // String with multiple newlines
    "Tabs\tand\tSpaces",         // String with tabs
    "SpecialChars!@#^&*()",      // Special characters and symbols
    "RandomCharacters!$%&",      // Random characters with special symbols
    "TheQuickBrownFox",          // A well-known phrase
    "JumpsOverLazyDog",          // Continuation of previous phrase
    "Test\nWith\tWhitespace",    // Mixed whitespace (spaces, tabs, newline)
    "LongStringWithSpecial$Characters123",  // Long alphanumeric string
    "1234567890abcdef",          // Alphanumeric string with numbers and letters
    "HelloWorldWithNumbers123",  // Mixed case with numbers
    "Testing\nLineBreaks",       // Test for line breaks
    "StringWithSpaceAtEnd ",     // String with trailing space
    "SomeRandomText\tand\tSpaces",  // Text with tabs and random spaces
    "EdgeCase1\nEdgeCase2",         // Edge case with line breaks
    "EmptySpace\tAtStart",          // String with leading tab
    "NoNull\0InMiddle",             // String with null in middle
    "StringWithVeryLongLength1234567890AndMore",  // Very long string
    "Special!StringWithSome$Characters",          // Special character string
    "SecondOne",                                  // Another simple string
    "LargeTestCaseWithNumbers9876543210",         // Large test case
    "StillGoingWithNumbers987654",                // More numeric string
    "ShortTest",                                  // Short string for comparison
    "123456789012345678901234567890",             // Long numeric string
    "abcdefabcdefabcdefabcdefabcdef",             // Repeating alphabetic string
    "   LeadingSpaces",                           // Leading spaces
    "TrailingSpaces   ",                          // Trailing spaces
    "Mix of 123 and abc!",            // Mixed alphanumeric and symbols
    "\0",                             // String with only null terminator
    "Tabs\t\t\tAndNewlines\n\n",      // Multiple tabs and newlines
    "EmptyStringTest",                // Redundant test for empty handling
    "AllSpecial@!#$%^&*()<>[]{}",     // Special characters only
    "MixedCasesABCabc123",            // Mixed cases and numbers
    "Multiple\n\n\nLineBreaks",       // Multiple line breaks
    "\x01\x02\x03ControlChars",       // Control characters at start
    "NonPrintable\xFF\xFE\xFD",       // Non-printable ASCII
    "UnicodeString😊🚀✨",            // Unicode characters
    "12345Embedded\0Null",            // Embedded null in the middle
    "StringWithTabsAndSpaces\t\t  ",  // Combination of tabs and spaces
    "EndsWithNull\0",                 // Ends with null character
    "ShortOneChar",                   // Very short alphanumeric string
    "SpecialCharMix!@#$%^",           // Mixed special characters
    "AllNumbers1234567890",           // String with all numbers
    "ExtraLongTestForBoundaryCasesabcdefghijklmnopqrstuvwxyz1234567890"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ",  // Long boundary string
};

const char* strbuff2[] = {
    "1",                         // Find first character
    "h",                         // Find last character
    "\n\t",                      // Find special symbols
    "\0Hello",                   // Find null terminator
    "abcd",                      // Find in empty string
    "..!..",                     // Find symbol after few misses
    "..@..",                     // Find symbol after few misses
    "..#..",                     // Find symbol after few misses
    "..$..",                     // Find symbol after few misses
    "..%..",                     // Find symbol after few misses
    "..^..",                     // Find symbol after few misses
    "bcdef",                     // Find expected NULL
    "bcdef",                     // Find symbol in single character string
    "0",                         // Find symbol in null-terminated string
    "abc\0xyz",                  // Find symbols abc in xyz, expected NULL
    "xyz\0abc",                  // Find symbols xyz in xyz
    "QuickBrown",                // Find word from a famous sentence
    "FoxJumped",                 // Continuation of above famous sentence
    "SpaceTest ",                // String with trailing space
    "TestTabs\t\t",              // String with multiple tabs
    "Multiple\nLineBreaks",      // String with multiple line breaks
    "RandomTextWithNumbers123",  // Random alphanumeric mix
    "Special#Symbols!Test",      // Symbols in the string
    "WhitespaceAndTabs\t \n",    // Whitespace mixed with tabs and newlines
    "EdgeCase\0Test",            // Test with null terminator inside
    "LastCharactersAtEnd",       // String ending with characters
    "StringWith123Numbers",      // String with numbers in between
    "MixedUpperLowerCASE",       // Case sensitivity test
    "TestWithSpecialChars!@#",   // Special characters for testing
    "MoreEdgeCasesHere",         // More complex test cases
    "EvenMoreEdgeCase",          // Further complex test case
    "ExtraSpaceHere ",           // With extra space at the end
    "EmptyStringTest",           // Another empty string to check
    "ShortString",               // Short string for quick tests
    "AnotherLongTestWithNumbers1234567890",  // Large test string with numbers
    "FindNewLines\tSpaces",                  // Searching for spaces and tabs
    "BoundaryCaseTesting\0",       // Test with null terminator in the middle
    "DifferentPatterns123",        // Alphanumeric pattern
    "AlphanumericWithSymbols!@#",  // Alphanumeric with symbols
    "TestingLongPatternsWithNumbers9876543210",  // Long pattern test
    "FinalTestCase",                // Last test case for completion
    "Edge\nLineBreak\0Test",        // Test with line breaks and null character
    "EndOfTestCase",                // Another ending string
    "SearchPatterns123456",         // Searching for patterns
    "CharactersWithSpacesAndMore",  // With spaces and characters
    "TabsInTest\tAndEnd",           // String with tabs in the middle
    "AnotherSimpleTest",            // Simple test case
    "\0",                           // Single null character
    " \t\n",                        // Whitespace mix
    "NonOverlapping1234",           // Characters with no overlap
    "!!!@@@",                       // Repeated special characters
    "UniquePatternXYZ",             // Non-overlapping unique pattern
    "a",                            // Single character
    "😊",                           // Single Unicode character
    "\x01\x02\x03",                 // Binary-like control characters
    "CaseSensitiveABC",             // Case-sensitive match
    "TrailingNull\0Test",           // Ends with embedded null
    "LeadingWhitespace ",           // Starts with a space
    "\t\t\t",                       // Only tabs
    "\n\n\n",                       // Only newlines
    "OnlySpaces   ",                // Only spaces
    "123abcdef456",                 // Mix of numbers and letters
    "ExtremelyLongTemplateToTestBoundaryConditionsInFunctionality",  // Very
                                                                     // long
    "LoremIpsumLoremIpsum",  // Repeated long pattern
    "EdgeCase:123!@#",       // Combination of special characters
};
const s21_size_t size_strbuff1 = sizeof(strbuff1) / sizeof(strbuff1[0]);
const s21_size_t size_strbuff2 = sizeof(strbuff2) / sizeof(strbuff2[0]);

s21_size_t tests_counter = 0;

#endif