hexll: main.o
	gcc main.o -o hexll

main.o: main.c
	gcc -Wall -Werror -Wconversion -pedantic -c main.c

.PHONY: clean
clean:
	rm main.o hexll

