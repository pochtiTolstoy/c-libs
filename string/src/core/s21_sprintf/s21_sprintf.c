#include "../../s21_sprintf.h"

#include "../../s21_string.h"

int s21_sprintf(char* output_buff, const char* format, ...) {
  output_buff[0] = '\0';

  specifier_data_t sd = {0};
  iterators_t it = {.curr_iter = format, .backup_iter = format};

  va_list args_list;
  va_start(args_list, format);
  clear_specifier_data(&sd);

  while (it.curr_iter && *it.curr_iter) {
    it.backup_iter = it.curr_iter;
    it.curr_iter = parse_specifier_field(&sd, &it);
    write_specifier_field(&sd, &it, output_buff, &args_list);
    write_trivial_string(output_buff, &it);
    clear_specifier_data(&sd);
  }

  va_end(args_list);

  return s21_strlen(output_buff);
}

void write_invalid_specifier_field(specifier_data_t* sd, iterators_t* it,
                                   char* output_buff) {
  if (sd->shielded_percent) {
    s21_strncat(output_buff, "%", 1);
  } else if (sd->last_non_shielded_percent) {
    it->backup_iter = it->curr_iter;
  } else if (sd->reduce_char) {
    iterators_t reduced_it = {.backup_iter = it->backup_iter,
                              .curr_iter = it->curr_iter - 1};
    reduced_it.curr_iter =
        write_reduced_invalid_flags(output_buff, &reduced_it);
    s21_strncat(output_buff, reduced_it.curr_iter,
                sd->reduced_field_begin - reduced_it.curr_iter);
    s21_strncat(output_buff, sd->reduced_field_begin + 1,
                it->curr_iter - sd->reduced_field_begin - 1);
  } else if (sd->reduce_substring) {
    write_reduced_invalid_flags(output_buff, it);
  } else {
    s21_strncat(output_buff, it->backup_iter, it->curr_iter - it->backup_iter);
  }
}

void write_specifier_field(specifier_data_t* sd, iterators_t* it,
                           char* output_buff, va_list* args_list) {
  if (sd->type == INIT_TYPE) {
    write_invalid_specifier_field(sd, it, output_buff);
  } else {
    write_valid_specifier_field(sd, it, output_buff, args_list);
  }
}

const char* write_reduced_invalid_flags(char* output_buff,
                                        const iterators_t* it) {
  int write_space = 0;
  int write_plus = 0;
  int write_minus = 0;
  int delete_spaces = 0;
  const char* iter = it->backup_iter;
  while (iter < it->curr_iter && !delete_spaces) {
    delete_spaces = (*iter == '+' || *iter == '-');
    ++iter;
  }
  iter = it->backup_iter;
  while (iter < it->curr_iter) {
    if (*iter != '\0' && !s21_strchr("+- ", *iter)) {
      s21_strncat(output_buff, iter, 1);
    }
    if (*iter == '+' && !write_plus) {
      write_plus = 1;
      s21_strncat(output_buff, "+", 1);
    }
    if (*iter == '-' && !write_minus) {
      write_minus = 1;
      s21_strncat(output_buff, "-", 1);
    }
    if (*iter == ' ' && !write_space && !delete_spaces) {
      write_space = 1;
      s21_strncat(output_buff, " ", 1);
    }
    ++iter;
  }
  return iter;
}

void write_valid_specifier_field(specifier_data_t* sd, iterators_t* it,
                                 char* output_buff, va_list* args_list) {
  char* output_iter = s21_strchr(
      output_buff, '\0');  // possible evil because of buffer random bytes
  switch (sd->type) {
    case 'u':
    case 'd': {
      write_specifier_du(sd, output_iter, args_list);
      break;
    }
    case 'f': {
      write_specifier_f(sd, output_iter, args_list);
      break;
    }
    case 'c': {
      write_specifier_c(sd, output_iter, args_list);
      break;
    }
    case 's': {
      write_specifier_s(sd, output_iter, args_list);
      break;
    }
  }
  if (sd->wrote_null_terminator) it->curr_iter = S21_NULL;
}

