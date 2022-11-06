#include <iostream>
#include <vector>
#include <string>

#include "BaseConvert.h"

int main(int argc, char *argv[]){
    baseconvert::BaseConvert t1 = baseconvert::BaseConvert("abcdefghijklmnopqrstuvwxzy !", "0123");
    std::string input_string1 {"hello world!"};
    std::vector<unsigned char> input1(input_string1.begin(), input_string1.end());
    std::string result1 = t1.encode(input1);
    std::cout << input_string1 << " -> " << result1 << " -> ";
    for (const auto c: t1.decode(result1)) std::cout << c; std::cout << std::endl;

    baseconvert::BaseConvert t2 = baseconvert::BaseConvert("0123456789", "0123456789ABCDEF");
    std::string input_string2 {"255"};
    std::vector<unsigned char> input2(input_string2.begin(), input_string2.end());
    std::string result2 = t2.encode(input2);
    std::cout << input_string2 << " -> " << result2 << " -> ";
    for (const auto c: t2.decode(result2)) std::cout << c; std::cout << std::endl;

    baseconvert::BaseConvert t3 = baseconvert::BaseConvert(
        "0123456789abcdefghijklmnopqrstuvwxyz;,/?:@&=+$-_.!~*'()#", 
        "abcdefghijklmnopqrstuvwxyz0123456789"
    );
    std::string input_string3 {"https://bafybeifx7yeb55armcsxwwitkymga5xf53dxiarykms3ygqic223w5sk3m.ipfs.dweb.link/"};
    std::vector<unsigned char> input3(input_string3.begin(), input_string3.end());
    std::string result3 = t3.encode(input3);
    std::cout << input_string3 << " -> " << result3 << " -> ";
    for (const auto c: t3.decode(result3)) std::cout << c; std::cout << std::endl;

    return 0;
}
