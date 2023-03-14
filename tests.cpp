// NOLINTBEGIN
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>
#include "BaseConvert.h"
#include "Alphabet.h"

TEST_CASE("Alphabet") {
	SUBCASE("Default") {
		baseconvert::DefaultAlphabet alpha1 {};
		CHECK(1 == alpha1.forward(std::byte{1}));
		CHECK(std::byte{1} == alpha1.reverse(1));


		baseconvert::CustomAlphabet<char> alpha2 {"abcd"};
		CHECK(0 == alpha2.forward('a'));
		CHECK(1 == alpha2.forward('b'));
		CHECK('c' == alpha2.reverse(2));
		CHECK('d' == alpha2.reverse(3));

		baseconvert::CustomAlphabet<char> alpha3 {'A', 'B'};
		CHECK(0 == alpha3.forward('A'));
		CHECK(1 == alpha3.forward('B'));
		CHECK('B' == alpha3.reverse(1));
	}
}

TEST_CASE("Testing new concept") {
    SUBCASE("Raw to hex"){
		baseconvert::CustomAlphabet<char> alpha {"0123456789ABCDEF"};
        std::vector<std::byte> input {std::byte{0x5B}, std::byte{0x7C}, std::byte{0xDE}, std::byte{0x3F}, std::byte{0xA4}};
        std::string result = baseconvert::encode(input, alpha);
        CHECK(result == "5B7CDE3FA4");
    }
}

TEST_CASE("Testing the baseconvert library") {
    SUBCASE("Decimal to hex"){
        baseconvert::BaseConvert t = baseconvert::BaseConvert("0123456789", "0123456789ABCDEF");
        std::vector<unsigned char> input {'2','5','5'};
        std::string result = t.encode(input);
        CHECK("FF" == result);
        CHECK(input == t.decode(result));
    }

    SUBCASE("Raw to hex"){
        baseconvert::BaseConvert t = baseconvert::BaseConvert("0123456789ABCDEF");
        std::vector<unsigned char> input {0x5B,0x7C,0xDE,0x3F,0xA4};
        std::string result = t.encode(input);
        CHECK(result == "5B7CDE3FA4");
        CHECK(input == t.decode(result));
    }

    SUBCASE("Raw to octal"){
        baseconvert::BaseConvert t = baseconvert::BaseConvert("01234567");
        std::vector<unsigned char> input {0xFF,0x00,0xFF,0x00};
        std::string result = t.encode(input);
        CHECK(result == "37700177400");
        CHECK(input == t.decode(result));
    }

    SUBCASE("Raw to binary"){
        baseconvert::BaseConvert t = baseconvert::BaseConvert("01");
        std::vector<unsigned char> input {'H','e','l','l','o',',',' ','W','o','r','l','d','!'};
        std::string result = t.encode(input);
        CHECK(result == "1001000011001010110110001101100011011110010110000100000010101110110111101110010011011000110010000100001");
        CHECK(t.decode(result) == input);
    }
}

TEST_CASE("Exceptions") {
    SUBCASE("Duplicate in alphabet"){
        CHECK_THROWS(baseconvert::BaseConvert("01234564789"), baseconvert::DuplicateCharacterException('4'));
    }

    SUBCASE("Non printable Character in alphabet"){
        CHECK_THROWS(baseconvert::BaseConvert("01234567\t89"), baseconvert::NonPrintableCharacterException('\t'));
    }

    SUBCASE("Unknown Character in input"){
        baseconvert::BaseConvert t = baseconvert::BaseConvert("0123456789", "0123456789ABCDEF");
        std::vector<unsigned char> input {'2', '5', 'A'};
        CHECK_THROWS(t.encode(input), baseconvert::UnknownCharacterException('A'));
    }
}
//NOLINTEND
