#include <s21_decimal.h>

void s21_str_to_decimal(const char *str, s21_decimal *dst) {
  s21_make_decimal_empty(dst);
  int is_negative = ((str[0] == '-') ? 1 : 0);
  char *find_dot = strchr(str, '.');
  size_t max_len = MAX_NUM_LEN + is_negative + (find_dot != NULL);
  size_t len_str = strlen(str);
  if (len_str > max_len) {
    len_str = max_len;
  }
  int dot_index = -1;
  int pow_index = 0;
  for (int i = len_str - 1; i >= is_negative; i--) {
    s21_decimal temp = {0};
    s21_big_decimal temp1 = {0};
    s21_big_decimal temp2 = {0};
    s21_big_decimal result_add = {0};

    if ((int)str[i] == 46) {
      dot_index = i;
    } else {
      const char ch = str[i];
      int digit = ch - '0';
      temp.bits[0] = digit;

      for (int _ = 0; _ < pow_index; _++) {
        s21_decimal_to_big_decimal(&temp, &temp1);
        s21_decimal_to_big_decimal(&temp, &temp2);
        s21_shift_left_big_decimal(&temp1, 3);
        s21_shift_left_big_decimal(&temp2, 1);
        s21_bitwise_add(&temp1, &temp2, &result_add);
        s21_big_decimal_to_decimal(&result_add, &temp);
      }
      pow_index += 1;
      s21_add(*dst, temp, dst);
    }
  }
  s21_set_scale(dst, (dot_index == -1 ? 0 : len_str - dot_index - 1));
  s21_set_sign(dst, is_negative);
}
