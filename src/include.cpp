#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

void __include_interp(std::ifstream file, std::ofstream output, std::string line) {

	
	getline(file, line);

	if(line.find("include:") != std::string::npos) {

		if(line.find("<") != std::string::npos && line.find(".well") != std::string::npos) {

			output << "\n#include<";
			int32_t InNum = 8;

			while(InNum != line.length()) {

				output << line;
				InNum ++;

			}
		
		} else if(line.find("'") != std::string::npos && line.find(".well") != std::string::npos) {
			std::cout << "ERROR:: personal includes are a W.I.P\n";
			exit(EXIT_FAILURE);
		} else {
		
			std::cout << "ERROR:: Invalid header/include...\n" << "\nError at: " << line << "\n";
			exit(EXIT_FAILURE);

		}
	
	}	


}
