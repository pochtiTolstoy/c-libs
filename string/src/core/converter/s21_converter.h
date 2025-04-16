#ifndef S21_MACROSES_H
#define S21_MACROSES_H

#define S21_ABS(value) ((value) < 0 ? -(value) : (value))
#define HANDLE_ZERO_CASE(ch, d) \
  do {                          \
    if ((d) == 0) {             \
      *(ch) = '0';              \
      (ch)++;                   \
    }                           \
  } while (0)

#define HANDLE_NEGATIVE_SIGN(iterator, predicate) \
  do {                                            \
    if (predicate) {                              \
      (**iterator) = '-';                         \
      ++(*iterator);                              \
    }                                             \
  } while (0)

#define EXTRACT_DIGITS_SIGNED(ch, last, d, type) \
  do {                                           \
    while (*(d) != 0) {                          \
      *(last) = *(d) % 10;                       \
      *(d) = (type)(*(d) / 10);                  \
      *(ch) = (char)(S21_ABS(*(last)) + '0');    \
      (ch)++;                                    \
    }                                            \
  } while (0)

#define EXTRACT_DIGITS_UNSIGNED(ch, last, d, type) \
  do {                                             \
    while (*(d) != 0) {                            \
      *(last) = *(d) % 10;                         \
      *(d) = (type)(*(d) / 10);                    \
      *(ch) = (char)((*(last)) + '0');             \
      (ch)++;                                      \
    }                                              \
  } while (0)

#define S21_CONVERT_DIGIT_TO_STRING_SIGNED(buf, value, type) \
  do {                                                       \
    type last = 0;                                           \
    type d = value;                                          \
    char* ch = buf;                                          \
    HANDLE_ZERO_CASE(ch, d);                                 \
    EXTRACT_DIGITS_SIGNED(ch, &last, &d, type);              \
    *ch = '\0';                                              \
    ch = s21_strreverse(buf);                                \
  } while (0)

#define S21_CONVERT_DIGIT_TO_STRING_UNSIGNED(buf, value, type) \
  do {                                                         \
    type last = 0;                                             \
    type d = value;                                            \
    char* ch = buf;                                            \
    HANDLE_ZERO_CASE(ch, d);                                   \
    EXTRACT_DIGITS_UNSIGNED(ch, &last, &d, type);              \
    *ch = '\0';                                                \
    ch = s21_strreverse(buf);                                  \
  } while (0)
#define COUNT_DIGITS(type, number, counter) \
  do {                                      \
    type temp_number = (type)(number);      \
    (counter) = ((temp_number) == 0);       \
    while ((temp_number) != 0) {            \
      temp_number /= 10;                    \
      ++(counter);                          \
    }                                       \
  } while (0)
#endif
