#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int flag_e;
  int flag_i;
  int flag_v;
  int flag_c;
  int flag_l;
  int flag_n;
  int flag_h;
  int flag_s;
  int flag_f;
  int flag_o;
} opt;

int parser(int argc, char *argv[], opt *flags, char template_pattern[990][990],
           int *count);
void get_template(char *argv[], char template_pattern[990][990], int *count);
void get_template_e(char template_pattern[990][990], int *count);
void get_template_f(char template_pattern[990][990], int *count);
void grep(int argc, char *argv[], opt *flags, char template_pattern[990][990],
          int *count);
void result_print(char *argv[], opt *flags, char **match, int *files_count,
                  int *number, regex_t *regex, int *regexec_flag, int *flg_o);
#endif  // SRC_GREP_S21_GREP_H_