void write_specifier_du(specifier_data_t* sd, char* output_iter,
                        va_list* args_list) {
  integer_type_u integer_type;
  sign_struct_t sign_struct;
  write_info_struct_t write_info;
  iters_field_t iters_field;

  initialize_write_info(&write_info);
  initialize_iters_field(&iters_field, output_iter);
  handle_type_du(sd, &integer_type, &write_info, args_list);
  write_to_sing_struct(
      &sign_struct,
      (write_info.is_negative || sd->precede_sign || sd->precede_blank),
      handle_negative(sd, write_info.is_negative));
  if (sd->precision > write_info.number_len) {
    write_info.min_digits_to_write = sd->precision;
    write_info.blank_digits_to_write = sd->precision - write_info.number_len;
  } else {
    write_info.min_digits_to_write = write_info.number_len;
  }
  handle_blank_chars(sd, &write_info, &sign_struct);
  handle_iters_field(sd, &iters_field, &sign_struct, &write_info, 1);
  write_padding(iters_field.digits_field, write_info.blank_digits_to_write,
                write_info.blank_digits_symb);
  write_digits_to_buffer(
      sd, iters_field.digits_field + write_info.blank_digits_to_write,
      integer_type);
  write_padding(iters_field.chars_field, write_info.blank_chars_to_write,
                write_info.blank_chars_symb);
  write_padding(iters_field.sign_field, sign_struct.is_signed,
                sign_struct.sign);
  handle_zero_if_justify_left(sd, &iters_field, &write_info);
}

void initialize_write_info(write_info_struct_t* write_info) {
  write_info->number_len = 0;
  write_info->is_negative = 0;
  write_info->min_digits_to_write = 0;
  write_info->blank_digits_to_write = 0;
  write_info->blank_chars_to_write = 0;
  write_info->blank_digits_symb = '0';
  write_info->blank_chars_symb = ' ';
}

void initialize_iters_field(iters_field_t* iters_field, char* output_iter) {
  iters_field->chars_field = output_iter;
  iters_field->digits_field = output_iter;
  iters_field->sign_field = output_iter;
}

void handle_type_du(specifier_data_t* sd, integer_type_u* integer_type,
                    write_info_struct_t* write_info, va_list* args_list) {
  if (sd->type == 'd') {
    integer_type->signed_num = get_signed_value(sd, args_list);
    if ((write_info->is_negative = (integer_type->signed_num < 0))) {
      integer_type->signed_num = -integer_type->signed_num;
    }
    COUNT_DIGITS(int64_t, integer_type->signed_num, write_info->number_len);
  } else if (sd->type == 'u') {
    integer_type->unsigned_num = get_unsigned_value(sd, args_list);
    COUNT_DIGITS(uint64_t, integer_type->unsigned_num, write_info->number_len);
    sd->precede_sign = 0;
    sd->precede_blank = 0;
  }
}

void write_to_sing_struct(sign_struct_t* ss, int is_signed, char sign) {
  ss->is_signed = is_signed;
  ss->sign = sign;
}

char handle_negative(specifier_data_t* sd, int is_negative) {
  char sign;
  if (is_negative) {
    sign = '-';
  } else if (sd->precede_blank) {
    sign = ' ';
  } else if (sd->precede_sign) {
    sign = '+';
  }
  return sign;
}

void handle_blank_chars(specifier_data_t* sd, write_info_struct_t* write_info,
                        sign_struct_t* sign_struct) {
  if (sd->width > write_info->min_digits_to_write + sign_struct->is_signed) {
    write_info->blank_chars_to_write =
        sd->width - write_info->min_digits_to_write - sign_struct->is_signed;
  }

  if (sd->padding_with_zeroes && !sd->precision && !sd->justify_left) {
    write_info->blank_chars_symb = '0';
  }
}

void handle_iters_field(specifier_data_t* sd, iters_field_t* iters_field,
                        sign_struct_t* sign_struct,
                        write_info_struct_t* write_info, int type) {
  if (sd->justify_left) {
    iters_field->chars_field +=
        sign_struct->is_signed + write_info->number_len +
        (type == 1 ? write_info->blank_digits_to_write : 0);
    iters_field->digits_field += sign_struct->is_signed;
  } else {
    iters_field->sign_field += (write_info->blank_chars_symb != '0')
                                   ? write_info->blank_chars_to_write
                                   : 0;
    iters_field->digits_field +=
        write_info->blank_chars_to_write + sign_struct->is_signed;
  }
}

char* write_padding(char* output_iter, int padding_length, char padding_symb) {
  for (int i = 0; i < padding_length; ++i, ++output_iter) {
    *output_iter = padding_symb;
  }
  return output_iter;
}

