#include "merrors.h"

#include <iostream>

std::fstream mErr::outfile;

void mErr::errors_init() {
	outfile.open("errors.txt", std::fstream::out);
	//outfile << "!!!" << std::endl;
}

std::ostream& mErr::oerr() {
	return std::cout;
}

void mErr::error_message(const std::string message) {
	outfile << message << std::endl;
}

void mErr::errors_quit() {
	outfile.close();
}

bool mErr::maccept(bool res, std::string message, bool& flag) {
	if (!res) {
		error_message(message);
		flag = false;
		return false;
	}
	return true;
}
