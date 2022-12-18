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

/**
 * TODO
 */
class DuplicateCharacterException : public std::exception {
    private:
        std::string msg;
    public:
        DuplicateCharacterException(const char c);
        const char* what() const noexcept;
};
}