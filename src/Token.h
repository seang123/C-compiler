#ifndef  _TokenH_
#define _TokenH_

#include <iostream>
#include <ostream>
#include <string>
#include <optional>
#include <variant>


// Single character tokens
const char singleCharTokens[] = {'\0', '+', '-', '/', '=', '>', '<', '(', ')', '{', '}', '[', ']', '&', '*', ';', ':'};


enum class TokenType : char {
  Identifier,
  KwVoid,
  KwInt, // Keyword (eg. function return type)
  KwFloat,
  KwChar,
  If,
  Else,
  For,
  While,
  Return,
  Dereference,
  Plus,
  Minus,
  Multiply,
  Divide, 
  Assign,
  Less,
  Greater,
  LeftAngle, // <
  RightAngle, // >
  Hash,
  Equal,
  GreaterEqual,
  LessEqual,
  LeftParen,
  RightParen,
  LeftBrace,
  RightBrace,
  LeftBracket,
  RightBracket,
  Semicolon,
  Colon,
  Comma,
  Quote,
  Dot,
  Number,
  IntegerLiteral, // actual number 
  FloatLiteral,
  CharLiteral,
  EndOfFile,
  Unk = -128, // Unknown token
};

std::string tokenTypeToString(TokenType t);

// Hold information about the source 
// of a token - useful if we compile
// multiple files
struct SourceLocation{
  std::string_view filepath;
  int line;
  int col;
};



// Token class
// Every token is some minimal meaningful element
class Token{
public:
  SourceLocation source;
  TokenType type;
  std::optional<std::string> lexeme = std::nullopt; // actual text of the token
  std::variant<int, float, char, std::string> literal;  // the literal value of the lexeme

  Token(SourceLocation &src) : source(src), type(TokenType::EndOfFile){}

  Token(SourceLocation& src, TokenType t)
        : source(src), type(t), lexeme(std::nullopt) {}

  Token(SourceLocation& src, TokenType t, const std::string &lex) : source(src), type(t), lexeme(lex) {}

  template<typename T>
  Token(SourceLocation& src, TokenType t, const std::string& lex, T lit)
      : source(src), type(t), lexeme(lex), literal(lit) {}

  friend std::ostream& operator<<(std::ostream& os, Token const & token) {
      //return os << "Token: " << static_cast<char>(token.type) << std::endl;
      os << "Token: " << tokenTypeToString(token.type);
      if(token.lexeme){
        os << " : " << *token.lexeme;
      }
      return os;
  }
};



#endif // ! _TokenH_

