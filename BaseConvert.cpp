#include "BaseConvert.h"

#include <fmt/core.h>
#include <gmpxx.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

// TODO(Parrot): Return this-> (not recommendet in general)

namespace baseconvert {
    auto generate_standard_alphabets() -> std::tuple<alphabet, alphabet> {
        alphabet alpha {};
        alphabet alpha_reverse {};

        for (int i = 0; i < 256; i++) {
            alpha[i] = i;
            alpha_reverse[i] = i;
        }

        return {alpha, alpha_reverse};
    }

    auto generate_alphabets(const std::string& _input) -> std::tuple<alphabet, alphabet> {
        alphabet alpha {};
        alphabet alpha_reverse {};

        for (unsigned char i = 0; const auto c: _input) {
            if (0 == isprint(c)) {
                throw NonPrintableCharacterException(c);
	    } 

	    if (alpha.contains(c)) {
                throw DuplicateCharacterException(c);
	    }

            alpha[c] = i;
            alpha_reverse[i] = c;
            i++;
        }

        return {alpha, alpha_reverse};
    }

    // TODO(Parrot): Use template for input and output data type
    // TODO(Parrot): Make use of string_view
    auto convert(
        alphabet& _input_alpha, 
        alphabet& _output_alpha_reverse,
        const std::vector<unsigned char>& _input
    ) -> std::vector<unsigned char> {
        mpz_class num {0}; 
        const auto input_alpha_size {_input_alpha.size()}; 
        for (const auto c: _input){
            num *= input_alpha_size;
	    // TODO(Parrot): Create own alphabet container that throws at std::out_of_range
            try {
                num += _input_alpha.at(c);
            } catch(const std::out_of_range&) {
                throw UnknownCharacterException(static_cast<char>(c));
            }
        }

	// TOOD: Size of output is known. Create Buffer. Fill from end to front. No reverse needed!
        std::vector<unsigned char> result {};
        const mpz_class output_alpha_size {_output_alpha_reverse.size()};
        while (num) {
	    // TODO(Parrot): Create wrapper around mpz_tdiv_qr that returns remainder.get_ui() and only takes num once. Uses int as input and output.
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
        std::tie(this->origin_alpha, this->origin_alpha_reverse) = generate_alphabets(_origin_alpha);
        std::tie(this->target_alpha, this->target_alpha_reverse) = generate_alphabets(_target_alpha);
    }

    BaseConvert::BaseConvert(const std::string& _target_alpha) {
        std::tie(this->origin_alpha, this->origin_alpha_reverse) = generate_standard_alphabets();
        std::tie(this->target_alpha, this->target_alpha_reverse) = generate_alphabets(_target_alpha);
    }

    auto BaseConvert::encode(const std::vector<unsigned char>& _input) -> std::string {
        std::vector<unsigned char> result = convert(this->origin_alpha, this->target_alpha_reverse, _input);
        return {result.begin(), result.end()};
    }

    auto BaseConvert::decode(const std::string& _input) -> std::vector<unsigned char> {
        std::vector<unsigned char> input{_input.begin(), _input.end()};
        return convert(this->target_alpha, this->origin_alpha_reverse, input);
    }

    // TODO(Parrot): Replace with C++20 std::format when available in gcc
    UnknownCharacterException::UnknownCharacterException(const char character) : msg{
	fmt::format("Found character \'0x{:02X}\' in input but not in input alphabet!", character)
    } {};
    const char* UnknownCharacterException::what() const noexcept { //NOLINT
        return msg.c_str();
    }

    // TODO(Parrot): Replace with C++20 std::format when available in gcc
    NonPrintableCharacterException::NonPrintableCharacterException(const char character) : msg{
	fmt::format("Character \'0x{:02X}\' found in alphabet is not printable!", character)
    } {};
    const char* NonPrintableCharacterException::what() const noexcept { // NOLINT
	return msg.c_str();
    }

    // TODO(Parrot): Replace with C++20 std::format when available in gcc
    DuplicateCharacterException::DuplicateCharacterException(const char character) : msg{
	fmt::format("Character \'0x{:02X}\' found multiple times in alphabet!", character)
    } {};
    const char* DuplicateCharacterException::what() const noexcept { // NOLINT
	return msg.c_str();
    }
} // namespace baseconvert
