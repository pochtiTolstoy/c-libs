#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <wchar.h>

#include "core/converter/s21_converter.h"

#define SIZE 100
#define INIT_TYPE '?'

#define LOG_SPEC 0
#define LOG_INPUT 0
#define LOG_OUTPUT 0

typedef enum default_precision_e {
  UNDEFINED_PRECISION = -1,
  INTEGER_PRECISION = 0,
  FLOAT_PRECISION = 6
} default_precision_e;

typedef struct specifier_data_t {
  int width;
  int precision;
  char type;                         // cdfsu
  uint16_t justify_left : 1;         // flag: -
  uint16_t precede_sign : 1;         // flag: +
  uint16_t precede_blank : 1;        // flag: ' '
  uint16_t short_len : 1;            // length: h
  uint16_t long_len : 1;             // length: l
  uint16_t padding_with_zeroes : 1;  // when 0 occures before width
  uint16_t shielded_percent : 1;
  uint16_t insert_precision_zero : 1;
  uint16_t last_non_shielded_percent : 1;
  uint16_t wrote_null_terminator : 1;
  uint16_t reduce_char : 1;
  uint16_t reduce_substring : 1;
  const char* reduced_field_begin;
} specifier_data_t;

typedef struct interators_t {
  const char* backup_iter;
  const char* curr_iter;
} iterators_t;

typedef union integer_type_u {
  uint64_t unsigned_num;
  int64_t signed_num;
} integer_type_u;

typedef union char_type_u {
  char byte_char;
  wchar_t wide_char;
} char_type_u;

typedef union iter_str_type_u {
  char* iter_basic_str;
  wchar_t* iter_wide_str;
} iter_str_type_u;

typedef struct sign_struct_t {
  int is_signed;
  char sign;
} sign_struct_t;

typedef struct write_info_struct_t {
  int number_len;
  int is_negative;
  int min_digits_to_write;
  int blank_digits_to_write;
  int blank_chars_to_write;
  char blank_digits_symb;
  char blank_chars_symb;

} write_info_struct_t;

typedef struct iters_field_t {
  char* chars_field;
  char* digits_field;
  char* sign_field;
} iters_field_t;

int s21_sprintf(char*, const char*, ...);

void clear_specifier_data(specifier_data_t*);
const char* parse_specifier_field(specifier_data_t*, iterators_t* it);
const char* parse_flags(const char*, specifier_data_t*);
const char* parse_width(const char*, specifier_data_t*);
const char* parse_number(const char*, int*);
const char* parse_precision(const char*, specifier_data_t*);
const char* skip_symb(const char*, char);
const char* parse_length(const char*, specifier_data_t*);
const char* parse_type(const char*, specifier_data_t*);
const char* parse_last_non_shielded_percent(const char*, specifier_data_t*);
const char* parse_shielded_percent(const char*, specifier_data_t*);
const char* parse_reduced_char(const char*, specifier_data_t*);
void write_specifier_field(specifier_data_t*, iterators_t*, char*, va_list*);
void write_invalid_specifier_field(specifier_data_t*, iterators_t*, char*);
void write_valid_specifier_field(specifier_data_t*, iterators_t*, char*,
                                 va_list*);
void write_specifier_du(specifier_data_t*, char*, va_list*);
void initialize_write_info(write_info_struct_t*);
void initialize_iters_field(iters_field_t*, char*);
void handle_type_du(specifier_data_t*, integer_type_u*, write_info_struct_t*,
                    va_list*);
void write_to_sing_struct(sign_struct_t*, int, char);
char handle_negative(specifier_data_t*, int);
void handle_blank_chars(specifier_data_t*, write_info_struct_t*,
                        sign_struct_t*);
void handle_iters_field(specifier_data_t*, iters_field_t*, sign_struct_t*,
                        write_info_struct_t*, int);
char* write_padding(char*, int, char);
void write_digits_to_buffer(specifier_data_t*, char*, integer_type_u);
void handle_zero_if_justify_left(specifier_data_t*, iters_field_t*,
                                 write_info_struct_t*);
void write_specifier_c(specifier_data_t*, char*, va_list*);
void write_specifier_s(specifier_data_t*, char*, va_list*);
void handle_str_specifier_s(specifier_data_t*, char*, char*, iter_str_type_u*,
                            int, int);
int write_float_to_buffer(specifier_data_t*, char*, double);
int64_t get_signed_value(specifier_data_t*, va_list*);
uint64_t get_unsigned_value(specifier_data_t*, va_list*);
void shift_left(char*, int);
void write_trivial_string(char*, iterators_t*);
void correct_type_precision(specifier_data_t*);
void write_specifier_f(specifier_data_t*, char*, va_list*);
void handle_type_f(specifier_data_t*, iters_field_t*, write_info_struct_t*,
                   double);
int count_digits(int64_t);
const char* parse_reduced_substr(const iterators_t*, specifier_data_t*);
const char* write_reduced_invalid_flags(char*, const iterators_t*);

#endif
