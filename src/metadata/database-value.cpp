#include "metadata\database-value.hpp"
#include "base\error-manager.hpp"
#include "base\generic-operations.hpp"

#include <cassert>
#include <stdexcept>

void DatabaseValue::ClearValue(){
	if (data_type_ == DB_STRING && need_clear_) {
		assert(value_.s != nullptr);
		delete value_.s;
		value_.s = nullptr;
	}
	need_clear_ = false;
}

DatabaseValue::DatabaseValue(const DatabaseValue& value) {
	ClearValue();
	this->data_type_ = value.data_type_;
	this->value_ = value.value_;
	this->is_null_ = value.is_null_;
}

DatabaseValue::~DatabaseValue() {
	ClearValue();
}

int DatabaseValue::Compare(DatabaseValue arg) {
	DatabaseValue a = arg;
	DatabaseValue b = *this;
	
	DataType common_type = CommonType(a.get_type(), b.get_type());

	if (common_type == DB_ERROR)
		return ErrorManager::error(__HERE__, ER_FAILED);

	if (a.get_type() != common_type)
		a.Cast(common_type);
	if (b.get_type() != common_type)
		b.Cast(common_type);
	
	switch (common_type) {
	case DB_INTEGER:
		return b.int_value() - a.int_value();
	case DB_FLOAT:
		float diff;
		diff = b.float_value() - a.float_value();
		if (fabs(diff) < MACHINE_ERROR) 
			return 0;
		return diff > 0 ? 1 : -1;
	case DB_STRING:
		return b.string_value().compare(a.string_value());
	case DB_BOOLEAN:
		if (a.bool_value() == b.bool_value()) return 0;
		return 1;
	default:
		assert(false);
		return ER_FAILED;
	}
}

bool DatabaseValue::operator<(const DatabaseValue& value) {
	DatabaseValue a = value;
	assert(this->get_type() != DB_BOOLEAN && a.get_type() != DB_BOOLEAN);
	int result = Compare(value);
	if (result < 0) return true;
	return false;
}

bool DatabaseValue::operator>(const DatabaseValue& value) {
	DatabaseValue a = value;
	assert(this->get_type() != DB_BOOLEAN && a.get_type() != DB_BOOLEAN);
	int result = Compare(value);
	if (result > 0) return true;
	return false;
}

bool DatabaseValue::operator>=(const DatabaseValue& value) {
	DatabaseValue a = value;
	assert(this->get_type() != DB_BOOLEAN && a.get_type() != DB_BOOLEAN);
	int result = Compare(value);
	if (result < 0) return false;
	return true;
}

bool DatabaseValue::operator<=(const DatabaseValue& value) {
	DatabaseValue a = value;
	assert(this->get_type() != DB_BOOLEAN && a.get_type() != DB_BOOLEAN);
	int result = Compare(value);
	if (result > 0) return false;
	return true;
}

bool DatabaseValue::operator==(const DatabaseValue& value) {
	int result = Compare(value);
	if (result == 0) return true;
	return false;
}

bool DatabaseValue::operator!=(const DatabaseValue& value) {
	int result = Compare(value);
	if (result == 0) return false;
	return true;
}

DatabaseValue& DatabaseValue::operator=(const DatabaseValue& value) {
	if (this != &value) {
		ClearValue();
		this->data_type_ = value.data_type_;
		this->value_ = value.value_;
		this->is_null_ = value.is_null_;
	}
	return *this;
}

DatabaseValue DatabaseValue::operator+(const DatabaseValue& value) {
	ErrorCode er = NO_ERROR;
	DatabaseValue result;
	DatabaseValue left = *this;
	DatabaseValue right = value;

	if (left.get_type() != DB_INTEGER && left.get_type() != DB_FLOAT) {
		result.set_type(DB_ERROR);
		return result;
	}

	if (right.get_type() != DB_INTEGER && right.get_type() != DB_FLOAT) {
		result.set_type(DB_ERROR);
		return result;
	}

	DataType dominant_type = (left.get_type() == DB_INTEGER
		&& right.get_type() == DB_INTEGER) ? DB_INTEGER : DB_FLOAT;

	if (left.get_type() != dominant_type) {
		er = left.Cast(dominant_type);
		if (er != NO_ERROR) {
			result.set_type(DB_ERROR);
			return result;
		}
	}

	if (right.get_type() != dominant_type) {
		er = right.Cast(dominant_type);
		if (er != NO_ERROR) {
			result.set_type(DB_ERROR);
			return result;
		}
	}

	switch (left.get_type()){
	case DB_INTEGER:
		result.set_int_value(left.int_value() + right.int_value());
		break;
	case DB_FLOAT:
		result.set_float_value(left.float_value() + right.float_value());
		break;
	default:
		result.set_type(DB_ERROR);
		break;
	}

	return result;
}

