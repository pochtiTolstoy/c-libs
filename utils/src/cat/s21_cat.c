#include "s21_cat.h"

int main(int argc, char *argv[]) {
  flags_t flags = {0};
  int flags_counter = parse_args(argc, argv, &flags);
  if (argc - flags_counter == 1 && !flags.err) {
    run_echo(&flags);
  } else if (!flags.err) {
    print_files(argc, argv, &flags);
  }
  return flags.err;
}

void run_echo(flags_t *pflags) {
  int line_number = 0;
  data_stat_t stat = {.prev_n = 1, .skip_n = 0};
  print_file_with_flags(stdin, pflags, &line_number, &stat);
}

void print_files(int argc, char *argv[], const flags_t *pflags) {
  FILE *fp = NULL;
  int line_number = 0;
  data_stat_t stat = {.prev_n = 1, .skip_n = 0};
  for (int i = 1; i < argc; ++i) {
    if (strcmp(argv[i], "-") == 0) {
      print_file_with_flags(stdin, pflags, &line_number, &stat);
      clearerr(stdin);
    } else if (argv[i][0] != '-') {
      fp = fopen(argv[i], "r");
      if (fp == NULL) {
        fprintf(stderr, "cat: %s: No such file or directory\n", argv[i]);
      } else {
        print_file_with_flags(fp, pflags, &line_number, &stat);
        fclose(fp);
      }
    }
  }
}

void print_file_with_flags(FILE *fp, const flags_t *pflags, int *pline_number,
                           data_stat_t *pstat) {
  int ch;
  while ((ch = fgetc(fp)) != EOF) {
    print_char(ch, pflags, pstat, pline_number);
  }
}

void print_char(int ch, const flags_t *pflags, data_stat_t *pstat,
                int *pline_number) {
  if (pflags->s && ch == '\n' && pstat->skip_n) return;
  pstat->skip_n = (ch == '\n' && pstat->prev_n);

  if ((pflags->n && pstat->prev_n) ||
      (pflags->b && pstat->prev_n && ch != '\n')) {
    ++*pline_number;
    printf("%6d\t", *pline_number);
  }

  if (pflags->e && ch == '\n') {
    putchar('$');
  }

  if (pflags->t && ch == '\t') {
    putchar('^');
    ch += SHIFT;
  }

  if (pflags->v && ch != '\t' && ch != '\n') {
    if (ch >= 160 && ch <= 254) {
      printf("M-");
      ch -= 2 * SHIFT;
    } else if (ch >= 0 && ch <= 31) {
      printf("^");
      ch += SHIFT;
    } else if (ch == 127) {
      printf("^");
      ch = SHIFT - 1;
    } else if (ch >= 128 && ch <= 159) {
      printf("M-^");
      ch -= SHIFT;
    } else if (ch >= 255) {
      printf("M-^");
      ch = SHIFT - 1;
    }
  }

  pstat->prev_n = (ch == '\n');
  putchar(ch);
}

int parse_args(int argc, char *argv[], flags_t *pflags) {
  int flags_counter = argc - 1;
  for (int i = 1; i < argc && !pflags->err; ++i) {
    if (strlen(argv[i]) > 1 && argv[i][0] == '-' && argv[i][1] == '-') {
      parse_long_flag(argv[i], pflags);
    } else if (argv[i][0] == '-') {
      parse_short_flag(argv[i], pflags);
    } else {
      --flags_counter;
    }
  }
  return flags_counter;
}

void parse_long_flag(char *str, flags_t *pflags) {
  static const char *LONG_FLAGS[LONG_FLAGS_SIZE] = {
      [NUMBER_NONBLANK] = "--number-nonblank",
      [NUMBER] = "--number",
      [SQUEEZE_BLANK] = "--squeeze-blank"};

  int long_flag_idx = -1;
  for (int i = 0; i < LONG_FLAGS_SIZE; ++i) {
    if (strcmp(str, LONG_FLAGS[i]) == 0) {
      long_flag_idx = i;
    }
  }
  switch (long_flag_idx) {
    case NUMBER_NONBLANK:
      pflags->b = 1;
      break;
    case NUMBER:
      pflags->n = 1;
      break;
    case SQUEEZE_BLANK:
      pflags->s = 1;
      break;
    default:
      pflags->err = 1;
  }

  if (pflags->n && pflags->b) pflags->n = 0;

  if (pflags->err) {
    fprintf(stderr, "cat: unrecognized option \'%s\'\n", str);
    fprintf(stderr, "Try \'cat --help\' for more information\n");
  }
}

void parse_short_flag(char *str, flags_t *pflags) {
  char err_char = '\0';
  for (size_t i = 1; i < strlen(str) && !pflags->err; ++i) {
    switch (str[i]) {
      case 'E':
        pflags->e = 1;
        break;
      case 'T':
        pflags->t = 1;
        break;
      case 'b':
        pflags->b = 1;
        break;
      case 'e':
        pflags->e = 1;
        pflags->v = 1;
        break;
      case 'n':
        pflags->n = 1;
        break;
      case 's':
        pflags->s = 1;
        break;
      case 't':
        pflags->t = 1;
        pflags->v = 1;
        break;
      case 'v':
        pflags->v = 1;
        break;
      default:
        pflags->err = 1;
        err_char = str[i];
    }
  }
  if (pflags->n && pflags->b) pflags->n = 0;

  if (pflags->err) {
    fprintf(stderr, "cat: invalid option -- \'%c\'\n", err_char);
    fprintf(stderr, "Try \'cat --help\' for more information\n");
  }
}
