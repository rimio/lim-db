#include "metadata\int-database-value.hpp"

IntDatabaseValue::IntDatabaseValue(INT32 val) {
	value_ = val;
}

INT32 IntDatabaseValue::get_value() {
	return value_;
}

void IntDatabaseValue::set_value(INT32 value) {
	value_ = value;
}

BYTE* IntDatabaseValue::Serialize(BYTE *ptr) {
	return Serializable::SerializeInt(value_, ptr);
}

BYTE* IntDatabaseValue::Deserialize(BYTE *ptr) {
	return Serializable::DeserializeInt(ptr, &value_);
}
