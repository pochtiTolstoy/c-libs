#include "test_s21_decimal.h"

int main() {
  int number_failed;
  Suite *suite = suite_create("s21_decimal_test");

  suite_add_tcase(suite, tcase_s21_div());
  suite_add_tcase(suite, tcase_s21_mul());
  suite_add_tcase(suite, tcase_s21_decimal_to_str());
  suite_add_tcase(suite, tcase_s21_str_to_decimal());
  suite_add_tcase(suite, tcase_s21_is_valid_decimal());
  suite_add_tcase(suite, tcase_s21_comparison());
  suite_add_tcase(suite, tcase_s21_add());
  suite_add_tcase(suite, tcase_s21_sub());
  suite_add_tcase(suite, tcase_s21_conversion());
  suite_add_tcase(suite, tcase_s21_other());

  SRunner *runner = srunner_create(suite);
  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return number_failed != 0;
}