DatabaseValue DatabaseValue::operator-(const DatabaseValue& value) {
	ErrorCode er = NO_ERROR;
	DatabaseValue result;
	DatabaseValue left = *this;
	DatabaseValue right = value;

	if (left.get_type() != DB_INTEGER && left.get_type() != DB_FLOAT) {
		result.set_type(DB_ERROR);
		return result;
	}

	if (right.get_type() != DB_INTEGER && right.get_type() != DB_FLOAT) {
		result.set_type(DB_ERROR);
		return result;
	}

	DataType dominant_type = (left.get_type() == DB_INTEGER
		&& right.get_type() == DB_INTEGER) ? DB_INTEGER : DB_FLOAT;

	if (left.get_type() != dominant_type) {
		er = left.Cast(dominant_type);
		if (er != NO_ERROR) {
			result.set_type(DB_ERROR);
			return result;
		}
	}

	if (right.get_type() != dominant_type) {
		er = right.Cast(dominant_type);
		if (er != NO_ERROR) {
			result.set_type(DB_ERROR);
			return result;
		}
	}

	switch (left.get_type()){
	case DB_INTEGER:
		result.set_int_value(left.int_value() - right.int_value());
		break;
	case DB_FLOAT:
		result.set_float_value(left.float_value() - right.float_value());
		break;
	default:
		result.set_type(DB_ERROR);
		break;
	}

	return result;
}

DatabaseValue DatabaseValue::operator*(const DatabaseValue& value) {
	ErrorCode er = NO_ERROR;
	DatabaseValue result;
	DatabaseValue left = *this;
	DatabaseValue right = value;

	if (left.get_type() != DB_INTEGER && left.get_type() != DB_FLOAT) {
		result.set_type(DB_ERROR);
		return result;
	}

	if (right.get_type() != DB_INTEGER && right.get_type() != DB_FLOAT) {
		result.set_type(DB_ERROR);
		return result;
	}

	DataType dominant_type = (left.get_type() == DB_INTEGER
		&& right.get_type() == DB_INTEGER) ? DB_INTEGER : DB_FLOAT;

	if (left.get_type() != dominant_type) {
		er = left.Cast(dominant_type);
		if (er != NO_ERROR) {
			result.set_type(DB_ERROR);
			return result;
		}
	}

	if (right.get_type() != dominant_type) {
		er = right.Cast(dominant_type);
		if (er != NO_ERROR) {
			result.set_type(DB_ERROR);
			return result;
		}
	}

	switch (left.get_type()){
	case DB_INTEGER:
		result.set_int_value(left.int_value() * right.int_value());
		break;
	case DB_FLOAT:
		result.set_float_value(left.float_value() * right.float_value());
		break;
	default:
		result.set_type(DB_ERROR);
		break;
	}

	return result;
}

DatabaseValue DatabaseValue::operator/(const DatabaseValue& value) {
	ErrorCode er = NO_ERROR;
	DatabaseValue result;
	DatabaseValue left = *this;
	DatabaseValue right = value;

	if (left.get_type() != DB_INTEGER && left.get_type() != DB_FLOAT) {
		result.set_type(DB_ERROR);
		return result;
	}

	if (right.get_type() != DB_INTEGER && right.get_type() != DB_FLOAT) {
		result.set_type(DB_ERROR);
		return result;
	}

	DataType dominant_type = (left.get_type() == DB_INTEGER
		&& right.get_type() == DB_INTEGER) ? DB_INTEGER : DB_FLOAT;

	if (left.get_type() != dominant_type) {
		er = left.Cast(dominant_type);
		if (er != NO_ERROR) {
			result.set_type(DB_ERROR);
			return result;
		}
	}

	if (right.get_type() != dominant_type) {
		er = right.Cast(dominant_type);
		if (er != NO_ERROR) {
			result.set_type(DB_ERROR);
			return result;
		}
	}

	switch (left.get_type()){
	case DB_INTEGER:
		result.set_int_value(left.int_value() / right.int_value());
		break;
	case DB_FLOAT:
		result.set_float_value(left.float_value() / right.float_value());
		break;
	default:
		result.set_type(DB_ERROR);
		break;
	}

	return result;
}

