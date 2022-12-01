#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "BaseConvert.h"

TEST_CASE("testing the baseconvert library") {
    baseconvert::BaseConvert t1 = baseconvert::BaseConvert("0123456789", "0123456789ABCDEF");
    std::string input_string1 {"255"};
    std::vector<unsigned char> input1(input_string1.begin(), input_string1.end());
    std::string result1 = t1.encode(input1);
    CHECK(result1 == "FF");
    CHECK(t1.decode(result1) == input1);
}