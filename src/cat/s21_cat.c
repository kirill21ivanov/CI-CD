#include "s21_cat.h"

int main(int argc, char **argv) {
  struct flag_cat flag = {0};
  if (argc > 1 && parser(argc, argv, &flag)) {
    if (flag.f_b) {
      flag.f_n = 0;
    }
    for (int i = 1; i < argc; i++) {
      if (argv[i][0] == '-') {
        continue;
      } else {
        FILE *file = fopen(argv[i], "r");
        if (file != NULL) {
          print_cat(file, flag);
          fclose(file);
        }
      }
    }
  }
  return 0;
}

void print_cat(FILE *file, struct flag_cat flag) {
  char ch;
  char pred_ch = '\n';
  char predpred_ch = 0;
  int number = 1;
  while ((ch = fgetc(file)) != EOF) {
    if ((flag.f_n) && !(flag.f_b) && (pred_ch == '\n') &&
        (!((flag.f_s) && (predpred_ch == '\n') && (ch == '\n')))) {
      printf("%6d\t", number);
      number++;
    }

    if ((flag.f_b) && !(flag.f_n) && (ch != '\n') && (pred_ch == '\n')) {
      printf("%6d\t", number);
      number++;
    }

    if ((flag.f_v) && (((ch < 32) && (ch != 9) && (ch != 10)) || (ch == 127))) {
      putchar(94);
      ch = (ch == 127) ? 63 : ch + 64;
    }

    if ((flag.f_t) && (ch == 9)) {
      putchar(94);
      ch += 64;
    }

    //  данный код работает на других версия си и баш при других версиях
    //  использовать это
    //    if (flag.f_n == 0 && flag.f_b == 1) {
    //      if ((flag.f_e) && (ch == '\n') &&
    //      (!((flag.f_s) && (pred_ch == '\n') && predpred_ch == '\n'))) {
    //        if (pred_ch == '\n') {
    //          printf("      \t");
    //          putchar(36);
    //        }
    //      }
    //    }
    //
    //    if (flag.f_b == 0 && flag.f_n == 0) {
    //      if ((flag.f_e) && (ch == '\n') &&
    //      (!((flag.f_s) && (pred_ch == '\n') && predpred_ch == '\n'))) {
    //        putchar(36);
    //      }
    //    }
    //
    //    if (flag.f_b == 1) {
    //      if ((flag.f_e) && (ch == '\n') &&
    //      (!((flag.f_s) && (pred_ch == '\n') && predpred_ch == '\n'))) {
    //        if (ch == '\n' && pred_ch != '\n') {
    //          putchar(36);
    //        }
    //      }
    //    }
    //
    //    if (flag.f_n == 1) {
    //      if ((flag.f_e) && (ch == '\n') &&
    //      (!((flag.f_s) && (pred_ch == '\n') && predpred_ch == '\n'))) {
    //        putchar(36);
    //      }
    //    }

    if ((flag.f_e) && (ch == '\n') &&
        (!((flag.f_s) && (pred_ch == '\n') && predpred_ch == '\n'))) {
      putchar(36);
    }

    if (!((flag.f_s) && (ch == '\n') && (pred_ch == '\n') &&
          predpred_ch == '\n')) {
      putchar(ch);
      predpred_ch = pred_ch;
      pred_ch = ch;
    }
  }
}

int parser(int argc, char **argv, struct flag_cat *flag) {
  int result = 1;
  int count = 1;
  while (count < argc) {
    if (argv[count][0] == '-') {
      int len = strlen(argv[count]);
      if (argv[count][1] == '-' || argv[count][1] == 'E' ||
          argv[count][1] == 'T') {
        if (strcmp(argv[count], "--number-nonblank") == 0) {
          flag->f_b = 1;
        } else if (strcmp(argv[count], "--number") == 0) {
          flag->f_n = 1;
        } else if (strcmp(argv[count], "--squeeze-blank") == 0) {
          flag->f_s = 1;
        } else {
          result = 0;
          break;
        }
      } else if (argv[count][1] == 'E' && argv[count][2] == '\0') {
        flag->f_E = 1;
      } else if (argv[count][1] == 'T' && argv[count][2] == '\0') {
        flag->f_T = 1;
      } else {
        for (int i = 1; i < len; i++) {
          if (argv[count][i] == 'b') {
            flag->f_b = 1;
          } else if (argv[count][i] == 'e') {
            flag->f_e = 1;
            flag->f_v = 1;
          } else if (argv[count][i] == 'n') {
            flag->f_n = 1;
          } else if (argv[count][i] == 's') {
            flag->f_s = 1;
          } else if (argv[count][i] == 't') {
            flag->f_t = 1;
            flag->f_v = 1;
          } else if (argv[count][i] == 'v') {
            flag->f_v = 1;
          } else {
            result = 0;
            break;
          }
        }
      }
    } else {
      break;
    }
    count++;
  }
  return result;
}
