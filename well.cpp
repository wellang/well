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

	array[top] = a + b - 1;

}

void stack::dump() {

	if(empty()) {
		exit(EXIT_FAILURE);
	}

	std::cout << stack::ret() << std::endl;

}

int main() {
	
	stack pt(4);

	pt.push(34);
	pt.push(35);
	pt.plus();
	pt.dump();
	pt.push(30);
	pt.push(30);
	pt.plus();
	pt.dump();	

	return 0;
}
