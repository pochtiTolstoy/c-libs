#include "s21_grep.h"

int main(int argc, char *argv[]) {
  flags_t flags = {0};
  if (argc == 1) {
    flags.err = 1;
    print_usage();
  } else if (argc == 2) {
    run_echo(argv[1], &flags);
  } else {
    run_grep_with_args(argc, argv, &flags);
  }
  return flags.err;
}

void run_grep_with_args(int argc, char *argv[], flags_t *pflags) {
  patterns_storage_t ps = {0};
  parse_flags(argc, argv, pflags);
  ps.type = (pflags->o) ? SPLIT_STORAGE : UNION_STORAGE;
  if (pflags->e || pflags->f) {
    collect_patterns(argc, argv, &ps);
  } else {
    find_first_non_flag_pattern(argc, argv, &ps);
  }
  if ((ps.patterns == NULL && ps.split_patterns == NULL)) {
    pflags->empty_pattern = 1;
  }
  if (!pflags->err && !ps.err) {
    process_files(argc, argv, pflags, &ps);
  }
  clear_patterns_storage(&ps);
}

void clear_patterns_storage(patterns_storage_t *ps) {
  for (size_t i = 0; i < ps->size && ps->split_patterns; ++i) {
    free(ps->split_patterns[i]);
  }
  free(ps->split_patterns);
  for (size_t i = 0; i < ps->size && ps->regex_buff; ++i) {
    regfree(ps->regex_buff + i);
  }
  free(ps->regex_buff);
  free(ps->patterns);
}

int is_data_file(int i, char *argv[], flags_t *pflags) {
  char *find_e = strchr(argv[i - 1], 'e');
  char *find_f = strchr(argv[i - 1], 'f');
  char *ptr_last_ch = argv[i - 1] + strlen(argv[i - 1]) - 1;
  int occurrence = first_occurrence_in_str('e', 'f', argv[i - 1]);
  int last_flag = (occurrence < 0 && find_e == ptr_last_ch) ||
                  (occurrence > 0 && find_f == ptr_last_ch);
  return (argv[i - 1][0] != '-' || !last_flag) && argv[i][0] != '-' &&
         !is_first_non_flag_pattern(i, argv, pflags);
}

int count_files(int argc, char *argv[], flags_t *pflags) {
  int file_counter = 0;
  for (int i = 2; i < argc; ++i) {
    if (is_data_file(i, argv, pflags)) {
      ++file_counter;
    }
  }
  return file_counter;
}

void process_files(int argc, char *argv[], flags_t *pflags,
                   patterns_storage_t *ps) {
  FILE *fp;
  int file_counter = count_files(argc, argv, pflags);
  regex_t regex;
  int reg_flags = (pflags->i) ? REG_ICASE : 0;
  int split_regex_res = compile_splitted_patterns(ps, pflags);
  allocate_if_empty(ps);
  int regex_res = regcomp(&regex, ps->patterns, reg_flags);
  for (int i = 2; i < argc && !regex_res && !split_regex_res; ++i) {
    if (is_data_file(i, argv, pflags)) {
      if ((fp = fopen(argv[i], "r")) != NULL) {
        exec_pattern_on_file(fp, pflags, &regex, file_counter, argv[i], ps);
        fclose(fp);
      } else if (!pflags->s) {
        print_file_err(argv[i]);
      }
    }
  }
  regfree(&regex);
}

int compile_splitted_patterns(patterns_storage_t *ps, flags_t *pflags) {
  if (!pflags->o || !ps->split_patterns || ps->size < 1) return 0;
  int regflags = (pflags->i) ? REG_ICASE : 0;
  int regres = 0;
  ps->regex_buff = calloc(ps->size, sizeof(regex_t));
  int err = 0;
  for (size_t i = 0; i < ps->size && !err; ++i) {
    if (!(err = (!ps->regex_buff || regres || ps->split_patterns[i] == NULL))) {
      regres = regcomp(ps->regex_buff + i, ps->split_patterns[i], regflags);
    }
  }
  return regres;
}

