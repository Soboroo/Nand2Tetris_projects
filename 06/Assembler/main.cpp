#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " <input file>" << std::endl;
		return 1;
	}
	else if (argc == 2) {
		std::ifstream input(argv[1]);
		if (!input.is_open()) {
			std::cout << "Error: could not open file '" << argv[1] << "'." << std::endl;
			return 1;
		}
		else {
			std::cout << "File '" << argv[1] << "' opened successfully." << std::endl;
			std::string line;
			while (std::getline(input, line)) {
				std::cout << line << std::endl;
			}
			input.close();
		}
		return 0;
	}
}