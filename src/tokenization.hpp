#pragma once

#include <iostream>
#include <optional>
#include <string>
#include <vector>

enum class TokenType {
    exit,
    int_lit,
    semi,
};

struct Token {
    TokenType type;
    std::optional<std::string> value {};
};

class Tokenizer {
public:
    inline explicit Tokenizer(std::string src)
        : m_src(std::move(src))
    {
    }

    inline std::vector<Token> tokenize()
    {
        std::vector<Token> tokens;
        std::string buf;

        while (peek().has_value()) {
            if (std::isalpha(peek().value())) {
                buf.push_back(consume());
                while (peek().has_value() && std::isalnum(peek().value())) {
                    buf.push_back(consume());
                }
                if (buf == "exit") {
                    tokens.push_back({ .type = TokenType::exit });
                    buf.clear();
                }
                else {
                    std::cerr << "You messed up! `exit`" << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
            else if (std::isdigit(peek().value())) {
                buf.push_back(consume());
                while (peek().has_value() && std::isdigit(peek().value())) {
                    buf.push_back(consume());
                }
                tokens.push_back({ .type = TokenType::int_lit, .value = buf });
                buf.clear();
            }
            else if (peek().value() == ';') {
                consume();
                tokens.push_back({ .type = TokenType::semi });
            }
            else if (std::isspace(peek().value())) {
                consume();
            }
            else {
                std::cerr << "You messed up! `else`" << std::endl;
                exit(EXIT_FAILURE);
            }
        }

        m_index = 0;

        return tokens;
    }

private:
    const std::string m_src;
    size_t m_index = 0;

    [[nodiscard]] inline std::optional<char> peek(int offset = 0) const
    {
        if (m_index + offset >= m_src.length()) {
            return {};
        }
        else {
            return m_src.at(m_index + offset);
        }
    }

    inline char consume()
    {
        char c = m_src.at(m_index);
        m_index++;

        return c;
    }
};

/*
    inline std::vector<Token> tokenize_old()
    {
        std::vector<Token> tokens;
        std::string buf;

        size_t len = m_src.length();

        for (size_t i = 0; i < len; i++) {
            char c = m_src.at(i);
            if (std::isalpha(c)) {
                buf.push_back(c);
                i++;

                while (std::isalnum(m_src.at(i))) {
                    buf.push_back(m_src.at(i));
                    i++;
                }
                i--;

                if (buf == "exit") {
                    tokens.push_back({ .type = TokenType::exit });
                    buf.clear();
                    continue;
                }
                else {
                    std::cerr << "You messed up!" << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
            else if (std::isdigit(c)) {
                buf.push_back(c);
                i++;

                while (std::isdigit(m_src.at(i))) {
                    buf.push_back(m_src.at(i));
                    i++;
                }
                i--;

                tokens.push_back({ .type = TokenType::int_lit, .value = buf });
                buf.clear();
            }
            else if (c == ';') {
                tokens.push_back({ .type = TokenType::semi });
            }
            else if (std::isspace(c)) {
                continue;
            }
        }

        return tokens;
    }
*/
