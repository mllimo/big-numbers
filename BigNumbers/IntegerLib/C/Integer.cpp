#include <cmath>
#include <stdexcept>
#include <iomanip>
#include <sstream>

#include <IntegerLib/H/Integer.h>

namespace big {
	// It is divided by a constant K to avoid overflows between chunk operations
	static const float K = 2;
	const size_t Integer::CHUNK_SIZE_ = (size_t)log10(pow(2, sizeof(uint64_t) * 8)) / K;

	Integer::Integer()
	{
		value_chunks_.push_back(0);
	}

	Integer::Integer(const std::string& number_str)
	{
		value_chunks_ = ToChunks_(number_str);
	}

	std::vector<uint64_t> Integer::ToChunks_(const std::string& number_str)
	{
		std::vector<uint64_t> result;

		if (number_str.empty())
			throw std::invalid_argument("number represented as str is empty");

		if (number_str.front() == '-') {
			is_signed_ = true;
		}

		const size_t TOTAL_CHUNKS = (size_t)std::ceil(((float)number_str.size() - is_signed_) / (float)CHUNK_SIZE_);
		int pos = number_str.size();
		size_t len = CHUNK_SIZE_;
		result.resize(TOTAL_CHUNKS);

		for (int i = TOTAL_CHUNKS - 1; i >= 0; --i) {
			pos -= CHUNK_SIZE_;
			if (pos < is_signed_) {
				len = CHUNK_SIZE_ + pos - is_signed_;
				pos = is_signed_;
			}

			std::string bytes = number_str.substr(pos, len);
			result[i] = ToChunk_(bytes);
		}

		return result;
	}

	uint64_t Integer::ToChunk_(const std::string& bytes)
	{
		if (bytes.size() == 0 || bytes.size() > CHUNK_SIZE_) {
			throw std::invalid_argument("bytes as str have to be gt 0 and lt CHUNK_SIZE");
		}

		char* endPtr;
		uint64_t result = std::strtoull(bytes.c_str(), &endPtr, 10);

		if (*endPtr != '\0') {
			throw std::bad_cast();
		}

		return result;
	}

	std::string Integer::ToString() const
	{
		std::string result = (is_signed_ ? "-" : "");
		result += std::to_string(value_chunks_.front());

		std::stringstream ss;

		for (int i = 1; i < value_chunks_.size(); ++i) {
			ss << std::setfill('0') << std::setw(CHUNK_SIZE_) << value_chunks_[i];
		}
		result += ss.str();

		return result;
	}
}