DatabaseValue DatabaseValue::operator%(const DatabaseValue& value) {
	ErrorCode er = NO_ERROR;
	DatabaseValue result;
	DatabaseValue left = *this;
	DatabaseValue right = value;

	if (left.get_type() != DB_INTEGER || right.get_type() != DB_INTEGER) {
		result.set_type(DB_ERROR);
		return result;
	}

    result.set_int_value(left.int_value() % right.int_value());
	
	return result;
}


BYTE* DatabaseValue::Serialize(BYTE* ptr) {
	switch (data_type_) {
	case DB_INTEGER:
		return Serializable::SerializeInt(value_.i, ptr);
	case DB_FLOAT:
		return Serializable::SerializeFloat(value_.f, ptr);
	case DB_STRING:
		return Serializable::SerializeString((*value_.s), ptr);
	case DB_BOOLEAN:
		if (value_.b)
			return Serializable::SerializeInt(1, ptr);
		return Serializable::SerializeInt(0, ptr);
	default:
		break;
	}
}

BYTE* DatabaseValue::Deserialize(BYTE* ptr) {
	switch (data_type_) {
	case DB_INTEGER:
		is_null_ = false;
		ClearValue();
		return Serializable::DeserializeInt(ptr, &value_.i);
	case DB_FLOAT:
		is_null_ = false;
		ClearValue();
		return Serializable::DeserializeFloat(ptr, &value_.f);
	case DB_STRING:
		is_null_ = false;
		return Serializable::DeserializeString(ptr, value_.s);
	case DB_BOOLEAN:
		is_null_ = false;
		ClearValue();
		INT32 val;
		BYTE* new_ptr;
		new_ptr = Serializable::DeserializeInt(ptr, &val);
		assert(val == 1 || val == 0);
		value_.b = (val == 1);
		return new_ptr;
	default:
		break;
	}
}

void DatabaseValue::set_int_value(INT32 value) {
	ClearValue();
	data_type_ = DB_INTEGER;
	value_.i = value;
	is_null_ = false;
}

void DatabaseValue::set_float_value(float value) {
	ClearValue();
	data_type_ = DB_FLOAT;
	value_.f = value;
	is_null_ = false;
}

void DatabaseValue::set_string_value(std::string* value, bool copy) {
	ClearValue();
	if (value == nullptr) {
		is_null_ = true;
		return;
	}
	data_type_ = DB_STRING;
	if (copy) {
		value_.s = new std::string(*value);
	}
	else {
		value_.s = value;
	}
	need_clear_ = copy;
	is_null_ = false;
}

void DatabaseValue::set_bool_value(bool value) {
	ClearValue();
	data_type_ = DB_BOOLEAN;
	value_.b = value;
	is_null_ = false;
}

ErrorCode DatabaseValue::Cast(DataType type) {
	return Cast(type, this);
}

