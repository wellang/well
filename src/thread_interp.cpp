#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <thread>

void thread_interp(std::ifstream file, std::ofstream output, int argc, char *argv[]) {

	std::string line;

	while(getline(file, line)) {
		
		if(line.find("thread:") != std::string::npos) {

			int32_t thread_num = 6;
			output << "void\n";
			while(thread_num != line.length()) {
				std::string THREAD_NAME = line;
				output << line;
				thread_num++;
			}

			break;

			
		}
		break;
	}
	
	file.close();

	std::string FNAME;

	FNAME = argv[1];

	std::string TLine;

	std::ifstream FIle(FNAME);

	while(getline(FIle, TLine)) {
	
		if(TLine.find("run:thread") != std::string::npos) {
			
			output << TLine;

		}

	}

}
