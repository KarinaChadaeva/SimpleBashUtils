#!/bin/bash

SUCCESS_COUNTER=0
FAIL_COUNTER=0
DIFF_RES=""
TEST_FILE="text.txt"
echo "" > log.txt

for var in -b -e -n -s -t -v #-E -T --number-nonblank --number --squeeze-blank
do
    TEST1="$var $TEST_FILE"
    echo "$TEST1"
    ./s21_cat $TEST1 > s21_cat.txt
    cat $TEST1 > cat.txt
    DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
    if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
        then
        (( SUCCESS_COUNTER++ ))
    else
        echo "$TEST1" >> log.txt
        (( FAIL_COUNTER++ ))
    fi
    rm s21_cat.txt cat.txt
done

echo "SUCCESS: $SUCCESS_COUNTER"
echo "FAIL: $FAIL_COUNTER"