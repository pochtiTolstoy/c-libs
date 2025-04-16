#include "test_s21_decimal.h"

typedef struct test_data_t {
  s21_decimal number;
  char *s21_buffer;
  char *orig_buffer;
  int num_tests;
  const char *file_name;
  FILE *fp;
} test_data_t;

static void s21_run_tests_(test_data_t *td);

START_TEST(test_s21_decimal_to_str_unit_1) {
  s21_decimal number = {{0x3E7, 0, 0, 0}};
  char s21_buffer[BUFFER_SIZE] = {0};
  s21_set_scale(&number, 1);
  s21_set_sign(&number, NEG_SIGN);

  s21_decimal_to_str(number, s21_buffer);
  const char *expected = "-99.9";
  ck_assert_str_eq(expected, s21_buffer);
}
END_TEST

START_TEST(test_s21_decimal_to_str_max_value) {
  const char *file_name = "tests/tests_logs/s21_decimal_to_str/max_value.txt";
  s21_decimal number = {{UINT32_MAX, UINT32_MAX, UINT32_MAX, 0}};
  char s21_buffer[BUFFER_SIZE] = {0};
  char orig_buffer[BUFFER_SIZE] = {0};
  int num_tests = 29;
  FILE *fp;
  s21_open_file(&fp, file_name);
  test_data_t td = {number, s21_buffer, orig_buffer, num_tests, file_name, fp};

  s21_run_tests_(&td);

  fclose(fp);

  printf("[PASSED] %s : %d\n", __func__, num_tests);
}
END_TEST

START_TEST(test_s21_decimal_to_str_min_value) {
  const char *file_name = "tests/tests_logs/s21_decimal_to_str/min_value.txt";
  s21_decimal number = {{UINT32_MAX, UINT32_MAX, UINT32_MAX, 0}};
  s21_set_sign(&number, NEG_SIGN);
  char s21_buffer[BUFFER_SIZE] = {0};
  char orig_buffer[BUFFER_SIZE] = {0};
  int num_tests = 29;
  FILE *fp;
  s21_open_file(&fp, file_name);
  test_data_t td = {number, s21_buffer, orig_buffer, num_tests, file_name, fp};

  s21_run_tests_(&td);

  fclose(fp);
  printf("[PASSED] %s : %d\n", __func__, num_tests);
}
END_TEST

START_TEST(test_s21_decimal_to_str_zero) {
  const char *file_name = "tests/tests_logs/s21_decimal_to_str/zero_value.txt";
  s21_decimal number = {{0, 0, 0, 0}};
  char s21_buffer[BUFFER_SIZE] = {0};
  char orig_buffer[BUFFER_SIZE] = {0};
  int num_tests = 29;
  FILE *fp;
  s21_open_file(&fp, file_name);
  test_data_t td = {number, s21_buffer, orig_buffer, num_tests, file_name, fp};

  s21_run_tests_(&td);

  rewind(fp);
  s21_set_sign(&td.number, NEG_SIGN);

  s21_run_tests_(&td);

  fclose(fp);
  printf("[PASSED] %s : %d\n", __func__, num_tests * 2);
}
END_TEST

START_TEST(test_s21_decimal_to_str_one_bit_1) {
  const char *file_name = "tests/tests_logs/s21_decimal_to_str/one_bit.txt";
  s21_decimal number = {{0, 0, 0, 0}};
  char s21_buffer[BUFFER_SIZE] = {0};
  char orig_buffer[BUFFER_SIZE] = {0};
  int num_tests = 96;
  FILE *fp;
  s21_open_file(&fp, file_name);

  for (int bit_pos = 0; bit_pos < num_tests; ++bit_pos) {
    s21_set_bit(&number, bit_pos, 1);
    s21_decimal_to_str(number, s21_buffer);
    s21_load_next_decimal(fp, orig_buffer, file_name);
    ck_assert_str_eq(orig_buffer, s21_buffer);
    s21_set_bit(&number, bit_pos, 0);
  }

  fclose(fp);
  printf("[PASSED] %s : %d\n", __func__, num_tests);
}
END_TEST

