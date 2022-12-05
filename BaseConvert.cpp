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

    void generate_standard_alphabets(
        std::unordered_map<unsigned char, unsigned char>& _alpha, 
        std::unordered_map<unsigned char, unsigned char>& _alpha_reverse
    ) {
        for (int i = 0; i < 256; i++) {
            _alpha[i] = i;
            _alpha_reverse[i] = i;
        }
    }

    void generate_alphabets(
        std::unordered_map<unsigned char, unsigned char>& _alpha, 
        std::unordered_map<unsigned char, unsigned char>& _alpha_reverse,
        const std::string& _input
    ) {
        for (unsigned char i = 0; const auto c: _input) {
            if (! isprint(c))
                throw NonPrintableCharacterException(c);
            else if (_alpha.contains(c))
                throw DuplicateCharacterException(c);

            _alpha[c] = i;
            _alpha_reverse[i] = c;
            i++;
        }
    }

    std::vector<unsigned char> convert(
        std::unordered_map<unsigned char, unsigned char>& _input_alpha, 
        std::unordered_map<unsigned char, unsigned char>& _output_alpha_reverse,
        const std::vector<unsigned char>& _input
    ) {
        mpz_class num {0}; 
        for (const auto c: _input){
            num *= _input_alpha.size();
            num += get_char_from_alphabet(_input_alpha, c);
        }

        std::vector<unsigned char> result {};
        const mpz_class output_alpha_size {_output_alpha_reverse.size()};
        while (num) {
            mpz_class remainder;
            mpz_tdiv_qr(num.get_mpz_t(), 
                        remainder.get_mpz_t(), 
                        num.get_mpz_t(), 
                        output_alpha_size.get_mpz_t());
            result.push_back(_output_alpha_reverse[remainder.get_ui()]);
        }

        std::reverse(result.begin(), result.end());
        return result;

    }

    BaseConvert::BaseConvert(const std::string& _origin_alpha, const std::string& _target_alpha) {
        generate_alphabets(this->origin_alpha, this->origin_alpha_reverse, _origin_alpha);
        generate_alphabets(this->target_alpha, this->target_alpha_reverse, _target_alpha);
    }

    BaseConvert::BaseConvert(const std::string& _target_alpha) {
        generate_standard_alphabets(this->origin_alpha, this->origin_alpha_reverse);
        generate_alphabets(this->target_alpha, this->target_alpha_reverse, _target_alpha);
    }

    std::string BaseConvert::encode(const std::vector<unsigned char>& _input) {
        std::vector<unsigned char> result = convert(this->origin_alpha, this->target_alpha_reverse, _input);
        return std::string(result.begin(), result.end());
    }

    std::vector<unsigned char> BaseConvert::decode(const std::string& _input) {
        std::vector<unsigned char> input(_input.begin(), _input.end());
        return convert(this->target_alpha, this->origin_alpha_reverse, input);
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
        : msg(fmt::format("Character \'0x{:02X}\' found in input alphabet is not printable!", c))
    {}
    const char* NonPrintableCharacterException::what() const noexcept {
        return this->msg.c_str();
    }

    // TODO: Replace with C++20 std::format when available in gcc
    DuplicateCharacterException::DuplicateCharacterException(const char c) 
        : msg(fmt::format("Character \'0x{:02X}\' found multiple times in input alphabet!", c))
    {}
    const char* DuplicateCharacterException::what() const noexcept {
        return this->msg.c_str();
    }
}