#include "symbol_table.h"

void SymbolTable::enterScope() {
    scopes.emplace_back();
}

void SymbolTable::leaveScope() {
    if (!scopes.empty()) {
        scopes.pop_back();
    }
}

bool SymbolTable::declare(const std::string &name) {
    if (scopes.empty()) {
        scopes.emplace_back();
    }
    auto &currentScope = scopes.back();
    if (currentScope.find(name) != currentScope.end()) {
        return false;
    }
    currentScope[name] = SymbolInfo{name};
    return true;
}

bool SymbolTable::isDeclared(const std::string &name) const {
    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
        if (it->find(name) != it->end()) {
            return true;
        }
    }
    return false;
}
