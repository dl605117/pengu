/*
Start Jan. 2024:
Developer: dl605117 (Darren)

AST Node Structure:
List of AST node types for semantic analysis.
*/

#include "tokens.hpp"

struct NodeExpr {
    Token int_lit;
};

struct NodeReturn {
    NodeExpr expr;
};