#ifndef _LexerH_
#define _LexerH_

#include "Token.h"
#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>

enum class LexerState{
  START,
  IN_IDENTIFIER,
  IN_NUMBER,
  IN_OPERATOR,
  DONE,
  ERROR,
};

struct SourceFile {
  std::string_view filepath;
  std::string buffer;
};

// Responsible for converting the textual representation
// into a list of tokens
// Should always complete without throwing any errors
// It is the job of the parser to validate the tokens, not the lexers
class Lexer {
  const SourceFile *source;
  size_t idx = 0;
  std::vector<Token> tokens; 

  int line = 1;
  int col = 0;

  // Map a operator to a TokenType
  static const std::unordered_map<std::string, TokenType> tokenMap;

public:
  //static constexpr char operators[] = {'=', '/', '+', '-', '*', '<', '>', ';', ':', '.', '#'};
  static constexpr char operators[] = {'\0', '+', '-', '#', '/', '=', '>', '<', '(', ')', '{', '}', '[', ']', '&', '*', ';', ':', '.', ','};

  std::string returnBuffer();

  Lexer(const SourceFile &source) : source(&source){};

  // Repeatidely call getNextToken till EOF reached
  void lex();

  std::vector<Token> getTokens();
  
  // Return the next token for the source file
  Token getNextToken();

  // Get the next char without moving the pointer forward
  char peekNextChar();

  // Return the next char in the buffer
  // advance the pointer forward 1 step
  char consumeChar();

  // Return the TokenType instance of a given lexeme 
  TokenType determineTokenType(const std::string&);

  bool isSpace(char);
  bool isAlpha(char);
  bool isNum(char);
  bool isOperator(char);
};

#endif // !_LexerH_