void write_digits_to_buffer(specifier_data_t* sd, char* digits_field,
                            integer_type_u integer_type) {
  if (sd->type == 'd') {
    if (sd->long_len) {
      S21_CONVERT_DIGIT_TO_STRING_SIGNED(digits_field, integer_type.signed_num,
                                         long);
    } else if (sd->short_len) {
      S21_CONVERT_DIGIT_TO_STRING_SIGNED(digits_field, integer_type.signed_num,
                                         short);
    } else {
      S21_CONVERT_DIGIT_TO_STRING_SIGNED(digits_field, integer_type.signed_num,
                                         int);
    }
  } else if (sd->type == 'u') {
    if (sd->long_len) {
      S21_CONVERT_DIGIT_TO_STRING_UNSIGNED(
          digits_field, integer_type.unsigned_num, unsigned long);
    } else if (sd->short_len) {
      S21_CONVERT_DIGIT_TO_STRING_UNSIGNED(
          digits_field, integer_type.unsigned_num, unsigned short);
    } else {
      S21_CONVERT_DIGIT_TO_STRING_UNSIGNED(
          digits_field, integer_type.unsigned_num, unsigned int);
    }
  }
}

void handle_zero_if_justify_left(specifier_data_t* sd,
                                 iters_field_t* iters_field,
                                 write_info_struct_t* write_info) {
  if (sd->justify_left)
    *(iters_field->chars_field + write_info->blank_chars_to_write) = '\0';
}

void write_specifier_f(specifier_data_t* sd, char* output_iter,
                       va_list* args_list) {
  sign_struct_t sign_struct;
  write_info_struct_t write_info;
  iters_field_t iters_field;
  initialize_write_info(&write_info);
  initialize_iters_field(&iters_field, output_iter);
  double number = (double)va_arg(*args_list, double);
  if (number < 0.0) {
    number = -number;
    write_info.is_negative = 1;
  }
  COUNT_DIGITS(unsigned long long, number, write_info.number_len);
  if (sd->precision) {
    write_info.number_len += sd->precision + 1;
  }

  write_to_sing_struct(
      &sign_struct,
      (write_info.is_negative || sd->precede_sign || sd->precede_blank),
      handle_negative(sd, write_info.is_negative));

  write_info.min_digits_to_write = write_info.number_len;

  handle_blank_chars(sd, &write_info, &sign_struct);
  handle_iters_field(sd, &iters_field, &sign_struct, &write_info, 0);
  handle_type_f(sd, &iters_field, &write_info, number);

  write_padding(iters_field.chars_field, write_info.blank_chars_to_write,
                write_info.blank_chars_symb);
  write_padding(iters_field.sign_field, sign_struct.is_signed,
                sign_struct.sign);
  handle_zero_if_justify_left(sd, &iters_field, &write_info);
}

void handle_type_f(specifier_data_t* sd, iters_field_t* iters_field,
                   write_info_struct_t* write_info, double number) {
  int add_extra_digit =
      write_float_to_buffer(sd, iters_field->digits_field, number);

  if (sd->justify_left && add_extra_digit) {
    ++iters_field->chars_field;
    --write_info->blank_chars_to_write;
    if (write_info->blank_chars_to_write < 0)
      write_info->blank_chars_to_write = 0;
  } else if (!sd->justify_left && add_extra_digit) {
    if (write_info->blank_chars_to_write > 0) {
      --iters_field->sign_field;
      shift_left(iters_field->digits_field,
                 write_info->number_len + add_extra_digit);
    }
    --write_info->blank_chars_to_write;
    if (write_info->blank_chars_to_write < 0)
      write_info->blank_chars_to_write = 0;
  }
}

void shift_left(char* begin, int size) {
  for (int i = 0; i < size; ++i) {
    begin[i - 1] = begin[i];
  }
  begin[size - 1] = '\0';
}

