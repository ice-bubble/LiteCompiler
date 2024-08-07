/**
 * @file lexer.cpp
 * @brief Lexer类及相关函数的实现。
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
#include "../token/token.h"
#include "../error/error.h"

namespace lexer {

    Lexer::Lexer(String source) {
        this->source = std::move(source);
    }


    List<token::Token> Lexer::scanTokens() {
        while (!isAtEnd()) {

            start = current;
            scanToken();
        }
        tokens.emplace_back(token::TOKEN_EOF, "", std::any{}, line);
        return tokens;
    }


    void Lexer::scanToken() {
        char c = advance();
        if (isDigit(c)) return number_();
        if (isAlpha(c))return _identifier();
        switch (c) {
            case '(':
                return addToken(token::TOKEN_LEFT_PAREN);
            case ')':
                return addToken(token::TOKEN_RIGHT_PAREN);
            case '[':
                return addToken(token::TOKEN_LEFT_BRACKET);
            case ']':
                return addToken(token::TOKEN_RIGHT_BRACKET);
            case '{':
                return addToken(token::TOKEN_LEFT_BRACE);
            case '}':
                return addToken(token::TOKEN_RIGHT_BRACE);
            case ',':
                return addToken(token::TOKEN_COMMA);
            case '.':
                if (isDigit(peek())) return real_();
                return addToken(token::TOKEN_DOT);
            case '-':
                if (match('-'))
                    return addToken(token::TOKEN_DOUBLE_MINUS);
                return addToken(token::TOKEN_MINUS);
            case '+':
                if (match('+'))
                    return addToken(token::TOKEN_DOUBLE_ADD);
                return addToken(token::TOKEN_PLUS);
            case '%':
                return addToken(token::TOKEN_MOD);
            case ';':
                return addToken(token::TOKEN_SEMICOLON);
            case '*':
                return addToken(token::TOKEN_STAR);
            case '#':
                while (peek() != '\n' && !isAtEnd()) advance();
                return;
            case '|':
                if (match('|')) return addToken(token::TOKEN_OR);
                break;
            case '&':
                if (match('&')) return addToken(token::TOKEN_AND);
                break;
            case '!':
                return addToken(match('=') ? token::TOKEN_NOT_EQUAL : token::TOKEN_NOT);
            case '=':
                return addToken(match('=') ? token::TOKEN_EQUAL_EQUAL : token::TOKEN_EQUAL);
            case '<':
                return addToken(match('=') ? token::TOKEN_LESS_EQUAL : token::TOKEN_LESS);
            case '>':
                return addToken(match('=') ? token::TOKEN_GREATER_EQUAL : token::TOKEN_GREATER);
            case '/':
                return slash();
            case '\'':
                return string_('\'');
            case '\"':
                return string_('\"');
            case '\n':
                line++;
            case ' ':
            case '\r':
            case '\t':
                return;
        }
        String unexpected_char(1, c);
        reportLexerError(this, line, "Unexpected character '" + unexpected_char + "'.");
    }

    void Lexer::_identifier() {
        // 一直消费字母和下划线，直到待消费的字符不是字母和下划线
        while (isAlphaNumeric(peek()) != '\0') advance();

        String text = source.substr(start, current - start);
        auto tokentype = token::Token::getKeywordTypeInMap(text);
        if (tokentype == token::TOKEN_EOF) {
            return addToken(token::TOKEN_IDENTIFIER);
        } else if (tokentype == token::TOKEN_TRUE) {
            return addToken(token::TOKEN_TRUE, String("true"));
        } else if (tokentype == token::TOKEN_FALSE) {
            return addToken(token::TOKEN_FALSE, String("false"));
        }
        addToken(tokentype);
    }

    void Lexer::real_() {
        // 一直消费数字，直到待消费的字符不是数字
        while (isDigit(peek())) advance();
        addToken(token::TOKEN_REAL_, std::stod(source.substr(start, current - start)));
    }

    void Lexer::number_() {
        // 一直消费数字，直到待消费的字符不是数字
        while (isDigit(peek())) advance();

        // 待消费的符号是"."，下一个待消费的符号是数字，说明是小数
        if (peek() == '.' && isDigit(peekNext())) {

            // 消费"."
            advance();

            // 一直消费数字，直到待消费的字符不是数字
            while (isDigit(peek())) advance();

            // 此时是小数
            addToken(token::TOKEN_REAL_, std::stod(source.substr(start, current - start)));
            return;
        }
        if (match('.')) {
            return addToken(token::TOKEN_REAL_,
                            (std::stod(source.substr(start, current - start))));
        }

        // 非小数，即整数
        addToken(token::TOKEN_INT_,
                 static_cast<long>(std::stod(source.substr(start, current - start))));
    }

    void Lexer::string_(char front) {
        while (peek() != front) {
            // 处理跨行字符串
            // 处理找不到闭合的 " 或 ' 的情况
            if (peek() == '\n' || isAtEnd()) return reportLexerError(this, line, "Unterminated string.");
            advance();
        }

        // 消费闭合的 " 或 '
        advance();

        // 截取子串时记得去掉开始和结尾的 " 或 '
        addToken(token::TOKEN_STRING_, source.substr(start + 1, current - start - 2));
    }

    void Lexer::slash() {
        //为未闭合注释记录下开始的行号
        size_t tmp_line = line;
        if (match('/')) {
            while (peek() != '\n' && !isAtEnd()) advance();
            return;
        }
        if (match('*')) {
            while (true) {
                // 多行注释未闭合
                if (isAtEnd()) return reportLexerError(this, tmp_line, "Unterminated comment.");
                char ch = advance();

                // 换行时记得把行号加一
                if (ch == '\n') line++;

                //注释结束
                if (ch == '*' && peek() == '/') {
                    // 消费"/"
                    advance();
                    break;
                }
            }
            return;
        }
        addToken(token::TOKEN_SLASH);
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

    void Lexer::addToken(token::TokenType type) {
        addToken(type, std::any{});
    }

    void Lexer::addToken(token::TokenType type, const Object &literal) {
        String lexeme = source.substr(start, current - start);
        tokens.emplace_back(type, lexeme, literal, line);
    }

}