CC = gcc
CFLAGS = -std=c89 -g
COMMON_.c = src/asm_interp.c \
	src/mov_search.c \
	src/syscall_interp.c \
	src/push_search.c \
	src/types.c \
	src/instructions.c \
	src/log.c \
	src/array_interp.c \
	src/asm_macros.c \
	src/include.c \
	src/lea.c \
	src/math.c \
	src/asm_interp_funcs.c \
	src/if.c \
	src/libwesm/com.c \
	src/libwesm/log_parse.c \
	src/argparse/argparse.c \
	src/argparse/extract.c \
	src/argparse/ap_inter.c
COMMONC_.o = asm_interp.o \
	mov_search.o \
	syscall_interp.o \
	push_search.o \
	types.o \
	instructions.o \
	log.o \
	array_interp.o \
	asm_macros.o \
	include.o \
	lea.o \
	math.o \
	asm_interp_funcs.o \
	if.o \
	com.o \
	log_parse.o \
	argparse.o \
	extract.o \
	ap_inter.o
USR = usr
CONFIG = .~
LOCAL = /$(CONFIG)/.config/wellang/
INCLUDELOC = /$(USR)/include/
LOC = /$(USR)/bin/

LIBWESM= src/libwesm

.PHONY: base install vim clean_vim clean purge

.SUFFIXES: .c .o

all: base

base:
	$(CC) $(CFLAGS) -L src -c $(COMMON_.c)
	$(CC) $(CFLAGS) -o wesm $(COMMONC_.o)

install:
# Windows style
ifeq ($(OS), Windows_NT)
# Replace for '\' directory separator of windows, '.\' current directory
	mkdir .$(subst /,\,$(INCLUDELOC))wellang
	mkdir .$(subst /,\,$(LOC))
	mkdir .$(subst /,\,$(LOCAL))logs
	mkdir C:\wesm\libwesm
	copy $(subst /,\,$(LIBWESM)) C:\wesm\libwesm
	copy wesm.exe .$(subst /,\,$(LOC))
else
	sudo mkdir $(INCLUDELOC)wellang
	@ # mkdir $(LOCAL)logs
	sudo cp -r $(LIBWESM) $(INCLUDELOC)wellang
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
#	del /f .\wesm.exe
	rmdir /s /q .\$(USR)
	rmdir /s /q .\$(CONFIG)
	rmdir /s /q C:\wesm
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
