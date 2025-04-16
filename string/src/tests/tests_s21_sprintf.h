#ifndef TESTS_S21_SPRINTF_H
#define TESTS_S21_SPRINTF_H

#include <limits.h>

#include "common_header.h"

START_TEST(test_s21_sprintf_single_c) {
#include "sprintf_tests_data/s21_sprintf_single_c_data.h"
  for (int i = 0; i < size_symbs; ++i) {
    symbs[i] = i;
  }

  // TEST BYTE CHARS
  for (int i = 0; i < size_symbs; ++i) {
    for (int j = 0; j < size_formats; ++j) {
      s21_sprintf(s21_buff, formats[j], symbs[i]);
      sprintf(orig_buff, formats[j], symbs[i]);
      ck_assert_str_eq(s21_buff, orig_buff);
    }
  }

  // TEST WIDE CHARS
  setlocale(LC_CTYPE, "");
  for (int i = 0; i < size_wide_chars; ++i) {
    for (int j = 0; j < size_wide_formats; ++j) {
      s21_sprintf(s21_buff, wide_formats[j], wide_chars[i]);
      sprintf(orig_buff, wide_formats[j], wide_chars[i]);
      ck_assert_str_eq(s21_buff, orig_buff);
    }
  }

  printf("[  TESTS  ] s21_sprintf single c tests number : %d\n",
         size_symbs * size_formats + size_wide_chars * size_wide_formats);
}
END_TEST

START_TEST(test_s21_sprintf_multiple_c) {
#include "sprintf_tests_data/s21_sprintf_multiple_c_data.h"
  int test_coutner = 0;

  // TEST ONE BYTE CHAR
  for (int arglen = 1; arglen <= MAX_ARGS_C; ++arglen) {
    for (int test = 0; test < TESTS_C; ++test) {
      TEST_SPRINTF(s21_buff, orig_buff, formats[arglen - 1][test],
                   byte_char_data[arglen - 1][test], arglen);
      ++test_coutner;
    }
  }
  printf("[  TESTS  ] s21_sprintf multiple c tests : %d\n", test_coutner);
}
END_TEST

START_TEST(test_s21_sprintf_multiple_s) {
  char s21_buff[1024];
  char orig_buff[1024];

  // Базовые тесты
  s21_sprintf(s21_buff, "%s", "Hello, World!");
  sprintf(orig_buff, "%s", "Hello, World!");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%s", "");
  sprintf(orig_buff, "%s", "");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%s", "   Spaces   ");
  sprintf(orig_buff, "%s", "   Spaces   ");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%s", "Special\tChars\n");
  sprintf(orig_buff, "%s", "Special\tChars\n");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%10s", "Hello");
  sprintf(orig_buff, "%10s", "Hello");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%-10s", "Hello");
  sprintf(orig_buff, "%-10s", "Hello");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%5s", "LongerString");
  sprintf(orig_buff, "%5s", "LongerString");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%.5s", "Hello, World!");
  sprintf(orig_buff, "%.5s", "Hello, World!");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%.0s", "Hello, World!");
  sprintf(orig_buff, "%.0s", "Hello, World!");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%.10s", "Short");
  sprintf(orig_buff, "%.10s", "Short");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%10.5s", "Hello, World!");
  sprintf(orig_buff, "%10.5s", "Hello, World!");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%-10.5s", "Hello, World!");
  sprintf(orig_buff, "%-10.5s", "Hello, World!");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%5.10s", "Hello");
  sprintf(orig_buff, "%5.10s", "Hello");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "Prefix: %s", "Hello");
  sprintf(orig_buff, "Prefix: %s", "Hello");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%s Suffix", "Hello");
  sprintf(orig_buff, "%s Suffix", "Hello");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "Prefix %s Suffix", "Hello");
  sprintf(orig_buff, "Prefix %s Suffix", "Hello");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%10.5s", "");
  sprintf(orig_buff, "%10.5s", "");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%-10.5s", "");
  sprintf(orig_buff, "%-10.5s", "");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%20s", "   Spaces   ");
  sprintf(orig_buff, "%20s", "   Spaces   ");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%-20s", "   Spaces   ");
  sprintf(orig_buff, "%-20s", "   Spaces   ");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%s", "Tab\tNewline\n");
  sprintf(orig_buff, "%s", "Tab\tNewline\n");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%.20s", "Short");
  sprintf(orig_buff, "%.20s", "Short");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%3s", "LongerString");
  sprintf(orig_buff, "%3s", "LongerString");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%s", "Hello\0World");
  sprintf(orig_buff, "%s", "Hello\0World");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%s", "Привет, мир!");
  sprintf(orig_buff, "%s", "Привет, мир!");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%100s", "Hello");
  sprintf(orig_buff, "%100s", "Hello");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%.100s", "Hello");
  sprintf(orig_buff, "%.100s", "Hello");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%50.30s", "Short");
  sprintf(orig_buff, "%50.30s", "Short");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%-10s", "Hello");
  sprintf(orig_buff, "%-10s", "Hello");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%0.0s", "Hello");
  sprintf(orig_buff, "%0.0s", "Hello");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%0s", "Hello");
  sprintf(orig_buff, "%0s", "Hello");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%1000.500s", "Hello");
  sprintf(orig_buff, "%1000.500s", "Hello");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%s",
              "This is a very long string that should be handled correctly.");
  sprintf(orig_buff, "%s",
          "This is a very long string that should be handled correctly.");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%-20.10s %10.5s %-5.3s", "Left", "Center", "Right");
  sprintf(orig_buff, "%-20.10s %10.5s %-5.3s", "Left", "Center", "Right");
  ck_assert_str_eq(s21_buff, orig_buff);
}
END_TEST

