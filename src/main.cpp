#include "lexer.h"
#include "parser.h"
#include "semantic.h"
#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage: pico_pp_frontend <source-file>\n";
        return 1;
    }

    std::ifstream in(argv[1]);
    if (!in) {
        std::cerr << "Could not open file: " << argv[1] << "\n";
        return 1;
    }

    std::stringstream buffer;
    buffer << in.rdbuf();
    std::string source = buffer.str();

    // 1. Lexing
    Lexer lexer(source);
    auto tokens = lexer.tokenize();

    // 2. Parsing
    Parser parser(tokens);
    auto program = parser.parseProgram();
    if (!parser.getErrors().empty()) {
        std::cerr << "Parse errors:\n";
        for (auto &e : parser.getErrors()) {
            std::cerr << "  " << e << "\n";
        }
        return 1;
    }

    // 3. Semantic analysis
    SemanticAnalyzer sema;
    sema.analyze(*program);
    if (!sema.getErrors().empty()) {
        std::cerr << "Semantic errors:\n";
        for (auto &e : sema.getErrors()) {
            std::cerr << "  " << e << "\n";
        }
        return 1;
    }

    std::cout << "Pico++ frontend ran successfully (skeleton).\n";
    return 0;
}
