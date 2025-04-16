#ifndef TEST_S21_DECIMAL_H
#define TEST_S21_DECIMAL_H

#include <check.h>
#include "s21_decimal.h"

#define TESTS_IN_FILE 50
#define RUN_ALL_TESTS TRUE
#if RUN_ALL_TESTS
#define TEST_DIV TRUE
#define TEST_MUL TRUE
#define TEST_DECIMAL_TO_STR TRUE
#define TEST_STR_TO_DECIMAL TRUE
#define TEST_IS_VALID_DECIMAL TRUE
#define TEST_COMPARISON TRUE
#define TEST_ADD TRUE
#define TEST_SUB TRUE
#define TEST_ADD TRUE
#define TEST_SUB TRUE
#define TEST_CONVERSION TRUE
#define TEST_OTHERS TRUE

#else
#define TEST_DIV FALSE
#define TEST_MUL TRUE
#define TEST_DECIMAL_TO_STR FALSE
#define TEST_STR_TO_DECIMAL FALSE
#define TEST_IS_VALID_DECIMAL FALSE
#define TEST_COMPARISON FALSE
#endif

#define LINE_BUFFER_SIZE 256
#define BUFFER_SIZE 50
#define END_OF_TEST '!'
#define ONE_WORD 1
#define WORD_LENGTH 50

/* messages */
#define RUN_MSG "[RUN] %s\n"
#define END_MSG "[END] %s : %zu\n"
#define PASSED_MSG "--[PASSED] %s : %zu\n"
#define FAILED_BIN_OP_MSG "--[FAILED]   : |%s %c %s|\n"
#define RESULT_MSG "--[RESULT]   : |%s|\n"
#define EXPECTED_MSG "--[EXPECTED] : |%s|\n"

/* error codes string mapping */
#define INSERT_ERR_CODES_STR()                                        \
  const char *ERR_CODES_STR[] = {[(ERR_CODES)OK] = "OK",              \
                                 [(ERR_CODES) LARGE] = "LARGE",       \
                                 [(ERR_CODES) SMALL] = "SMALL",       \
                                 [(ERR_CODES) DIV_ZERO] = "DIV_ZERO", \
                                 [(ERR_CODES) INVALID_DATA] = "INVALID_DATA"};

TCase *tcase_s21_div(void);
TCase *tcase_s21_mul(void);
TCase *tcase_s21_decimal_to_str(void);
TCase *tcase_s21_str_to_decimal(void);
TCase *tcase_s21_is_valid_decimal(void);
TCase *tcase_s21_comparison(void);

TCase *tcase_s21_add(void);
TCase *tcase_s21_sub(void);
TCase *tcase_s21_conversion(void);
TCase *tcase_s21_other(void);
void s21_load_next_decimal(FILE *fp, char *buffer, const char *file_name);
void s21_open_file(FILE **fp, const char *file_name);

#endif
