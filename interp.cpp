#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

void file() {

	std::cout << ":: Enter file name" << std::endl;
	
	char fname[80];
	scanf("%79s", fname);

	std::string line;

	std::ifstream file(fname);

	std::ofstream output("a.cpp");
	output << "#include <wellang/well.hpp>\nint main() {";

	while(getline(file, line)) {
		output << line << "\n";
	}
	
	output << "}\n";

	file.close();
	output.close();

}

void comp() {

	system("g++ a.cpp -o a.o");
	system("rm -f a.cpp");
	std::cout << "done compiling program" << std::endl;

}

int main() {

	file();
	comp();
	return 0;

}