START_TEST(test_s21_sprintf_ls) {
  setlocale(LC_CTYPE, "");

  char s21_buff[1024];
  char orig_buff[1024];

  // Базовые тесты с широкими строками
  s21_sprintf(s21_buff, "%ls", L"Hello, World!");
  sprintf(orig_buff, "%ls", L"Hello, World!");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%ls", L"");
  sprintf(orig_buff, "%ls", L"");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%ls", L"   Spaces   ");
  sprintf(orig_buff, "%ls", L"   Spaces   ");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%ls", L"Special\tChars\n");
  sprintf(orig_buff, "%ls", L"Special\tChars\n");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%10ls", L"Hello");
  sprintf(orig_buff, "%10ls", L"Hello");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%-10ls", L"Hello");
  sprintf(orig_buff, "%-10ls", L"Hello");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%5ls", L"LongerString");
  sprintf(orig_buff, "%5ls", L"LongerString");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%.5ls", L"Hello, World!");
  sprintf(orig_buff, "%.5ls", L"Hello, World!");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%.0ls", L"Hello, World!");
  sprintf(orig_buff, "%.0ls", L"Hello, World!");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%.10ls", L"Short");
  sprintf(orig_buff, "%.10ls", L"Short");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%10.5ls", L"Hello, World!");
  sprintf(orig_buff, "%10.5ls", L"Hello, World!");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%-10.5ls", L"Hello, World!");
  sprintf(orig_buff, "%-10.5ls", L"Hello, World!");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%5.10ls", L"Hello");
  sprintf(orig_buff, "%5.10ls", L"Hello");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "Prefix: %ls", L"Hello");
  sprintf(orig_buff, "Prefix: %ls", L"Hello");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%ls Suffix", L"Hello");
  sprintf(orig_buff, "%ls Suffix", L"Hello");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "Prefix %ls Suffix", L"Hello");
  sprintf(orig_buff, "Prefix %ls Suffix", L"Hello");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%10.5ls", L"");
  sprintf(orig_buff, "%10.5ls", L"");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%-10.5ls", L"");
  sprintf(orig_buff, "%-10.5ls", L"");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%20ls", L"   Spaces   ");
  sprintf(orig_buff, "%20ls", L"   Spaces   ");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%-20ls", L"   Spaces   ");
  sprintf(orig_buff, "%-20ls", L"   Spaces   ");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%ls", L"Tab\tNewline\n");
  sprintf(orig_buff, "%ls", L"Tab\tNewline\n");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%.20ls", L"Short");
  sprintf(orig_buff, "%.20ls", L"Short");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%3ls", L"LongerString");
  sprintf(orig_buff, "%3ls", L"LongerString");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%ls", L"Hello\0World");
  sprintf(orig_buff, "%ls", L"Hello\0World");
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тесты с многобайтовыми символами
  s21_sprintf(s21_buff, "%ls", L"Привет, мир!");
  sprintf(orig_buff, "%ls", L"Привет, мир!");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%ls", L"😊🌟🌈");
  sprintf(orig_buff, "%ls", L"😊🌟🌈");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%ls", L"こんにちは");
  sprintf(orig_buff, "%ls", L"こんにちは");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%ls", L"你好，世界！");
  sprintf(orig_buff, "%ls", L"你好，世界！");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%10ls", L"😊");
  sprintf(orig_buff, "%10ls", L"😊");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%-10ls", L"🌟");
  sprintf(orig_buff, "%-10ls", L"🌟");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%.2ls", L"😊🌟🌈");
  sprintf(orig_buff, "%.2ls", L"😊🌟🌈");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%ls", L"🤖+👽=👾");
  sprintf(orig_buff, "%ls", L"🤖+👽=👾");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%ls", L"🚀🌕");
  sprintf(orig_buff, "%ls", L"🚀🌕");
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%ls", L"🎉🎊");
  sprintf(orig_buff, "%ls", L"🎉🎊");
  ck_assert_str_eq(s21_buff, orig_buff);
}
END_TEST
START_TEST(test_s21_sprintf_single_d) {
  char s21_buff[1024];
  char orig_buff[1024];

  // NEEDS REFACTORING...
  s21_sprintf(s21_buff, "%hd", 32767);
  sprintf(orig_buff, "%hd", 32767);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%hd", -32768);
  sprintf(orig_buff, "%hd", -32768);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%hd", 0);
  sprintf(orig_buff, "%hd", 0);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%hd", 12345);
  sprintf(orig_buff, "%hd", 12345);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%hd", -12345);
  sprintf(orig_buff, "%hd", -12345);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%ld", 9223372036854775807);
  sprintf(orig_buff, "%ld", 9223372036854775807);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%d", 9223372036854775807);
  sprintf(orig_buff, "%d", 9223372036854775807);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%ld", -9223372036854775807 - 1);
  sprintf(orig_buff, "%ld", -9223372036854775807 - 1);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%ld", 0);
  sprintf(orig_buff, "%ld", 0);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%ld", 1234567890);
  sprintf(orig_buff, "%ld", 1234567890);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%ld", -1234567890);
  sprintf(orig_buff, "%ld", -1234567890);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%d", 2147483647);
  sprintf(orig_buff, "%d", 2147483647);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%d", -2147483648);
  sprintf(orig_buff, "%d", -2147483648);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%d", 0);
  sprintf(orig_buff, "%d", 0);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%d", 123456);
  sprintf(orig_buff, "%d", 123456);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%d", -123456);
  sprintf(orig_buff, "%d", -123456);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%hd", 32768);
  sprintf(orig_buff, "%hd", 32768);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%hd", -32769);
  sprintf(orig_buff, "%hd", -32769);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%d", 2147483648);
  sprintf(orig_buff, "%d", 2147483648);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%d", -2147483649);
  sprintf(orig_buff, "%d", -2147483649);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%hd", 0);
  sprintf(orig_buff, "%hd", 0);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%ld", 0);
  sprintf(orig_buff, "%ld", 0);
  ck_assert_str_eq(s21_buff, orig_buff);
}
END_TEST

START_TEST(test_s21_sprintf_single_u) {
  char s21_buff[1024];
  char orig_buff[1024];
  s21_sprintf(s21_buff, "%hu", 32767);
  sprintf(orig_buff, "%hu", 32767);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%hu", -32768);
  sprintf(orig_buff, "%hu", -32768);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%hu", 0);
  sprintf(orig_buff, "%hu", 0);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%hu", 12345);
  sprintf(orig_buff, "%hu", 12345);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%hu", -12345);
  sprintf(orig_buff, "%hu", -12345);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%lu", 9223372036854775807);
  sprintf(orig_buff, "%lu", 9223372036854775807);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%u", 9223372036854775807);
  sprintf(orig_buff, "%u", 9223372036854775807);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%lu", -9223372036854775807 - 1);
  sprintf(orig_buff, "%lu", -9223372036854775807 - 1);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%lu", 0);
  sprintf(orig_buff, "%lu", 0);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%lu", 1234567890);
  sprintf(orig_buff, "%lu", 1234567890);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%lu", -1234567890);
  sprintf(orig_buff, "%lu", -1234567890);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%u", 2147483647);
  sprintf(orig_buff, "%u", 2147483647);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%u", -2147483648);
  sprintf(orig_buff, "%u", -2147483648);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%u", 0);
  sprintf(orig_buff, "%u", 0);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%u", 123456);
  sprintf(orig_buff, "%u", 123456);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%u", -123456);
  sprintf(orig_buff, "%u", -123456);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%hu", 32768);
  sprintf(orig_buff, "%hu", 32768);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%hu", -32769);
  sprintf(orig_buff, "%hu", -32769);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%u", 2147483648);
  sprintf(orig_buff, "%u", 2147483648);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%u", -2147483649);
  sprintf(orig_buff, "%u", -2147483649);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%hu", 0);
  sprintf(orig_buff, "%hu", 0);
  ck_assert_str_eq(s21_buff, orig_buff);
  s21_sprintf(s21_buff, "%lu", 0);
  sprintf(orig_buff, "%lu", 0);
  ck_assert_str_eq(s21_buff, orig_buff);
}
END_TEST

START_TEST(test_s21_sprintf_d) {
#include "sprintf_tests_data/s21_sprintf_d_data.h"

  int test_counter = 0;
  // TEST INT64_T VALUES
  for (int arglen = 1; arglen <= MAX_ARGS_D; ++arglen) {
    for (int test = 0; test < TESTS_D; ++test) {
      TEST_SPRINTF(s21_buff, orig_buff, formats[arglen - 1][test],
                   integer_data[arglen - 1][test], arglen);
      ++test_counter;
    }
  }

  // TEST UINT64_T VALUES
  for (int arglen = 2; arglen <= 2; ++arglen) {
    for (int test = 0; test < TESTS_D; ++test) {
      TEST_SPRINTF(s21_buff, orig_buff, formats[arglen - 1][test],
                   unsigned_data[arglen - 1][test], arglen);
      ++test_counter;
    }
  }
  printf("[  TESTS  ] s21_sprintf d tests : %d\n", test_counter);
}
END_TEST

START_TEST(test_s21_sprintf_u) {
#include "sprintf_tests_data/s21_sprintf_u_data.h"

  int test_counter = 0;
  for (int arglen = 1; arglen <= DEBUG_BOUND_U_1; ++arglen) {
    for (int test = 0; test < DEBUG_BOUND_U_2; ++test) {
      TEST_SPRINTF(s21_buff, orig_buff, formats[arglen - 1][test],
                   unsigned_data[arglen - 1][test], arglen);
      ++test_counter;
    }
  }

  for (int arglen = 2; arglen <= 2; ++arglen) {
    for (int test = 0; test < TESTS_U; ++test) {
      TEST_SPRINTF(s21_buff, orig_buff, formats[arglen - 1][test],
                   unsigned_data[arglen - 1][test], arglen);
      ++test_counter;
    }
  }
  printf("[  TESTS  ] s21_sprintf u tests : %d\n", test_counter);
}
END_TEST

