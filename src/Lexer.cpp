#include <exception>
#include <stdexcept>
#include "Lexer.h"
#include "Token.h"
#include <cctype>




const std::unordered_map<std::string, TokenType> Lexer::tokenMap = {
    {"#", TokenType::Hash},
    {"=", TokenType::Assign},
    {"+", TokenType::Plus},
    {"-", TokenType::Minus},
    {"/", TokenType::Divide},
    {"*", TokenType::Multiply},
    {".", TokenType::Dot},
    {",", TokenType::Comma},
    {"<", TokenType::Less},
    {">", TokenType::Greater},
    {"(", TokenType::LeftParen},
    {")", TokenType::RightParen},
    {"[", TokenType::LeftBracket},
    {"]", TokenType::RightBracket},
    {"{", TokenType::LeftBrace},
    {"}", TokenType::RightBrace},
    {";", TokenType::Semicolon},
    {"\"", TokenType::Quote},
    {"\0", TokenType::EndOfFile}
};

bool Lexer::isSpace(char c)
{
    return c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' ||
           c == '\v';
}

bool Lexer::isNum(char c)
{
    return std::isdigit(static_cast<unsigned char>(c));
}

bool Lexer::isAlpha(char c)
{
    return std::isalpha(static_cast<unsigned char>(c));
}

bool Lexer::isOperator(char c)
{
    for (char op : Lexer::operators)
    {
        if (c == op)
        {
            return true;
        }
    }
    return false;
}


TokenType Lexer::determineTokenType(const std::string &lexeme){
    auto it = Lexer::tokenMap.find(lexeme);
    //std::cout << "determineTokenType: " << it->first << " " << tokenTypeToString(it->second) << std::endl;
    if (it != Lexer::tokenMap.end()){
        return it->second;
    }else{
        return TokenType::Unk;
    }
}

void Lexer::lex()
{
    bool eof_reached = false;
    while (!eof_reached)
    {
        Token t = getNextToken();
        tokens.push_back(t);
        if (t.type == TokenType::EndOfFile)
        {
            eof_reached = true;
        }
    }
}

std::vector<Token> Lexer::getTokens(){
    return tokens;
}

char Lexer::peekNextChar()
{
    return source->buffer[idx];
}

char Lexer::consumeChar()
{
    ++col;

    if (source->buffer[idx] == '\n')
    {
        ++line;
        col = 0;
    }
    return source->buffer[idx++];
}


std::string Lexer::returnBuffer(){
    return source->buffer;
}

Token Lexer::getNextToken()
{
    LexerState state = LexerState::START;
    std::string lexeme;

    int loop_count = 0;
    char currentChar;
    while (!(state == LexerState::DONE))
    {
        //char currentChar = consumeChar();
        //std::cout << "Current char: " << currentChar << "\n";
        loop_count += 1;
        //std::cout << "Outer state\n";

        if(idx == source->buffer.size()){
            state = LexerState::DONE;
        }
        switch (state)
        {
        case LexerState::START:
        {
            currentChar = consumeChar();
            //std::cout << "(START): currentChar: " << currentChar << "\n";
            //currentChar = peekNextChar();
            //std::cout << "(START) Current char: " << currentChar << "\n";
            // char is letter | number | opertor | space
            if (isSpace(currentChar))
            {
                continue;
            }
            else if (isNum(currentChar))
            {
                state = LexerState::IN_NUMBER;
            }
            else if (isAlpha(currentChar))
            {
                state = LexerState::IN_IDENTIFIER;
            }
            else if (isOperator(currentChar))
            {
                state = LexerState::IN_OPERATOR;
            }
            else
            {
                std::throw_with_nested(std::runtime_error("Invalid character encountered"));
            }
            break;
        }

        case LexerState::IN_IDENTIFIER:
        {
            //std::cout << "(IN_IDENTIFIER): currentChar: " << currentChar << "\n";
            lexeme += currentChar;
            char nextChar = peekNextChar();
            if(isAlpha(nextChar)){
                currentChar = consumeChar();
            }
            else if(isNum(nextChar)){
                currentChar = consumeChar();
            }
            else if(isOperator(nextChar)){
                SourceLocation sl{source->filepath, line, col};
                return Token(sl, TokenType::Identifier, lexeme);
            }
            else if (isSpace(nextChar)){
                SourceLocation sl{source->filepath, line, col};
                return Token(sl, TokenType::Identifier, lexeme);
            }
            break;
        }
        case LexerState::IN_NUMBER:
        {
            lexeme += currentChar;
            char nextChar = peekNextChar();
            if(isNum(nextChar)){
                currentChar = consumeChar();
            }
            else if(isAlpha(nextChar)){
                SourceLocation sl{source->filepath, line, col};
                return Token(sl, TokenType::Number, lexeme);
            }
            else if(isOperator(nextChar)){
                SourceLocation sl{source->filepath, line, col};
                return Token(sl, TokenType::Number, lexeme);
            }
            else if(isSpace(nextChar)){
                SourceLocation sl{source->filepath, line, col};
                return Token(sl, TokenType::Number, lexeme);
            }
            break;
        }
        case LexerState::IN_OPERATOR:
        {
            //std::cout << "(IN_OPERATOR): currentChar: " << currentChar << "\n";
            lexeme += currentChar;
            char nextChar = peekNextChar();
            SourceLocation sl{source->filepath, line, col};
            if (isAlpha(nextChar)){
                return Token(sl, determineTokenType(lexeme));
            }else if(isNum(nextChar)){
                // terminal state
                return Token(sl, determineTokenType(lexeme));
            }
            else if(isSpace(nextChar)){
                return Token(sl, determineTokenType(lexeme));
            }
            else if(isOperator(nextChar)){
                return Token(sl, determineTokenType(lexeme));
            }else{
                return Token(sl, TokenType::Unk);
            }
            break;
        }
        case LexerState::DONE:
        {
            SourceLocation sl{source->filepath, line, col};
            return Token(sl, TokenType::EndOfFile);
        }
        }
    }
}
