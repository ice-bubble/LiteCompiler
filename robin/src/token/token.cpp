/**
 * @file token.cpp
 * @brief Token类及相关函数的实现。
 * @author lzy
 * @date 24-4-22
 */

#include "token.h"

/**
 * @brief 命名空间，包含了关于Token定义的类和函数。
 */
namespace Token {

    std::map<std::string, TokenType> Token::keywords = {
            {"and",      TOKEN_AND},        /**< "and" 关键字对应的标记类型。 */
            {"break",    TOKEN_BREAK},      /**< "break" 关键字对应的标记类型。 */
            {"class",   TOKEN_CLASS},      /**< "class" 关键字对应的标记类型。 */
            {"continue", TOKEN_CONTINUE},   /**< "continue" 关键字对应的标记类型。 */
            {"double",   TOKEN_DOUBLE},     /**< "double" 关键字对应的标记类型。 */
            {"else",     TOKEN_ELSE},       /**< "else" 关键字对应的标记类型。 */
            {"false",    TOKEN_FALSE},      /**< "false" 关键字对应的标记类型。 */
            {"for",      TOKEN_FOR},        /**< "for" 关键字对应的标记类型。 */
            {"function", TOKEN_FUNCTION},   /**< "function" 关键字对应的标记类型。 */
            {"if",       TOKEN_IF},         /**< "if" 关键字对应的标记类型。 */
            {"integer",  TOKEN_INTEGER},    /**< "integer" 关键字对应的标记类型。 */
            {"nil",      TOKEN_NIL},        /**< "nil" 关键字对应的标记类型。 */
            {"not",      TOKEN_NOT},        /**< "not" 关键字对应的标记类型。 */
            {"or",       TOKEN_OR},         /**< "or" 关键字对应的标记类型。 */
            {"print",    TOKEN_PRINT},      /**< "print" 关键字对应的标记类型。 */
            {"return",   TOKEN_RETURN},     /**< "return" 关键字对应的标记类型。 */
            {"super",    TOKEN_SUPER},      /**< "super" 关键字对应的标记类型。 */
            {"this",     TOKEN_THIS},       /**< "this" 关键字对应的标记类型。 */
            {"true",     TOKEN_TRUE},       /**< "true" 关键字对应的标记类型。 */
            {"var",      TOKEN_VAR},        /**< "var" 关键字对应的标记类型。 */
            {"while",    TOKEN_WHILE}       /**< "while" 关键字对应的标记类型。 */
    };

    std::vector<std::string> Token::tokenStrings = {
            "LEFT_PAREN",
            "RIGHT_PAREN",
            "LEFT_BRACE",
            "RIGHT_BRACE",
            "LEFT_BRACKET",
            "RIGHT_BRACKET",
            "COMMA",
            "DOT",
            "MINUS",
            "PLUS",
            "SEMICOLON",
            "SLASH",
            "STAR",
            "MOD",

            "NOT_EQUAL",
            "EQUAL",
            "EQUAL_EQUAL",
            "GREATER",
            "GREATER_EQUAL",
            "LESS",
            "LESS_EQUAL",

            "IDENTIFIER",
            "STRING",
            "INT",
            "REAL",

            "AND",
            "BREAK",
            "CLASS",
            "CONTINUE",
            "DOUBLE",
            "ELSE",
            "FALSE",
            "FOR",
            "FUNCTION",
            "IF",
            "INTEGER",
            "NIL",
            "NOT",
            "OR",
            "PRINT",
            "RETURN",
            "SUPER",
            "THIS",
            "TRUE",
            "VAR",
            "WHILE",

            "EOF"
    };


    Token::Token(TokenType type, std::string lexeme, std::any literal, size_t line)
            : type{type}, lexeme{std::move(lexeme)}, literal{std::move(literal)}, line{line} {}


    std::string Token::toString() const {
        return "line:" + std::to_string(line) + " < " + tokenStrings[type] + " " + lexeme + " "
        + getLiteralString() +" >";
    }

    std::string Token::getLiteralString() const {
        switch (type) {
            case (TOKEN_STRING):
                return std::any_cast<std::string>(literal);
            case (TOKEN_REAL):
                return std::to_string(std::any_cast<double>(literal));
            case (TOKEN_INT):
                return std::to_string(std::any_cast<long>(literal));
            case (TOKEN_TRUE):
                return "true";
            case (TOKEN_FALSE):
                return "false";
            default:
                return "nil";
        }
    }

    TokenType Token::getKeywordTypeInMap(const std::string& text){
        auto it = keywords.find(text);
        if (it == keywords.end()) {
            return TOKEN_EOF;
        }
        return it->second;
    }

    std::string Token::gettokenStringInMap(TokenType tokentype) {
        if (tokentype > TOKEN_EOF)
            return std::string{"Error: Invalid token type"};
        return tokenStrings[tokentype];
    }

}