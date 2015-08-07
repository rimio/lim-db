#include "metadata\bool-database-value.hpp"

BoolDatabaseValue::BoolDatabaseValue(bool val) {
	value_ = val;
}

bool BoolDatabaseValue::get_value() {
	return value_;
}

void BoolDatabaseValue::set_value(bool value) {
	value_ = value;
}

BYTE* BoolDatabaseValue::Serialize(BYTE *ptr) {
	if (value_)
		return Serializable::SerializeInt(1, ptr);
	return Serializable::SerializeInt(0, ptr);
}

BYTE* BoolDatabaseValue::Deserialize(BYTE *ptr) {
	INT32 val;
	
	BYTE* new_ptr = Serializable::DeserializeInt(ptr, &val);

	value_ = ( val == 1 ) ? true : false;

	return new_ptr;
}
