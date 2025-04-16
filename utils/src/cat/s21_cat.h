#ifndef S21_CAT_H
#define S21_CAT_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define SHIFT 64
#define ull unsigned long long
#define LONG_FLAGS_SIZE 3

enum long_flags_lookup { NUMBER_NONBLANK = 0, NUMBER = 1, SQUEEZE_BLANK = 2 };

typedef struct {
  uint8_t b : 1;
  uint8_t e : 1;
  uint8_t n : 1;
  uint8_t s : 1;
  uint8_t t : 1;
  uint8_t v : 1;
  uint8_t err : 1;
} flags_t;

typedef struct {
  uint8_t prev_n : 1;
  uint8_t skip_n : 1;
} data_stat_t;

void run_echo(flags_t *pflags);

void print_flags(flags_t *pflags);

void print_files(int argc, char *argv[], const flags_t *pflags);

int parse_args(int argc, char *argv[], flags_t *pflags);

void parse_short_flag(char *str, flags_t *pflags);

void parse_long_flag(char *str, flags_t *pflags);

void print_file_with_flags(FILE *fp, const flags_t *pflags, int *pline_number,
                           data_stat_t *);

void print_char(int ch, const flags_t *pflags, data_stat_t *pstat,
                int *pline_number);

#endif /* S21_CAT_H */
