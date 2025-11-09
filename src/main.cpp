#include "ir_generator.h"
#include "ast.h"
#include <iostream>

using namespace std;

int main() {
    std::shared_ptr<ASTNode> dummyRoot = std::make_shared<ASTNode>();

    IRGenerator irgen;
    irgen.generate(dummyRoot);

    cout << "\n--- Generated LLVM IR ---\n";
    irgen.printIR();

    return 0;
}
