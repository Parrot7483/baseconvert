#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <gmpxx.h>
#include <fmt/core.h>
#include "BaseConvert.h"

namespace baseconvert {
    unsigned char get_char_from_alphabet(
        const std::unordered_map<unsigned char, unsigned char>& _alpha, 
        const char _c
    ) {
        if (const auto tmp = _alpha.find(_c); tmp != _alpha.end()) {
            return tmp->second;
        } else {
           throw UnknownCharacterException(_c);
        }
    }

    BaseConvert::BaseConvert(const std::string& _origin_alpha, const std::string& _target_alpha) {
        this->origin_alpha = {};
        for (unsigned char i = 0; const auto c: _origin_alpha) {
            if (! isprint(c))
                throw NonPrintableCharacterException(c);

            this->origin_alpha[c] = i;
            this->origin_alpha_reverse[i] = c;
            i++;
        }

        this->target_alpha = {};
        for (unsigned char i = 0; const auto c: _target_alpha) {
            if (! isprint(c))
                throw NonPrintableCharacterException(c);

            this->target_alpha[c] = i;
            this->target_alpha_reverse[i] = c;
            i++;
        }
    }

    std::string BaseConvert::encode(const std::vector<unsigned char>& _input) {
        mpz_class num {0}; 
        for (const auto c: _input){
            num *= this->origin_alpha.size();
            num += get_char_from_alphabet(this->origin_alpha, c);
        }

        std::string result {};
        const mpz_class target_alpha_size {target_alpha.size()};
        while (num) {
            mpz_class remainder;
            mpz_tdiv_qr(num.get_mpz_t(), 
                        remainder.get_mpz_t(), 
                        num.get_mpz_t(), 
                        target_alpha_size.get_mpz_t());
            result.push_back(this->target_alpha_reverse[remainder.get_ui()]);
        }

        std::reverse(result.begin(), result.end());
        return result;
    }

    std::vector<unsigned char> BaseConvert::decode(const std::string& _input) {
        mpz_class num {0}; 
        for (const auto c: _input){
            num *= this->target_alpha.size();
            num += get_char_from_alphabet(this->target_alpha, c);
        }

        std::vector<unsigned char> result {};
        const mpz_class origin_alpha_size {origin_alpha.size()};
        while (num) {
            mpz_class remainder;
            mpz_tdiv_qr(num.get_mpz_t(), 
                        remainder.get_mpz_t(), 
                        num.get_mpz_t(), 
                        origin_alpha_size.get_mpz_t());
            result.push_back(this->origin_alpha_reverse[remainder.get_ui()]);
        }

        std::reverse(result.begin(), result.end());
        return result;
    }

    
    // TODO: Replace with C++20 std::format when available in gcc
    UnknownCharacterException::UnknownCharacterException(const char c) 
        : msg(fmt::format("Found character \'{}\' in input but not input alphabet!", c))
    {}
    const char* UnknownCharacterException::what() const noexcept {
        return this->msg.c_str();
    }

    // TODO: Replace with C++20 std::format when available in gcc
    NonPrintableCharacterException::NonPrintableCharacterException(const char c) 
        : msg(fmt::format("Character \'0x{:02X}\' found in input alphabet is not printable", c))
    {}
    const char* NonPrintableCharacterException::what() const noexcept {
        return this->msg.c_str();
    }
}