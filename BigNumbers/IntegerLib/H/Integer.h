#pragma once

#include <cctype>
#include <string>
#include <vector>

namespace big {
	class Integer {
	public:
		Integer() = default;
		Integer(const Integer&) = default;
		Integer(Integer&&) = default;

		Integer(const std::string& number_str);

		Integer Add(const Integer& other) const;

		std::string ToString() const;

	private:
		std::vector<uint64_t> value_chunks_; //< in big-endian
		// TODO: Add chunk size as static const

		/**
		 *  Return a vector of uint64_t in big-endian order.
		 *	This function only accepts numbers in decimal representation like:
		 *		- "1"
		 *		- "12345678919"
		 *		- Not "0001", it will cause a undefined behaviour
		 */
		std::vector<uint64_t> ToChunks(const std::string& number_str);

		/**
		 * Convert a string into a uint64_t if bytes > 0 && bytes <= 8
		 */
		uint64_t ToChunk(const std::string& bytes);

	};
}
