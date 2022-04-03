#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

void file() {

	std::cout << ":: Enter file name" << std::endl;
	
<<<<<<< HEAD
	char fname[128];
	scanf("%127s", fname);
=======
	char fname[80];
	scanf("%79s", fname);
>>>>>>> a2551dcbc71df74b153636aa57de659e9d5762c7

	std::string line;

	std::ifstream file(fname);

	std::ofstream output("a.cpp");
<<<<<<< HEAD
	output << "#include <wellang/well.hpp>\n";

	while(getline(file, line)) {
		int32_t FUNC_NUM = 0;

		if(line.find("func:main") != std::string::npos) {
			output << "int main() {\n";
			if(line.find("}") != std::string::npos) {
				output << "}\n";
			} else {
				output << "//" << line << "\n";
			}
		} else if(line.find("func:") != std::string::npos) {
			output << "void \n";
			int32_t num = 5;
			while(num != line.length()) {
				output << line[num];
				num++;
				
			}
			output << "\n";
                        if(line.find("}") != std::string::npos) {
                                output << "}\n";
                        } else {
                                output << "//" << line << "\n";
                        }
		} else {
			output << line << "\n";
		}
		FUNC_NUM++;

	}
	
	//output << "}\n";
=======
	output << "#include <wellang/well.hpp>\nint main() {";

	while(getline(file, line)) {
		output << line << "\n";
	}
	
	output << "}\n";
>>>>>>> a2551dcbc71df74b153636aa57de659e9d5762c7

	file.close();
	output.close();

}

void comp() {

	system("g++ a.cpp -o a.o");
<<<<<<< HEAD
	//system("rm -f a.cpp");
=======
	system("rm -f a.cpp");
>>>>>>> a2551dcbc71df74b153636aa57de659e9d5762c7
	std::cout << "done compiling program" << std::endl;

}

int main() {

	file();
	comp();
	return 0;

}
