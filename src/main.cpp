#include "Token.h"
#include "Lexer.h"
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char *argv[])
{
    std::ifstream input("/home/sean/Documents/Other/C/Compiler/example/example2.c");
    std::stringstream buffer;
    buffer << input.rdbuf();

    SourceFile sourcefile{"/home/sean/Documents/Other/C/Compiler/example/example2.c", buffer.str()};
    Lexer lexer(sourcefile);

    //printf("1st character: %c\n", lexer.peekNextChar());

    /*SourceLocation sl{"abc", 0, 0};
    Token t(sl, TokenType{'/'});
    std::cout << t << "\n";*/


    /*
    Token t = lexer.getNextToken();
    std::cout << t << "\n";

    for (int i = 0; i < 50; i++){
        std::cout << i << "\n";
        t = lexer.getNextToken();
        std::cout << t << "\n";
    }
    */

    lexer.lex();
    for(Token t : lexer.getTokens()){
        std::cout << t << "\n";
    }

    return 0;
}
