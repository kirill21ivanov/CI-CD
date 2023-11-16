NAME=s21_cat
CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11 -g 

all: $(NAME)

$(NAME): $(NAME).c
	$(CC) $(CFLAGS) $(NAME).c -o $(NAME)

clean:
	rm -rf $(NAME) *.log *.dSYM
docker_test:
	sh ../../materials/build/run.sh
test:
	bash test_func_cat.sh
clang:
	bash ../style.sh && rm -rf test.txt
leak:
	leaks -atExit -- ./$(NAME)
check:
	clang-format -style=Google -n *.c

rebuild:
	$(MAKE) clean
	$(MAKE) all
