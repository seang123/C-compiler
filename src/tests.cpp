#include <iostream>
#include <vector>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Lexer.h"

//using namespace Ops;
using std::cout;

TEST_CASE("Lexer character checking"){
    SourceFile sf{"test", "#include <iostream>\nint main(){}"};
    Lexer l(sf);
    CHECK(l.isAlpha('A') == true);
    CHECK(l.isAlpha('3') == false);
    CHECK(l.isNum('1') == true);
    CHECK(l.isNum('9') == true);
    CHECK(l.isNum('b') == false);
    CHECK(l.isOperator('#') == true);
    CHECK(l.isOperator('.') == true);
    CHECK(l.isOperator(';') == true);
    CHECK(l.isOperator('z') == false);
    CHECK(l.isOperator('4') == false);
}