void write_specifier_c(specifier_data_t* sd, char* output_iter,
                       va_list* args_list) {
  char_type_u char_type;
  if (sd->long_len) {
    char_type.wide_char = (wchar_t)va_arg(*args_list, int64_t);
  } else {
    char_type.byte_char = (char)va_arg(*args_list, int64_t);
  }
  char blank_buff[8] = {0};
  int char_size = 0;
  if (sd->long_len) {
    char_size = wctomb(blank_buff, char_type.wide_char);
  } else {
    char_size = 1;
  }
  int overall_field_size = (sd->width > char_size) ? sd->width : char_size;
  int blank_field_size = overall_field_size - char_size;

  char* null_pos = write_padding(output_iter, overall_field_size, ' ');
  if (!sd->justify_left) {
    output_iter += blank_field_size;
  }
  if (sd->long_len) {
    wctomb(output_iter, char_type.wide_char);
  } else {
    *output_iter = char_type.byte_char;
  }
  sd->wrote_null_terminator = (*output_iter == '\0');
  *null_pos = '\0';
}
void write_specifier_s(specifier_data_t* sd, char* output_iter,
                       va_list* args_list) {
  iter_str_type_u iter_str_type;
  if (sd->long_len) {
    iter_str_type.iter_wide_str = (wchar_t*)va_arg(*args_list, const wchar_t*);
  } else {
    iter_str_type.iter_basic_str = (char*)va_arg(*args_list, const char*);
  }
  if ((sd->long_len && iter_str_type.iter_wide_str == NULL) ||
      (!sd->long_len && iter_str_type.iter_basic_str == NULL)) {
    s21_strncat(output_iter, "(null)\0", 7);
  } else {
    s21_size_t len_str =
        (sd->long_len ? wcslen(iter_str_type.iter_wide_str)
                      : s21_strlen(iter_str_type.iter_basic_str));

    s21_size_t final_str_size_bytes =
        (sd->precision != -1 && (s21_size_t)sd->precision < len_str)
            ? (s21_size_t)sd->precision
            : (sd->long_len ? wcstombs(NULL, iter_str_type.iter_wide_str, 0)
                            : len_str);
    int blank_chars_to_write = 0;
    if ((s21_size_t)sd->width > final_str_size_bytes) {
      blank_chars_to_write = sd->width - final_str_size_bytes;
    }

    char* empty_field = output_iter;
    char* str_field = output_iter;
    if (sd->justify_left) {
      empty_field += final_str_size_bytes;
    } else {
      str_field += blank_chars_to_write;
    }
    handle_str_specifier_s(sd, empty_field, str_field, &iter_str_type,
                           blank_chars_to_write, final_str_size_bytes);
  }
}
void handle_str_specifier_s(specifier_data_t* sd, char* empty_field,
                            char* str_field, iter_str_type_u* iter_str_type,
                            int blank_chars_to_write,
                            int final_str_size_bytes) {
  write_padding(empty_field, blank_chars_to_write, ' ');
  if (sd->long_len) {
    wcstombs(str_field, iter_str_type->iter_wide_str, final_str_size_bytes);
    str_field += final_str_size_bytes;
  } else {
    for (int i = 0; i < final_str_size_bytes; i++, str_field++) {
      *str_field = iter_str_type->iter_basic_str[i];
    }
  }

  if (sd->justify_left)
    empty_field[blank_chars_to_write] = '\0';
  else
    *str_field = '\0';
}

int write_float_to_buffer(specifier_data_t* sd, char* digits_field,
                          double number) {
  return s21_dtoa(digits_field, number, sd->precision);
}

int64_t get_signed_value(specifier_data_t* sd, va_list* args_list) {
  if (sd->long_len) return (long int)va_arg(*args_list, int64_t);
  if (sd->short_len) return (short)va_arg(*args_list, int64_t);
  return (int)va_arg(*args_list, int64_t);
}

uint64_t get_unsigned_value(specifier_data_t* sd, va_list* args_list) {
  if (sd->long_len) return (unsigned long)va_arg(*args_list, uint64_t);
  if (sd->short_len) return (unsigned short)va_arg(*args_list, uint64_t);
  return (unsigned int)va_arg(*args_list, uint64_t);
}

void shift_right(char* str) {
  int len = s21_strlen(str);
  if (len > 0) {
    for (int i = len; i > 0; i--) str[i] = str[i - 1];
  }
  str[len + 1] = '\0';
}

const char* parse_specifier_field(specifier_data_t* sd, iterators_t* it) {
  if (*it->curr_iter != '%') return it->curr_iter;
  it->curr_iter = parse_flags(it->curr_iter + 1, sd);
  it->curr_iter = parse_width(it->curr_iter, sd);
  it->curr_iter = parse_precision(it->curr_iter, sd);
  it->curr_iter = parse_length(it->curr_iter, sd);
  it->curr_iter = parse_type(it->curr_iter, sd);
  if (sd->type == INIT_TYPE) {
    it->curr_iter = parse_shielded_percent(it->curr_iter, sd);
    if (!sd->shielded_percent) {
      it->curr_iter = parse_last_non_shielded_percent(it->curr_iter, sd);
    }
    if (!sd->shielded_percent && !sd->last_non_shielded_percent) {
      it->curr_iter = parse_reduced_char(it->curr_iter, sd);
    }
  }
  return it->curr_iter;
}

