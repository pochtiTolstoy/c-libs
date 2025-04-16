#include "test_s21_decimal.h"

START_TEST(test_s21_mul_unit_1) {
  char s21_buffer[BUFFER_SIZE] = {0};
  char orig_buffer[BUFFER_SIZE] = "532611770970.53212838643961087";
  const char *lhs_str = "143859988.65173318586836303008";
  const char *rhs_str = "3702.29259686595538444042879";
  s21_decimal lhs;
  s21_decimal rhs;
  s21_decimal s21_res;
  s21_str_to_decimal(lhs_str, &lhs);
  s21_str_to_decimal(rhs_str, &rhs);
  s21_mul(lhs, rhs, &s21_res);
  s21_decimal_to_str(s21_res, s21_buffer);
  ck_assert_str_eq(s21_buffer, orig_buffer);
}
END_TEST

START_TEST(test_s21_mul_mnt_err_ok) {
  printf(RUN_MSG, __func__);
  const char *file_names[] = {"tests/tests_logs/s21_mul/mul_mnt_0.txt",
                              "tests/tests_logs/s21_mul/mul_mnt_1.txt",
                              "tests/tests_logs/s21_mul/mul_mnt_2.txt",
                              "tests/tests_logs/s21_mul/mul_mnt_3.txt",
                              "tests/tests_logs/s21_mul/mul_exp_0.txt",
                              "tests/tests_logs/s21_mul/mul_exp_1.txt",
                              "tests/tests_logs/s21_mul/mul_exp_2.txt"};
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

      result_code = s21_mul(lhs, rhs, &res);
      s21_decimal_to_str(res, s21_buffer);

      if (result_code != expected_code) {
        printf(FAILED_BIN_OP_MSG, lhs_buffer, '*', rhs_buffer);
        printf(RESULT_MSG, ERR_CODES_STR[result_code]);
        printf(EXPECTED_MSG, ERR_CODES_STR[expected_code]);
        ck_assert_msg(0, "\n");
      }

      int s21_last_digit = s21_buffer[strlen(s21_buffer) - 1] - '0';
      int orig_last_digit = orig_buffer[strlen(orig_buffer) - 1] - '0';
      if (abs(orig_last_digit - s21_last_digit) == 1) {
        orig_buffer[strlen(orig_buffer) - 1] = s21_last_digit + '0';
        s21_set_bit(&orig, 0, 0);
      }

      int both_zeros = (s21_is_zero(&res) && s21_is_zero(&orig));

      if (!both_zeros && strncmp(orig_buffer, s21_buffer, BUFFER_SIZE) != 0) {
        printf(FAILED_BIN_OP_MSG, lhs_buffer, '*', rhs_buffer);
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

TCase *tcase_s21_mul(void) {
  TCase *tcase = tcase_create("s21_mul");
  tcase_add_test(tcase, test_s21_mul_mnt_err_ok);
  tcase_add_test(tcase, test_s21_mul_unit_1);
  return tcase;
}
