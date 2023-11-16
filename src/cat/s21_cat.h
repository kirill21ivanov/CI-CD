#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct flag_cat {
  int f_b;
  int f_e;
  int f_n;
  int f_s;
  int f_t;
  int f_v;
  int f_E;
  int f_T;
};

int parser(int argc, char **argv, struct flag_cat *flag);
void print_cat(FILE *file, struct flag_cat flag);

#endif
