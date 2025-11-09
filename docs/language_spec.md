# Pico++ Language Specification (Draft)

Pico++ is a small teaching language that extends the Week 1 Pico example.

## Keywords

let, if, else, while, print

## Basic Grammar (informal)

Program     -> { Statement }

Statement   -> VarDecl | AssignStmt | IfStmt | WhileStmt | PrintStmt | Block

VarDecl     -> "let" Identifier "=" Expression ";"
AssignStmt  -> Identifier "=" Expression ";"
IfStmt      -> "if" "(" Expression ")" Statement [ "else" Statement ]
WhileStmt   -> "while" "(" Expression ")" Statement
PrintStmt   -> "print" Expression ";"
Block       -> "{" { Statement } "}"

Expression  -> ... (arithmetic and comparison expressions)
