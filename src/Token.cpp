#include "Token.h"

std::string tokenTypeToString(TokenType type) {
    switch(type){
        case TokenType::IntegerLiteral: return "Int litearl";
        case TokenType::FloatLiteral: return "Float literal";
        case TokenType::CharLiteral: return "Char literal";
        case TokenType::EndOfFile: return "EOF";
        case TokenType::Identifier: return "Identifier";
        case TokenType::KwVoid: return "KwVoid";
        case TokenType::KwInt: return "KwInt";
        case TokenType::KwFloat: return "KwFloat";
        case TokenType::KwChar: return "KwChar";
        case TokenType::If: return "KwIf";
        case TokenType::Else: return "KwElse";
        case TokenType::For: return "KwFor";
        case TokenType::While: return "KwWhile";
        case TokenType::Return: return "KwReturn";
        case TokenType::Dereference: return "Dereference";
        case TokenType::Plus: return "+";
        case TokenType::Minus: return "-";
        case TokenType::Multiply: return "*";
        case TokenType::Divide: return "/";
        case TokenType::Assign: return "=";
        case TokenType::Less: return "<";
        case TokenType::Greater: return ">";
        case TokenType::Hash: return "#";
        case TokenType::Equal: return "==";
        case TokenType::GreaterEqual: return ">=";
        case TokenType::LessEqual: return "<=";
        case TokenType::LeftParen: return "(";
        case TokenType::RightParen: return ")";
        case TokenType::LeftBrace: return "{";
        case TokenType::RightBrace: return "}";
        case TokenType::LeftBracket: return "[";
        case TokenType::RightBracket: return "]";
        case TokenType::Semicolon: return ";";
        case TokenType::Colon: return ":";
        case TokenType::Dot: return ".";
        case TokenType::Comma: return ",";
        case TokenType::Quote: return "\"";
        case TokenType::Number: return "Number";
        case TokenType::Unk: return "UNK";
        default: return "No matching token";
    }
}