void exec_pattern_on_file(FILE *fp, flags_t *pflags, regex_t *pregex,
                          int file_counter, const char *file_name,
                          patterns_storage_t *ps) {
  char buff[LINE_SIZE] = {0};
  int lines_counter = 1;
  int count_matches_in_file = 0;
  while (fgets(buff, LINE_SIZE, fp) != NULL) {
    char *find_n = strchr(buff, '\n');
    if (find_n) {
      *find_n = '\0';
    }
    if (!pflags->o) {
      int regex_res =
          (buff[0]) ? regexec(pregex, buff, 0, NULL, 0) : REG_NOMATCH;
      exec_pattern_on_line(buff, regex_res, pflags, &count_matches_in_file,
                           &lines_counter, file_counter, file_name);
    } else if (!pflags->v && !pflags->empty_pattern) {
      exec_greedy_pattern_on_line(buff, ps, pflags, &lines_counter,
                                  file_counter, file_name);
    }
  }
  if (pflags->c && (!pflags->empty_pattern || pflags->v)) {
    if (file_counter > 1 && !pflags->h) {
      printf("%s:", file_name);
    }
    printf("%d\n", count_matches_in_file);
  }
  if (pflags->l && count_matches_in_file > 0) {
    printf("%s\n", file_name);
  }
}

void exec_greedy_pattern_on_line(const char *line, patterns_storage_t *ps,
                                 flags_t *pflags, int *lines_counter,
                                 int file_counter, const char *file_name) {
  matched_data_t md;
  int reg_flags = (pflags->i) ? REG_ICASE : 0;
  size_t shift = 0;

  while (shift < strlen(line)) {
    md = (matched_data_t){0};
    for (size_t i = 0; i < ps->size; ++i) {
      if (ps->split_patterns[i][0] != '^' || shift == 0) {
        md.match_code = regexec(ps->regex_buff + i, line + shift, 1,
                                &md.regmatch, reg_flags);
        get_matched_substr(&md, shift);
      }
    }
    shift += (md.max_len_substr) ? md.max_len_substr : 1;
    if (md.ready_substring) {
      if (file_counter > 1 && !pflags->h) {
        printf("%s:", file_name);
      }
      if (pflags->n) {
        printf("%d:", *lines_counter);
      }
      char *extracted_string = get_substr(line, md.begin, md.end);
      if (extracted_string) {
        printf("%s", extracted_string);
      }
      free(extracted_string);
      printf("\n");
    }
  }
  ++*lines_counter;
}

void get_matched_substr(matched_data_t *md, size_t shift) {
  if (md->match_code == 0) {
    size_t substr_len = md->regmatch.rm_eo - md->regmatch.rm_so;
    if ((md->regmatch.rm_so <= md->pos_first_substring) &&
        (substr_len > md->max_len_substr)) {
      md->pos_first_substring = md->regmatch.rm_so;
      md->max_len_substr = substr_len;
      md->ready_substring = 1;
      md->begin = shift + md->regmatch.rm_so;
      md->end = shift + md->regmatch.rm_eo - 1;
    }
  }
}

char *get_substr(const char *source, size_t begin, size_t end) {
  if (source == NULL || begin > end || begin >= strlen(source) ||
      end >= strlen(source))
    return NULL;
  int new_size = end - begin + 1;
  char *substring = malloc((new_size + 1) * sizeof(char));
  if (substring) {
    memcpy(substring, source + begin, new_size);
    substring[new_size] = '\0';
  }
  return substring;
}

void exec_pattern_on_line(char *line, int regex_res, flags_t *pflags,
                          int *count_matches_in_file, int *lines_counter,
                          int file_counter, const char *file_name) {
  int found_pattern = 0;
  if ((!pflags->v && regex_res == 0 && !pflags->empty_pattern) ||
      (pflags->v && (regex_res == REG_NOMATCH || pflags->empty_pattern))) {
    found_pattern = 1;
    ++*count_matches_in_file;
  }
  if (found_pattern && !pflags->l && !pflags->c) {
    if (file_counter > 1 && !pflags->h) {
      printf("%s:", file_name);
    }
    if (pflags->n) {
      printf("%d:", *lines_counter);
    }
    printf("%s\n", line);
  }
  ++*lines_counter;
}

int is_first_non_flag_pattern(int idx, char *argv[], flags_t *pflags) {
  if (pflags->e || pflags->f) return 0;
  int res = -1;
  for (int i = 1; i <= idx && res == -1; ++i) {
    if (argv[i][0] != '-') {
      res = (i == idx) ? 1 : 0;
    }
  }
  return res;
}

