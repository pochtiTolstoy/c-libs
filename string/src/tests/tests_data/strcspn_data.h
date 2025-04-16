#ifndef STRCSPN_DATA_H
#define STRCSPN_DATA_H
#include "../../s21_string.h"
const char* source_buff[] = {
    "",                           // Empty string
    "number: 4-8-15-16-23-42",    // Alphanumeric with special characters
    "test all of it!",            // Sentence with spaces
    "abcdef",                     // Simple string
    "abc",                        // Short string
    "1234567890",                 // Numbers only
    "!@#$%^&*()",                 // Special characters
    "Whitespace\tand\nnewlines",  // Includes whitespace and newlines
    "CaseSensitivityCheckABC",    // Mixed case
    "RepeatingPattern123123",     // Repeated pattern
    "OverlappingCharacters",      // String with many unique characters
    "SingleCharacter",            // No overlapping with template
    "EdgeCaseWithNoOverlap",      // Completely unique
    "LastCaseToTestHere",         // General long case
    "EmptyCasesHereAndThere",     // Mix of common and edge scenarios
    "Trailing space ",            // String ending with space
    "  Leading space",            // String with leading spaces
    "123456abcdef",               // Alphanumeric mix
    "ShortOne",                   // Short and simple
    "Tab\tIncluded",              // Tab included
    "NullChar\0HiddenPart",       // Embedded null character
    "EndWithNull\0",              // Ends with a null character
    "\tTabbedStart",              // Starts with a tab
    "\nNewlineStart",             // Starts with a newline
    "\t\nMixedWhitespace",        // Tabs and newlines together
    "!!!Special@@@",              // Repeated special characters
    "1234!5678#90",               // Mix of numbers and special characters
    "CaseTestAbcABC",             // Case-sensitive test
    "Repeating aaaabbbbcccc",     // Repeated character groups
    "LongStringWithNoTemplateMatchToTestLimits",  // Long string with no match
    "UnicodeTest😊👍",                            // Unicode characters
    "\x01\x02\x03BinaryData",  // Binary-like data with control characters
    "Short",                   // Very short string
    " ",                       // Single space
    "\t",                      // Single tab
    "\n",                      // Single newline
    "\0",                      // Single null character
    "Mixed\x00EmbeddedNull",   // Mixed characters with embedded null
    "LoremIpsumLoremIpsumLoremIpsumLorem",  // Long repeating pattern
    "\0",                                   // Single null character
    " \t\n",                                // Whitespace mix
    "NonOverlapping1234",                   // Characters with no overlap
    "!!!@@@",                               // Repeated special characters
    "UniquePatternXYZ",                     // Non-overlapping unique pattern
    "a",                                    // Single character
    "😊",                                   // Single Unicode character
    "\x01\x02\x03",                         // Binary-like control characters
    "CaseSensitiveABC",                     // Case-sensitive match
    "TrailingNull\0Test",                   // Ends with embedded null
    "LeadingWhitespace ",                   // Starts with a space
    "\t\t\t",                               // Only tabs
    "\n\n\n",                               // Only newlines
    "OnlySpaces   ",                        // Only spaces
    "123abcdef456",                         // Mix of numbers and letters
    "ExtremelyLongTemplateToTestBoundaryConditionsInFunctionality",  // Very
                                                                     // long
    "LoremIpsumLoremIpsum",  // Repeated long pattern
    "EdgeCase:123!@#",       // Combination of special characters
};
const s21_size_t size_source = sizeof(source_buff) / sizeof(source_buff[0]);
const char* template_buff[] = {
    "",                            // Empty string
    "1234567890",                  // Numbers only
    "test",                        // Simple word
    "xyz",                         // Non-overlapping characters
    "abef",                        // Partial overlap with source
    "abcdef",                      // Complete match with a source string
    "abc",                         // Short string
    "!@#$%^&*",                    // Special characters only
    "WhitespaceNewlines",          // Mix with spaces/newlines
    "CASECHECK",                   // Uppercase only
    "123",                         // Short numeric
    "UniqueTemplateSet",           // Non-overlapping template
    "Pattern",                     // Substring of a source
    "Overlapping",                 // Partial overlap
    "Single",                      // A common word
    "Spaces Here",                 // String with spaces
    "\t\n",                        // Tabs and newlines
    "LongerTemplateForEdgeCases",  // Very long template
    "abcdef123",                   // Alphanumeric overlap
    "TrailingWhitespace ",         // String with trailing space
};
const s21_size_t size_template =
    sizeof(template_buff) / sizeof(template_buff[0]);

s21_size_t tests_num = 0;
#endif