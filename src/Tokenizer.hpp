#pragma once
#include <string>
#include <vector>
#include <optional>
#include <iostream>
#include <format>

enum class TokenType {
    return_ident, 
    int_lit,
    string_lit,
    ident,
    int_ident,
    string_ident,
    semi
};

struct Token {
    TokenType type;
    int line;
    std::optional<std::string> value {};
    std::string toString(){
        if (type == TokenType::return_ident)
            return "return_ident";
        else if (type == TokenType::semi)
            return "semi";
        else if (type == TokenType::int_lit)
            return "int_lit";
        return "";
    }
};

class Tokenizer {
public:
    explicit Tokenizer(std::string src) : file_src_(std::move(src)) {
    }

    std::vector<Token> tokenize() {
        int line_num = 1;
        std::vector<Token> tokens;
        std::string word_buf;
        while (peek().has_value()) {
            word_buf.clear();
            if (std::isalpha(peek().value())) {  // Starts with alpha
                while (peek().has_value() && std::isalnum(peek().value())) {
                    word_buf += consume();
                }
                if (word_buf == "return")
                    tokens.push_back({TokenType::return_ident, line_num});
                else {
                    std::cerr << "[Lexical Ananlysis Error] Invalid AlphaNumeric token on line " << line_num << " {" << word_buf << "}" << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
            else if (std::isdigit(peek().value())) {
                while (peek().has_value() && std::isdigit(peek().value()))
                    if (std::isdigit(peek().value()))
                        word_buf += consume();
                    else {
                        std::cerr << "[Lexical Analysis Error] Invalid Digit token on line " << line_num << " {" << word_buf <<"}" << std::endl;
                    }
                tokens.push_back({TokenType::int_lit, line_num, word_buf});
            }
            else if (peek().value() == ';'){
                consume();
                tokens.push_back({TokenType::semi, line_num});
            }
            else if (std::isspace(peek().value()))
                consume();
            else {
                while (peek().has_value())
                    word_buf += consume();
                std::cerr << "[Lexical Analysis Error] Token invalid {" << word_buf <<"}" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        return tokens;
    }
    
private:
    std::optional<char> peek(const size_t offset = 0) const {
        if (index + offset < file_src_.length())
            return file_src_.at(index + offset);
        return {};
    }

    char consume() {
        if (index < file_src_.length())
            return file_src_.at(index++);
        std::cerr << "consumed past EOF" << std::endl;
        exit(EOF);
    }

    const std::string file_src_;
    size_t index = 0;
};