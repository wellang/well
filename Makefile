C = gcc
CFLAGS = -std=c99
COMMON_.c = src/asm_interp.c src/mov_search.c src/syscall_interp.c src/push_search.c src/types.c src/instructions.c src/log.c src/array_interp.c src/asm_macros.c src/include.c
COMMONC_.o = asm_interp.o mov_search.o syscall_interp.o push_search.o types.o instructions.o log.o array_interp.o asm_macros.o include.o
INCLUDELOC = /usr/include/
LOC = /usr/bin/

.PHONY: base install vim clean_vim clean purge

.SUFFIXES: .c .o

base:
	$(C) $(CFLAGS) -L src -c $(COMMON_.c)
	$(C) $(CFLAGS) -o wesm $(COMMONC_.o)

install:
	sudo mkdir $(INCLUDELOC)wellang
	sudo cp wesm $(LOC)
vim:
	cp vim/syntax/well.vim ~/.vim/syntax/
	cp vim/ftdetect/well.vim ~/.vim/ftdetect/
clean_vim:
	rm -f ~/.vim/syntax/well.vim
	rm -f ~/.vim/ftdetect/well.vim
clean:
	rm -f $(COMMONC_.o)
	sudo rm -R $(INCLUDELOC)wellang
	sudo rm -R $(LOC)wesm
purge:
	rm -f $(COMMONC_.o)
	rm -f ~/.vim/syntax/well.vim
	rm -f ~/.vim/ftdetect/well.vim
	sudo rm -R $(INCLUDELOC)wellang
	sudo rm -R $(LOC)wesm
