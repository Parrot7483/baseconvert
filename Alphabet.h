#pragma once
#include <initializer_list>
#include <string>
#include <unordered_map>
#include <tuple>
#include <vector>

namespace baseconvert {

template <typename T, typename S>
class Alphabet {
public:
	virtual auto forward(const T character) const -> S = 0;
	virtual auto reverse(const S character) const -> T = 0;
	virtual auto size() const -> int = 0;
};

class DefaultAlphabet: public Alphabet<std::byte, unsigned char> {
public:
	auto forward(const std::byte character) const -> unsigned char override {
		return static_cast<unsigned char>(character);
	}

	auto reverse(const unsigned char character) const -> std::byte override {
		return static_cast<std::byte>(character);
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

	template <typename InputIterator>
	static auto transform1(InputIterator begin, InputIterator end) {
		std::unordered_map<T, unsigned char> result {};

		for (auto i = 0; begin != end; begin++) {
			result[*begin] = i++;
		}

		return result;
	}

	template <typename InputIterator>
	static auto transform2(InputIterator begin, InputIterator end) {
		std::unordered_map<unsigned char, T> result {};

		for (auto i = 0; begin != end; begin++) {
			result[i++] = *begin;
		}

		return result;
	}
public:
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

	// CustomAlphabet(const std::initializer_list<std::pair<T, unsigned char>> init);

	auto forward(const T character) const -> unsigned char override {
    	return _forward.at(character);
	}

	auto reverse(const unsigned char character) const -> T override {
    	return _reverse.at(character);
	}

	auto size() const -> int {
		return _forward.size();
	}
};

//TODO(Parrot): Do template deduction guide so CustomeAlphabet(const std::string) can be used without explicit template parameter

} // Namespace baseconvert
