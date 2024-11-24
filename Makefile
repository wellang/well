CC= gcc
CFLAGS= -g -O2 -std=c89 -Iinclude

COMMON_C= $(wildcard src/*.c) \
		  $(wildcard include/*.c)
COMMON_O= $(wildcard *.o)

BIN= well

all: base

base:
	$(CC) $(CFLAGS) $(COMMON_C) -c
	$(CC) $(CFLAGS) $(COMMON_O) -o $(BIN)

vim:
	mkdir -p ~/.vim/syntax
	mkdir -p ~/.vim/ftdetect
	cp vim/syntax/well.vim ~/.vim/syntax/
	cp vim/ftdetect/well.vim ~/.vim/ftdetect/

clean_vim:
	rm -f ~/.vim/syntax/well.vim
	rm -f ~/.vim/ftdetect/well.vim
