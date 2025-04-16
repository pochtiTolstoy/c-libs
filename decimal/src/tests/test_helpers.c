#include "test_s21_decimal.h"

void s21_load_next_decimal(FILE *fp, char *buffer, const char *file_name) {
  int words_read = fscanf(fp, "%50s", buffer);
  buffer[BUFFER_SIZE - 1] = '\0';
  if (words_read != ONE_WORD || buffer[0] == END_OF_TEST) {
    fprintf(stderr, "[ERROR] Can't load next token from: %s\n", file_name);
    ck_assert_msg(0, "\n");
  }
}

void s21_open_file(FILE **fp, const char *file_name) {
  *fp = fopen(file_name, "r");
  if (*fp == NULL) {
    fprintf(stderr, "[ERROR] Can't open file: %s\n", file_name);
    ck_assert_msg(*fp, "\n");
  }
}
