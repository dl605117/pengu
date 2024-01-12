/*
Start Jan. 2024:
Developer: dl605117 (Darren)

Pengu hobby language built with LLVM, tested on x86 infrastructure.
Introductory compiler for AI/ML applications.
*/

#include <fstream>
#include <iostream>
#include <sstream>
#include "src/compiler/tokenizer.hpp"
#include "src/compiler/parser.hpp"
#include "src/compiler/generator.hpp"


int main(int argc, char* argv[]) {
	/* 	
		Ingest .pu File
	*/
	std::string contents;
	std::stringstream content_stream;
	std::ifstream file_read_stream("penguTest.pu", std::ios::in);
	content_stream << file_read_stream.rdbuf();
	contents = content_stream.str();
	file_read_stream.close();

	/*
		Perform Lexical Analysis 
			Input: std::string
			Output: std::vector<Tokens> 
	*/
	std::cout << "*** Start of Lexical Analysis (Tokenizer) ***" << std::endl;
	Tokenizer tokenizer(std::move(contents));
	auto tokens = tokenizer.tokenize();
	for (auto token: tokens)
		std::cout << token.toString() << std::endl;

	/*
		Perform Sematic Analysis
			Input: std::vector<Tokens>
			Output: NodeReturn
	*/
	std::cout << "*** Start of Semantic Anylsis (Parser) ***" << std::endl;
	Parser parser(std::move(tokens));
	auto ast_root = parser.parse();

	/*
		Perform IR Generation ie. ASM
			Input: NodeReturn
			Output: std::string
	*/
	std::cout << "*** Start of IR (Generator) ***" << std::endl;
	Generator generator(std::move(ast_root.value()));
	auto raw_ir = generator.generate();
	std::cout << raw_ir << std::endl;

	/*
		Output ASM/IR to File
	*/
	std::fstream file_write_stream("penguTest.asm", std::ios::out);
	file_write_stream << raw_ir;
	file_write_stream.close();

	std::cout << "Compiled Successfully" << std::endl;

	//system("nasm -felf64 ../penguTest.asm");
	//system("ld -o penguTest penguTest.o");

	return 0;
}