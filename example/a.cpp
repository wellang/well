#include <wellang/well.hpp>
void 
test() {
//func:test() {
	stack program(4);

	program.push(34);
	program.push(35);
	program.plus();
	program.dump();
}

int main() {
//func:main() {

	test();

}
