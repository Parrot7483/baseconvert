#include <unordered_map>
#include <vector>
#include <string>


// TODO: Add option for leading zeros

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
         * TODO
         */
        BaseConvert(const std::string& _origin_alpha, const std::string& _target_alpha);

        /**
         * TODO
         */
        BaseConvert(const std::string& _target_alpha);

        /**
         * TODO
         */
        auto encode(const std::vector<unsigned char>& _input) -> std::string;

        /**
         * TODO
         */
        auto decode(const std::string& _input) -> std::vector<unsigned char>;
};

/**
 * TODO
 */
class UnknownCharacterException : public std::exception {
        char c;
    public:
        UnknownCharacterException(const char c);
        auto what() const noexcept -> const char*;
};

/**
 * TODO
 */
class NonPrintableCharacterException : public std::exception {
        char c;
    public:
        NonPrintableCharacterException(const char c);
        auto what() const noexcept -> const char*;
};

/**
 * TODO
 */
class DuplicateCharacterException : public std::exception {
        char c;
    public:
        DuplicateCharacterException(const char c);
        auto what() const noexcept -> const char*;
};
}