START_TEST(test_s21_sprintf_f) {
#include "sprintf_tests_data/s21_sprintf_f_data.h"

  // Custom tests:
  s21_sprintf(s21_buff, "%f", 0.0);
  sprintf(orig_buff, "%f", 0.0);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%.f", 0.0);
  sprintf(orig_buff, "%.f", 0.0);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%.0f", 0.0);
  sprintf(orig_buff, "%.0f", 0.0);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%.1f", 0.0);
  sprintf(orig_buff, "%.1f", 0.0);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%.2f", 0.0);
  sprintf(orig_buff, "%.2f", 0.0);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%.10f", 0.0);
  sprintf(orig_buff, "%.10f", 0.0);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%.100f", 0.0);
  sprintf(orig_buff, "%.100f", 0.0);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%.f", 100.9);
  sprintf(orig_buff, "%.f", 100.9);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%.0f", 100.9);
  sprintf(orig_buff, "%.0f", 100.9);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%.1f", 100.9);
  sprintf(orig_buff, "%.1f", 100.9);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%.0f", 9.9);
  sprintf(orig_buff, "%.0f", 9.9);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%.1f", 9.9);
  sprintf(orig_buff, "%.1f", 9.9);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%.1f", 99999.99);
  sprintf(orig_buff, "%.1f", 99999.99);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%.3f", 1023456.99999);
  sprintf(orig_buff, "%.3f", 1023456.99999);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%.41f",
              10234249956.9234825293492500008042359823459395839583994358239509);
  sprintf(orig_buff, "%.41f",
          10234249956.9234825293492500008042359823459395839583994358239509);
  ck_assert_str_eq(s21_buff, orig_buff);

  // edge case with 5 at the end
  s21_sprintf(s21_buff, "%1.1f", 2.25);
  sprintf(orig_buff, "%1.1f", 2.25);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%1.1f", 2.35);
  sprintf(orig_buff, "%1.1f", 2.35);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%1.0f", -0.5);
  sprintf(orig_buff, "%1.0f", -0.5);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%1.0f", -1.5);
  sprintf(orig_buff, "%1.0f", -1.5);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%1.0f", -2.5);
  sprintf(orig_buff, "%1.0f", -2.5);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%1.0f", -9999.5);
  sprintf(orig_buff, "%1.0f", -9999.5);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%1.0f", 0.5);
  sprintf(orig_buff, "%1.0f", 0.5);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%1.0f", 1.5);
  sprintf(orig_buff, "%1.0f", 1.5);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%1.0f", 2.5);
  sprintf(orig_buff, "%1.0f", 2.5);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%1.0f", 10.5);
  sprintf(orig_buff, "%1.0f", 10.5);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%.4f", 10.0002500000000);
  sprintf(orig_buff, "%.4f", 10.0002500000000);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%.4f", 10.0002500000023);
  sprintf(orig_buff, "%.4f", 10.0002500000023);
  ck_assert_str_eq(s21_buff, orig_buff);

  // edge cases with extra digit
  s21_sprintf(s21_buff, "%.0f", 10.9);
  sprintf(orig_buff, "%.0f", 10.9);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%.0f", 19.9);
  sprintf(orig_buff, "%.0f", 19.9);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%.0f", 99.9);
  sprintf(orig_buff, "%.0f", 99.9);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%.0f", 99.9);
  sprintf(orig_buff, "%.0f", 99.9);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%-.0f", 99.9);
  sprintf(orig_buff, "%-.0f", 99.9);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%-10.0f", 99.9);
  sprintf(orig_buff, "%-10.0f", 99.9);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%10.0f", 99.9);
  sprintf(orig_buff, "%10.0f", 99.9);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%+10.0f", 99.9);
  sprintf(orig_buff, "%+10.0f", 99.9);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "% 10.0f", 99.9);
  sprintf(orig_buff, "% 10.0f", 99.9);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "hello%10.3fworld", 9999.999);
  sprintf(orig_buff, "hello%10.3fworld", 9999.999);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "hello%10.3fworld", -9999.999);
  sprintf(orig_buff, "hello%10.3fworld", -9999.999);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "hello%.3fworld", -9999.999);
  sprintf(orig_buff, "hello%.3fworld", -9999.999);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "hello%9.3fworld", -9999.999);
  sprintf(orig_buff, "hello%9.3fworld", -9999.999);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "hello%-12.3fworld", -9999.999);
  sprintf(orig_buff, "hello%-12.3fworld", -9999.999);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "hello%20.3fworld", -9999.999);
  sprintf(orig_buff, "hello%20.3fworld", -9999.999);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "hello%20.3fworld", -9099.999);
  sprintf(orig_buff, "hello%20.3fworld", -9099.999);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "hello%20.2fworld", -9999.999);
  sprintf(orig_buff, "hello%20.2fworld", -9999.999);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "hello%-20.0fworld", 99.99);
  sprintf(orig_buff, "hello%-20.0fworld", 99.99);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "hello%-20.0fworld", 99.50);
  sprintf(orig_buff, "hello%-20.0fworld", 99.50);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "hello%-20.0fworld", 98.50);
  sprintf(orig_buff, "hello%-20.0fworld", 98.50);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "hello%-.0fworld", 9.9);
  sprintf(orig_buff, "hello%-.0fworld", 9.9);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "hello%.0fworld", 999999999999999999.9);
  sprintf(orig_buff, "hello%.0fworld", 999999999999999999.9);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "hello%12.0fworld", 99.9);
  sprintf(orig_buff, "hello%12.0fworld", 99.9);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "hello%199.0fworld", 99999999999999.9);
  sprintf(orig_buff, "hello%199.0fworld", 99999999999999.9);
  ck_assert_str_eq(s21_buff, orig_buff);

  int test_counter = 0;

#define CORE_TESTS_F 1
#if CORE_TESTS_F
  for (int arglen = 1; arglen <= DEBUG_BOUND_F_1; ++arglen) {
    for (int test = 0; test < DEBUG_BOUND_F_2; ++test) {
      TEST_SPRINTF(s21_buff, orig_buff, formats[arglen - 1][test],
                   float_data[arglen - 1][test], arglen);
      ++test_counter;
    }
  }
#endif

  // Brutforce tests:
#define EPS_TESTS_1 1
#define EPS_TESTS_2 1

#if EPS_TESTS_1
  const double eps = 0.500000;
  double begin_value = -1;
  double end_value = 1;
  double number[] = {begin_value};
  s21_size_t eps_tests = 0;
  for (int format = 0; format < 100; ++format) {
    for (number[0] = begin_value; number[0] <= end_value; number[0] += eps) {
      TEST_SPRINTF(s21_buff, orig_buff, precision_formats[format], number, 1);
      ++eps_tests;
    }
  }
#endif

#if EPS_TESTS_2
  double numbers[] = {0.0,
                      0.9,
                      0.999,
                      0.999999,
                      9.9,
                      9.99999999,
                      99.999999,
                      999.9,
                      99999.9999999,
                      899999.999999,
                      8999999.99999999,
                      9000000.9999999,
                      9000009.9000001,
                      900009.9009,
                      90000.90000999,
                      9009.9999999,
                      999.0,
                      99.0,
                      9.9 - 0.9,
                      -0.999,
                      -0.999999,
                      -9.9,
                      -9.99999999,
                      -99.999999,
                      -999.9,
                      -99999.9999999,
                      -899999.999999,
                      -8999999.99999999,
                      -9000000.9999999,
                      -9000009.9000001,
                      -900009.9009,
                      -90000.90000999,
                      -9009.9999999,
                      -999.0,
                      -99.0,
                      -9.9};
  s21_size_t size_numbers = sizeof(numbers) / sizeof(numbers[0]);
  for (int format = 0; format < 100; ++format) {
    for (int i = 0; i < size_numbers; ++i) {
      TEST_SPRINTF(s21_buff, orig_buff, formats[0][format], numbers, 1);
    }
  }
#endif

  printf("[  TESTS  ] s21_sprintf f tests : %d\n", test_counter);
}
END_TEST

