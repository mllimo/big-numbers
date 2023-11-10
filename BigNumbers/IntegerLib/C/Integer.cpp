#include <cmath>
#include <stdexcept>
#include <iomanip>
#include <sstream>

#include <IntegerLib/H/Integer.h>

namespace big {
	Integer::Integer(const std::string& number_str)
	{
		value_chunks_ = ToChunks(number_str);
	}

	std::vector<uint64_t> Integer::ToChunks(const std::string& number_str)
	{
		std::vector<uint64_t> result;

		const size_t CHUNK_SIZE = (size_t)log10(pow(2, sizeof(uint64_t) * 8));
		const size_t TOTAL_CHUNKS = (size_t)std::ceil((float)number_str.size() / (float)CHUNK_SIZE);
		int pos = number_str.size();
		size_t len = CHUNK_SIZE;
		result.resize(TOTAL_CHUNKS);

		for (int i = TOTAL_CHUNKS - 1; i >= 0; --i) {
			pos -= CHUNK_SIZE;
			if (pos < 0) {
				len = CHUNK_SIZE + pos;
				pos = 0;
			}

			std::string bytes = number_str.substr(pos, len);
			result[i] = ToChunk(bytes);
		}

		return result;
	}

	uint64_t Integer::ToChunk(const std::string& bytes)
	{
		const size_t CHUNK_SIZE = (size_t)log10(pow(2, sizeof(uint64_t) * 8));

		if (bytes.size() == 0 || bytes.size() > CHUNK_SIZE) { // TODO: improve exception
			throw std::runtime_error("ToChunk: bytes == 0 || bytes > max_digits");
		}

		char* endPtr;
		uint64_t result = std::strtoull(bytes.c_str(), &endPtr, 10);

		if (*endPtr != '\0') { // TODO: improve exception
			throw std::runtime_error("ToChunk: Conversion failed");
		}

		return result;
	}

	Integer Integer::Add(const Integer& other) const
	{
		Integer result;

		const size_t size = std::max(value_chunks_.size(), other.value_chunks_.size());
		result.value_chunks_.resize(size, 0);

		uint64_t carry = 0;

		for (size_t i = 0; i < size; ++i) {
			const uint64_t a = (i < value_chunks_.size()) ? value_chunks_[i] : 0;
			const uint64_t b = (i < other.value_chunks_.size()) ? other.value_chunks_[i] : 0;

			// overflow and carry
			uint64_t sum = a;
			if (UINT64_MAX - sum < b || UINT64_MAX - carry < sum + b) {
				sum = UINT64_MAX;
				carry = 1;
			}
			else {
				sum += b + carry;
				carry = 0;
			}

			result.value_chunks_[i] = sum;
		}

		if (carry == 1) {
			result.value_chunks_.insert(value_chunks_.begin(), carry);
		}

		return result;
	}

	std::string Integer::ToString() const
	{
		const size_t CHUNK_SIZE = (size_t)log10(pow(2, sizeof(uint64_t) * 8));
		std::string result = std::to_string(value_chunks_.front());

		std::stringstream ss;

		for (int i = 1; i < value_chunks_.size(); ++i) {
			ss << std::setfill('0') << std::setw(CHUNK_SIZE) << value_chunks_[i];
		}
		result += ss.str();

		return result;
	}


}


