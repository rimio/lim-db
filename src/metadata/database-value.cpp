#include "metadata\database-value.hpp"
#include "base\error-manager.hpp"
#include "base\generic-operations.hpp"

#include <stdexcept>

void DatabaseValue::ClearValue(){
	if (data_type_ == DB_STRING && need_clear_) {
		assert(value_.s != nullptr);
		delete value_.s;
		value_.s = nullptr;
	}
	need_clear_ = false;
}

DatabaseValue::~DatabaseValue() {
	ClearValue();
}

int DatabaseValue::Compare(DatabaseValue arg) {
	DataType common_type = CommonType(arg.get_type(), this->get_type());

	if (arg.get_type() != common_type)
		arg.Cast(common_type);
	if (this->get_type() != common_type)
		this->Cast(common_type);
	
	// result = 1 if this > arg
	// result = 0 if this = arg
	// result = -1 if this < arg
	switch (common_type)
	{
	case DB_INTEGER:
		return this->int_value() - arg.int_value();
		break;
	case DB_FLOAT:
		if (fabs(this->float_value() - arg.float_value()) < MACHINE_ERROR) 
			return 0;
		return this->float_value() - arg.float_value();
		break;
	case DB_STRING:
		return this->string_value().compare(arg.string_value());
		break;
	default:
		assert(false);
		return ER_FAILED;
		break;
	}
}

bool DatabaseValue::operator<(const DatabaseValue& value) {
	int result = Compare(value);
	if (result < 0) return true;
	return false;
}

bool DatabaseValue::operator>(const DatabaseValue& value) {
	int result = Compare(value);
	if (result > 0) return true;
	return false;
}

bool DatabaseValue::operator>=(const DatabaseValue& value) {
	int result = Compare(value);
	if (result < 0) return false;
	return true;
}

bool DatabaseValue::operator<=(const DatabaseValue& value) {
	int result = Compare(value);
	if (result > 0) return false;
	return true;
}

bool DatabaseValue::operator==(const DatabaseValue& value) {
	int result = Compare(value);
	if (result == 0) return true;
	return false;
}

ErrorCode DatabaseValue::Compute(DatabaseValue left, DatabaseValue right, ArithmeticOperators op, DatabaseValue* result) {
	ErrorCode er = NO_ERROR;
	// Holds which is the broadest type of the result
	DataType dominant_type = (left.get_type() == DB_INTEGER
		&& right.get_type() == DB_INTEGER) ? DB_INTEGER : DB_FLOAT;

	if (left.get_type() != dominant_type) {
		er = left.Cast(dominant_type);
		if (er != NO_ERROR)
			return er;
	}

	if (right.get_type() != dominant_type) {
		er = right.Cast(dominant_type);
		if (er != NO_ERROR)
			return er;
	}

	// Compute the result
	// Whatever the operator between numbers, we can consider a plus sign in front of the first one
	INT32 iresult;
	float fresult;

	switch (dominant_type) {
	case DB_INTEGER:
		iresult = left.int_value();
		switch (op) {
		case PLUS:
			iresult += right.int_value();
			break;
		case MINUS:
			iresult -= right.int_value();
			break;
		case MULTIPLY:
			iresult *= right.int_value();
			break;
		case DIVIDE:
			iresult /= right.int_value();
			break;
		case MODULO:
			iresult %= right.int_value();
			break;
		default:
			assert(false);
			return ER_FAILED;
			break;
		}
		*result = DatabaseValue(iresult);
		break;
	case DB_FLOAT:
		fresult = left.float_value();
		switch (op) {
		case PLUS:
			fresult += right.float_value();
			break;
		case MINUS:
			fresult -= right.float_value();
			break;
		case MULTIPLY:
			fresult *= right.float_value();
			break;
		case DIVIDE:
			fresult /= right.float_value();
			break;
		case MODULO:
			return ErrorManager::error(__HERE__, ER_ARITHMETIC_COMPUTATION_MOD);
			break;
		default:
			assert(false);
			return ER_FAILED;
			break;
		}
		*result = DatabaseValue(fresult);
		break;
	default:
		assert(false);
		return ER_FAILED;
		break;
	}
	
	return er;
}

DatabaseValue DatabaseValue::operator=(const DatabaseValue& value) {
	if (this != &value) {
		this->data_type_ = value.data_type_;
		this->value_ = value.value_;
		this->need_clear_ = false;
	}
	return *this;
}

DatabaseValue DatabaseValue::operator+(const DatabaseValue& value) {
	DatabaseValue result;
	ErrorCode er = Compute(*this, value, PLUS, &result);
	if (er != NO_ERROR)
		result.set_type(DB_ERROR);
	return result;
}

DatabaseValue DatabaseValue::operator-(const DatabaseValue& value) {
	DatabaseValue result;
	ErrorCode er = Compute(*this, value, MINUS, &result);
	if (er != NO_ERROR)
		result.set_type(DB_ERROR);
	return result;
}

DatabaseValue DatabaseValue::operator*(const DatabaseValue& value) {
	DatabaseValue result;
	ErrorCode er = Compute(*this, value, MULTIPLY, &result);
	if (er != NO_ERROR)
		result.set_type(DB_ERROR);
	return result;
}

DatabaseValue DatabaseValue::operator/(const DatabaseValue& value) {
	DatabaseValue result;
	ErrorCode er = Compute(*this, value, DIVIDE, &result);
	if (er != NO_ERROR)
		result.set_type(DB_ERROR);
	return result;
}

DatabaseValue DatabaseValue::operator%(const DatabaseValue& value) {
	DatabaseValue result;
	ErrorCode er = Compute(*this, value, MODULO, &result);
	if (er != NO_ERROR)
		result.set_type(DB_ERROR);
	return result;
}


