#include "test_s21_decimal.h"

START_TEST(test_s21_div_rem_5) {
  printf(RUN_MSG, __func__);
  const char *file_names[] = {"tests/tests_logs/s21_div/div_rem_5.txt"};
  const size_t num_files = sizeof(file_names) / sizeof(file_names[0]);
  s21_decimal orig = {0};
  s21_decimal res = {0};
  s21_decimal lhs = {0};
  s21_decimal rhs = {0};
  char s21_buffer[BUFFER_SIZE] = {0};
  char orig_buffer[BUFFER_SIZE] = {0};
  char lhs_buffer[BUFFER_SIZE] = {0};
  char rhs_buffer[BUFFER_SIZE] = {0};
  size_t tests_in_file = 27;
  size_t tests_in_unit = tests_in_file * num_files;
  INSERT_ERR_CODES_STR();
  ERR_CODES result_code;
  ERR_CODES expected_code = (ERR_CODES)OK;
  FILE *fp;
  for (size_t file_id = 0; file_id < num_files; ++file_id) {
    s21_open_file(&fp, file_names[file_id]);
    for (size_t test_id = 0; test_id < tests_in_file; ++test_id) {
      s21_load_next_decimal(fp, lhs_buffer, file_names[file_id]);
      s21_str_to_decimal(lhs_buffer, &lhs);

      s21_load_next_decimal(fp, rhs_buffer, file_names[file_id]);
      s21_str_to_decimal(rhs_buffer, &rhs);

      s21_load_next_decimal(fp, orig_buffer, file_names[file_id]);
      s21_str_to_decimal(orig_buffer, &orig);
      s21_remove_trailing_zeros(&orig);
      s21_decimal_to_str(orig, orig_buffer);

      result_code = s21_div(lhs, rhs, &res);
      s21_decimal_to_str(res, s21_buffer);

      if (result_code != expected_code) {
        printf(FAILED_BIN_OP_MSG, lhs_buffer, '/', rhs_buffer);
        printf(RESULT_MSG, ERR_CODES_STR[result_code]);
        printf(EXPECTED_MSG, ERR_CODES_STR[expected_code]);
        ck_assert_msg(0, "\n");
      }

      int both_zeros = (s21_is_zero(&res) && s21_is_zero(&orig));

      if (!both_zeros && strncmp(orig_buffer, s21_buffer, BUFFER_SIZE) != 0) {
        printf(FAILED_BIN_OP_MSG, lhs_buffer, '/', rhs_buffer);
        printf(RESULT_MSG, s21_buffer);
        printf(EXPECTED_MSG, orig_buffer);
        ck_assert_msg(0, "\n");
      }
    }
    printf(PASSED_MSG, file_names[file_id], tests_in_file);
    fclose(fp);
  }
  printf(END_MSG, __func__, tests_in_unit);
}
END_TEST

START_TEST(test_s21_div_err_ok) {
  printf(RUN_MSG, __func__);
  const char *file_names[] = {"tests/tests_logs/s21_div/div_0.txt",
                              "tests/tests_logs/s21_div/div_1.txt",
                              "tests/tests_logs/s21_div/div_2.txt",
                              "tests/tests_logs/s21_div/div_3.txt",
                              "tests/tests_logs/s21_div/div_4.txt",
                              "tests/tests_logs/s21_div/div_5.txt"};
  const size_t num_files = sizeof(file_names) / sizeof(file_names[0]);
  s21_decimal orig = {0};
  s21_decimal res = {0};
  s21_decimal lhs = {0};
  s21_decimal rhs = {0};
  char s21_buffer[BUFFER_SIZE] = {0};
  char orig_buffer[BUFFER_SIZE] = {0};
  char lhs_buffer[BUFFER_SIZE] = {0};
  char rhs_buffer[BUFFER_SIZE] = {0};
  size_t tests_in_file = TESTS_IN_FILE;
  size_t tests_in_unit = tests_in_file * num_files;
  INSERT_ERR_CODES_STR();
  ERR_CODES result_code;
  ERR_CODES expected_code = (ERR_CODES)OK;
  FILE *fp;
  for (size_t file_id = 0; file_id < num_files; ++file_id) {
    s21_open_file(&fp, file_names[file_id]);
    for (size_t test_id = 0; test_id < tests_in_file; ++test_id) {
      s21_load_next_decimal(fp, lhs_buffer, file_names[file_id]);
      s21_str_to_decimal(lhs_buffer, &lhs);

      s21_load_next_decimal(fp, rhs_buffer, file_names[file_id]);
      s21_str_to_decimal(rhs_buffer, &rhs);

      s21_load_next_decimal(fp, orig_buffer, file_names[file_id]);
      s21_str_to_decimal(orig_buffer, &orig);
      s21_remove_trailing_zeros(&orig);
      s21_decimal_to_str(orig, orig_buffer);

      result_code = s21_div(lhs, rhs, &res);
      s21_decimal_to_str(res, s21_buffer);

      if (result_code != expected_code) {
        printf(FAILED_BIN_OP_MSG, lhs_buffer, '/', rhs_buffer);
        printf(RESULT_MSG, ERR_CODES_STR[result_code]);
        printf(EXPECTED_MSG, ERR_CODES_STR[expected_code]);
        ck_assert_msg(0, "\n");
      }

      int both_zeros = (s21_is_zero(&res) && s21_is_zero(&orig));

      if (!both_zeros && strncmp(orig_buffer, s21_buffer, BUFFER_SIZE) != 0) {
        printf(FAILED_BIN_OP_MSG, lhs_buffer, '/', rhs_buffer);
        printf(RESULT_MSG, s21_buffer);
        printf(EXPECTED_MSG, orig_buffer);
        ck_assert_msg(0, "\n");
      }
    }
    printf(PASSED_MSG, file_names[file_id], tests_in_file);
    fclose(fp);
  }
  printf(END_MSG, __func__, tests_in_unit);
}
END_TEST

TCase *tcase_s21_div(void) {
  TCase *tcase = tcase_create("s21_div");
  tcase_add_test(tcase, test_s21_div_rem_5);
  tcase_add_test(tcase, test_s21_div_err_ok);
  return tcase;
}
