CC = g++
COMMON_.cpp = src/interp.cpp src/include.cpp src/thread_interp.cpp
COMMON_.o = interp.o include.o thread_interp.o
INCLUDE = src/well.hpp

INCLUDELOC = /usr/include/
LOC = /usr/bin/
NAME = well

COMMON_LIB = printf.well
COMMON_LIB_.cpp = printf.hpp

.PHONY: base clean

.SUFFIXES: .cpp .o

base:
	$(CC) -L src -c $(COMMON_.cpp)
	$(CC) -o $(NAME) $(COMMON_.o)

install:
	sudo mkdir $(INCLUDELOC)wellang
	sudo cp well $(LOC)
	sudo cp $(INCLUDE) $(INCLUDELOC)wellang
	cd lib
	well printf.well -E printf.hpp && sudo cp printf.hpp $(INCLUDELOC)


clean:
	rm -f $(COMMON_.o)
	sudo rm -R $(INCLUDELOC)wellang
	sudo rm -R $(LOC)well
