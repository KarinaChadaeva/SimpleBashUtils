#!/bin/bash

DIFF_RES=""
SUCCESS_COUNTER=0
FAIL_COUNTER=0
TEST_FILE1="hi.txt"
TEST_FILE2="test.txt"
echo "" > log.txt

for var in -i -v -c -l -n -h -iv -ic -il -in -ih -vc -vl -vn -vh -cn -ch -ln -lh -nh
do
  TEST="$var panda $TEST_FILE1"
  echo "$TEST"
  ./s21_grep $TEST > s21_grep.txt
  grep $TEST > grep.txt
  DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
  if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
    then
    (( SUCCESS_COUNTER++ ))
    else
    echo "$TEST" >> log.txt
    (( FAIL_COUNTER++ ))
  fi
  rm s21_grep.txt grep.txt
done

for var in -i -v -c -l -n -h -iv -ic -il -in -ih -vc -vl -vn -vh -cn -ch -ln -lh -nh
do
  TEST="$var panda $TEST_FILE1 $TEST_FILE2"
  echo "$TEST"
  ./s21_grep $TEST > s21_grep.txt
  grep $TEST > grep.txt
  DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
  if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
    then
    (( SUCCESS_COUNTER++ ))
    else
    echo "$TEST" >> log.txt
    (( FAIL_COUNTER++ ))
  fi
  rm s21_grep.txt grep.txt
done

for var in -e -ie -ve -ce -le -ne -he -se
do
  TEST="$var panda -e mola $TEST_FILE1 $TEST_FILE2"
  echo "$TEST"
  ./s21_grep $TEST > s21_grep.txt
  grep $TEST > grep.txt
  DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
  if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
    then
    (( SUCCESS_COUNTER++ ))
    else
    echo "$TEST" >> log.txt
    (( FAIL_COUNTER++ ))
  fi
  rm s21_grep.txt grep.txt
done

for var in -e -ie -ve -ce -le -ne -he -se
  do
  TEST="$var panda -e mola $TEST_FILE1"
  echo "$TEST"
  ./s21_grep $TEST > s21_grep.txt
  grep $TEST > grep.txt
  DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
  if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
    then
    (( SUCCESS_COUNTER++ ))
    else
    echo "$TEST" >> log.txt
    (( FAIL_COUNTER++ ))
  fi
  rm s21_grep.txt grep.txt
done

for var in -f -if -vf -cf -lf -nf -hf -sf
do
  TEST="$var p.txt $TEST_FILE2"
  echo "$TEST"
  ./s21_grep $TEST > s21_grep.txt
  grep $TEST > grep.txt
  DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
  if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
    then
    (( SUCCESS_COUNTER++ ))
    else
    echo "$TEST" >> log.txt
    (( FAIL_COUNTER++ ))
  fi
  rm s21_grep.txt grep.txt
done

for var in -f -if -vf -cf -lf -nf -hf -sf
do
  TEST="$var p.txt $TEST_FILE1 $TEST_FILE2"
  echo "$TEST"
  ./s21_grep $TEST > s21_grep.txt
  grep $TEST > grep.txt
  DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
  if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
    then
    (( SUCCESS_COUNTER++ ))
    else
    echo "$TEST" >> log.txt
    (( FAIL_COUNTER++ ))
  fi
  rm s21_grep.txt grep.txt
done

for var in -o -oi -ov -oc -ol -on -oh -os
do
  TEST="$var panda $TEST_FILE2"
  echo "$TEST"
  ./s21_grep $TEST > s21_grep.txt
  grep $TEST > grep.txt
  DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
  if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
    then
    (( SUCCESS_COUNTER++ ))
    else
    echo "$TEST" >> log.txt
    (( FAIL_COUNTER++ ))
  fi
  rm s21_grep.txt grep.txt
done

for var in -o -oi -ov -oc -ol -on -oh -os
do
  TEST="$var panda $TEST_FILE1 $TEST_FILE2"
  echo "$TEST"
  ./s21_grep $TEST > s21_grep.txt
  grep $TEST > grep.txt
  DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
  if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
    then
    (( SUCCESS_COUNTER++ ))
    else
    echo "$TEST" >> log.txt
    (( FAIL_COUNTER++ ))
  fi
  rm s21_grep.txt grep.txt
done

echo "SUCCESS: $SUCCESS_COUNTER"
echo "FAIL: $FAIL_COUNTER"