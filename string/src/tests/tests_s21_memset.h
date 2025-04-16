#ifndef TESTS_S21_MEMSET_H
#define TESTS_S21_MEMSET_H
#include "common_header.h"
START_TEST(test_s21_memset) {
#include "tests_data/memset_data.h"

  for (s21_size_t i = 0; i < size_buffers; i++) {
    for (s21_size_t j = 0; j < size_fill_chars; j++) {
      char temp1[1024] = "";
      char temp2[1024] = "";
      strcpy(temp1, buffers[i]);
      strcpy(temp2, buffers[i]);
      char *s21_result =
          (char *)s21_memset(temp1, fill_chars[j], fill_sizes[i]);
      char *orig_result = (char *)memset(temp2, fill_chars[j], fill_sizes[i]);
      int result = (strcmp(s21_result, orig_result) == 0);
      if (!result) {
        fprintf(stderr,
                "\n"
                "[  FAILED  ] s21_memset test\n"
                "[      IN  ] [%s], [%c], [%llu]\n"
                "[  EXP     ] %s\n"
                "[     OUT  ] %s\n\n",
                temp1, fill_chars[i], fill_sizes[j], orig_result, s21_result);
      }
      ck_assert(result);
      tests_num++;
    }
  }
  printf("[  TESTS  ] s21_memset tests number : %lld\n", tests_num);
}
END_TEST

#endif
