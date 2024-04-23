/**
 * @file lexer.cpp
 * @brief Lexer类及相关函数的实现。
 * @author lzy
 * @date 24-4-22
 *
 * @note current指向待消费的字符。
 * @note 消费字符：让current+1。
 * @note peek()返回待消费的字符，但是不消费它。
 * @note peekNext()返回待消费的字符的下一个字符，不消费任何字符。
 * @note advance()返回待消费的字符，同时让current+1，即消费了字符。
 * @note match(ch)当待消费的字符为ch时，消费这个字符返回true,否则不消费字符返回false。
 *
 */

#include "lexer.h"

#include <utility>
#include "../error/error.h"

namespace Lexer {

    /**
     * @brief 关键字到标记类型的映射表。
     */
    std::map<std::string, Token::TokenType> Lexer::keywords = {
            {"and",      Token::TOKEN_AND},        /**< "and" 关键字对应的标记类型。 */
            {"break",    Token::TOKEN_BREAK},      /**< "break" 关键字对应的标记类型。 */
            {"class",    Token::TOKEN_CLASS},      /**< "class" 关键字对应的标记类型。 */
            {"continue", Token::TOKEN_CONTINUE},   /**< "continue" 关键字对应的标记类型。 */
            {"double",   Token::TOKEN_DOUBLE},     /**< "double" 关键字对应的标记类型。 */
            {"else",     Token::TOKEN_ELSE},       /**< "else" 关键字对应的标记类型。 */
            {"false",    Token::TOKEN_FALSE},      /**< "false" 关键字对应的标记类型。 */
            {"for",      Token::TOKEN_FOR},        /**< "for" 关键字对应的标记类型。 */
            {"function", Token::TOKEN_FUNCTION},   /**< "function" 关键字对应的标记类型。 */
            {"if",       Token::TOKEN_IF},         /**< "if" 关键字对应的标记类型。 */
            {"integer",  Token::TOKEN_INTEGER},    /**< "integer" 关键字对应的标记类型。 */
            {"nil",      Token::TOKEN_NIL},        /**< "nil" 关键字对应的标记类型。 */
            {"not",      Token::TOKEN_NOT},        /**< "not" 关键字对应的标记类型。 */
            {"or",       Token::TOKEN_OR},         /**< "or" 关键字对应的标记类型。 */
            {"print",    Token::TOKEN_PRINT},      /**< "print" 关键字对应的标记类型。 */
            {"return",   Token::TOKEN_RETURN},     /**< "return" 关键字对应的标记类型。 */
            {"super",    Token::TOKEN_SUPER},      /**< "super" 关键字对应的标记类型。 */
            {"this",     Token::TOKEN_THIS},       /**< "this" 关键字对应的标记类型。 */
            {"true",     Token::TOKEN_TRUE},       /**< "true" 关键字对应的标记类型。 */
            {"var",      Token::TOKEN_VAR},        /**< "var" 关键字对应的标记类型。 */
            {"while",    Token::TOKEN_WHILE}       /**< "while" 关键字对应的标记类型。 */
    };

    Lexer::Lexer(std::string source) {
        this->source = std::move(source);
    }

    std::vector<Token::Token> Lexer::scanTokens() {
        while (!isAtEnd()) {

            start = current;
            scanToken();
        }
        tokens.emplace_back(Token::TOKEN_EOF, "", std::any{}, line);
        return tokens;
    }


    void Lexer::scanToken() {
        char c = advance();
        if (isDigit(c)) return _number();
        if (isAlpha(c))return _identifier();
        switch (c) {
            case '(':
                return addToken(Token::TOKEN_LEFT_PAREN);
            case ')':
                return addToken(Token::TOKEN_RIGHT_PAREN);
            case '[':
                return addToken(Token::TOKEN_LEFT_BRACKET);
            case ']':
                return addToken(Token::TOKEN_RIGHT_BRACKET);
            case '{':
                return addToken(Token::TOKEN_LEFT_BRACE);
            case '}':
                return addToken(Token::TOKEN_RIGHT_BRACE);
            case ',':
                return addToken(Token::TOKEN_COMMA);
            case '.':
                if (isDigit(peek())) return _real();
                return addToken(Token::TOKEN_DOT);
            case '-':
                return addToken(Token::TOKEN_MINUS);
            case '+':
                return addToken(Token::TOKEN_PLUS);
            case '%':
                return addToken(Token::TOKEN_MOD);
            case ';':
                return addToken(Token::TOKEN_SEMICOLON);
            case '*':
                return addToken(Token::TOKEN_STAR);
            case '#':
                while (peek() != '\n' && !isAtEnd()) advance();
                break;
            case '|':
                if (match('|')) return addToken(Token::TOKEN_OR);
                break;
            case '&':
                if (match('&')) return addToken(Token::TOKEN_AND);
                break;
            case '!':
                return addToken(match('=') ? Token::TOKEN_NOT_EQUAL : Token::TOKEN_NOT);
            case '=':
                return addToken(match('=') ? Token::TOKEN_EQUAL_EQUAL : Token::TOKEN_EQUAL);
            case '<':
                return addToken(match('=') ? Token::TOKEN_LESS_EQUAL : Token::TOKEN_LESS);
            case '>':
                return addToken(match('=') ? Token::TOKEN_GREATER_EQUAL : Token::TOKEN_GREATER);
            case '/':
                return slash();
            case '"':
                return _string();
            case '\n':
                line++;
                return;
            case ' ':
            case '\r':
            case '\t':
                return;
        }
        std::string UnexpectedChar(1, c);
        error(line, "Unexpected character '" + UnexpectedChar + "'.");
    }

