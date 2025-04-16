#include "test_s21_matrix.h"

int main() {
  int number_failed;
  Suite *suite = suite_create("s21_matrix_test");
  SRunner *runner = srunner_create(suite);

  suite_add_tcase(suite, tcase_s21_create_matrix());
  suite_add_tcase(suite, tcase_s21_eq_matrix());
  suite_add_tcase(suite, tcase_s21_remove_matrix());
  suite_add_tcase(suite, tcase_s21_sum_sub_mult_matrix());
  suite_add_tcase(suite, tcase_s21_mult_matrix());
  suite_add_tcase(suite, tcase_s21_transpose());
  suite_add_tcase(suite, tcase_s21_calc_complements_determinant());
  suite_add_tcase(suite, tcase_s21_inverse_matrix());
  suite_add_tcase(suite, tcase_unit_1());
  suite_add_tcase(suite, tcase_s21_calc_complements_new());
  suite_add_tcase(suite, tcase_s21_create_matrix_new());
  suite_add_tcase(suite, tcase_s21_determinant_new());
  suite_add_tcase(suite, tcase_s21_eq_matrix_new());
  suite_add_tcase(suite, tcase_s21_inverse_matrix_new());
  suite_add_tcase(suite, tcase_s21_mult_matrix_new());
  suite_add_tcase(suite, tcase_s21_mult_number_new());
  suite_add_tcase(suite, tcase_s21_remove_matrix_new());
  suite_add_tcase(suite, tcase_s21_sub_matrix_new());
  suite_add_tcase(suite, tcase_s21_sum_matrix_new());
  suite_add_tcase(suite, tcase_s21_transpose_new());

  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return number_failed != 0;
}
