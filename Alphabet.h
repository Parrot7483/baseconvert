#pragma once
#include <fmt/core.h>
#include <initializer_list>
#include <string>
#include <unordered_map>
#include <tuple>
#include <vector>

#include "Exceptions.h"

namespace baseconvert {

template <typename T, typename S>
class Alphabet {
public:
	virtual auto forward(const T character) const -> S = 0;
	virtual auto reverse(const S character) const -> T = 0;
	virtual auto size() const -> int = 0;
};

class DefaultAlphabet: public Alphabet<unsigned char, unsigned char> {
public:
	auto forward(const unsigned char character) const -> unsigned char override {
		return character;
	}

	auto reverse(const unsigned char character) const -> unsigned char override {
		return character;
	}

	auto size() const -> int {
		return 256;
	}
};

// TODO(Parrot): Make second template variable dependend on the size of string/initializer_list
template <typename T>
class CustomAlphabet: public Alphabet<T, unsigned char> {
	const std::unordered_map<T, unsigned char> _forward;
	const std::unordered_map<unsigned char, T> _reverse;

	// TODO: Simplify this code reuse
	template <typename InputIterator>
	static auto transform1(InputIterator begin, InputIterator end) {
		std::unordered_map<T, unsigned char> result {};

		for (auto i = 0; begin != end; begin++) {
            if (0 == isprint(*begin)) {
                throw NonPrintableCharacterException(*begin);
			} 

			if (result.contains(*begin)) {
                throw DuplicateCharacterException(*begin);
			}

			result[*begin] = i++;
		}

		return result;
	}

	template <typename InputIterator>
	static auto transform2(InputIterator begin, InputIterator end) {
		std::unordered_map<unsigned char, T> result {};

		for (auto i = 0; begin != end; begin++) {
            if (0 == isprint(*begin)) {
                throw NonPrintableCharacterException(*begin);
			} 

			if (result.contains(*begin)) {
                throw DuplicateCharacterException(*begin);
			}

			result[i++] = *begin;
		}

		return result;
	}

public:
	CustomAlphabet(const char* init) 
	: CustomAlphabet(std::string(init))
	{}

	CustomAlphabet(const std::string& init)
	: Alphabet<T, unsigned char>{}
	, _forward{ transform1(init.begin(), init.end()) }
	, _reverse{ transform2(init.begin(), init.end()) }
	{}

	CustomAlphabet(std::initializer_list<T> init)
	: Alphabet<T, unsigned char>{}
	, _forward{ transform1(init.begin(), init.end()) }
	, _reverse{ transform2(init.begin(), init.end()) }
	{}

	// CustomAlphabet(std::initializer_list<std::pair<T, unsigned char>> init);

	auto forward(const T character) const -> unsigned char override {
		try {
			return _forward.at(character);
		} catch(const std::out_of_range&) {
			throw UnknownCharacterException(static_cast<char>(character));
		}
	}

	auto reverse(const unsigned char character) const -> T override {
		try {
			return _reverse.at(character);
        } catch(const std::out_of_range&) {
            throw UnknownCharacterException(static_cast<char>(character));
        }
	}

	auto size() const -> int {
		return _forward.size();
	}
};

CustomAlphabet(const char*) -> CustomAlphabet<char>;

CustomAlphabet(const std::string&) -> CustomAlphabet<char>;

template <typename T>
CustomAlphabet(std::initializer_list<T>) -> CustomAlphabet<T>;

} // Namespace baseconvert