void find_first_non_flag_pattern(int argc, char *argv[],
                                 patterns_storage_t *ps) {
  for (int i = 1; i < argc - 1 && !ps->patterns && !ps->split_patterns; ++i) {
    if (argv[i][0] != '-' || strlen(argv[i]) == 1) {
      collect_pattern(argv[i], ps);
    }
  }
}

void collect_patterns(int argc, char *argv[], patterns_storage_t *ps) {
  for (int i = 1; i < argc; ++i) {
    int occurrence = first_occurrence_in_str('e', 'f', argv[i]);
    if (argv[i][0] == '-' && occurrence != 0) {
      process_ef_flags_collection(i, argc, argv, occurrence, ps);
    }
  }
}

void process_ef_flags_collection(int idx, int argc, char *argv[],
                                 int occurrence, patterns_storage_t *ps) {
  char ch = (occurrence < 0) ? 'e' : 'f';
  collector_f collect =
      (occurrence < 0) ? collect_pattern : collect_pattern_from_file;
  char *find_ch = strchr(argv[idx], ch);
  if (find_ch == argv[idx] + strlen(argv[idx]) - 1) {
    (idx + 1 < argc) ? collect(argv[idx + 1], ps) : print_missed_arg_err(ch);
  } else {
    collect(find_ch + 1, ps);
  }
}

void collect_pattern_from_file(const char *filename,
                               patterns_storage_t *patterns_storage) {
  FILE *fp = fopen(filename, "r");
  if (fp != NULL) {
    char buff[LINE_SIZE] = {0};
    while (fgets(buff, LINE_SIZE, fp) != NULL) {
      if (buff[strlen(buff) - 1] == '\n') {
        buff[strlen(buff) - 1] = '\0';
      }
      collect_pattern(buff, patterns_storage);
    }
    fclose(fp);
  } else {
    print_file_err(filename);
  }
}

int first_occurrence_in_str(char a, char b, const char *str) {
  char *pa = strchr(str, a);
  char *pb = strchr(str, b);
  int res = 0;
  if (pa == NULL && pb == NULL) {
    res = 0;
  } else if (pa == NULL) {
    res = 1;
  } else if (pb == NULL) {
    res = -1;
  } else {
    res = (int)(pa - pb);
  }
  return res;
}

void collect_pattern(const char *pattern, patterns_storage_t *ps) {
  if (!ps->err && ps->type == UNION_STORAGE) {
    (ps->patterns == NULL) ? create_pattern_storage(pattern, ps)
                           : add_pattern_to_storage(pattern, ps);
  }
  if (!ps->err && ps->type == SPLIT_STORAGE) {
    (ps->split_patterns == NULL) ? create_pattern_split_storage(pattern, ps)
                                 : add_pattern_to_split_storage(pattern, ps);
  }
}

void allocate_if_empty(patterns_storage_t *ps) {
  if (ps->patterns == NULL) {
    create_pattern_storage("", ps);
  }
  if (ps->split_patterns == NULL) {
    create_pattern_split_storage("", ps);
  }
}

void create_pattern_storage(const char *pattern, patterns_storage_t *ps) {
  if (NULL != (ps->patterns = malloc(sizeof(char) * (strlen(pattern) + 1)))) {
    memcpy(ps->patterns, pattern, strlen(pattern));
    ps->patterns[strlen(pattern)] = '\0';
  }
  ps->err = (ps->patterns == NULL) ? 1 : 0;
}

void add_pattern_to_storage(const char *pattern, patterns_storage_t *ps) {
  size_t new_len = strlen(ps->patterns) + strlen(pattern) + 2;
  char *ptr = realloc(ps->patterns, sizeof(char) * (new_len + 1));
  if (ptr != NULL) {
    ps->patterns = ptr;
    strncat(ps->patterns, "\\|", 3);
    strncat(ps->patterns, pattern, strlen(pattern));
    ps->patterns[new_len] = '\0';
  }
  ps->err = (ptr == NULL) ? 1 : 0;
}

