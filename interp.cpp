#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

void interp_sim() {

	std::cout << ":: Enter file name" << std::endl;

	char fname[128];
	scanf("%127s", fname);

	std::string line;

	std::ifstream file(fname);

	std::ofstream output("a.cpp");
	output << "#include <wellang/well.hpp>\n";

	while(getline(file, line)) {
		int32_t FUNC_NUM = 0;

		if(line.find("func:main") != std::string::npos) {
			output << "int main() {\n";
			if(line.find("}") != std::string::npos) {
				output << "}\n";
			} else if() {
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
                        } else if(line.find("if:") != std::string::npos) {
                        	output << "if";
                         
	                        int32_t IFNUM = 3;
                         
        	                while(IFNUM != line.length()) {
                	                 output << line[IFNUM];
                        	         IFNUM++;
                        	}
                         	output << "\n";
                         	if(line.find("}") != std::string::npos) {
                                 	output << "}\n";
                         	}
			} else {
				output << "//" << line << "\n";
                        }
		} else if(line.find("if:") != std::string::npos) {
			output << "if";
			
			int32_t IFNUM = 3;
			
			while(IFNUM != line.length()) {
				output << line[IFNUM];
				IFNUM++;
			}
			output << "\n";
			if(line.find("}") != std::string::npos) {
				output << "}\n";
			}
		} else {
			output << line << "\n";
		}
		FUNC_NUM++;

	}
	
	//output << "}\n";

	file.close();
	output.close();

}

void comp() {

	system("g++ a.cpp -o a.o");
	//system("rm -f a.cpp");
	std::cout << "done compiling program" << std::endl;

}

int main() {

	interp_sim();
	comp();
	return 0;

}