    void Lexer::_identifier() {
        // 一直消费字母和下划线，直到待消费的字符不是字母和下划线
        while (isAlphaNumeric(peek())) advance();

        std::string text = source.substr(start, current - start);
        auto it = keywords.find(text);
        if (it == keywords.end()) {
            addToken(Token::TOKEN_IDENTIFIER);
            return;
        }
        addToken(it->second);
    }

    void Lexer::_real() {
        // 一直消费数字，直到待消费的字符不是数字
        while (isDigit(peek())) advance();
        addToken(Token::TOKEN_REAL, std::stod(source.substr(start, current - start)));
    }

    void Lexer::_number() {
        // 一直消费数字，直到待消费的字符不是数字
        while (isDigit(peek())) advance();

        // 待消费的符号是"."，下一个待消费的符号是数字，说明是小数
        if (peek() == '.' && isDigit(peekNext())) {

            // 消费"."
            advance();

            // 一直消费数字，直到待消费的字符不是数字
            while (isDigit(peek())) advance();

            // 此时是小数
            addToken(Token::TOKEN_REAL, std::stod(source.substr(start, current - start)));
            return;
        }
       // 非小数，即整数
        addToken(Token::TOKEN_INT,
                 static_cast<long>(std::stod(source.substr(start, current - start))));
    }

    void Lexer::_string() {
        while (peek() != '"' && !isAtEnd()) {
            if (peek() == '\n') line++;
            advance();
        }

        // 处理找不到闭合的 " 的情况
        if (isAtEnd()) {
            error(line, "Unterminated string.");
            return;
        }

        // 消费闭合的 "
        advance();

        // 截取子串时记得去掉开始和结尾的"
        addToken(Token::TOKEN_STRING, source.substr(start + 1, current - start - 2));
    }

    void Lexer::slash() {
        if (match('/')) {
            // 单行注释
            while (peek() != '\n' && !isAtEnd()) advance();
        } else if (match('*')) {
            // 多行注释
            while (true) {
                // 多行注释未闭合
                if (isAtEnd()) {
                    error(line, "Unterminated comment.");
                    return;
                }
                char Ch = advance();

                // 换行时记得把行号加一
                if (Ch == '\n')
                    line++;

                if (Ch == '*' && peek() == '/') {
                    // 消费"/"
                    advance();
                    break;
                }
            }
        } else {
            // 是除号的情况
            addToken(Token::TOKEN_SLASH);
        }
    }

    bool Lexer::match(char expected) {
        if (isAtEnd()) return false;
        if (source[current] != expected) return false;

        current++;
        return true;
    }

    char Lexer::peek() {
        if (isAtEnd()) return '\0';
        return source[current];
    }

    char Lexer::peekNext() {
        if (current + 1 >= source.length()) return '\0';
        return source[current + 1];
    }

    bool Lexer::isAlpha(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
    }

    bool Lexer::isAlphaNumeric(char c) {
        return isAlpha(c) || isDigit(c);
    }

    bool Lexer::isDigit(char c) {
        return c >= '0' && c <= '9';
    }

    bool Lexer::isAtEnd() {
        return current >= source.length();
    }

    char Lexer::advance() {
        current++;
        return source[current - 1];
    }

    void Lexer::addToken(Token::TokenType type) {
        addToken(type, std::any{});
    }

    void Lexer::addToken(Token::TokenType type, const Object &literal) {
        std::string lexeme = source.substr(start, current - start);
        tokens.emplace_back(type, lexeme, literal, line);
    }

}