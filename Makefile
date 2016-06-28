build/bin/hexll: build/obj/main.o
	gcc build/obj/main.o -o build/bin/hexll

build/obj/main.o: src/main.c
	mkdir -p build/obj
	mkdir build/bin
	
	gcc -Wall -Werror -Wconversion -pedantic -c src/main.c -o build/obj/main.o

.PHONY: clean
clean:
	rm -r build