BYTE* DatabaseValue::Serialize(BYTE* ptr) {
	switch (data_type_) {
	case DB_INTEGER:
		return Serializable::SerializeInt(value_.i, ptr);
		break;
	case DB_FLOAT:
		return Serializable::SerializeFloat(value_.f, ptr);
		break;
	case DB_STRING:
		return Serializable::SerializeString((*value_.s), ptr);
		break;
	case DB_BOOLEAN:
		if (value_.b)
			return Serializable::SerializeInt(1, ptr);
		return Serializable::SerializeInt(0, ptr);
		break;
	default:
		break;
	}
}

BYTE* DatabaseValue::Deserialize(BYTE* ptr) {
	switch (data_type_) {
	case DB_INTEGER:
		return Serializable::DeserializeInt(ptr, &value_.i);
		break;
	case DB_FLOAT:
		return Serializable::DeserializeFloat(ptr, &value_.f);
		break;
	case DB_STRING:
		return Serializable::DeserializeString(ptr, value_.s);
		break;
	case DB_BOOLEAN:
		INT32 val;
		BYTE* new_ptr;
		new_ptr = Serializable::DeserializeInt(ptr, &val);
		assert(val == 1 || val == 0);
		value_.b = (val == 1) ? true : false;
		return new_ptr;
	default:
		break;
	}
}

void DatabaseValue::set_int_value(INT32 value) {
	ClearValue();
	data_type_ = DB_INTEGER;
	value_.i = value;
}

void DatabaseValue::set_float_value(float value) {
	ClearValue();
	data_type_ = DB_FLOAT;
	value_.f = value;
}

void DatabaseValue::set_string_value(std::string* value, bool copy) {
	ClearValue();
	data_type_ = DB_STRING;
	if (copy) {
		value_.s = new std::string(*value);
	}
	else {
		value_.s = value;
	}
	need_clear_ = copy;
}

void DatabaseValue::set_bool_value(bool value) {
	ClearValue();
	data_type_ = DB_BOOLEAN;
	value_.b = value;
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
			break;
		case DB_FLOAT:
			fl_val = (float)int_val;
			output->set_float_value(fl_val);
			return NO_ERROR;
			break;
		case DB_STRING:
			str_val = std::to_string(int_val);
			output->set_string_value(&str_val,true);
			return NO_ERROR;
			break;
		case DB_BOOLEAN:
			b_val = (int_val == 0) ? false : true;
			output->set_bool_value(b_val);
			return NO_ERROR;
			break;
		case DB_NUMERIC:
			output->set_int_value(int_val);
			return NO_ERROR;
			break;
		case DB_ANY:
			output->set_int_value(int_val);
			return NO_ERROR;
			break;
		default:
			assert(false);
			return ER_FAILED;
			break;
		}

		break;

	case DB_FLOAT:
		fl_val = this->float_value();

		switch (type) {
		case DB_INTEGER:
			int_val = (INT32)fl_val;
			output->set_int_value(int_val);
			return NO_ERROR;
			break;
		case DB_FLOAT:
			output->set_float_value(fl_val);
			return NO_ERROR;
			break;
		case DB_STRING:
			str_val = std::to_string(fl_val);
			output->set_string_value(&str_val,true);
			return NO_ERROR;
			break;
		case DB_BOOLEAN:
			b_val = (abs(fl_val) < MACHINE_ERROR) ? false : true;
			output->set_bool_value(b_val);
			return NO_ERROR;
			break;
		case DB_NUMERIC:
			output->set_float_value(fl_val);
			return NO_ERROR;
			break;
		case DB_ANY:
			output->set_float_value(fl_val);
			return NO_ERROR;
			break;
		default:
			assert(false);
			return ER_FAILED;
			break;
		}

		break;

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
			break;
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
			break;
		case DB_STRING:
			output->set_string_value(&str_val,true);
			return NO_ERROR;
			break;
		case DB_BOOLEAN:
			return ErrorManager::error(__HERE__, ER_CAST_ERROR);
			break;
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
			break;
		case DB_ANY:
			output->set_string_value(&str_val,true);
			return NO_ERROR;
			break;
		default:
			assert(false);
			return ErrorManager::error(__HERE__, ER_FAILED);
			break;
		}

		break;

	case DB_BOOLEAN:
		b_val = this->bool_value();
		
		switch (type) {
		case DB_INTEGER:
			if (b_val)
				output->set_int_value(1);
			else
				output->set_int_value(0);
			return NO_ERROR;
			break;
		case DB_FLOAT:
			if (b_val)
				output->set_float_value(1.0);
			else
				output->set_float_value(0.0);
			return NO_ERROR;
			break;
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
			break;
		case DB_BOOLEAN:
			output->set_bool_value(b_val);
			return NO_ERROR;
		case DB_NUMERIC:
			return ErrorManager::error(__HERE__, ER_CAST_ERROR);
			break;
		case DB_ANY:
			output->set_bool_value(b_val);
			return NO_ERROR;
			break;
		default:
			assert(false);
			return ErrorManager::error(__HERE__, ER_FAILED);;
			break;
		}

		break;

	default:
		assert(false);
		return ErrorManager::error(__HERE__, ER_FAILED);
		break;
	}

	return NO_ERROR;
}

DatabaseValue::DatabaseValue(const DatabaseValue& value) {
	switch (value.data_type_) {
	case DB_INTEGER:
		this->set_int_value(value.value_.i);
		break;
	case DB_FLOAT:
		this->set_float_value(value.value_.f);
		break;
	case DB_STRING:
		this->set_string_value(value.value_.s,true);
		break;
	case DB_BOOLEAN:
		this->set_bool_value(value.value_.b);
		break;
	default:
		assert(false);
		break;
	}
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
	default:
		assert(false);
		break;
	}
}