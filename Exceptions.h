#pragma once
#include <exception>

namespace baseconvert {

/**
 * TODO(parrot)
 */
struct AlphabetException : public std::exception {
	const std::string msg;
	AlphabetException(const std::string msg) : msg{msg} {};
	const char* what() const noexcept override { //NOLINT
		return msg.c_str();
	}
};

/**
 * TODO(parrot)
 */
struct UnknownCharacterException : public AlphabetException {
	explicit UnknownCharacterException(const char character) : AlphabetException(
		fmt::format("Found character \'0x{:02X}\' in input but not in input alphabet!", character)
	){};
};

/**
 * TODO(parrot)
 */
struct NonPrintableCharacterException : public AlphabetException {
	explicit NonPrintableCharacterException(const char character) : AlphabetException(
		fmt::format("Character \'0x{:02X}\' found in alphabet is not printable!", character)
	){};
};

/**
 * TODO(parrot)
 */
struct DuplicateCharacterException : public AlphabetException {
    explicit DuplicateCharacterException(const char character) : AlphabetException(
		fmt::format("Character \'0x{:02X}\' found multiple times in alphabet!", character)
	) {};
};

} // namespace baseconvert
