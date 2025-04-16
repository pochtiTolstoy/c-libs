#include "test_s21_decimal.h"

START_TEST(test_s21_str_to_decimal_unit_1) {
  const char *expected = "0";
  char s21_buffer[BUFFER_SIZE] = {0};
  s21_decimal number = {0};
  s21_str_to_decimal(expected, &number);
  s21_str_to_decimal(expected, &number);
  s21_decimal_to_str(number, s21_buffer);
  ck_assert_str_eq(expected, s21_buffer);
  printf("[PASSED] %s : %d\n", __func__, 1);
}
END_TEST

START_TEST(test_s21_str_to_decimal_1) {
  const char *file_name = "tests/tests_logs/s21_str_to_decimal/std_1.txt";
  FILE *fp;
  s21_open_file(&fp, file_name);
  int num_tests = TESTS_IN_FILE;
  s21_decimal number = {0};

  char s21_buffer[BUFFER_SIZE];
  char orig_buffer[BUFFER_SIZE];

  for (int test_id = 0; test_id < num_tests; ++test_id) {
    s21_load_next_decimal(fp, orig_buffer, file_name);

    s21_str_to_decimal(orig_buffer, &number);
    s21_decimal_to_str(number, s21_buffer);

    ck_assert_str_eq(orig_buffer, s21_buffer);
  }

  fclose(fp);

  printf("[PASSED] %s : %d\n", __func__, num_tests);
}
END_TEST

START_TEST(test_s21_str_to_decimal_2) {
  const char *file_name = "tests/tests_logs/s21_str_to_decimal/std_2.txt";
  FILE *fp;
  s21_open_file(&fp, file_name);
  int num_tests = TESTS_IN_FILE;
  s21_decimal number = {0};

  char s21_buffer[BUFFER_SIZE];
  char orig_buffer[BUFFER_SIZE];

  for (int test_id = 0; test_id < num_tests; ++test_id) {
    s21_load_next_decimal(fp, orig_buffer, file_name);

    s21_str_to_decimal(orig_buffer, &number);
    s21_decimal_to_str(number, s21_buffer);

    ck_assert_str_eq(orig_buffer, s21_buffer);
  }

  fclose(fp);

  printf("[PASSED] %s : %d\n", __func__, num_tests);
}
END_TEST

START_TEST(test_s21_str_to_decimal_3) {
  const char *file_name = "tests/tests_logs/s21_str_to_decimal/std_3.txt";
  FILE *fp;
  s21_open_file(&fp, file_name);
  int num_tests = TESTS_IN_FILE;
  s21_decimal number = {0};

  char s21_buffer[BUFFER_SIZE];
  char orig_buffer[BUFFER_SIZE];

  for (int test_id = 0; test_id < num_tests; ++test_id) {
    s21_load_next_decimal(fp, orig_buffer, file_name);

    s21_str_to_decimal(orig_buffer, &number);
    s21_decimal_to_str(number, s21_buffer);

    ck_assert_str_eq(orig_buffer, s21_buffer);
  }

  fclose(fp);

  printf("[PASSED] %s : %d\n", __func__, num_tests);
}
END_TEST

START_TEST(test_s21_str_to_decimal_4) {
  const char *file_name = "tests/tests_logs/s21_str_to_decimal/std_4.txt";
  FILE *fp;
  s21_open_file(&fp, file_name);
  int num_tests = TESTS_IN_FILE;
  s21_decimal number = {0};

  char s21_buffer[BUFFER_SIZE];
  char orig_buffer[BUFFER_SIZE];

  for (int test_id = 0; test_id < num_tests; ++test_id) {
    s21_load_next_decimal(fp, orig_buffer, file_name);

    s21_str_to_decimal(orig_buffer, &number);
    s21_decimal_to_str(number, s21_buffer);

    ck_assert_str_eq(orig_buffer, s21_buffer);
  }

  fclose(fp);

  printf("[PASSED] %s : %d\n", __func__, num_tests);
}
END_TEST

TCase *tcase_s21_str_to_decimal(void) {
  TCase *tcase = tcase_create("s21_str_to_decimal");
  tcase_add_test(tcase, test_s21_str_to_decimal_unit_1);
  tcase_add_test(tcase, test_s21_str_to_decimal_1);
  tcase_add_test(tcase, test_s21_str_to_decimal_2);
  tcase_add_test(tcase, test_s21_str_to_decimal_3);
  tcase_add_test(tcase, test_s21_str_to_decimal_4);
  return tcase;
}
