#!/bin/bash
# Форматируем все файлы .c, перенаправляем ошибки в файл test_cat/test_grep
clang-format -style=google   -n ./cat/*.c ./grep/*.c &> test.txt
# Считаем количество строк в файле test_cat/test_grep
count_test=$(cat test.txt | wc -l)
# Если количество строк отлично от 0, значит есть ошибки форматирования
if [ $count_test != 0 ]; then
    echo "Найдена ошибка в стиле кода"
    exit 0
else
    echo "Программа работает без ошибок"
    exit 1
fi