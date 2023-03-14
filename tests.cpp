// NOLINTBEGIN
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>
#include "Alphabet.h"
#include "BaseConvert.h"

// auto make_buffer(const std::vector<int> input) -> std::vector<std::byte> {
// 	std::vector<std::byte> result {};
// 
// 	for (const auto b: input)
// 		result.push_back(static_cast<std::byte>(b));
// 
// 	return result;
// }

TEST_CASE("Alphabet") {
	SUBCASE("Default") {
		baseconvert::DefaultAlphabet alpha1 {};
		CHECK(1 == alpha1.forward(1));
		CHECK(1 == alpha1.reverse(1));


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

TEST_CASE("Testing the baseconvert library") {
    SUBCASE("Decimal to hex"){
		baseconvert::CustomAlphabet<unsigned char> alpha1 {"0123456789"};
		baseconvert::CustomAlphabet<unsigned char> alpha2 {"0123456789ABCDEF"};
        std::vector<unsigned char> input {'2','5','5'};
        std::string result = baseconvert::encode(input, alpha1, alpha2);
        CHECK("FF" == result);
        CHECK(input == baseconvert::decode(result, alpha1, alpha2));
	}

   SUBCASE("Raw to hex"){
		baseconvert::CustomAlphabet<unsigned char> alpha {"0123456789ABCDEF"};
        std::vector<unsigned char> input {0x5B,0x7C,0xDE,0x3F,0xA4};
        std::string result = baseconvert::encode(input, alpha);
        CHECK(result == "5B7CDE3FA4");
        CHECK(input == baseconvert::decode(result, alpha));
    }

    SUBCASE("Raw to octal"){
		baseconvert::CustomAlphabet<unsigned char> alpha {"01234567"};
        std::vector<unsigned char> input {0xFF,0x00,0xFF,0x00};
        std::string result = baseconvert::encode(input, alpha);
        CHECK(result == "37700177400");
        CHECK(input == baseconvert::decode(result, alpha));
    }

    SUBCASE("Raw to binary"){
		baseconvert::CustomAlphabet<unsigned char> alpha {"01"};
        std::vector<unsigned char> input {'H','e','l','l','o',',',' ','W','o','r','l','d','!'};
        std::string result = baseconvert::encode(input, alpha);
        CHECK(result == "1001000011001010110110001101100011011110010110000100000010101110110111101110010011011000110010000100001");
        CHECK(input == baseconvert::decode(result, alpha));
    }
}

TEST_CASE("Exceptions") {
    SUBCASE("Duplicate in alphabet"){
		CHECK_THROWS(baseconvert::CustomAlphabet<unsigned char>("01234564789"), baseconvert::DuplicateCharacterException('4'));
    }

    SUBCASE("Non printable Character in alphabet"){
		CHECK_THROWS(baseconvert::CustomAlphabet<unsigned char>("01234567\t89"), baseconvert::NonPrintableCharacterException('\t'));
    }

    SUBCASE("Unknown Character in input"){
		baseconvert::CustomAlphabet<unsigned char> alpha1 {"0123456789"};
		baseconvert::CustomAlphabet<unsigned char> alpha2 {"0123456789ABCDEF"};
        std::vector<unsigned char> input {'2', '5', 'A'};
		CHECK_THROWS(baseconvert::encode(input, alpha1, alpha2));
    }
}
//NOLINTEND
