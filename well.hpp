#ifndef WELL_H
#define WELL_H

#include <iostream>
#include <cstdlib>

#define __STACK_SIZE__ 3

class stack {
	int *array;
	int top;
	int cap;
public:
	stack(int size = __STACK_SIZE__);
	void deconstruct();
	void push(int);
	void plus();
<<<<<<< HEAD
	void min();
=======
>>>>>>> a2551dcbc71df74b153636aa57de659e9d5762c7
	void dump();
	int ret();
	int size();
	bool empty();
	bool full();
};

stack::stack(int size) {

		array = new int[size];
		cap = size;
		top = -1;

}

void stack::deconstruct() {

	delete[] array;

}

int stack::size() {

	return top + 1;

}

bool stack::empty() {
	
	return top == -1;

}

bool stack::full() {

	return top == cap - 1;

}

int stack::ret() {

	if(!empty()) {
		return array[top];
	} else {
		exit(EXIT_FAILURE);
	}

}

void stack::push(int num) {

	if (full()) {
		exit(EXIT_FAILURE);
	}

	array[top] = num;

}

void stack::plus() {

	int a = array[top];
	int b = array[top--];

	if(a + b < 100) {
		array[top] = a + b - 1;
	} else if(a + b > 100) {
		array[top] = a + b;
	}
}

<<<<<<< HEAD
void stack::min() {

	int a = array[top];
	int b = array[top--];
	
	std::cout << "Minus function is a W.I.P" << std::endl;

	if(a - b < 100) {
		array[top] = a - b - 1;
	} else if(b - a > 100) {
		array[top] = a - b;
	}
}

=======
>>>>>>> a2551dcbc71df74b153636aa57de659e9d5762c7
void stack::dump() {

	if(empty()) {
		exit(EXIT_FAILURE);
	}

	std::cout << stack::ret() << std::endl;
<<<<<<< HEAD
//	stack::deconstruct();
=======

>>>>>>> a2551dcbc71df74b153636aa57de659e9d5762c7
}

#endif
