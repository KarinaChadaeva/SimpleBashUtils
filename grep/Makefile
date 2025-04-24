FLAGS= -Wall -Werror -Wextra -std=c11

s21_grep: grep.o flags.o node_func.o
	gcc $(FLAGS) grep.o flags.o node_func.o -o s21_grep

all: s21_grep

build: s21_grep

rebuild: clean s21_grep

flags.o: 
	gcc $(FLAGS) -c flags.c -o flags.o

grep.o:
	gcc $(FLAGS) -c grep.c -o grep.o

node_func.o:
	gcc $(FLAGS) -c node_func.c -o node_func.o

clean:
	rm -rf s21_grep *.o