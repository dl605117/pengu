/*
Start Jan. 2024:
Developer: dl605117 (Darren)

Token Structure:
List of TokenTypes and Token struct for lexical analysis.
*/

#pragma once
#include <string>
#include <optional>

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