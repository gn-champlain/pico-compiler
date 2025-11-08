#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "lexer.h"
#include "parser.h"
#include "codegen.h"

#include <llvm/IR/Module.h>          // ✅ Add this line
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/raw_ostream.h>



// Read entire file into a string
static std::string readAll(const std::string& path) {
    std::ifstream in(path);
    if (!in) {
        throw std::runtime_error("Cannot open input file: " + path);
    }
    std::ostringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: pico <input.pico> <output.ll>\n";
        return 1;
    }

    std::string inPath = argv[1];
    std::string outPath = argv[2];

    std::string text;
    try {
        text = readAll(inPath);
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << "\n";
        return 1;
    }

    Lexer lex(text);
    Parser parser(lex);
    Program prog;

    if (!parser.parseProgram(prog)) {
        std::cerr << "Parsing failed\n";
        return 2;
    }

    CodeGen cg("pico_module");
    auto mod = cg.emit(prog);

    std::error_code ec;
    llvm::raw_fd_ostream os(outPath, ec, llvm::sys::fs::OF_Text);
    if (ec) {
        std::cerr << "Cannot open output file: " << ec.message() << "\n";
        return 3;
    }
    mod->print(os, nullptr);

    std::cout << "Wrote IR to " << outPath << "\n";
    return 0;
}
