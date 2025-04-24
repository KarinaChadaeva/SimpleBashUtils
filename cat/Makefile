FLAGS= -Wall -Werror -Wextra -std=c11

s21_cat: cat.o flags.o
	gcc $(FLAGS) cat.o flags.o -o s21_cat

all: s21_cat

build: s21_cat

rebuild: clean s21_cat

cat.o: 
	gcc $(FLAGS) -c cat.c -o cat.o

flags.o: 
	gcc $(FLAGS) -c flags.c -o flags.o

clean:
	rm -rf s21_cat *.o