ErrorCode DatabaseValue::Cast(DataType type, DatabaseValue* output) {
	INT32 int_val;
	float fl_val;
	std::string str_val;
	bool b_val;

	switch (this->get_type()) {
	case DB_INTEGER:
		int_val = value_.i;

		switch (type) {
		case DB_INTEGER:
			output->set_int_value(int_val);
			return NO_ERROR;
		case DB_FLOAT:
			fl_val = (float)int_val;
			output->set_float_value(fl_val);
			return NO_ERROR;
		case DB_STRING:
			str_val = std::to_string(int_val);
			output->set_string_value(&str_val,true);
			return NO_ERROR;
		case DB_BOOLEAN:
			b_val = (int_val == 0) ? false : true;
			output->set_bool_value(b_val);
			return NO_ERROR;
		case DB_NUMERIC:
			output->set_int_value(int_val);
			return NO_ERROR;
		case DB_ANY:
			output->set_int_value(int_val);
			return NO_ERROR;
		default:
			assert(false);
			return ER_FAILED;
		}

	case DB_FLOAT:
		fl_val = this->float_value();

		switch (type) {
		case DB_INTEGER:
			int_val = (INT32)fl_val;
			output->set_int_value(int_val);
			return NO_ERROR;
		case DB_FLOAT:
			output->set_float_value(fl_val);
			return NO_ERROR;
		case DB_STRING:
			str_val = std::to_string(fl_val);
			output->set_string_value(&str_val,true);
			return NO_ERROR;
		case DB_BOOLEAN:
			b_val = !(abs(fl_val) < MACHINE_ERROR);
			output->set_bool_value(b_val);
			return NO_ERROR;
		case DB_NUMERIC:
			output->set_float_value(fl_val);
			return NO_ERROR;
		case DB_ANY:
			output->set_float_value(fl_val);
			return NO_ERROR;
		default:
			assert(false);
			return ER_FAILED;
		}

	case DB_STRING:
		str_val = this->string_value();
		std::string::size_type after;
		bool conv_ok;

		switch (type) {
		case DB_INTEGER:
			// Try to convert from string to int 
			try {
				int_val = std::stoi(str_val, &after);
			}
			catch (const std::exception &e) {
				return ErrorManager::error(__HERE__, ER_CAST_ERROR);
			}
			// Check if the string was containg nothing else after the converted int
			if (str_val.substr(after) != "")
				return ErrorManager::error(__HERE__, ER_CAST_ERROR);

			output->set_int_value(int_val);
			return NO_ERROR;
		case DB_FLOAT:
			// Try to convert from string to float
			try {
				fl_val = std::stof(str_val, &after);
			}
			catch (const std::exception &e) {
				return ErrorManager::error(__HERE__, ER_CAST_ERROR);
			}
			// Check if the string was containg nothing else after the converted float
			if (str_val.substr(after) != "")
				return ErrorManager::error(__HERE__, ER_CAST_ERROR);

			output->set_float_value(fl_val);
			return NO_ERROR;
		case DB_STRING:
			output->set_string_value(&str_val,true);
			return NO_ERROR;
		case DB_BOOLEAN:
			return ErrorManager::error(__HERE__, ER_CAST_ERROR);
		case DB_NUMERIC:
			bool int_ok;
			int_ok = true;
			// First try to convert from string to int 
			try {
				int_val = std::stoi(str_val, &after);
			}
			catch (const std::exception &e) {
				int_ok = false;
			}
			// Check if the string was containg nothing else after the converted int
			if (str_val.substr(after) != "")
				int_ok = false;

			if (int_ok) {
				output->set_int_value(int_val);
				return NO_ERROR;
			}

			// Try to convert from string to float
			try {
				fl_val = std::stof(str_val, &after);
			}
			catch (const std::exception &e) {
				return ErrorManager::error(__HERE__, ER_CAST_ERROR);
			}
			// Check if the string was containg nothing else after the converted float
			if (str_val.substr(after) != "")
				return ErrorManager::error(__HERE__, ER_CAST_ERROR);

			output->set_float_value(fl_val);
			return NO_ERROR;
		case DB_ANY:
			output->set_string_value(&str_val,true);
			return NO_ERROR;
		default:
			assert(false);
			return ErrorManager::error(__HERE__, ER_FAILED);
		}

	case DB_BOOLEAN:
		b_val = this->bool_value();
		
		switch (type) {
		case DB_INTEGER:
			if (b_val)
				output->set_int_value(1);
			else
				output->set_int_value(0);
			return NO_ERROR;
		case DB_FLOAT:
			if (b_val)
				output->set_float_value(1.0);
			else
				output->set_float_value(0.0);
			return NO_ERROR;
		case DB_STRING:
			if (b_val) {
				str_val = "true";
				output->set_string_value(&str_val, true);
			}
			else {
				str_val = "false";
				output->set_string_value(&str_val, true);
			}
			return NO_ERROR;
		case DB_BOOLEAN:
			output->set_bool_value(b_val);
			return NO_ERROR;
		case DB_NUMERIC:
			return ErrorManager::error(__HERE__, ER_CAST_ERROR);
		case DB_ANY:
			output->set_bool_value(b_val);
			return NO_ERROR;
		default:
			assert(false);
			return ErrorManager::error(__HERE__, ER_FAILED);;
		}

	default:
		assert(false);
		return ErrorManager::error(__HERE__, ER_FAILED);
	}

	return NO_ERROR;
}


void DatabaseValue::Clone(const DatabaseValue& value) {
	switch (value.data_type_) {
	case DB_INTEGER:
		this->set_int_value(value.value_.i);
		break;
	case DB_FLOAT:
		this->set_float_value(value.value_.f);
		break;
	case DB_STRING:
		this->set_string_value(value.value_.s, true);
		break;
	case DB_BOOLEAN:
		this->set_bool_value(value.value_.b);
		break;
	case DB_UNKNOWN:
		data_type_ = DB_UNKNOWN;
		need_clear_ = false;
		is_null_ = true;
		value_.s = nullptr;
		break;
	default:
		assert(false);
		break;
	}
}
