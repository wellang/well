CC = g++
COMMON_.cpp = src/interp.cpp src/thread_interp.cpp
COMMON_.o = interp.o thread_interp.o
INCLUDE = src/well.hpp

INCLUDELOC = /usr/include/
LOC = /usr/bin/
NAME = well

.PHONY: base clean

.SUFFIXES: .cpp .o

base:
	$(CC) -L src -c $(COMMON_.cpp)
	$(CC) -o $(NAME) $(COMMON_.o)

install:
	sudo mkdir $(INCLUDELOC)wellang
	sudo cp well $(LOC)
	sudo cp $(INCLUDE) $(INCLUDELOC)wellang

clean:
	rm -f $(COMMON_.o)
	sudo rm -R $(INCLUDELOC)wellang
	sudo rm -R $(LOC)well
