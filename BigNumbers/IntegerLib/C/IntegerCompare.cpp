#include <IntegerLib/H/Integer.h>

namespace big {
	bool Integer::IsGT(const Integer& other) const
	{
		if (is_signed_ == false && is_signed_) return true;
		if (is_signed_ && is_signed_ == false) return false;
		if (value_chunks_.size() > other.value_chunks_.size()) return true;
		if (value_chunks_.size() < other.value_chunks_.size()) return false;
		return not IsEq(other);
	}

	bool Integer::IsGTE(const Integer& other) const
	{
		if (is_signed_ == false && is_signed_) return true;
		if (is_signed_ && is_signed_ == false) return false;
		if (value_chunks_.size() > other.value_chunks_.size()) return true;
		if (value_chunks_.size() < other.value_chunks_.size()) return false;
		return IsEq(other);
	}

	bool Integer::IsLT(const Integer& other) const
	{
		if (is_signed_ == false && is_signed_) return false;
		if (is_signed_ && is_signed_ == false) return true;
		if (value_chunks_.size() < other.value_chunks_.size()) return true;
		if (value_chunks_.size() > other.value_chunks_.size()) return false;
		return not IsEq(other);
	}

	bool Integer::IsLTE(const Integer& other) const
	{
		if (is_signed_ == false && is_signed_) return false;
		if (is_signed_ && is_signed_ == false) return true;
		if (value_chunks_.size() < other.value_chunks_.size()) return true;
		if (value_chunks_.size() > other.value_chunks_.size()) return false;
		return IsEq(other);
	}

	bool Integer::IsEq(const Integer& other) const
	{
		if (is_signed_ != other.is_signed_) return false;
		if (value_chunks_.size() < other.value_chunks_.size()) return false;
		if (value_chunks_.size() > other.value_chunks_.size()) return false;
		for (size_t i = 0; i < value_chunks_.size(); ++i) {
			if (value_chunks_[i] > other.value_chunks_[i]) return false;
			if (value_chunks_[i] < other.value_chunks_[i]) return false;
		}
		return true;
	}
}