START_TEST(test_s21_sprintf_all_specifiers) {
  char s21_buff[1024];
  char orig_buff[1024];

  // Тест 1: несколько спецификаторов, флагов и точности
  s21_sprintf(s21_buff, "Char: %-5c, Int: %+10d, Float: %.3f", 'A', 12345,
              3.14159);
  sprintf(orig_buff, "Char: %-5c, Int: %+10d, Float: %.3f", 'A', 12345,
          3.14159);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 2: с длиной (h, l)
  s21_sprintf(s21_buff, "Short: %hd, Long: %ld, Unsigned: %lu", (short)32767,
              (long)1234567890L, (unsigned long)ULONG_MAX);
  sprintf(orig_buff, "Short: %hd, Long: %ld, Unsigned: %lu", (short)32767,
          (long)1234567890L, (unsigned long)ULONG_MAX);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "%%");
  sprintf(orig_buff, "%%");
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 3: различные флаги и точность
  s21_sprintf(s21_buff, "Int: %10d, Float: %.5f, Percent: %%", 12345,
              3.14159265358979);
  sprintf(orig_buff, "Int: %10d, Float: %.5f, Percent: %%", 12345,
          3.14159265358979);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 4: ширина и флаги
  s21_sprintf(s21_buff, "String: %-20s, Unsigned: %+10u", "Hello", 123456);
  sprintf(orig_buff, "String: %-20s, Unsigned: %+10u", "Hello", 123456);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 5: комбинированные спецификаторы
  s21_sprintf(s21_buff, "Char: %-10c, String: %.5s, Hex: %hd", 'Z',
              "LongString", 255);
  sprintf(orig_buff, "Char: %-10c, String: %.5s, Hex: %hd", 'Z', "LongString",
          255);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 6: с длиной (h, l), флаги и точность
  s21_sprintf(s21_buff, "Short: %hd, Long: %10ld, Percent: %%", (short)1234,
              (long)9876543210L);
  sprintf(orig_buff, "Short: %hd, Long: %10ld, Percent: %%", (short)1234,
          (long)9876543210L);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 7: с несколькими спецификаторами и шириной
  s21_sprintf(s21_buff, "Int: %-10d, Char: %c, Float: %.3f", 42, 'B', 3.14);
  sprintf(orig_buff, "Int: %-10d, Char: %c, Float: %.3f", 42, 'B', 3.14);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 8: комбинированные спецификаторы, флаги и точность
  s21_sprintf(s21_buff, "String: %.5s, Unsigned: %+10u, Float: %.2f",
              "abcdefgh", 123, 456.789);
  sprintf(orig_buff, "String: %.5s, Unsigned: %+10u, Float: %.2f", "abcdefgh",
          123, 456.789);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 9: с флагами, шириной и длиной (h, l)
  s21_sprintf(s21_buff, "Hex: %hd, Char: %-5c, Short: %hd", 255, 'X',
              (short)32767);
  sprintf(orig_buff, "Hex: %hd, Char: %-5c, Short: %hd", 255, 'X',
          (short)32767);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 10: с процентом и несколькими спецификаторами
  s21_sprintf(s21_buff, "Percent: %% , Int: %d, Unsigned: %u", 12345, 67890);
  sprintf(orig_buff, "Percent: %% , Int: %d, Unsigned: %u", 12345, 67890);
  ck_assert_str_eq(s21_buff, orig_buff);

  s21_sprintf(s21_buff, "Char: %c, Short: %hd, Long: %ld, Unsigned: %lu", 'X',
              (short)32767, (long)123456789L, (unsigned long)9876543210UL);
  sprintf(orig_buff, "Char: %c, Short: %hd, Long: %ld, Unsigned: %lu", 'X',
          (short)32767, (long)123456789L, (unsigned long)9876543210UL);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 2: несколько спецификаторов с флагами
  s21_sprintf(s21_buff, "String: %-10s, Hex: %hd, Percent: %%", "Hello", 255,
              100);
  sprintf(orig_buff, "String: %-10s, Hex: %hd, Percent: %%", "Hello", 255, 100);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 3: комбинированные спецификаторы с точностью
  s21_sprintf(s21_buff, "Int: %+10d, Float: %.4f, String: %.5s", 456,
              3.14159265359, "LongString");
  sprintf(orig_buff, "Int: %+10d, Float: %.4f, String: %.5s", 456,
          3.14159265359, "LongString");
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 4: с длиной h, l и флагами
  s21_sprintf(s21_buff, "Short: %hd, Long: %10ld, Char: %-5c", (short)1234,
              (long)9876543210L, 'A');
  sprintf(orig_buff, "Short: %hd, Long: %10ld, Char: %-5c", (short)1234,
          (long)9876543210L, 'A');
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 5: комбинированные флаги и точность
  s21_sprintf(s21_buff, "Hex: %hd, Unsigned: %10u, Percent: %%", (short)0,
              12345);
  sprintf(orig_buff, "Hex: %hd, Unsigned: %10u, Percent: %%", (short)0, 12345);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 6: с шириной и длиной (h, l)
  s21_sprintf(s21_buff, "Char: %-10c, Int: %10d, Unsigned Long: %10lu", 'B',
              56789, 1234567890UL);
  sprintf(orig_buff, "Char: %-10c, Int: %10d, Unsigned Long: %10lu", 'B', 56789,
          1234567890UL);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 7: с несколькими целыми числами
  s21_sprintf(s21_buff, "Int 1: %10d, Int 2: %-10d, Int 3: %+d", 12345, 67890,
              -100);
  sprintf(orig_buff, "Int 1: %10d, Int 2: %-10d, Int 3: %+d", 12345, 67890,
          -100);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 8: комбинация флагов и точности
  s21_sprintf(s21_buff, "Float: %+10.3f, Unsigned: %10u, String: %.5s",
              3.14159265359, 1234567890, "TestString");
  sprintf(orig_buff, "Float: %+10.3f, Unsigned: %10u, String: %.5s",
          3.14159265359, 1234567890, "TestString");
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 9: длина и точность
  s21_sprintf(s21_buff, "Long: %10ld, Short: %-5hd, Char: %-3c", 1234567890L,
              (short)32767, 'Z');
  sprintf(orig_buff, "Long: %10ld, Short: %-5hd, Char: %-3c", 1234567890L,
          (short)32767, 'Z');
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 10: несколько флагов с точностью
  s21_sprintf(s21_buff, "Hex: %hd, Int: %+10d, Float: %.3f, String: %-10s",
              (short)255, 12345, 3.1415, "Hello");
  sprintf(orig_buff, "Hex: %hd, Int: %+10d, Float: %.3f, String: %-10s",
          (short)255, 12345, 3.1415, "Hello");
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 11: комбинированные спецификаторы с длиной (h, l)
  s21_sprintf(s21_buff, "Short: %hd, Long: %10ld, Unsigned Short: %hu",
              (short)1234, (long)9876543210L, (unsigned short)65535);
  sprintf(orig_buff, "Short: %hd, Long: %10ld, Unsigned Short: %hu",
          (short)1234, (long)9876543210L, (unsigned short)65535);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 12: строка, с точностью и шириной
  s21_sprintf(s21_buff, "String: %.3s, Unsigned: %10u, Hex: %hd", "LongString",
              123456, 255);
  sprintf(orig_buff, "String: %.3s, Unsigned: %10u, Hex: %hd", "LongString",
          123456, 255);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 13: несколько флагов и спецификаторов с точностью
  s21_sprintf(s21_buff, "Int: %-10d, Float: %+10.3f, Percent: %%", 12345,
              3.14159, 100);
  sprintf(orig_buff, "Int: %-10d, Float: %+10.3f, Percent: %%", 12345, 3.14159,
          100);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 14: комбинация целых чисел с флагами
  s21_sprintf(s21_buff, "Short: %-5hd, Long: %+10ld, Int: %10d", (short)32767,
              (long)1234567890L, 12345);
  sprintf(orig_buff, "Short: %-5hd, Long: %+10ld, Int: %10d", (short)32767,
          (long)1234567890L, 12345);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 15: комбинированные спецификаторы и проценты
  s21_sprintf(s21_buff, "Hex: %hd, Char: %-5c, String: %.5s, Percent: %%", 255,
              'A', "Example", 100);
  sprintf(orig_buff, "Hex: %hd, Char: %-5c, String: %.5s, Percent: %%", 255,
          'A', "Example", 100);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 16: с длиной h, l и точностью
  s21_sprintf(s21_buff, "Short: %hd, Long: %ld, Float: %.2f", (short)100,
              10000L, 3.14159);
  sprintf(orig_buff, "Short: %hd, Long: %ld, Float: %.2f", (short)100, 10000L,
          3.14159);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 17: комбинированные спецификаторы с шириной
  s21_sprintf(s21_buff, "String: %-15s, Unsigned: %10u, Hex: %hd", "Test", 100,
              255);
  sprintf(orig_buff, "String: %-15s, Unsigned: %10u, Hex: %hd", "Test", 100,
          255);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 18: флаги с точностью и длиной
  s21_sprintf(s21_buff, "Int: %+10d, Hex: %hd, String: %.3s", 12345, 255,
              "LongString");
  sprintf(orig_buff, "Int: %+10d, Hex: %hd, String: %.3s", 12345, 255,
          "LongString");
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 19: комбинация целых чисел, флагов и точности
  s21_sprintf(s21_buff, "Int: %+10d, Short: %hd, Long: %10ld", 12345,
              (short)32767, (long)9876543210L);
  sprintf(orig_buff, "Int: %+10d, Short: %hd, Long: %10ld", 12345, (short)32767,
          (long)9876543210L);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 20: комбинированные спецификаторы и флаги
  s21_sprintf(s21_buff, "Int: %-10d, Char: %+c, String: %.5s", 12345, 'A',
              "TestString");
  sprintf(orig_buff, "Int: %-10d, Char: %+c, String: %.5s", 12345, 'A',
          "TestString");
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 21: несколько спецификаторов с шириной и точностью
  s21_sprintf(s21_buff, "Int: %10d, Float: %-10.2f, String: %.4s", 12345,
              3.14159, "TestString");
  sprintf(orig_buff, "Int: %10d, Float: %-10.2f, String: %.4s", 12345, 3.14159,
          "TestString");
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 22: комбинированные флаги с точностью и длиной
  s21_sprintf(s21_buff, "Short: %-5hd, Unsigned: %10u, Char: %+5c",
              (short)32767, 255, 'X');
  sprintf(orig_buff, "Short: %-5hd, Unsigned: %10u, Char: %+5c", (short)32767,
          255, 'X');
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 23: длина h и точность
  s21_sprintf(s21_buff, "Short: %.3hd, Long: %ld, Unsigned: %-5lu",
              (short)12345, 9876543210L, 1234567890UL);
  sprintf(orig_buff, "Short: %.3hd, Long: %ld, Unsigned: %-5lu", (short)12345,
          9876543210L, 1234567890UL);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 24: комбинация флагов, ширины и точности
  s21_sprintf(s21_buff, "Hex: %hd, Float: %+8.2f, Int: %-10d", 255, 3.1415,
              12345);
  sprintf(orig_buff, "Hex: %hd, Float: %+8.2f, Int: %-10d", 255, 3.1415, 12345);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 25: с несколькими флагами
  s21_sprintf(s21_buff, "String: %-15s, Char: %+5c, Percent: %%", "Test", 'Y');
  sprintf(orig_buff, "String: %-15s, Char: %+5c, Percent: %%", "Test", 'Y');
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 26: спецификаторы с длиной и точностью
  s21_sprintf(s21_buff, "Char: %-3c, Int: %.4d, Float: %.3f", 'Z', 123, 3.1415);
  sprintf(orig_buff, "Char: %-3c, Int: %.4d, Float: %.3f", 'Z', 123, 3.1415);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 27: несколько целых чисел с флагами и точностью
  s21_sprintf(s21_buff, "Int: %+10d, Short: %-5hd, Long: %.5ld", 123456,
              (short)32767, 9876543210L);
  sprintf(orig_buff, "Int: %+10d, Short: %-5hd, Long: %.5ld", 123456,
          (short)32767, 9876543210L);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 28: комбинированные спецификаторы с точностью
  s21_sprintf(s21_buff, "Hex: %hd, Float: %.2f, Percent: %%", 255, 3.14);
  sprintf(orig_buff, "Hex: %hd, Float: %.2f, Percent: %%", 255, 3.14);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 29: несколько строк с флагами и точностью
  s21_sprintf(s21_buff, "String 1: %.5s, String 2: %-10s, Percent: %%",
              "LongString", "Hello");
  sprintf(orig_buff, "String 1: %.5s, String 2: %-10s, Percent: %%",
          "LongString", "Hello");
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 30: комбинация длины и точности
  s21_sprintf(s21_buff, "Long: %10ld, Short: %.3hd, Unsigned: %-5lu",
              9876543210L, (short)12345, 1234567890UL);
  sprintf(orig_buff, "Long: %10ld, Short: %.3hd, Unsigned: %-5lu", 9876543210L,
          (short)12345, 1234567890UL);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 31: с длиной и флагами
  s21_sprintf(s21_buff, "Long: %-10ld, Unsigned: %+10u, Short: %-5hd",
              9876543210L, 1234567890UL, (short)32767);
  sprintf(orig_buff, "Long: %-10ld, Unsigned: %+10u, Short: %-5hd", 9876543210L,
          1234567890UL, (short)32767);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 32: с флагами, точностью и длиной
  s21_sprintf(s21_buff, "Float: %+10.4f, String: %.3s, Unsigned: %10u", 3.1415,
              "Hello", 255);
  sprintf(orig_buff, "Float: %+10.4f, String: %.3s, Unsigned: %10u", 3.1415,
          "Hello", 255);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 33: комбинированные спецификаторы и флаги
  s21_sprintf(s21_buff, "Int: %+10d, Char: %-5c, Hex: %hd", 12345, 'Y', 255);
  sprintf(orig_buff, "Int: %+10d, Char: %-5c, Hex: %hd", 12345, 'Y', 255);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 34: спецификаторы с точностью и флагами
  s21_sprintf(s21_buff, "Short: %+10hd, Unsigned: %10u, Float: %.3f", 32767,
              1234567890UL, 3.1415);
  sprintf(orig_buff, "Short: %+10hd, Unsigned: %10u, Float: %.3f", 32767,
          1234567890UL, 3.1415);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 35: несколько чисел с длиной и флагами
  s21_sprintf(s21_buff, "Int: %10d, Long: %-10ld, Hex: %hd", 12345, 9876543210L,
              255);
  sprintf(orig_buff, "Int: %10d, Long: %-10ld, Hex: %hd", 12345, 9876543210L,
          255);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 36: несколько строк с флагами
  s21_sprintf(s21_buff, "String 1: %-5s, String 2: %.3s, Percent: %%",
              "LongString", "Short");
  sprintf(orig_buff, "String 1: %-5s, String 2: %.3s, Percent: %%",
          "LongString", "Short");
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 37: комбинация флагов, точности и длины
  s21_sprintf(s21_buff, "Int: %10d, Short: %.3hd, Long: %-10ld", 12345,
              (short)32767, 9876543210L);
  sprintf(orig_buff, "Int: %10d, Short: %.3hd, Long: %-10ld", 12345,
          (short)32767, 9876543210L);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 38: несколько чисел и процентов
  s21_sprintf(s21_buff, "Int: %d, Float: %.2f, Percent: %%", 12345, 3.1415);
  sprintf(orig_buff, "Int: %d, Float: %.2f, Percent: %%", 12345, 3.1415);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 39: несколько целых чисел с точностью
  s21_sprintf(s21_buff, "Int: %.4d, Short: %.3hd, Long: %10ld", 12345,
              (short)32767, 9876543210L);
  sprintf(orig_buff, "Int: %.4d, Short: %.3hd, Long: %10ld", 12345,
          (short)32767, 9876543210L);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 40: комбинированные спецификаторы и проценты
  s21_sprintf(s21_buff, "Char: %-5c, String: %.4s, Percent: %%", 'Y',
              "LongString");
  sprintf(orig_buff, "Char: %-5c, String: %.4s, Percent: %%", 'Y',
          "LongString");
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 41: несколько спецификаторов с длиной
  s21_sprintf(s21_buff, "Char: %-5c, Short: %hd, Long: %-10ld", 'Z',
              (short)32767, 9876543210L);
  sprintf(orig_buff, "Char: %-5c, Short: %hd, Long: %-10ld", 'Z', (short)32767,
          9876543210L);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 42: с флагами, точностью и длиной
  s21_sprintf(s21_buff, "Hex: %hd, Int: %+10d, Percent: %%", 255, 12345);
  sprintf(orig_buff, "Hex: %hd, Int: %+10d, Percent: %%", 255, 12345);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 43: комбинация флагов с точностью
  s21_sprintf(s21_buff, "Int: %5d, Float: %.3f, Char: %+5c", 12345, 3.1415,
              'X');
  sprintf(orig_buff, "Int: %5d, Float: %.3f, Char: %+5c", 12345, 3.1415, 'X');
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 44: несколько чисел и строк с точностью
  s21_sprintf(s21_buff, "String: %.4s, Short: %hd, Unsigned: %10u",
              "HelloWorld", (short)32767, 255);
  sprintf(orig_buff, "String: %.4s, Short: %hd, Unsigned: %10u", "HelloWorld",
          (short)32767, 255);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 45: комбинация флагов и длины
  s21_sprintf(s21_buff, "Float: %+10.3f, Long: %-10ld, Char: %5c", 3.1415,
              9876543210L, 'A');
  sprintf(orig_buff, "Float: %+10.3f, Long: %-10ld, Char: %5c", 3.1415,
          9876543210L, 'A');
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 46: несколько чисел и процентов с флагами
  s21_sprintf(s21_buff, "Int: %10d, Percent: %%", 12345);
  sprintf(orig_buff, "Int: %10d, Percent: %%", 12345);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 47: комбинированные спецификаторы с точностью и длиной
  s21_sprintf(s21_buff, "Int: %10d, Float: %.2f, Char: %-5c", 12345, 3.1415,
              'Z');
  sprintf(orig_buff, "Int: %10d, Float: %.2f, Char: %-5c", 12345, 3.1415, 'Z');
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 48: несколько чисел с флагами и точностью
  s21_sprintf(s21_buff, "Short: %.5hd, Unsigned: %10u, Long: %-10ld",
              (short)12345, 255, 9876543210L);
  sprintf(orig_buff, "Short: %.5hd, Unsigned: %10u, Long: %-10ld", (short)12345,
          255, 9876543210L);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 49: строки с точностью и флагами
  s21_sprintf(s21_buff, "String: %.3s, Char: %-5c, Percent: %%", "LongString",
              'A');
  sprintf(orig_buff, "String: %.3s, Char: %-5c, Percent: %%", "LongString",
          'A');
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 50: с несколькими числами, флагами и точностью
  s21_sprintf(s21_buff, "Int: %10d, Float: %.3f, Char: %+5c", 12345, 3.1415,
              'Y');
  sprintf(orig_buff, "Int: %10d, Float: %.3f, Char: %+5c", 12345, 3.1415, 'Y');
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 51: несколько чисел с флагами и точностью
  s21_sprintf(s21_buff, "Int: %10d, Short: %.4hd, Long: %10ld", 12345,
              (short)32767, 9876543210L);
  sprintf(orig_buff, "Int: %10d, Short: %.4hd, Long: %10ld", 12345,
          (short)32767, 9876543210L);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 52: комбинация флагов с точностью и длиной
  s21_sprintf(s21_buff, "Int: %-10d, Short: %.4hd, Unsigned: %10u", 12345,
              (short)32767, 255);
  sprintf(orig_buff, "Int: %-10d, Short: %.4hd, Unsigned: %10u", 12345,
          (short)32767, 255);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 53: комбинированные спецификаторы с точностью
  s21_sprintf(s21_buff, "String: %.3s, Int: %-5d, Long: %.5ld", "Hello", 12345,
              9876543210L);
  sprintf(orig_buff, "String: %.3s, Int: %-5d, Long: %.5ld", "Hello", 12345,
          9876543210L);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 54: несколько чисел с флагами
  s21_sprintf(s21_buff, "Int: %-5d, Char: %+5c, Percent: %%", 12345, 'Z');
  sprintf(orig_buff, "Int: %-5d, Char: %+5c, Percent: %%", 12345, 'Z');
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 55: несколько чисел с флагами и длиной
  s21_sprintf(s21_buff, "Int: %+10d, Short: %-5hd, Long: %-10ld", 12345,
              (short)32767, 9876543210L);
  sprintf(orig_buff, "Int: %+10d, Short: %-5hd, Long: %-10ld", 12345,
          (short)32767, 9876543210L);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 56: комбинированные спецификаторы с точностью и длиной
  s21_sprintf(s21_buff, "Int: %10d, Short: %.4hd, Unsigned: %10u", 12345,
              (short)32767, 255);
  sprintf(orig_buff, "Int: %10d, Short: %.4hd, Unsigned: %10u", 12345,
          (short)32767, 255);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 57: несколько чисел с точностью и флагами
  s21_sprintf(s21_buff, "Float: %.3f, Int: %+10d, Char: %-5c", 3.1415, 12345,
              'X');
  sprintf(orig_buff, "Float: %.3f, Int: %+10d, Char: %-5c", 3.1415, 12345, 'X');
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 58: комбинированные спецификаторы с флагами и точностью
  s21_sprintf(s21_buff, "Int: %-10d, Float: %.4f, Char: %+5c", 12345, 3.1415,
              'Z');
  sprintf(orig_buff, "Int: %-10d, Float: %.4f, Char: %+5c", 12345, 3.1415, 'Z');
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 59: с несколькими строками и точностью
  s21_sprintf(s21_buff, "String 1: %.3s, String 2: %-5s, Percent: %%",
              "LongString", "Short");
  sprintf(orig_buff, "String 1: %.3s, String 2: %-5s, Percent: %%",
          "LongString", "Short");
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 60: комбинированные флаги, точность и длина
  s21_sprintf(s21_buff, "Int: %-5d, Long: %10ld, Short: %.3hd", 12345,
              9876543210L, (short)32767);
  sprintf(orig_buff, "Int: %-5d, Long: %10ld, Short: %.3hd", 12345, 9876543210L,
          (short)32767);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 61: с флагами, точностью и длиной
  s21_sprintf(s21_buff, "Float: %+10.2f, Int: %-5d, Long: %10ld", 3.1415, 12345,
              9876543210L);
  sprintf(orig_buff, "Float: %+10.2f, Int: %-5d, Long: %10ld", 3.1415, 12345,
          9876543210L);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 62: несколько чисел с флагами, точностью и длиной
  s21_sprintf(s21_buff, "Char: %-5c, Int: %+10d, Float: %.3f", 'A', 12345,
              3.1415);
  sprintf(orig_buff, "Char: %-5c, Int: %+10d, Float: %.3f", 'A', 12345, 3.1415);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 63: комбинированные спецификаторы с точностью и длиной
  s21_sprintf(s21_buff, "Int: %10d, Short: %.4hd, Long: %-5ld", 12345,
              (short)32767, 9876543210L);
  sprintf(orig_buff, "Int: %10d, Short: %.4hd, Long: %-5ld", 12345,
          (short)32767, 9876543210L);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 64: несколько чисел и строк с флагами
  s21_sprintf(s21_buff, "String: %-5s, Int: %+10d, Float: %.2f", "Hello", 12345,
              3.1415);
  sprintf(orig_buff, "String: %-5s, Int: %+10d, Float: %.2f", "Hello", 12345,
          3.1415);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 65: комбинированные флаги, точность и длина
  s21_sprintf(s21_buff, "Int: %10d, Short: %.3hd, Long: %-10ld", 12345,
              (short)32767, 9876543210L);
  sprintf(orig_buff, "Int: %10d, Short: %.3hd, Long: %-10ld", 12345,
          (short)32767, 9876543210L);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 66: с процентом, флагами и длиной
  s21_sprintf(s21_buff, "Percent: %%  Int: %-10d, Char: %5c", 12345, 'X');
  sprintf(orig_buff, "Percent: %%  Int: %-10d, Char: %5c", 12345, 'X');
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 67: несколько чисел и строк с флагами, точностью и длиной
  s21_sprintf(s21_buff, "Int: %-5d, String: %.4s, Char: %+5c", 12345,
              "HelloWorld", 'Y');
  sprintf(orig_buff, "Int: %-5d, String: %.4s, Char: %+5c", 12345, "HelloWorld",
          'Y');
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 68: несколько чисел и строк с флагами и точностью
  s21_sprintf(s21_buff, "String: %.3s, Int: %+5d, Float: %.2f", "Hello", 12345,
              3.1415);
  sprintf(orig_buff, "String: %.3s, Int: %+5d, Float: %.2f", "Hello", 12345,
          3.1415);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 69: несколько чисел с флагами, точностью и длиной
  s21_sprintf(s21_buff, "Int: %-5d, Long: %-10ld, Char: %+5c", 12345,
              9876543210L, 'A');
  sprintf(orig_buff, "Int: %-5d, Long: %-10ld, Char: %+5c", 12345, 9876543210L,
          'A');
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 70: с флагами, точностью и процентом
  s21_sprintf(s21_buff, "Percent: %% Int: %+10d, Float: %.2f", 12345, 3.1415);
  sprintf(orig_buff, "Percent: %% Int: %+10d, Float: %.2f", 12345, 3.1415);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 71: комбинированные спецификаторы и точность
  s21_sprintf(s21_buff, "Short: %.3hd, Long: %-5ld, Float: %.2f", (short)32767,
              9876543210L, 3.1415);
  sprintf(orig_buff, "Short: %.3hd, Long: %-5ld, Float: %.2f", (short)32767,
          9876543210L, 3.1415);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 72: несколько строк с флагами, точностью и длиной
  s21_sprintf(s21_buff, "String 1: %.4s, String 2: %-5s, Char: %+5c", "Hello",
              "World", 'Z');
  sprintf(orig_buff, "String 1: %.4s, String 2: %-5s, Char: %+5c", "Hello",
          "World", 'Z');
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 73: с флагами и точностью
  s21_sprintf(s21_buff, "Char: %+5c, Int: %-10d, Float: %.2f", 'Y', 12345,
              3.1415);
  sprintf(orig_buff, "Char: %+5c, Int: %-10d, Float: %.2f", 'Y', 12345, 3.1415);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 74: несколько чисел с флагами и точностью
  s21_sprintf(s21_buff, "Int: %+5d, Float: %.3f, Char: %-5c", 12345, 3.1415,
              'X');
  sprintf(orig_buff, "Int: %+5d, Float: %.3f, Char: %-5c", 12345, 3.1415, 'X');
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 75: несколько чисел и строк с флагами, точностью и длиной
  s21_sprintf(s21_buff, "Int: %+5d, String: %.3s, Char: %+5c", 12345, "Hello",
              'A');
  sprintf(orig_buff, "Int: %+5d, String: %.3s, Char: %+5c", 12345, "Hello",
          'A');
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 76: с флагами и точностью
  s21_sprintf(s21_buff, "Int: %-5d, Float: %.4f, Char: %+5c", 12345, 3.1415,
              'Z');
  sprintf(orig_buff, "Int: %-5d, Float: %.4f, Char: %+5c", 12345, 3.1415, 'Z');
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 77: несколько чисел с длиной, флагами и точностью
  s21_sprintf(s21_buff, "Int: %-10d, Short: %.4hd, Long: %10ld", 12345,
              (short)32767, 9876543210L);
  sprintf(orig_buff, "Int: %-10d, Short: %.4hd, Long: %10ld", 12345,
          (short)32767, 9876543210L);
  ck_assert_str_eq(s21_buff, orig_buff);

  // Тест 78: несколько чисел с флагами, точностью и длиной
  s21_sprintf(s21_buff, "Short: %-5hd, Long: %-10ld, Int: %10d", (short)32767,
              9876543210L, 12345);
  sprintf(orig_buff, "Short: %-5hd, Long: %-10ld, Int: %10d", (short)32767,
          9876543210L, 12345);
  ck_assert_str_eq(s21_buff, orig_buff);
}
END_TEST

