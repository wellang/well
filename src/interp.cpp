#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "thread_interp.hpp"
#include "include.hpp"

int interp_sim(int argc, char *argv[]) {

	
	std::string fname;
	
	if(argv[1] == NULL) {
		
		std::cout << "\n:: Invalid file name, ex: well (.well file) -o well.o\n\n";
		return 0;
	
	} 

	fname = argv[1];

	std::string line;

	std::ifstream file(fname);
        
	//std::string N_EXC = "-E";
	
	std::ofstream output("a.cpp");

	/*if(argv[2] == N_EXC) {
		char buf[0x100];
		const char *OUTPUT_NAME = argv[3];
        	snprintf(buf, sizeof(buf), "%s", OUTPUT_NAME);
		std::ofstream output(buf);
	} else {
		std::ofstream output("a.cpp");
	}*/

	output << "#include <wellang/well.hpp>\n";

	while(getline(file, line)) {
		
		/*if(line.find("include:") != std::string::npos) {

            		if(line.find("<") != std::string::npos && line.find(".well") != std::string::npos) {

                        	output << "\n#include<";
                        	int32_t InNum = 8;

                        	while(InNum != line.length()) {

                                	output << line;
                                	InNum ++;

                        	}
			} else {
			
				std::cout << "\nInclude ERROR at line: \n\e[4;35m" << line << "\e[0m\n\n";

			}
		}*/
		//__include_interp(file2, output, line);
		
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
		} else if(line.find("v:func:") != std::string::npos) {
			output << "void \n";
			int32_t num = 7;
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
		} else if(line.find("r:func:") != std::string::npos) {
			output << "int \n";
			int32_t Num = 7;
			while(Num != line.length()) {
				output << line[Num];
				Num++;
			}
			output << "\n";

			if(line.find("}") != std::string::npos) {
				output << "}";
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
		//} else if(line.find("thread:")) {
		//	thread_interp(file, output, argc, argv);
		} else if(line.find("for:") != std::string::npos) {
			output << "for";
			int32_t FOR_NUM = 4;

			while(FOR_NUM != line.length()) {
				output << line[FOR_NUM];
				FOR_NUM++;
			}
			output << "\n";
			if(line.find("}") != std::string::npos) {
				output << "}\n";
			}
		} else if(line.find("switch:") != std::string::npos) {
			output << "switch";
			int32_t SNUM = 7;

			while(SNUM != line.length()) {
				output << line[SNUM];
				SNUM++;
			}
			output << "\n";
			if(line.find("}") != std::string::npos) {
				output << "}\n";
			}
	
		} else if(line.find("do: {") != std::string::npos) {
			output << "do {";
			output << "//" << line;
			if(line.find("} while:") != std::string::npos) {
				output << "}while";
				int32_t DWNUM = 8;
				while(DWNUM != line.length()) {
					output << line[DWNUM];
					DWNUM++;
				}
			}
		} else if(line.find("define:") != std::string::npos) {
			output << "#define ";
			int32_t DEFNUM = 7;

			while(DEFNUM != line.length()) {
				output << line[DEFNUM];
				DEFNUM++;
			}
			output << "\n";
		} else if(line.find("include:") != std::string::npos) {
			
			output << "\n#include";
			output << "/*" << line << "*/";
			int32_t INNUM = 8;
			while(INNUM != line.length()) {
				output << line[INNUM];
				INNUM++;
			}
			output << "\n";
			

            		/*if(line.find("<") != std::string::npos && line.find(".well") != std::string::npos) {

                        	output << "\n#include<";
                        	int32_t InNum = 8;

                        	while(InNum != line.length()) {

                                	output << line;
                                	InNum ++;

                        	}
			} */ /*else {
			
				std::cout << "\nInclude ERROR at line: \n\e[4;35m" << line << "\e[0m\n\n";

			}*/
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

	std::string N_EXC = "-E";

        if(argv[1] == NULL) {

                std::cout << "\n:: Invalid file name, ex: well (.well file) -o well.o\n\n";
                return 0;

        } else if(argv[2] == N_EXC) {
		interp_sim(argc, argv);
		const char *OUTNAME = argv[3];
		char buf[0x100];
		snprintf(buf, sizeof(buf), "cp a.cpp %s", OUTNAME);
		system(buf);
		return 0;
	}

	interp_sim(argc, argv);
	comp(argc, argv);
	return 0;

}

