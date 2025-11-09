#ifndef PICO_PP_SYMBOL_TABLE_H
#define PICO_PP_SYMBOL_TABLE_H

#include <string>
#include <unordered_map>
#include <vector>

struct SymbolInfo {
    std::string name;
};

class SymbolTable {
public:
    void enterScope();
    void leaveScope();

    bool declare(const std::string &name);
    bool isDeclared(const std::string &name) const;

private:
    std::vector<std::unordered_map<std::string, SymbolInfo>> scopes;
};

#endif
