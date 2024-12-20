CC= gcc
CFLAGS= -g -std=c89 -Iinclude

COMMON_C= src/*.c \
		  include/*.c
COMMON_O= *.o

BIN= well

all: base

base:
	$(CC) $(CFLAGS) $(COMMON_C) -c
	$(CC) $(CFLAGS) $(COMMON_O) -o $(BIN)

run_test:
	well tests/helloWorld/helloworld.well -i

vim_:
	mkdir -p ~/.vim/syntax
	mkdir -p ~/.vim/ftdetect
	cp vim/syntax/well.vim ~/.vim/syntax/
	cp vim/ftdetect/well.vim ~/.vim/ftdetect/

clean_vim:
	rm -f ~/.vim/syntax/well.vim
	rm -f ~/.vim/ftdetect/well.vim

clean:
	rm *.o $(BIN)
