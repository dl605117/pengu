/*
Start Jan. 2024:
Developer: dl605117 (Darren)

Parser (Front-end):
Semantic analysis of Pengu compiler. Translates vector of tokens to AST tree for
code generation. Contains grammar as followedin ___.md
*/

#pragma once
#include "tokenizer.hpp"
#include "../structures/nodeAST.hpp"

class Parser{
public:
    explicit Parser (std::vector<Token> tokens) : tokens_(std::move(tokens)) {}
    std::optional<NodeReturn> parse() {
        std::optional<NodeReturn> node_return;
        while (peek().has_value()) {
            if (peek().value().type == TokenType::return_ident) {
                consume();
                if (auto node_expr = parseExpr()) {
                    node_return = NodeReturn {node_expr.value()};
                }
                consume();
            }
        }
        return node_return;
    }
    
    std::optional<NodeExpr> parseExpr() {
        if (peek().has_value() && peek().value().type == TokenType::int_lit) {
            return NodeExpr {consume()};
        }
        return {};
    }
private:
    std::optional<Token> peek(const size_t offset = 0) const {
        if (index + offset < tokens_.size()) {
            return tokens_.at(index);
        }
        return {};
    }
    
    Token consume() {
        return tokens_.at(index++);
    }

    std::vector<Token> tokens_;
    size_t index = 0;
};