void create_pattern_split_storage(const char *pattern, patterns_storage_t *ps) {
  if (NULL != (ps->split_patterns = malloc(sizeof(char *)))) {
    if (NULL != (ps->split_patterns[0] =
                     malloc(sizeof(char) * (strlen(pattern) + 1)))) {
      memcpy(ps->split_patterns[0], pattern, strlen(pattern));
      ps->split_patterns[0][strlen(pattern)] = '\0';
      ps->size = 1;
    }
  }
  ps->err = (!ps->split_patterns || !ps->split_patterns[0]) ? 1 : 0;
}

void add_pattern_to_split_storage(const char *pattern, patterns_storage_t *ps) {
  ++ps->size;
  char **pattern_arr = realloc(ps->split_patterns, ps->size * sizeof(char *));
  if (NULL != pattern_arr) {
    if (NULL != (pattern_arr[ps->size - 1] =
                     malloc(sizeof(char) * (strlen(pattern) + 1)))) {
      memcpy(pattern_arr[ps->size - 1], pattern, strlen(pattern));
      pattern_arr[ps->size - 1][strlen(pattern)] = '\0';
    }
    ps->split_patterns = pattern_arr;
  }
  ps->err = (!ps->split_patterns || !ps->split_patterns[ps->size - 1]) ? 1 : 0;
}

void parse_flags(int argc, char *argv[], flags_t *pflags) {
  for (int i = 1; i < argc; ++i) {
    char last_char = argv[i - 1][strlen(argv[i - 1]) - 1];
    if (argv[i][0] == '-' &&
        (argv[i - 1][0] != '-' || (last_char != 'e' && last_char != 'f'))) {
      parse_short_flag(argv[i], pflags);
    }
  }
}

void parse_short_flag(const char *str, flags_t *pflags) {
  char err_code = 0;
  char stop_parser = 0;
  for (size_t i = 1; i < strlen(str) && !pflags->err && !stop_parser; ++i) {
    switch (str[i]) {
      case 'e':
        pflags->e = 1;
        stop_parser = 1;
        break;
      case 'i':
        pflags->i = 1;
        break;
      case 'v':
        pflags->v = 1;
        break;
      case 'c':
        pflags->c = 1;
        break;
      case 'l':
        pflags->l = 1;
        break;
      case 'n':
        pflags->n = 1;
        break;
      case 's':
        pflags->s = 1;
        break;
      case 'h':
        pflags->h = 1;
        break;
      case 'f':
        pflags->f = 1;
        stop_parser = 1;
        break;
      case 'o':
        pflags->o = 1;
        break;
      default:
        pflags->err = 1;
        err_code = str[i];
    }
  }
  flags_postprocessing(pflags);
  if (pflags->err) {
    print_inv_opt_err(err_code);
  }
}

void flags_postprocessing(flags_t *pflags) {
  if (pflags->l || pflags->c) {
    pflags->o = 0;
  }
  if (pflags->v && pflags->o) {
    pflags->empty_output = 1;
  }
  if (pflags->l) {
    pflags->h = 0;
    pflags->c = 0;
  }
}

void print_inv_opt_err(int code) {
  fprintf(stderr, "grep: invalid option -- \'%c\'\n", code);
}

void print_usage(void) {
  fprintf(stderr, "Usage: grep [OPTION]... PATTERNS [FILE]...\n");
  fprintf(stderr, "Try \'grep --help\' for more information.\n");
}

void print_file_err(const char *file) {
  fprintf(stderr, "grep: %s: No such file or directory\n", file);
}

void print_missed_arg_err(int code) {
  fprintf(stderr, "grep: option requires an argument -- %c\n", code);
  fprintf(stderr, "Usage: grep [OPTION]... PATTERNS [FILE]...\n");
  fprintf(stderr, "Try \'grep --help\' for more information.\n");
}

void run_echo(const char *str, flags_t *pflags) {
  regex_t regex;
  char *line = NULL;
  size_t len = 0;
  if (strlen(str) > 1 && str[0] == '-') {
    if (str[1] != '-') {
      print_inv_opt_err((int)str[1]);
    }
    print_usage();
    pflags->err = 1;
  }

  if (!pflags->err) {
    regcomp(&regex, str, 0);
    ssize_t read = 0;
    while ((read = getline(&line, &len, stdin)) != EOF) {
      int regres = regexec(&regex, line, 0, NULL, 0);
      if (regres != REG_NOMATCH) {
        printf("%s", line);
      }
    }
  }
}
