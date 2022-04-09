#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

int interp_sim(int argc, char *argv[]) {

	
	std::string fname;
	
	if(argv[1] == NULL) {
		
		std::cout << "\n:: Invalid file name, ex: well (.well file) -o well.o\n\n";
		return 0;
	
	} 

	fname = argv[1];

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

			} else if(line.find("while:") != std::string::npos) {
				
				output << "while";

				int32_t WHILENUM = 6;

				while(WHILENUM != line.length()) {
					output << line[WHILENUM];
					WHILENUM++;
				}

				output << "\n";
				if(line.find("}") != std::string::npos) {
					output << "}\n";
				}

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
			} else if(line.find("while:") != std::string::npos) {
				
				output << "while";

				int32_t WHILENUM = 6;

				while(WHILENUM != line.length()) {
					output << line[WHILENUM];
					WHILENUM++;
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
		} else if(line.find("while:") != std::string::npos) {
			output << "while";
			int32_t WNUM = 6;
			while(WNUM != line.length()) {
				output << line[WNUM];
				WNUM++;
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

	return 0;

}

void comp(int argc, char *argv[]) {

	const char *gpp = "g++ a.cpp -o";
	char buf[0x100];

	std::string arg = "-o";
	const char *OUTPUT_NAME;

	if(argv[2] == arg) {
		OUTPUT_NAME = argv[3];
		snprintf(buf, sizeof(buf), "g++ a.cpp -o %s", OUTPUT_NAME);
		system(buf);
		std::cout << "done compiling programn\n" << argv[3] << std::endl;
	} else {
		system("g++ a.cpp -o a.o");
		//system("rm -f a.cpp");
		std::cout << "done compiling program" << argv[2] << std::endl;
	}

}

int main(int argc, char *argv[]) {

	interp_sim(argc, argv);
	comp(argc, argv);
	return 0;

}
