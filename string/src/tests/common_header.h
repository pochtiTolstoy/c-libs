#ifndef COMMON_HEADER_H
#define COMMON_HEADER_H

#include <check.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

#define UNPACK_1(arr) arr[0]
#define UNPACK_2(arr) UNPACK_1(arr), arr[1]
#define UNPACK_3(arr) UNPACK_2(arr), arr[2]
#define UNPACK_4(arr) UNPACK_3(arr), arr[3]
#define UNPACK_5(arr) UNPACK_4(arr), arr[4]
#define UNPACK_6(arr) UNPACK_5(arr), arr[5]
#define UNPACK_7(arr) UNPACK_6(arr), arr[6]
#define UNPACK_8(arr) UNPACK_7(arr), arr[7]
#define UNPACK_9(arr) UNPACK_8(arr), arr[8]
#define UNPACK_10(arr) UNPACK_9(arr), arr[9]
#define UNPACK_11(arr) UNPACK_10(arr), arr[10]
#define UNPACK_12(arr) UNPACK_11(arr), arr[11]

// TO UNPACK DATA ELEMENTS BASED ON COMPILE-TIME CONSTANT
#define UNPACK(arr, n) UNPACK_##n(arr)

// TO KEEP DATA TYPE GENERIC
#define TEST_SPRINTF(s21_buff, orig_buff, format, data, arglen) \
  do {                                                          \
    switch (arglen) {                                           \
      case 0:                                                   \
        s21_sprintf(s21_buff, format);                          \
        sprintf(orig_buff, format);                             \
      case 1:                                                   \
        s21_sprintf(s21_buff, format, UNPACK(data, 1));         \
        sprintf(orig_buff, format, UNPACK(data, 1));            \
        break;                                                  \
      case 2:                                                   \
        s21_sprintf(s21_buff, format, UNPACK(data, 2));         \
        sprintf(orig_buff, format, UNPACK(data, 2));            \
        break;                                                  \
      case 3:                                                   \
        s21_sprintf(s21_buff, format, UNPACK(data, 3));         \
        sprintf(orig_buff, format, UNPACK(data, 3));            \
        break;                                                  \
      case 4:                                                   \
        s21_sprintf(s21_buff, format, UNPACK(data, 4));         \
        sprintf(orig_buff, format, UNPACK(data, 4));            \
        break;                                                  \
      case 5:                                                   \
        s21_sprintf(s21_buff, format, UNPACK(data, 5));         \
        sprintf(orig_buff, format, UNPACK(data, 5));            \
        break;                                                  \
      case 6:                                                   \
        s21_sprintf(s21_buff, format, UNPACK(data, 6));         \
        sprintf(orig_buff, format, UNPACK(data, 6));            \
        break;                                                  \
      case 7:                                                   \
        s21_sprintf(s21_buff, format, UNPACK(data, 7));         \
        sprintf(orig_buff, format, UNPACK(data, 7));            \
        break;                                                  \
      case 8:                                                   \
        s21_sprintf(s21_buff, format, UNPACK(data, 8));         \
        sprintf(orig_buff, format, UNPACK(data, 8));            \
        break;                                                  \
      case 9:                                                   \
        s21_sprintf(s21_buff, format, UNPACK(data, 9));         \
        sprintf(orig_buff, format, UNPACK(data, 9));            \
        break;                                                  \
      case 10:                                                  \
        s21_sprintf(s21_buff, format, UNPACK(data, 10));        \
        sprintf(orig_buff, format, UNPACK(data, 10));           \
        break;                                                  \
      case 11:                                                  \
        s21_sprintf(s21_buff, format, UNPACK(data, 11));        \
        sprintf(orig_buff, format, UNPACK(data, 11));           \
        break;                                                  \
      case 12:                                                  \
        s21_sprintf(s21_buff, format, UNPACK(data, 12));        \
        sprintf(orig_buff, format, UNPACK(data, 12));           \
        break;                                                  \
      default:                                                  \
        printf("Unsupported argument length: %d\n", arglen);    \
        break;                                                  \
    }                                                           \
    ck_assert_str_eq(s21_buff, orig_buff);                      \
  } while (0)

#endif
