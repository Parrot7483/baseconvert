#pragma once
#include <unordered_map>
#include <vector>
#include <string>

#include "Alphabet.h"

// TODO(Parror): Add support for constexpr

namespace baseconvert {
	auto encode(
		const std::vector<unsigned char>& _input, 
		const Alphabet<unsigned char, unsigned char>& _target
	) -> std::string;

	auto encode(
		const std::vector<char>& _input, 
		const Alphabet<unsigned char, unsigned char>& _target
	) -> std::string;

	auto encode(
		const std::vector<std::byte>& _input, 
		const Alphabet<unsigned char, unsigned char>& _target
	) -> std::string;

	auto encode(const std::vector<unsigned char>& _input, const Alphabet<unsigned char, unsigned char>& _origin, const Alphabet<unsigned char, unsigned char>& _target) -> std::string;
	
	auto decode(const std::string& _input, const Alphabet<unsigned char, unsigned char>& _origin) -> std::vector<unsigned char>;
	
	auto decode(const std::string& _input, const Alphabet<unsigned char, unsigned char>& _origin, const Alphabet<unsigned char, unsigned char>& _target) -> std::vector<unsigned char>;
}
