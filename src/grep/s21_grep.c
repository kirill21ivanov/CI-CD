#include "s21_grep.h"

int main(int argc, char **argv) {
  opt flags = {0};
  int count = 0;
  char template_pattern[990][990] = {0};
  if (argc > 2) {
    parser(argc, argv, &flags, template_pattern, &count);
    grep(argc, argv, &flags, template_pattern, &count);
  }
  return 0;
}

int parser(int argc, char **argv, opt *flags, char template_pattern[990][990],
           int *count) {
  opterr = 0;
  int options = 0;
  int opt_index = 0;
  while (options != -1) {
    options = getopt_long(argc, argv, "e:ivclnhsf:o", 0, &opt_index);
    switch (options) {
      case 'e':
        flags->flag_e = 1;
        get_template_e(template_pattern, count);
        break;

      case 'i':
        flags->flag_i = 1;
        break;

      case 'v':
        flags->flag_v = 1;
        break;

      case 'c':
        flags->flag_c = 1;
        break;

      case 'l':
        flags->flag_l = 1;
        break;

      case 'n':
        flags->flag_n = 1;
        break;

      case 'h':
        flags->flag_h = 1;
        break;

      case 's':
        flags->flag_s = 1;
        break;

      case 'f':
        flags->flag_f = 1;
        get_template_f(template_pattern, count);
        break;

      case 'o':
        flags->flag_o = 1;
        break;
    }
    if (flags->flag_v) flags->flag_o = 0;

    if (flags->flag_l) {
      flags->flag_o = 0;
      flags->flag_s = 0;
      flags->flag_n = 0;
    }
  }

  if ((flags->flag_f == 0) && (flags->flag_e == 0)) {
    get_template(argv, template_pattern, count);
  }

  return 0;
}

void get_template(char *argv[], char template_pattern[990][990], int *count) {
  strcpy(template_pattern[*count], argv[optind]);
  *count = *count + 1;
}

void get_template_e(char template_pattern[990][990], int *count) {
  strcpy(template_pattern[*count], optarg);
  *count = *count + 1;
}

void get_template_f(char template_pattern[990][990], int *count) {
  char c[990] = {0};
  FILE *file_text = fopen(optarg, "r");
  if (file_text == NULL) {
    fprintf(stderr, "not file for flag -f\n");
  } else {
    while (fgets(c, 990, file_text) != NULL) {
      strcpy(template_pattern[*count], c);
      if (template_pattern[*count][(strlen(template_pattern[*count]) - 1)] ==
          '\n') {
        template_pattern[*count][(strlen(template_pattern[*count]) - 1)] = '\0';
      }
      *count = *count + 1;
    }
    fclose(file_text);
  }
}

void grep(int argc, char *argv[], opt *flags, char template_pattern[990][990],
          int *count) {
  char str[2048] = {0};
  char *match = str;
  int reg_i = REG_EXTENDED;
  if (flags->flag_i) reg_i = REG_ICASE;
  int success_comp = 0;
  int success_ec = 0;
  int files_count = 0;
  if (!flags->flag_e && !flags->flag_f) {
    files_count = argc - optind - 1;
  } else {
    files_count = argc - optind;
  }
  for (; optind < argc; optind++) {
    int flg_o = 1;

    int number = 0, number_c = 0, number_c_v = 0;
    FILE *files = fopen(argv[optind], "r");
    if (files != NULL) {
      while (fgets(match, 990, files) != NULL) {
        number++;
        if (match[strlen(match) - 1] == '\n') {
          match[strlen(match) - 1] = '\0';
        }
        int success_ec_count = 0;
        flg_o = 1;
        int flg_v = 0;
        int regexec_flag = 0;
        int br = 1;
        for (int i = 0; i < *count && br >= 1; i++) {
          regex_t regex;
          if (regcomp(&regex, template_pattern[i], reg_i) != 0) {
            if ((template_pattern[i][0] != '\0' && !flags->flag_v) ||
                (template_pattern[i][0] == '\0' && flags->flag_v)) {
              success_comp = 1;
            }
          }
          if (!success_comp) {
            success_ec = regexec(&regex, match, 0, NULL, 0);
            if ((!success_ec || template_pattern[i][0] == '\0') &&
                !flags->flag_v) {
              if (flg_o) number_c++;
              result_print(argv, flags, &match, &files_count, &number, &regex,
                           &regexec_flag, &flg_o);
              if (!flags->flag_o) br = 0;
            }
            if (flags->flag_v && br >= 1) {
              if (success_ec != 0) {
                success_ec_count++;
                flg_v++;
                if (flg_v == *count) number_c_v++;
              }
            }
          }
          regfree(&regex);
        }
        if ((flags->flag_v) && (success_ec_count == *count)) {
          if (files_count > 1 && !flags->flag_h && !flags->flag_c &&
              !flags->flag_l)
            printf("%s:", argv[optind]);
          if (flags->flag_n && !flags->flag_c && !flags->flag_l && flg_o == 1)
            printf("%d:", number);
          if (!flags->flag_o && !flags->flag_c && !flags->flag_l && flg_o == 1)
            printf("%s\n", match);
        }
      }

      if (files_count != 1 && flags->flag_c && !flags->flag_h &&
          !flags->flag_l) {
        printf("%s:", argv[optind]);
      }
      if (flags->flag_c && !flags->flag_l) {
        if (!flags->flag_v)
          printf("%d\n", number_c);
        else if (flags->flag_v)
          printf("%d\n", number_c_v);
      }
      if (flags->flag_l) {
        if (flags->flag_c) {
          if (files_count != 1 && !flags->flag_h) printf("%s:", argv[optind]);
          if (!flags->flag_v) {
            if (number_c > 1) {
              printf("%d\n", 1);
            } else {
              printf("%d\n", number_c);
            }
            if (number_c > 0) printf("%s\n", argv[optind]);
          } else if (flags->flag_v) {
            if (number_c_v > 1)
              printf("%d\n", 1);
            else
              printf("%d\n", number_c_v);
          }
          if (number_c_v > 0) printf("%s\n", argv[optind]);
        } else {
          if (!flags->flag_v) {
            if (number_c > 0) printf("%s\n", argv[optind]);
          } else if (flags->flag_v) {
            if (number_c_v > 0) printf("%s\n", argv[optind]);
          }
        }
      }
      fclose(files);
    }
  }
}

void result_print(char *argv[], opt *flags, char **match, int *files_count,
                  int *number, regex_t *regex, int *regexec_flag, int *flg_o) {
  if (*files_count > 1 && !flags->flag_h && !flags->flag_c && !flags->flag_l)
    printf("%s:", argv[optind]);
  if (flags->flag_n && !flags->flag_c && !flags->flag_l && *flg_o == 1)
    printf("%d:", *number);
  if (!flags->flag_o && !flags->flag_c && !flags->flag_l && *flg_o == 1)
    printf("%s\n", *match);
  *flg_o = 0;
  if (flags->flag_o && !flags->flag_c) {
    regmatch_t match_o[1];
    while (regexec(regex, *match, 1, match_o, *regexec_flag) == 0) {
      char tmp[990] = "\0";
      int tmp_counter = 0;
      for (int i = match_o[0].rm_so; i < match_o[0].rm_eo; i++) {
        tmp[tmp_counter] = (*match)[i];
        tmp_counter++;
      }
      printf("%s\n", tmp);
      *match = *match + match_o[0].rm_eo;
      *regexec_flag = REG_NOTBOL;
    }
  }
}
