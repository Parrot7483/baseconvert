#pragma once
#include <gmpxx.h>
#include <unordered_map>
#include <vector>
#include <string>

#include "Alphabet.h"

// TODO(Parror): Add support for constexpr

namespace baseconvert {
    /*
     * In place Euclidean division (division with remainder) of the dividend by the divisor. 
     * Remainder is returned.
     */
    auto mpz_tdiv_qr_ui(mpz_class& dividend, const auto& divisor) {
        const mpz_class divi {divisor};
        mpz_class remainder;
        mpz_tdiv_qr(dividend.get_mpz_t(), 
                    remainder.get_mpz_t(), 
                    dividend.get_mpz_t(), 
					divi.get_mpz_t());
        return remainder.get_ui();
    }

    // TODO(Parrot): Use template for input and output data type
    template <typename OutputContainer, typename AlphaFrom, typename AlphaTo>
    auto convert(
		const AlphaFrom& _from,
		const AlphaTo& _to,
        const auto& _input
    ) -> OutputContainer {
        mpz_class num {0}; 
        for (const auto c: _input){
			num *= _from.size();
            num += _from.forward(c);
        }

		// TOOD: Size of output is known. Create Buffer. Fill from end to front. No reverse needed!
        OutputContainer result {};
        while (num) {
            result.push_back(_to.reverse(mpz_tdiv_qr_ui(num, _to.size())));
        }

        std::reverse(result.begin(), result.end());
        return result;
    }

	auto encode(
		const std::vector<unsigned char>& _input, 
		const Alphabet<unsigned char, unsigned char>& _origin, 
		const Alphabet<unsigned char, unsigned char>& _target
	) -> std::string {
		return convert<std::string>(_origin, _target, _input);
	}

	auto encode(
		const std::vector<unsigned char>& _input, 
		const Alphabet<unsigned char, unsigned char>& _target
	) -> std::string {
		return encode(_input, DefaultAlphabet(), _target);
	}

	auto decode(
		const std::string& _input, 
		const Alphabet<unsigned char, unsigned char>& _origin, 
		const Alphabet<unsigned char, unsigned char>& _target
	) -> std::vector<unsigned char> {
		return convert<std::vector<unsigned char>>(_target, _origin, _input);
	}

	auto decode(
		const std::string& _input, 
		const Alphabet<unsigned char, unsigned char>& _origin
	) -> std::vector<unsigned char> {
		return decode(_input, DefaultAlphabet(), _origin);
	}
} // namespace baseconvert
