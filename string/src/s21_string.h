#ifndef S21_STRING_H
#define S21_STRING_H
#define s21_size_t unsigned long long
#define S21_NULL (void *)0

#include <ctype.h>
#include <math.h>
#include <stdlib.h>

#include "s21_sprintf.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strtok(char *str, const char *delim);
s21_size_t s21_strlen(const char *);
s21_size_t s21_strcspn(const char *, const char *);
void *s21_memchr(const void *, int, s21_size_t);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *buf, int ch, s21_size_t count);
char *s21_strchr(const char *str, int c);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
char *s21_strerror(int errnum);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
int is_trim_char(char c, const char *trim_chars);
int s21_dtoa(char *, double, int);
char *s21_strreverse(char *str);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

#endif
