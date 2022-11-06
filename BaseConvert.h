#include <unordered_map>
#include <vector>
#include <string>

// TODO: Second Constructor without origin_alphabet
// TOOD: Command line Utility
// TOOD: Unit tests
// TODO: std::vector<std::byte> as input/output for encode/decode

namespace baseconvert {
class BaseConvert {
    private:
        std::unordered_map<unsigned char, unsigned char> origin_alpha;
        std::unordered_map<unsigned char, unsigned char> origin_alpha_reverse;
        std::unordered_map<unsigned char, unsigned char> target_alpha;
        std::unordered_map<unsigned char, unsigned char> target_alpha_reverse;
    public: 
        /**
         * TODO
         */
        BaseConvert(const std::string& _origin_alpha, const std::string& _target_alpha);

        /**
         * TODO
         */
        std::string encode(const std::vector<unsigned char>& _input);

        /**
         * TODO
         */
        std::vector<unsigned char> decode(const std::string& _input);
};

/**
 * TODO
 */
class UnknownCharacterException : public std::exception {
    private:
        std::string msg;
    public:
        UnknownCharacterException(const char c);
        const char* what() const noexcept;
};

/**
 * TODO
 */
class NonPrintableCharacterException : public std::exception {
    private:
        std::string msg;
    public:
        NonPrintableCharacterException(const char c);
        const char* what() const noexcept;
};
}