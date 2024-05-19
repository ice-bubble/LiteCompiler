/**
 * @file token.cpp
 * @brief Token类及相关函数的实现。
 * @date 24-4-22
 */

#include "token.h"

/**
 * @brief 命名空间，包含了关于Token定义的类和函数。
 */
namespace token {

    Map<String, TokenType> Token::keywords = {
            {"and",      TOKEN_AND},        /**< "and" 关键字对应的标记类型。 */
            {"bool",     TOKEN_BOOL},       /**< "bool" 关键字对应的标记类型。 */
            {"break",    TOKEN_BREAK},      /**< "break" 关键字对应的标记类型。 */
            {"char",     TOKEN_CHAR},       /**< "char" 关键字对应的标记类型。 */
            {"class",    TOKEN_CLASS},      /**< "class" 关键字对应的标记类型。 */
            {"continue", TOKEN_CONTINUE},   /**< "continue" 关键字对应的标记类型。 */
            {"do",       TOKEN_DO},         /**< "do" 关键字对应的标记类型。 */
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
            {"read",     TOKEN_READ},       /**< "read" 关键字对应的标记类型。 */
            {"repeat",   TOKEN_REPEAT},     /**< "repeat" 关键字对应的标记类型。 */
            {"return",   TOKEN_RETURN},     /**< "return" 关键字对应的标记类型。 */
            {"string",   TOKEN_STRING},     /**< "string" 关键字对应的标记类型。 */
            {"super",    TOKEN_SUPER},      /**< "super" 关键字对应的标记类型。 */
            {"this",     TOKEN_THIS},       /**< "this" 关键字对应的标记类型。 */
            {"true",     TOKEN_TRUE},       /**< "true" 关键字对应的标记类型。 */
            {"until",    TOKEN_UNTIL},      /**< "until" 关键字对应的标记类型。 */
            {"var",      TOKEN_VAR},        /**< "var" 关键字对应的标记类型。 */
            {"while",    TOKEN_WHILE},      /**< "while" 关键字对应的标记类型。 */
            {"write",    TOKEN_WRITE}       /**< "return" 关键字对应的标记类型。 */
    };

    List<String> Token::tokenStrings = {
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
            "DOUBLE_ADD",
            "DOUBLE_MINUS",

            "NOT_EQUAL",
            "EQUAL",
            "EQUAL_EQUAL",
            "GREATER",
            "GREATER_EQUAL",
            "LESS",
            "LESS_EQUAL",

            "IDENTIFIER",
            "STRING_",
            "INT_",
            "REAL_",
            "BOOL_",

            "AND",
            "BOOL",
            "BREAK",
            "CHAR",
            "CLASS",
            "CONTINUE",
            "DO",
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
            "READ",
            "REPEAT",
            "RETURN",
            "STRING",
            "SUPER",
            "THIS",
            "TRUE",
            "UNTIL",
            "VAR",
            "WHILE",
            "WRITE",

            "EOF"
    };


    Token::Token(TokenType type, String lexeme, std::any literal, size_t line)
            : type{type}, lexeme{std::move(lexeme)}, literal{std::move(literal)}, line{line} {}


    String Token::toString() const {
        return "line:" + std::to_string(line) + " < " + tokenStrings[type] +
               " " + lexeme + " " + getLiteralString() + " >";
    }

    String Token::getLiteralString() const {
        switch (type) {
            case (TOKEN_STRING_):
            case (TOKEN_BOOL_):
                return std::any_cast<String>(literal);
            case (TOKEN_REAL_):
                return std::to_string(std::any_cast<double>(literal));
            case (TOKEN_INT_):
                return std::to_string(std::any_cast<long>(literal));
            default:
                return "nil";
        }
    }

    TokenType Token::getKeywordTypeInMap(const String &text) {
        auto it = keywords.find(text);
        if (it == keywords.end()) {
            return TOKEN_EOF;
        }
        return it->second;
    }

    String Token::gettokenStringInMap(TokenType tokentype) {
        if (tokentype > TOKEN_EOF)
            return String{"Error: Invalid token type"};
        return tokenStrings[tokentype];
    }

    TokenType Token::getType() const {
        return type;
    }

    const String &Token::getLexeme() const {
        return lexeme;
    }

    size_t Token::getLine() const {
        return line;
    }

    void Token::printKeywords() {
        for (const auto &it: keywords) {
            std::cout << "KEYWORD " << it.first << std::endl;
        }
    }

}