#include <fstream>
#include <iostream>
#include <sstream>
#include "Tokenizer.hpp"


int main(int argc, char* argv[]) {
	

	std::string contents;
	std::stringstream content_stream;
	std::ifstream file_stream("../penguTest.pu", std::ios::in);
	content_stream << file_stream.rdbuf();
	contents = content_stream.str();

	std::cout << "*** Start of Lexical Analysis ***" << std::endl;
	Tokenizer tokenizer(std::move(contents));
	auto tokens = tokenizer.tokenize();

	for ( auto token: tokens)
		std::cout << token.toString() << std::endl ;

	return 0;
}