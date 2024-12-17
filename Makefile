all: 01 02

bin: 
	mkdir bin

01: 01.c bin
	cc 01.c -o bin/01 -Wall -Wextra
	cp input1.txt bin
	bin/01

02: 02.c bin
	cc 02.c -o bin/02 -Wall -Wextra
	cp input2.txt bin
	bin/02

clean:
	rm -rf bin
