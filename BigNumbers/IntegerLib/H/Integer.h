#pragma once

#include <cctype>
#include <string>
#include <vector>

namespace big {
	class Integer {
	public:
		Integer(const Integer&) = default;
		Integer(Integer&&) = default;

		Integer();
		Integer(const std::string& number_str);

		Integer& operator=(const Integer&) = default;
		Integer& operator=(Integer&&) = default;

		Integer Add(const Integer& other) const;
		Integer Sub(const Integer& other) const;
		Integer Mult(const Integer& other) const;

		bool IsGT(const Integer& other, bool ignore_sign = false) const;
		bool IsGTE(const Integer& other, bool ignore_sign = false) const;
		bool IsLT(const Integer& other, bool ignore_sign = false) const;
		bool IsLTE(const Integer& other, bool ignore_sign = false) const;
		bool IsEq(const Integer& other, bool ignore_sign = false) const;

		std::string ToString() const;

	private:
		std::vector<uint64_t> value_chunks_; //< in big-endian
		bool is_signed_ = false;
		static const size_t CHUNK_SIZE_;

		/**
		 *  Return a vector of uint64_t in big-endian order.
		 *	This function only accepts numbers in decimal representation like:
		 *		- "1"
		 *		- "12345678919"
		 *		- Not "0001", it will cause a undefined behaviour
		 */
		std::vector<uint64_t> ToChunks_(const std::string& number_str);

		/**
		 * Convert a string into a uint64_t if bytes > 0 && bytes <= chunk_size
		 */
		uint64_t ToChunk_(const std::string& bytes);

		Integer Add_(const Integer& other) const;
		Integer Sub_(const Integer& other) const;
		uint64_t Add1Left_(uint64_t n) const;

	};
}
