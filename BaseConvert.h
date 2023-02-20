#include <unordered_map>
#include <vector>
#include <string>


// TODO(Parrot): Add option for leading zeros
// Add support for constexpr

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
struct UnknownCharacterException : public std::exception {
        const char c;
        UnknownCharacterException(const char _c) : c{_c} {};
        auto what() const noexcept -> const char*;
};

/**
 * TODO
 */
struct NonPrintableCharacterException : public std::exception {
        const char c;
        NonPrintableCharacterException(const char _c) : c{_c} {};
        auto what() const noexcept -> const char*;
};

/**
 * TODO
 */
struct DuplicateCharacterException : public std::exception {
        const char c;
        DuplicateCharacterException(const char _c) : c{_c} {};
        auto what() const noexcept -> const char*;
};
}
