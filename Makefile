CC = g++
COMMON_.cpp = interp.cpp
COMMON_.o = interp.o
INCLUDE = well.hpp

INCLUDELOC = /usr/include/
LOC = /usr/bin/
NAME = well

.PHONY: base clean

.SUFFIXES: .cpp .o

base:
	$(CC) $(COMMON_.cpp) -o $(NAME)

install:
	sudo mkdir $(INCLUDELOC)wellang
	sudo cp well $(LOC)
	sudo cp $(INCLUDE) $(INCLUDELOC)wellang

clean:
	rm -f $(COMMON_.o)
	sudo rm -R $(INCLUDELOC)wellang
	sudo rm -R $(LOC)well
