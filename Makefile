all:
	gcc -ggdb cvector.c -o cvector.out
	gcc -ggdb vector.c -o vector.out
	gcc -ggdb map.c -o map.out

install:
	sudo cp -i map.h vector.h /usr/include/

uninstall:
	sudo rm -f /usr/include/map.h /usr/include/vector.h
