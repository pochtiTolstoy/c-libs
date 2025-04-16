#ifndef S21_GREP_H
#define S21_GREP_H

#define _GNU_SOURCE
#define LINE_SIZE 10000

#include <assert.h>
#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { UNION_STORAGE = 0, SPLIT_STORAGE = 1 } buff_type_e;

typedef struct {
  uint16_t e : 1;
  uint16_t i : 1;
  uint16_t v : 1;
  uint16_t c : 1;
  uint16_t l : 1;
  uint16_t n : 1;
  uint16_t s : 1;
  uint16_t h : 1;
  uint16_t f : 1;
  uint16_t o : 1;
  uint16_t err : 1;
  uint16_t empty_pattern : 1;
  uint16_t empty_output : 1;
} flags_t;

typedef struct {
  buff_type_e type;
  char *patterns;
  char **split_patterns;
  regex_t *regex_buff;
  size_t size;
  int err;
} patterns_storage_t;

typedef struct {
  regmatch_t regmatch;
  int pos_first_substring;
  int match_code;
  int ready_substring;
  size_t max_len_substr;
  size_t begin;
  size_t end;
} matched_data_t;

typedef void (*collector_f)(const char *, patterns_storage_t *);

void print_usage(void);
void run_echo(const char *, flags_t *);
void run_grep_with_args(int, char *[], flags_t *);
void print_inv_opt_err(int);
void parse_short_flag(const char *, flags_t *);
void parse_flags(int, char *[], flags_t *);
void collect_patterns(int, char *[], patterns_storage_t *);
void collect_pattern(const char *, patterns_storage_t *);
void find_first_non_flag_pattern(int, char *[], patterns_storage_t *);
void print_file_err(const char *);
char *get_substr(const char *, size_t, size_t);
void print_missed_arg_err(int);
void exec_pattern_on_file(FILE *, flags_t *, regex_t *, int, const char *,
                          patterns_storage_t *);
void exec_pattern_on_line(char *, int, flags_t *, int *, int *, int,
                          const char *);
void exec_greedy_pattern_on_line(const char *, patterns_storage_t *, flags_t *,
                                 int *, int, const char *);
void process_files(int, char *[], flags_t *, patterns_storage_t *);
int count_files(int, char *[], flags_t *);
int is_first_non_flag_pattern(int, char *[], flags_t *);
int is_data_file(int, char *[], flags_t *);
int first_occurrence_in_str(char, char, const char *);
void process_ef_flags_collection(int, int, char *[], int, patterns_storage_t *);
void collect_pattern_from_file(const char *, patterns_storage_t *);
void get_matched_substr(matched_data_t *, size_t);
void flags_postprocessing(flags_t *);

void clear_patterns_storage(patterns_storage_t *);
void create_pattern_storage(const char *, patterns_storage_t *);
void add_pattern_to_storage(const char *, patterns_storage_t *);
void create_pattern_split_storage(const char *, patterns_storage_t *);
void add_pattern_to_split_storage(const char *, patterns_storage_t *);
void allocate_if_empty(patterns_storage_t *);
int compile_splitted_patterns(patterns_storage_t *, flags_t *);

#endif /* S21_GREP_H */