const char* parse_reduced_char(const char* str, specifier_data_t* sd) {
  const char* reduced_filter = "hjlqtzLZ";
  for (int i = 0; i < 2 && !sd->reduce_char; ++i) {
    if (*(str - 1 + i) && s21_strchr(reduced_filter, *(str - 1 + i))) {
      sd->reduce_char = 1;
      sd->reduced_field_begin = str - 1 + i;
    }
  }
  if (sd->reduced_field_begin == str) {
    ++str;
  }
  return str;
}

void clear_specifier_data(specifier_data_t* sd) {
  sd->width = 0;
  sd->precision = UNDEFINED_PRECISION;
  sd->type = INIT_TYPE;
  sd->justify_left = 0;
  sd->precede_sign = 0;
  sd->precede_blank = 0;
  sd->short_len = 0;
  sd->long_len = 0;
  sd->padding_with_zeroes = 0;
  sd->shielded_percent = 0;
  sd->insert_precision_zero = 0;
  sd->last_non_shielded_percent = 0;
  sd->wrote_null_terminator = 0;
  sd->reduce_char = 0;
  sd->reduce_substring = 0;
  sd->reduced_field_begin = S21_NULL;
}

const char* parse_flags(const char* str, specifier_data_t* sd) {
  for (char is_flag = 1; *str && is_flag; ++str) {
    switch (*str) {
      case '+':
        if (sd->precede_sign) sd->reduce_substring = 1;
        sd->precede_sign = 1;
        break;
      case '-':
        if (sd->justify_left) sd->reduce_substring = 1;
        sd->justify_left = 1;
        break;
      case ' ':
        if (sd->precede_blank) sd->reduce_substring = 1;
        sd->precede_blank = 1;
        break;
      default:
        is_flag = 0;
        --str;  // to negate effect of ++str in for loop and stay on non flag
                // character
    }
  }
  if (sd->precede_sign) {
    sd->precede_blank = 0;
  }
  return str;
}

const char* parse_width(const char* str, specifier_data_t* sd) {
  if (*str == '0') {
    sd->padding_with_zeroes = 1;
  }
  return parse_number(str, &sd->width);
}

const char* parse_number(const char* str, int* pnum) {
  *pnum = 0;
  for (; *str >= '0' && *str <= '9'; ++str) {
    *pnum = *pnum * 10 + (*str - '0');
  }
  return str;
}

const char* parse_precision(const char* str, specifier_data_t* sd) {
  if (*str != '.') return str;
  str = skip_symb(++str, '0');
  str = parse_number(str, &sd->precision);
  sd->insert_precision_zero = (str[-1] == '.');
  return str;
}

const char* skip_symb(const char* str, char symb) {
  while (*str == symb) {
    ++str;
  }
  return str;
}

const char* parse_length(const char* str, specifier_data_t* sd) {
  switch (*str) {
    case 'h':
      sd->short_len = 1;
      break;
    case 'l':
      sd->long_len = 1;
      break;
    default:
      --str;  // to negate effect of ++str in return and stay on non length
              // character
  }
  return ++str;
}

const char* parse_type(const char* str, specifier_data_t* sd) {
  if (*str && s21_strchr("cdfsu", *str)) {
    sd->type = *str;
    correct_type_precision(sd);
    ++str;
  }
  return str;
}

void write_trivial_string(char* output_buff, iterators_t* it) {
  if (!it->curr_iter) return;
  while (*it->curr_iter != '%' && *it->curr_iter != '\0') {
    s21_strncat(output_buff, it->curr_iter, 1);
    ++it->curr_iter;
  }
}

const char* parse_last_non_shielded_percent(const char* str,
                                            specifier_data_t* sd) {
  const char* filter = "hjlqtzLZ";
  if (*str == '\0' || (!str[1] && s21_strchr(filter, *str) &&
                       !s21_strchr(filter, *(str - 1)))) {
    sd->last_non_shielded_percent = 1;
    if (*str != '\0') ++str;
  }
  return str;
}

const char* parse_shielded_percent(const char* str, specifier_data_t* sd) {
  if (str[0] == '%') {
    sd->shielded_percent = 1;
    ++str;
  }
  return str;
}

void correct_type_precision(specifier_data_t* sd) {
  if (sd->precision != UNDEFINED_PRECISION) return;
  switch (sd->type) {
    case 'u':
    case 'd':
      sd->precision = INTEGER_PRECISION;
      break;
    case 'f':
      sd->precision = FLOAT_PRECISION;
      break;
  }
}
