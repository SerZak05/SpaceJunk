#pragma once
#include <fstream>

class mErr {
public:
	static void errors_init();

	static std::ostream& oerr();

	static void error_message(const std::string message);

	static void errors_quit();

	static bool maccept(bool res, std::string message, bool& flag);
private:
	static std::fstream outfile;
};