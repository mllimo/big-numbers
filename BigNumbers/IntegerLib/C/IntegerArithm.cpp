#include <IntegerLib/H/Integer.h>

namespace big {

	Integer Integer::Add(const Integer& other) const
	{

		if (is_signed_ && other.is_signed_) { // -A + -B
			auto result = Add_(other); // A + B
			result.is_signed_ = true; 
			return result;
		}
		else if (is_signed_) { // -A + B
			auto result = other.Subs_(*this); // B - A
			if (IsGT(other)) {
				result.is_signed_ = true;
			}
			return result;
		}
		else if (other.is_signed_) { // A + -B
			auto result = Subs_(*this); // A - B
			if (other.IsGT(*this)) {
				result.is_signed_ = true;
			}
			return result;
		}

		return Add_(other); // A + B
	}

	Integer Integer::Subs(const Integer& other) const
	{
		if (is_signed_ && other.is_signed_) { // -A - -B
			auto result = other.Subs(*this); // -A + B -> B - A
			if (other.IsGT(*this)) {
				result.is_signed_ = true;
			}
			return result;
		}
		else if (is_signed_) { // -A - B
			auto result = other.Add_(*this); // A + B
			result.is_signed_ = true;
			return result;
		}
		else if (other.is_signed_) { // A - -B
			return Add_(*this); // A + B
		}

		return Subs_(other); // A - B
	}

	Integer Integer::Add_(const Integer& other) const
	{
		Integer result;

		const size_t size = std::max(value_chunks_.size(), other.value_chunks_.size());
		result.value_chunks_.resize(size, 0);

		uint64_t carry = 0;

		for (int i = size - 1; i >= 0; --i) {
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

	Integer Integer::Subs_(const Integer& other) const
	{
		Integer result;

		const size_t size = std::max(value_chunks_.size(), other.value_chunks_.size());
		result.value_chunks_.resize(size, 0);

		uint64_t borrow = 0;

		for (int i = size - 1; i >= 0; --i) {
			uint64_t a = (i < value_chunks_.size()) ? value_chunks_[i] : 0;
			uint64_t b = (i < other.value_chunks_.size()) ? other.value_chunks_[i] : 0;

			if (a < b) {
				std::swap(a, b);
			}

			uint64_t difference = a;

			if (difference < b) {
				difference = 0;
				borrow = 1;
			}
			else {
				difference -= b + borrow;
				borrow = 0;
			}

			result.value_chunks_[i] = difference;
		}

		while (result.value_chunks_.size() > 1 && result.value_chunks_.front() == 0) {
			result.value_chunks_.erase(result.value_chunks_.begin());
		}

		return result;
	}

}


