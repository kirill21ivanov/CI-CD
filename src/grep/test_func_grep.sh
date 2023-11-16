#!/bin/bash

DIFF_RES=""
COUNTER_SUCCESS=0
COUNTER_FAIL=0
NUMBER=1

GREEN='\033[32m'
RED='\033[31m'
NORMAL='\033[0m'
echo -e $GREEN "TESTS for GREP"

for var1 in -i -v -c -h -n -s 
do
    for var2 in -i -v -c -h -n -s
    do
        for var3 in -i -v -c -h -n -s
        do
            TEST0="-e while $var1 $var2 $var3 Makefile s21_grep.c"
            ./s21_grep $TEST0 > s21_grep.txt
            grep $TEST0 > grep.txt
            DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
            if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
                then
                    echo -e $NORMAL TEST $NUMBER "$TEST0" $GREEN "\tSUCCESS"
                    (( COUNTER_SUCCESS++ ))
                else
                    echo -e $NORMAL TEST $NUMBER "$TEST0" $RED "\tFAIL"
                    (( COUNTER_FAIL++ ))
                fi
                ((NUMBER++))
            rm s21_grep.txt grep.txt
        done
    done
done

for var5 in -i -c -n -h -v -s 
do  
    for var6 in i c n h v s 
    do
            TEST0="$var5$var6 handler Makefile s21_grep.c"
            ./s21_grep $TEST0 > s21_grep.txt
            grep $TEST0 > grep.txt
            DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
            if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
                echo -e $NORMAL TEST $NUMBER "$TEST0" $GREEN "\tSUCCESS"
                (( COUNTER_SUCCESS++ ))
            else
                echo -e $NORMAL TEST $NUMBER "$TEST0" $RED "\tFAIL"
                (( COUNTER_FAIL++ ))
            fi
            ((NUMBER++))
            rm s21_grep.txt grep.txt
    done
done

echo -e $GREEN SUCCESS $COUNTER_SUCCESS
echo -e $RED FAIL $COUNTER_FAIL

if [ $COUNTER_FAIL != 0 ]; then
    exit 1
fi