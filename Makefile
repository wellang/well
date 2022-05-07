CC = g++
C = gcc
COMMON_.cpp = src/interp.cpp src/include.cpp src/thread_interp.cpp
COMMON_.c = src/asm_interp.c src/mov_search.c src/syscall_interp.c src/push_search.c src/types.c
COMMONC++_.o = interp.o include.o thread_interp.o
COMMONC_.o = asm_interp.o mov_search.o syscall_interp.o push_search.o types.o
COMMON_.hpp = printf.hpp
INCLUDE = src/well.hpp

INCLUDELOC = /usr/include/
LOC = /usr/bin/
NAME = well

COMMON_LIB = printf.well
COMMON_LIB_.cpp = printf.hpp

.PHONY: base install clean

.SUFFIXES: .cpp .c .o

base:
	$(CC) -L src -c $(COMMON_.cpp)
	$(CC) -o $(NAME) $(COMMONC++_.o)
	$(C) -L src -c $(COMMON_.c)
	$(C) -o wesm $(COMMONC_.o)

install:
	sudo mkdir $(INCLUDELOC)wellang
	sudo cp well $(LOC)
	sudo cp wesm $(LOC)
	sudo cp $(INCLUDE) $(INCLUDELOC)wellang
	cd lib
	well sizeof.well -E sizeof.well && sudo cp sizeof.well $(INCLUDELOC)wellang


clean:
	rm -f $(COMMONC_.o)
	rm -f $(COMMONC++_.o)
	rm -f $(COMMON_.hpp)
	sudo rm -R $(INCLUDELOC)wellang
	sudo rm -R $(LOC)well
