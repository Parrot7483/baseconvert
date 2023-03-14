#pragma once
#include <unordered_map>
#include <vector>
#include <string>

#include "Alphabet.h"

// TODO(parrot)(Parrot): Add option for leading zeros
// Add support for constexpr

// using input_data = std::variant<std::vector<unsigned char>,std::vector<std::byte>>;

namespace baseconvert {

using alphabet = std::unordered_map<unsigned char, unsigned char>;

class BaseConvert {
        alphabet origin_alpha;
        alphabet origin_alpha_reverse;
        alphabet target_alpha;
        alphabet target_alpha_reverse;
    public: 
        /**
         * TODO(parrot)
         */
        explicit BaseConvert(const std::string& _origin_alpha, const std::string& _target_alpha);

        /**
         * TODO(parrot)
         */
        explicit BaseConvert(const std::string& _target_alpha);

        /**
         * TODO(parrot)
         */
        auto encode(const std::vector<unsigned char>& _input) -> std::string;

        /**
         * TODO(parrot)
         */
        auto decode(const std::string& _input) -> std::vector<unsigned char>;
};

auto encode(const std::vector<std::byte>& _input, const Alphabet<char, unsigned char>& _target) -> std::string;
// auto encode(const std::vector<unsigned char>& _input, const Alphabet& _origin, const Alphabet& _target) -> std::string;
// auto decode(const std::string& _input, const Alphabet& _origin) -> std::vector<unsigned char>;
// auto decode(const std::string& _input, const Alphabet& _origin, const Alphabet& _target) -> std::vector<unsigned char>;

/**
 * TODO(parrot)
 */
class UnknownCharacterException : public std::exception {
	const std::string msg;
	public:
        explicit UnknownCharacterException(char character);
        const char* what() const noexcept override; //NOLINT
};

/**
 * TODO(parrot)
 */
class NonPrintableCharacterException : public std::exception {
	const std::string msg;
	public:
        explicit NonPrintableCharacterException(char character);
        const char* what() const noexcept override; //NOLINT
};

/**
 * TODO(parrot)
 */
class DuplicateCharacterException : public std::exception {
	const std::string msg;
	public:
        explicit DuplicateCharacterException(char character);
        const char* what() const noexcept override; //NOLINT
};
}
