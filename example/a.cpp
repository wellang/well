#include <wellang/well.hpp>
int main() {
//r:func:main() {

	char text[] = "test\n";

asm volatile(/*	ASM:("mov $1, %%rax\n\t"*/"mov $1, %%rax\n\t"
		"mov $1, %%rdi\n\t"
		"mov %0, %%rsi\n\t"
		"mov $5, %%rdx\n\t"
		"int $0x80\n\t"
		"mov $60, %%rax\n\t"
		"mov $0, %%rdi\n\t"
		"int $0x80\n\t" :: "m"(*text));
	
	return 0;
}
