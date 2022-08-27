C = gcc
CFLAGS = -std=c99
COMMON_.c = src/asm_interp.c src/mov_search.c src/syscall_interp.c src/push_search.c src/types.c src/instructions.c src/log.c src/array_interp.c src/asm_macros.c src/include.c src/lea.c src/math.c src/argparse/argparse.c src/argparse/extract.c src/argparse/ap_inter.c #src/asm2obj.c src/asm2obj_elf.c
COMMONC_.o = asm_interp.o mov_search.o syscall_interp.o push_search.o types.o instructions.o log.o array_interp.o asm_macros.o include.o lea.o math.o argparse.o extract.o ap_inter.o #asm2obj.o asm2obj_elf.o
USR = usr
INCLUDELOC = /$(USR)/include/
LOC = /$(USR)/bin/

.PHONY: base install vim clean_vim clean purge

.SUFFIXES: .c .o

base:
	$(C) $(CFLAGS) -L src -c $(COMMON_.c)
	$(C) $(CFLAGS) -o wesm $(COMMONC_.o)

install:
# Windows style
ifeq ($(OS), Windows_NT)
# Replace for '\' directory separator of windows, '.\' current directory
	mkdir .$(subst /,\,$(INCLUDELOC))wellang
	mkdir .$(subst /,\,$(LOC))
	copy wesm.exe .$(subst /,\,$(LOC))
else
	sudo mkdir $(INCLUDELOC)wellang
	sudo cp wesm $(LOC)
endif

vim:
	mkdir -p ~/.vim/syntax
	mkdir -p ~/.vim/ftdetect
	cp vim/syntax/well.vim ~/.vim/syntax/
	cp vim/ftdetect/well.vim ~/.vim/ftdetect/
clean_vim:
	rm -f ~/.vim/syntax/well.vim
	rm -f ~/.vim/ftdetect/well.vim

clean:
ifeq ($(OS), Windows_NT)
	del /f $(COMMONC_.o)
	del /f .\wesm.exe
	rmdir /s /q .\$(USR)
else
	rm -f $(COMMONC_.o)
	sudo rm -R $(INCLUDELOC)wellang
	sudo rm -R $(LOC)wesm
endif

purge:
	rm -f $(COMMONC_.o)
	rm -f ~/.vim/syntax/well.vim
	rm -f ~/.vim/ftdetect/well.vim
	sudo rm -R $(INCLUDELOC)wellang
	sudo rm -R $(LOC)wesm
