#include <cmath>
#include <stdexcept>
#include <iomanip>
#include <sstream>

#include <IntegerLib/H/Integer.h>

namespace big {
	const size_t Integer::CHUNK_SIZE = (size_t)log10(pow(2, sizeof(uint64_t) * 8));

	Integer::Integer()
	{
		value_chunks_.push_back(0);
	}

	Integer::Integer(const std::string& number_str)
	{
		value_chunks_ = ToChunks(number_str);
	}

	std::vector<uint64_t> Integer::ToChunks(const std::string& number_str)
	{
		std::vector<uint64_t> result;

		if (number_str.empty()) // TODO: improve exception
			throw std::invalid_argument("Invalid parameter");

		if (number_str.front() == '-') {
			is_signed_ = true;
		}

		const size_t TOTAL_CHUNKS = (size_t)std::ceil(((float)number_str.size() - is_signed_) / (float)CHUNK_SIZE);
		int pos = number_str.size();
		size_t len = CHUNK_SIZE;
		result.resize(TOTAL_CHUNKS);

		for (int i = TOTAL_CHUNKS - 1; i >= 0; --i) {
			pos -= CHUNK_SIZE;
			if (pos < is_signed_) {
				len = CHUNK_SIZE + pos - is_signed_;
				pos = is_signed_;
			}

			std::string bytes = number_str.substr(pos, len);
			result[i] = ToChunk(bytes);
		}

		return result;
	}

	uint64_t Integer::ToChunk(const std::string& bytes)
	{
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

	std::string Integer::ToString() const
	{
		std::string result = (is_signed_ ? "-" : "");
		result += std::to_string(value_chunks_.front());

		std::stringstream ss;

		for (int i = 1; i < value_chunks_.size(); ++i) {
			ss << std::setfill('0') << std::setw(CHUNK_SIZE) << value_chunks_[i];
		}
		result += ss.str();

		return result;
	}
}