START_TEST(test_s21_decimal_to_str_scale_1) {
  const char *file_name = "tests/tests_logs/s21_decimal_to_str/scale_1.txt";
  s21_decimal number = {{0xFE495752, 0x69548944, 0, 0}};
  char s21_buffer[BUFFER_SIZE] = {0};
  char orig_buffer[BUFFER_SIZE] = {0};
  int num_tests = 29;
  FILE *fp;
  s21_open_file(&fp, file_name);

  for (int scale = 0; scale < num_tests; ++scale) {
    s21_set_sign(&number, (scale % 2));
    s21_set_scale(&number, scale);
    s21_decimal_to_str(number, s21_buffer);
    s21_load_next_decimal(fp, orig_buffer, file_name);
    ck_assert_str_eq(orig_buffer, s21_buffer);
  }

  fclose(fp);
  printf("[PASSED] %s : %d\n", __func__, num_tests);
}
END_TEST

START_TEST(test_s21_decimal_to_str_scale_2) {
  const char *file_name = "tests/tests_logs/s21_decimal_to_str/scale_2.txt";
  s21_decimal number = {{0xFE495752, 0x69548944, 0x1F24A55A, 0}};
  char s21_buffer[BUFFER_SIZE] = {0};
  char orig_buffer[BUFFER_SIZE] = {0};
  int num_tests = 29;
  FILE *fp;
  s21_open_file(&fp, file_name);

  for (int scale = 0; scale < num_tests; ++scale) {
    s21_set_scale(&number, scale);
    s21_decimal_to_str(number, s21_buffer);
    s21_load_next_decimal(fp, orig_buffer, file_name);
    ck_assert_str_eq(orig_buffer, s21_buffer);
  }

  fclose(fp);
  printf("[PASSED] %s : %d\n", __func__, num_tests);
}
END_TEST

START_TEST(test_s21_decimal_to_str_scale_3) {
  const char *file_name = "tests/tests_logs/s21_decimal_to_str/scale_3.txt";
  s21_decimal number = {{0xF5, 0xFFFFFFFF, 0x9, 0}};
  char s21_buffer[BUFFER_SIZE] = {0};
  char orig_buffer[BUFFER_SIZE] = {0};
  int num_tests = 29;
  FILE *fp;
  s21_open_file(&fp, file_name);

  for (int scale = 0; scale < num_tests; ++scale) {
    s21_set_scale(&number, scale);
    s21_decimal_to_str(number, s21_buffer);
    s21_load_next_decimal(fp, orig_buffer, file_name);
    ck_assert_str_eq(orig_buffer, s21_buffer);
  }

  printf("[PASSED] %s : %d\n", __func__, num_tests);
  fclose(fp);
}
END_TEST

START_TEST(test_s21_decimal_to_str_scale_4) {
  const char *file_name = "tests/tests_logs/s21_decimal_to_str/scale_4.txt";
  s21_decimal number = {{123, 0, 0, 0}};
  char s21_buffer[BUFFER_SIZE] = {0};
  char orig_buffer[BUFFER_SIZE] = {0};
  int num_tests = 29;
  FILE *fp;
  s21_open_file(&fp, file_name);

  for (int scale = 0; scale < num_tests; ++scale) {
    s21_set_scale(&number, scale);
    s21_decimal_to_str(number, s21_buffer);
    s21_load_next_decimal(fp, orig_buffer, file_name);
    ck_assert_str_eq(orig_buffer, s21_buffer);
  }

  printf("[PASSED] %s : %d\n", __func__, num_tests);
  fclose(fp);
}
END_TEST

TCase *tcase_s21_decimal_to_str(void) {
  TCase *tcase = tcase_create("s21_decimal_to_str");
  tcase_add_test(tcase, test_s21_decimal_to_str_max_value);
  tcase_add_test(tcase, test_s21_decimal_to_str_min_value);
  tcase_add_test(tcase, test_s21_decimal_to_str_zero);
  tcase_add_test(tcase, test_s21_decimal_to_str_one_bit_1);
  tcase_add_test(tcase, test_s21_decimal_to_str_scale_1);
  tcase_add_test(tcase, test_s21_decimal_to_str_scale_2);
  tcase_add_test(tcase, test_s21_decimal_to_str_scale_3);
  tcase_add_test(tcase, test_s21_decimal_to_str_scale_4);
  tcase_add_test(tcase, test_s21_decimal_to_str_unit_1);
  return tcase;
}

static void s21_run_tests_(test_data_t *td) {
  for (int test_id = 0; test_id < td->num_tests; ++test_id) {
    s21_set_scale(&td->number, test_id);
    s21_decimal_to_str(td->number, td->s21_buffer);
    s21_load_next_decimal(td->fp, td->orig_buffer, td->file_name);
    ck_assert_str_eq(td->orig_buffer, td->s21_buffer);
  }
}
