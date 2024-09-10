CC = gcc
CFLAGS = -std=c89 -g -L include/SQLite3
COMMON_.c := src/*.c \
	include/SQLite3/sqlite3.c

COMMONC_.o := *.o 

USR = usr
CONFIG = .~
LOCAL = /$(CONFIG)/.config/wellang/
INCLUDELOC = /$(USR)/include/
LOC = /$(USR)/bin/
LOC_WIN = C:/wesm

LIBWESM= src/libwesm

PREFIX_OSX = /Library/Developer/CommandLineTools/usr/include/wellang
INCLUDELOC_OSX = $(PREFIX_OSX)/include
LOC_OSX = $(PREFIX_OSX)/bin

UNAME = $(shell uname)

.PHONY: base install vim clean_vim clean purge

.SUFFIXES: .c .o

all: base

base:
	$(CC) $(CFLAGS) -L src -c $(COMMON_.c)
	$(CC) $(CFLAGS) -o wesm $(COMMONC_.o)

base-arm:
	$(CC) $(CFLAGS) -ldl -L src -c $(patsubst %include/SQLite3/sqlite3.c,%,$(COMMON_.c)) -lsqlite3
	$(CC) $(CFLAGS) -ldl -o wesm $(patsubst %sqlite3.o,%,$(COMMONC_.o)) -lsqlite3

install-win:
	mkdir $(subst /,\,$(LOC_WIN))\libwesm
	mkdir $(subst /,\,$(LOC_WIN))\DB
	mkdir $(subst /,\,$(LOC_WIN))\bin
	copy $(subst /,\,$(LIBWESM)) $(subst /,\,$(LOC_WIN))\libwesm
	copy src\DB\welldb.db C:\wesm\DB
	copy wesm.exe $(subst /,\,$(LOC_WIN))\bin

install-osx:
	sudo mkdir $(PREFIX_OSX)
	sudo mkdir $(INCLUDELOC_OSX)
	sudo mkdir $(LOC_OSX)
	sudo cp -r $(LIBWESM) $(INCLUDELOC_OSX)
	sudo cp wesm $(LOC_OSX)

install-unix:
	sudo mkdir $(INCLUDELOC)wellang
	@ # mkdir $(LOCAL)logs
	sudo cp -r $(LIBWESM) $(INCLUDELOC)wellang
	sudo cp wesm $(LOC)

vim:
	mkdir -p ~/.vim/syntax
	mkdir -p ~/.vim/ftdetect
	cp vim/syntax/well.vim ~/.vim/syntax/
	cp vim/ftdetect/well.vim ~/.vim/ftdetect/
clean_vim:
	rm -f ~/.vim/syntax/well.vim
	rm -f ~/.vim/ftdetect/well.vim

clean-win:
	del /f $(COMMONC_.o)
#	del /f .\wesm.exe
#	rmdir /s /q .\$(USR)
#	rmdir /s /q .\$(CONFIG)
	rmdir /s /q $(subst /,\,$(LOC_WIN))

clean-osx:
		rm -f $(COMMONC_.o)
		sudo rm -R $(PREFIX_OSX)

clean-unix:
	rm -f $(COMMONC_.o)
	sudo rm -R $(INCLUDELOC)wellang
	sudo rm -R $(LOC)wesm

clean-all-unix:
	rm -f $(COMMONC_.o)
	rm -f ~/.vim/syntax/well.vim
	rm -f ~/.vim/ftdetect/well.vim
	sudo rm -R $(INCLUDELOC)wellang
	sudo rm -R $(LOC)wesm
