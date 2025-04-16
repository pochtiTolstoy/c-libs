#include "tests_s21_insert.h"
#include "tests_s21_memchr.h"
#include "tests_s21_memcmp.h"
#include "tests_s21_memcpy.h"
#include "tests_s21_memset.h"
#include "tests_s21_sprintf.h"
#include "tests_s21_strchr.h"
#include "tests_s21_strcspn.h"
#include "tests_s21_strerror.h"
#include "tests_s21_strlen.h"
#include "tests_s21_strncat.h"
#include "tests_s21_strncmp.h"
#include "tests_s21_strncpy.h"
#include "tests_s21_strpbrk.h"
#include "tests_s21_strrchr.h"
#include "tests_s21_strstr.h"
#include "tests_s21_strtok.h"
#include "tests_s21_to_lower.h"
#include "tests_s21_to_upper.h"
#include "tests_s21_trim.h"

#define CORE_TESTS 1
#define SPRINTF_C_TESTS 1
#define SPRINTF_D_TESTS 1
#define SPRINTF_U_TESTS 1
#define SPRINTF_S_TESTS 1
#define SPRINTF_F_TESTS 1
#define SPRINTF_MIXED_TESTS 1
#define SPRINTF_EDGE_TESTS 1
#define SPRINTF_RETURN_TESTS 1

Suite* s21_unit_tests_suite(void) {
  Suite* suite = suite_create("s21_string unit tests suite");
  TCase* core_tests = tcase_create("Core functionality");
  TCase* sprintf_tests = tcase_create("sprintf functionality");
#if CORE_TESTS
  tcase_add_test(core_tests, test_s21_strlen);
  tcase_add_test(core_tests, test_s21_strcspn);
  tcase_add_test(core_tests, test_s21_memchr);
  tcase_add_test(core_tests, test_s21_memcmp);
  tcase_add_test(core_tests, test_s21_strncat);
  tcase_add_test(core_tests, test_s21_strncmp);
  tcase_add_test(core_tests, test_s21_strpbrk);
  tcase_add_test(core_tests, test_s21_strtok);
  tcase_add_test(core_tests, test_s21_memcpy);
  tcase_add_test(core_tests, test_s21_memset);
  tcase_add_test(core_tests, test_s21_strchr);
  tcase_add_test(core_tests, test_s21_strncpy);
  tcase_add_test(core_tests, test_s21_strerror);
  tcase_add_test(core_tests, test_s21_strrchr);
  tcase_add_test(core_tests, test_s21_strstr);
  tcase_add_test(core_tests, test_s21_to_upper);
  tcase_add_test(core_tests, test_s21_to_lower);
  tcase_add_test(core_tests, test_s21_insert);
  tcase_add_test(core_tests, test_s21_trim);
#endif
#if SPRINTF_C_TESTS
  tcase_add_test(sprintf_tests, test_s21_sprintf_single_c);
  tcase_add_test(sprintf_tests, test_s21_sprintf_multiple_c);
#endif
#if SPRINTF_D_TESTS
  tcase_add_test(sprintf_tests, test_s21_sprintf_d);
  tcase_add_test(sprintf_tests, test_s21_sprintf_single_d);
#endif
#if SPRINTF_U_TESTS
  tcase_add_test(sprintf_tests, test_s21_sprintf_u);
  tcase_add_test(sprintf_tests, test_s21_sprintf_single_u);
#endif
#if SPRINTF_F_TESTS
  tcase_add_test(sprintf_tests, test_s21_sprintf_f);
#endif
#if SPRINTF_S_TESTS
  tcase_add_test(sprintf_tests, test_s21_sprintf_multiple_s);
  tcase_add_test(sprintf_tests, test_s21_sprintf_ls);
#endif
#if SPRINTF_MIXED_TESTS
  tcase_add_test(sprintf_tests, test_s21_sprintf_all_specifiers);
#endif
#if SPRINTF_EDGE_TESTS
  tcase_add_test(sprintf_tests, test_s21_sprintf_edge_cases);
#endif
#if SPRINTF_RETURN_TESTS
  tcase_add_test(sprintf_tests, test_s21_sprintf_returns);
#endif
  suite_add_tcase(suite, core_tests);
  suite_add_tcase(suite, sprintf_tests);
  return suite;
}

int main(void) {
  SRunner* suite_runner = srunner_create(s21_unit_tests_suite());
  srunner_set_fork_status(suite_runner, CK_NOFORK);
  srunner_run_all(suite_runner, CK_VERBOSE);
  int failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