START_TEST(test_s21_sprintf_edge_cases) {
#include "sprintf_tests_data/s21_sprintf_edge_cases_data.h"
  for (s21_size_t test = 0; test < tests; ++test) {
    TEST_SPRINTF(s21_buff, orig_buff, formats[test], blank_array, 0);
  }
}
END_TEST

START_TEST(test_s21_sprintf_returns) {
  char buffer_s21[1024] = {0};
  char buffer_orig[1024] = {0};
  int n_s21, n_orig;

  // Тест для %d
  n_s21 = s21_sprintf(buffer_s21, "Integer: %d", 123);
  n_orig = sprintf(buffer_orig, "Integer: %d", 123);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для %f
  n_s21 = s21_sprintf(buffer_s21, "Float: %.2f", 3.14159);
  n_orig = sprintf(buffer_orig, "Float: %.2f", 3.14159);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для %s
  n_s21 = s21_sprintf(buffer_s21, "String: %s", "Hello, World!");
  n_orig = sprintf(buffer_orig, "String: %s", "Hello, World!");
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для %c
  n_s21 = s21_sprintf(buffer_s21, "Char: %c", 'A');
  n_orig = sprintf(buffer_orig, "Char: %c", 'A');
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для %u
  n_s21 = s21_sprintf(buffer_s21, "Unsigned: %u", 4294967295);
  n_orig = sprintf(buffer_orig, "Unsigned: %u", 4294967295);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для %%
  n_s21 = s21_sprintf(buffer_s21, "Percent: %%");
  n_orig = sprintf(buffer_orig, "Percent: %%");
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для флага ширины
  n_s21 = s21_sprintf(buffer_s21, "Width: %10d", 123);
  n_orig = sprintf(buffer_orig, "Width: %10d", 123);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для флага точности
  n_s21 = s21_sprintf(buffer_s21, "Precision: %.5f", 3.14159);
  n_orig = sprintf(buffer_orig, "Precision: %.5f", 3.14159);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для флага +
  n_s21 = s21_sprintf(buffer_s21, "Plus: %+d", 123);
  n_orig = sprintf(buffer_orig, "Plus: %+d", 123);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для флага пробела
  n_s21 = s21_sprintf(buffer_s21, "Space: % d", 123);
  n_orig = sprintf(buffer_orig, "Space: % d", 123);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для флага -
  n_s21 = s21_sprintf(buffer_s21, "Left align: %-10d", 123);
  n_orig = sprintf(buffer_orig, "Left align: %-10d", 123);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для длины h (short)
  n_s21 = s21_sprintf(buffer_s21, "Short: %hd", (short)12345);
  n_orig = sprintf(buffer_orig, "Short: %hd", (short)12345);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для длины l (long)
  n_s21 = s21_sprintf(buffer_s21, "Long: %ld", 123456789L);
  n_orig = sprintf(buffer_orig, "Long: %ld", 123456789L);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для %d с флагом + и шириной
  n_s21 = s21_sprintf(buffer_s21, "Positive with width: %+10d", 123);
  n_orig = sprintf(buffer_orig, "Positive with width: %+10d", 123);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для %d с флагом пробела и шириной
  n_s21 = s21_sprintf(buffer_s21, "Space with width: % 10d", 123);
  n_orig = sprintf(buffer_orig, "Space with width: % 10d", 123);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для %d с флагом - и шириной
  n_s21 = s21_sprintf(buffer_s21, "Left align with width: %-10d", 123);
  n_orig = sprintf(buffer_orig, "Left align with width: %-10d", 123);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для %d с шириной и точностью
  n_s21 = s21_sprintf(buffer_s21, "Width and precision: %10.5d", 123);
  n_orig = sprintf(buffer_orig, "Width and precision: %10.5d", 123);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для %f с флагом + и шириной
  n_s21 =
      s21_sprintf(buffer_s21, "Positive float with width: %+10.2f", 3.14159);
  n_orig = sprintf(buffer_orig, "Positive float with width: %+10.2f", 3.14159);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для %f с флагом пробела и шириной
  n_s21 = s21_sprintf(buffer_s21, "Space float with width: % 10.2f", 3.14159);
  n_orig = sprintf(buffer_orig, "Space float with width: % 10.2f", 3.14159);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для %f с флагом - и шириной
  n_s21 =
      s21_sprintf(buffer_s21, "Left align float with width: %-10.2f", 3.14159);
  n_orig =
      sprintf(buffer_orig, "Left align float with width: %-10.2f", 3.14159);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для %f с шириной и точностью
  n_s21 = s21_sprintf(buffer_s21, "Float width and precision: %10.5f", 3.14159);
  n_orig = sprintf(buffer_orig, "Float width and precision: %10.5f", 3.14159);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для %s с флагом - и шириной
  n_s21 =
      s21_sprintf(buffer_s21, "Left align string with width: %-10s", "Hello");
  n_orig = sprintf(buffer_orig, "Left align string with width: %-10s", "Hello");
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для %s с шириной и точностью
  n_s21 = s21_sprintf(buffer_s21, "String width and precision: %10.5s",
                      "Hello, World!");
  n_orig = sprintf(buffer_orig, "String width and precision: %10.5s",
                   "Hello, World!");
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для %u с шириной
  n_s21 = s21_sprintf(buffer_s21, "Unsigned with width: %10u", 4294967295);
  n_orig = sprintf(buffer_orig, "Unsigned with width: %10u", 4294967295);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для %u с шириной и точностью
  n_s21 = s21_sprintf(buffer_s21, "Unsigned width and precision: %10.5u",
                      4294967295);
  n_orig =
      sprintf(buffer_orig, "Unsigned width and precision: %10.5u", 4294967295);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для %c с флагом - и шириной
  n_s21 = s21_sprintf(buffer_s21, "Left align char with width: %-10c", 'A');
  n_orig = sprintf(buffer_orig, "Left align char with width: %-10c", 'A');
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для %% с шириной
  n_s21 = s21_sprintf(buffer_s21, "Percent with width: %10%");
  n_orig = sprintf(buffer_orig, "Percent with width: %10%");
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для %d с длиной h (short)
  n_s21 = s21_sprintf(buffer_s21, "Short int: %hd", (short)12345);
  n_orig = sprintf(buffer_orig, "Short int: %hd", (short)12345);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для %d с длиной l (long)
  n_s21 = s21_sprintf(buffer_s21, "Long int: %ld", 123456789L);
  n_orig = sprintf(buffer_orig, "Long int: %ld", 123456789L);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для %u с длиной l (unsigned long)
  n_s21 = s21_sprintf(buffer_s21, "Unsigned long: %lu", 123456789UL);
  n_orig = sprintf(buffer_orig, "Unsigned long: %lu", 123456789UL);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для %f с длиной l (double)
  n_s21 = s21_sprintf(buffer_s21, "Double: %.2f", 3.14159);
  n_orig = sprintf(buffer_orig, "Double: %.2f", 3.14159);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для %s с NULL
  n_s21 = s21_sprintf(buffer_s21, "String with NULL: %s", NULL);
  n_orig = sprintf(buffer_orig, "String with NULL: %s", NULL);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для %d с NULL (некорректный случай, но для проверки)
  n_s21 = s21_sprintf(buffer_s21, "Integer with NULL: %d", (int)NULL);
  n_orig = sprintf(buffer_orig, "Integer with NULL: %d", (int)NULL);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для %u с NULL (некорректный случай, но для проверки)
  n_s21 = s21_sprintf(buffer_s21, "Unsigned with NULL: %u", (unsigned int)NULL);
  n_orig = sprintf(buffer_orig, "Unsigned with NULL: %u", (unsigned int)NULL);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест для %% с NULL (некорректный случай, но для проверки)
  n_s21 = s21_sprintf(buffer_s21, "Percent with NULL: %%", NULL);
  n_orig = sprintf(buffer_orig, "Percent with NULL: %%", NULL);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест 1: Комбинация %d, %f, %s
  n_s21 = s21_sprintf(buffer_s21, "Integer: %d, Float: %.2f, String: %s", 123,
                      3.14159, "Hello");
  n_orig = sprintf(buffer_orig, "Integer: %d, Float: %.2f, String: %s", 123,
                   3.14159, "Hello");
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест 2: Комбинация %c, %u, %%
  n_s21 = s21_sprintf(buffer_s21, "Char: %c, Unsigned: %u, Percent: %%", 'A',
                      4294967295);
  n_orig = sprintf(buffer_orig, "Char: %c, Unsigned: %u, Percent: %%", 'A',
                   4294967295);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест 3: Комбинация флагов, ширины и точности
  n_s21 = s21_sprintf(buffer_s21, "Width: %10d, Precision: %.5f, Flag: %+d",
                      123, 3.14159, 456);
  n_orig = sprintf(buffer_orig, "Width: %10d, Precision: %.5f, Flag: %+d", 123,
                   3.14159, 456);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест 4: Комбинация длины и спецификаторов
  n_s21 = s21_sprintf(buffer_s21, "Short: %hd, Long: %ld", (short)12345,
                      123456789L);
  n_orig =
      sprintf(buffer_orig, "Short: %hd, Long: %ld", (short)12345, 123456789L);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест 5: Комбинация всех возможных параметров
  n_s21 = s21_sprintf(buffer_s21, "All: %-+10.3f, %10s, %05d, %c", 3.14159,
                      "Hello", 123, 'X');
  n_orig = sprintf(buffer_orig, "All: %-+10.3f, %10s, %05d, %c", 3.14159,
                   "Hello", 123, 'X');
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест 6: Комбинация с нулевой шириной и точностью
  n_s21 = s21_sprintf(buffer_s21, "Zero: %0d, %.0f", 0, 0.0);
  n_orig = sprintf(buffer_orig, "Zero: %0d, %.0f", 0, 0.0);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест 7: Комбинация с отрицательными числами
  n_s21 = s21_sprintf(buffer_s21, "Negative: %d, %f, %d", -123, -3.14159, -456);
  n_orig = sprintf(buffer_orig, "Negative: %d, %f, %d", -123, -3.14159, -456);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест 8: Комбинация с большими числами
  n_s21 = s21_sprintf(buffer_s21, "Large: %ld, %lu", 123456789012345L,
                      123456789012345L);
  n_orig = sprintf(buffer_orig, "Large: %ld, %lu", 123456789012345L,
                   123456789012345L);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест 9: Комбинация с пустой строкой
  n_s21 = s21_sprintf(buffer_s21, "Empty: %s", "");
  n_orig = sprintf(buffer_orig, "Empty: %s", "");
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);

  // Тест 10: Комбинация с нулевым указателем
  n_s21 = s21_sprintf(buffer_s21, "Null: %s", NULL);
  n_orig = sprintf(buffer_orig, "Null: %s", NULL);
  ck_assert_str_eq(buffer_s21, buffer_orig);
  ck_assert_int_eq(n_s21, n_orig);
}
END_TEST

#endif
