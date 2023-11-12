#include <IntegerLib/H/Integer.h>

namespace big {

	Integer Integer::Add(const Integer& other) const
	{

		if (is_signed_ && other.is_signed_) { // -A + -B
			auto result = Add_(other); // A + B
			result.is_signed_ = true; 
			return result;
		}
		else if (is_signed_ != other.is_signed_) { // -A + B || A + -B
			Integer result;
			if (IsGT(other, true)) {
				result = Sub_(other); // A - B
				result.is_signed_ = is_signed_;
			}
			else {
				result = other.Sub_(*this); // B - A
				result.is_signed_ = other.is_signed_;
			}
			return result;
		}

		return Add_(other); // A + B
	}

	Integer Integer::Sub(const Integer& other) const
	{
		if (is_signed_ && other.is_signed_) { // -A - -B -> -A + B
			Integer result;
			if (IsGT(other, true)) {
				result = Sub_(other); // A - B
				result.is_signed_ = is_signed_;
			}
			else {
				result = other.Sub_(*this); // B - A
				result.is_signed_ = other.is_signed_;
			}
			return result;
		}
		else if (is_signed_ == true && other.is_signed_ == false) { // -A - B
			auto result = Add_(other);
			result.is_signed_ = true;
			return result;
		}
		else if (is_signed_ == false && other.is_signed_ == true) { // A - -B
			return Add_(*this); // A + B
		}

		return Sub_(other); // A - B
	}

	Integer Integer::Add_(const Integer& other) const
	{
		Integer result;

		const size_t size = std::max(value_chunks_.size(), other.value_chunks_.size());
		result.value_chunks_.resize(size, 0);

		uint64_t carry = 0;

		int i = value_chunks_.size() - 1, j = other.value_chunks_.size() - 1;
		while (not (i < 0 && j < 0)) {
			const uint64_t a = (i < value_chunks_.size() && i >= 0) ? value_chunks_[i] : 0;
			const uint64_t b = (j < other.value_chunks_.size() && j >= 0) ? other.value_chunks_[j] : 0;

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
			i -= 1;
			j -= 1;
		}

		if (carry == 1) {
			result.value_chunks_.insert(value_chunks_.begin(), carry);
		}

		return result;
	}

	uint64_t Integer::Add1Left_(uint64_t n) const
	{
		if (n == 0) {
			return pow(10, CHUNK_SIZE_);
		}
		
		uint8_t e10 = 1;

		while (e10 <= n) {
			e10 <<= 1;
		}

		return e10 + n;
	}

	Integer Integer::Sub_(const Integer& other) const
	{
		Integer result;

		const size_t size = std::max(value_chunks_.size(), other.value_chunks_.size());
		result.value_chunks_.resize(size, 0);

		uint64_t borrow = 0;
		int i = value_chunks_.size() - 1, j = other.value_chunks_.size() - 1;
		while (not (i < 0 && j < 0)) {
			uint64_t a = (i < value_chunks_.size() && i >= 0) ? value_chunks_[i] : 0;
			uint64_t b = (j < other.value_chunks_.size() && j >= 0) ? other.value_chunks_[j] : 0;

			uint64_t difference = a;

			if (difference < b) {
				uint64_t a_1_in_left = Add1Left_(a);
				difference = a_1_in_left - b;
		  		borrow = 1;
			}
			else {
				b = b + borrow;
				if (difference < b) {
					uint64_t a_1_in_left = Add1Left_(a);
					difference = a_1_in_left - b;
					borrow = 1;
				}
				else {
					difference -= b;
					borrow = 0;
				}
			}

			result.value_chunks_[std::max(i,j)] = difference;
			i -= 1;
			j -= 1;
		}

		while (result.value_chunks_.size() > 1 && result.value_chunks_.front() == 0) {
			result.value_chunks_.erase(result.value_chunks_.begin());
		}

		return result;
	}

}


