#include <IntegerLib/H/Integer.h>

namespace big {
	bool Integer::IsGT(const Integer& other, bool ignore_sign) const
	{
		if (IsEq(other)) return false;

		if (!ignore_sign) {
			if (is_signed_ == true && other.is_signed_ == false) return false;
			if (is_signed_ == false && other.is_signed_ == true) return true;
		}

		if (is_signed_ == other.is_signed_ && value_chunks_.size() < other.value_chunks_.size()) return false;
		if (is_signed_ == other.is_signed_ && value_chunks_.size() > other.value_chunks_.size()) return true;

		for (size_t i = 0; i < value_chunks_.size(); ++i) {
			if (value_chunks_[i] > other.value_chunks_[i]) return true;
			if (value_chunks_[i] < other.value_chunks_[i]) return false;
		}

		return false;
	}

	bool Integer::IsGTE(const Integer& other, bool ignore_sign) const
	{
		return IsGT(other, ignore_sign) || IsEq(other);
	}

	bool Integer::IsLT(const Integer& other, bool ignore_sign) const
	{
		if (IsEq(other)) return false;

		if (!ignore_sign) {
			if (is_signed_ == true && other.is_signed_ == false) return true;
			if (is_signed_ == false && other.is_signed_ == true) return false;
		}

		if (is_signed_ == other.is_signed_ && value_chunks_.size() < other.value_chunks_.size()) return true;
		if (is_signed_ == other.is_signed_ && value_chunks_.size() > other.value_chunks_.size()) return false;

		for (size_t i = 0; i < value_chunks_.size(); ++i) {
			if (value_chunks_[i] > other.value_chunks_[i]) return false;
			if (value_chunks_[i] < other.value_chunks_[i]) return true;
		}

		return false;
	}

	bool Integer::IsLTE(const Integer& other, bool ignore_sign) const
	{
		return IsLT(other, ignore_sign) || IsEq(other);
	}

	bool Integer::IsEq(const Integer& other, bool ignore_sign) const
	{
		if (value_chunks_.size() == 1 && other.value_chunks_.size() == 1 && value_chunks_.front() == 0 && other.value_chunks_.front() == 0) return true;
		if (value_chunks_.size() < other.value_chunks_.size()) return false;
		if (value_chunks_.size() > other.value_chunks_.size()) return false;

		for (size_t i = 0; i < value_chunks_.size(); ++i) {
			if (value_chunks_[i] > other.value_chunks_[i]) return false;
			if (value_chunks_[i] < other.value_chunks_[i]) return false;
		}

		if (!ignore_sign && is_signed_ != other.is_signed_) return false;

		return true;
	}

}
