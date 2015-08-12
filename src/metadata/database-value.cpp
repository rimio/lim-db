#include "metadata\database-value.hpp"
#include "base\error-manager.hpp"
#include "base\generic-operations.hpp"

#include <stdexcept>

#define MACHINE_ERROR 0.0000001

void DatabaseValue::ClearValue(){
	if (need_clear_ && data_type_ == DB_STRING)
		delete value_.s;
}

DatabaseValue::~DatabaseValue() {
	ClearValue();
}

int DatabaseValue::Compare(DatabaseValue arg) {
	DataType common_type = DB_INTEGER;
	if (arg.get_type() == DB_FLOAT || this->get_type() == DB_FLOAT)
		common_type = DB_FLOAT;
	if (arg.get_type() == DB_STRING || this->get_type() == DB_STRING)
		common_type = DB_STRING;

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
		if (arg.int_value() > this->int_value())
			return -1;
		if (arg.int_value() < this->int_value())
			return 1;
		return 0;
		break;
	case DB_FLOAT:
		if (arg.float_value() > this->float_value())
			return -1;
		if (arg.float_value() < this->float_value())
			return 1;
		return 0;
		break;
	case DB_STRING:
		if (arg.string_value() > this->string_value())
			return -1;
		if (arg.string_value() < this->string_value())
			return 1;
		return 0;
		break;
	default:
		break;
	}
}

bool DatabaseValue::operator<(const DatabaseValue& value) {
	int result = Compare(value);
	if (result == -1) return true;
	return false;
}

bool DatabaseValue::operator>(const DatabaseValue& value) {
	int result = Compare(value);
	if (result == 1) return true;
	return false;
}

bool DatabaseValue::operator>=(const DatabaseValue& value) {
	int result = Compare(value);
	if (result == -1) return false;
	return true;
}

bool DatabaseValue::operator<=(const DatabaseValue& value) {
	int result = Compare(value);
	if (result == 1) return false;
	return true;
}

bool DatabaseValue::operator==(const DatabaseValue& value) {
	int result = Compare(value);
	if (result == 0) return true;
	return false;
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
		value_.b = (val == 1) ? true : false;
		return new_ptr;
	default:
		break;
	}
}

void DatabaseValue::set_int_value(INT32 value) {
	need_clear_ = true;
	ClearValue();
	data_type_ = DB_INTEGER;
	value_.i = value;
}

void DatabaseValue::set_float_value(float value) {
	need_clear_ = true;
	ClearValue();
	data_type_ = DB_FLOAT;
	value_.f = value;
}

void DatabaseValue::set_string_value(std::string value) {
	data_type_ = DB_STRING;
	value_.s = new std::string(value);
	int i = 2;
}

void DatabaseValue::set_bool_value(bool value) {
	need_clear_ = true;
	ClearValue();
	data_type_ = DB_BOOLEAN;
	value_.b = value;
}

ErrorCode DatabaseValue::Cast(DataType type) {
	INT32 int_val;
	float fl_val;
	std::string str_val;
	bool b_val;

	switch (this->get_type()) {
	case DB_INTEGER:
		int_val = value_.i;

		switch (type) {
		case DB_INTEGER:
			return NO_ERROR;
			break;
		case DB_FLOAT:
			fl_val = (float)int_val;
			this->set_float_value(fl_val);
			return NO_ERROR;
			break;
		case DB_STRING:
			str_val = std::to_string(int_val);
			this->set_string_value(str_val);
			return NO_ERROR;
			break;
		case DB_BOOLEAN:
			b_val = (int_val == 0) ? false : true;
			this->set_bool_value(b_val);
			return NO_ERROR;
			break;
		case DB_NUMERIC:
			return NO_ERROR;
			break;
		case DB_ANY:
			return NO_ERROR;
			break;
		default:
			return ErrorManager::error(__HERE__, ER_CAST_UNEXPECTED);
			break;
		}

		break;

	case DB_FLOAT:
		fl_val = this->float_value();

		switch (type) {
		case DB_INTEGER:
			int_val = (INT32)fl_val;
			if (fabs(fl_val - int_val) > MACHINE_ERROR)
				return ErrorManager::error(__HERE__, ER_COLUMN_AND_VALUE_TYPE_MISMATCH);
			this->set_int_value(int_val);
			return NO_ERROR;
			break;
		case DB_FLOAT:
			return NO_ERROR;
			break;
		case DB_STRING:
			str_val = std::to_string(fl_val);
			this->set_string_value(str_val);
			return NO_ERROR;
			break;
		case DB_BOOLEAN:
			b_val = (abs(fl_val) < MACHINE_ERROR) ? false : true;
			this->set_bool_value(b_val);
			return NO_ERROR;
			break;
		case DB_NUMERIC:
			return NO_ERROR;
			break;
		case DB_ANY:
			return NO_ERROR;
			break;
		default:
			return ErrorManager::error(__HERE__, ER_CAST_UNEXPECTED);
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
				return ErrorManager::error(__HERE__, ER_COLUMN_AND_VALUE_TYPE_MISMATCH);
			}
			// Check if the string was containg nothing else after the converted int
			if (str_val.substr(after) != "")
				return ErrorManager::error(__HERE__, ER_COLUMN_AND_VALUE_TYPE_MISMATCH);

			this->set_int_value(int_val);
			return NO_ERROR;
			break;
		case DB_FLOAT:
			// Try to convert from string to float
			try {
				fl_val = std::stof(str_val, &after);
			}
			catch (const std::exception &e) {
				return ErrorManager::error(__HERE__, ER_COLUMN_AND_VALUE_TYPE_MISMATCH);
			}
			// Check if the string was containg nothing else after the converted float
			if (str_val.substr(after) != "")
				return ErrorManager::error(__HERE__, ER_COLUMN_AND_VALUE_TYPE_MISMATCH);

			this->set_float_value(fl_val);
			return NO_ERROR;
			break;
		case DB_STRING:
			return NO_ERROR;
			break;
		case DB_BOOLEAN:
			STRING_TO_LOWER(str_val);
			if (str_val == "true") {
				this->set_bool_value(true);
				return NO_ERROR;
			}

			if (str_val == "false") {
				this->set_bool_value(false);
				return NO_ERROR;
			}

			// Check if the string is an integer value that can be therefore converted to bool
			conv_ok = true;
			try {
				int_val = std::stoi(str_val, &after);
			}
			catch (const std::exception &e) {
				conv_ok = false;
			}
			// Check if the string was containg nothing else after the converted int
			if (str_val.substr(after) == "" && conv_ok) {
				b_val = (int_val == 0) ? false : true;
				this->set_bool_value(b_val);
				return NO_ERROR;
			}

			// Check if the string is a float value that can be therefore converted to bool
			conv_ok = true;
			try {
				fl_val = std::stof(str_val, &after);
			}
			catch (const std::exception &e) {
				conv_ok = false;
			}
			// Check is the string was containg nothing else after the converted float
			if (str_val.substr(after) == "" && conv_ok) {
				b_val = (abs(fl_val) < MACHINE_ERROR) ? false : true;
				this->set_bool_value(b_val);
				return NO_ERROR;
			}

			// No conversion from string to bool was possible
			return ErrorManager::error(__HERE__, ER_COLUMN_AND_VALUE_TYPE_MISMATCH);
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
				this->set_int_value(int_val);
				return NO_ERROR;
			}

			// Try to convert from string to float
			try {
				fl_val = std::stof(str_val, &after);
			}
			catch (const std::exception &e) {
				return ErrorManager::error(__HERE__, ER_COLUMN_AND_VALUE_TYPE_MISMATCH);
			}
			// Check if the string was containg nothing else after the converted float
			if (str_val.substr(after) != "")
				return ErrorManager::error(__HERE__, ER_COLUMN_AND_VALUE_TYPE_MISMATCH);

			this->set_float_value(fl_val);
			return NO_ERROR;
			break;
		case DB_ANY:
			return NO_ERROR;
			break;
		default:
			return ErrorManager::error(__HERE__, ER_CAST_UNEXPECTED);
			break;
		}

		break;

	case DB_BOOLEAN:
		b_val = this->bool_value();

		switch (type) {
		case DB_INTEGER:
			if (b_val)
				this->set_int_value(1);
			else
				this->set_int_value(0);
			return NO_ERROR;
			break;
		case DB_FLOAT:
			if (b_val)
				this->set_float_value(1.0);
			else
				this->set_float_value(0.0);
			return NO_ERROR;
			break;
		case DB_STRING:
			if (b_val)
				this->set_string_value("true");
			else
				this->set_string_value("false");
			return NO_ERROR;
			break;
		case DB_BOOLEAN:
			return NO_ERROR;
			break;
		case DB_NUMERIC:
			return ErrorManager::error(__HERE__, ER_COLUMN_AND_VALUE_TYPE_MISMATCH);
			break;
		case DB_ANY:
			return NO_ERROR;
			break;
		default:
			return ErrorManager::error(__HERE__, ER_CAST_UNEXPECTED);
			break;
		}

		break;

	default:
		return ErrorManager::error(__HERE__, ER_CAST_UNEXPECTED);
		break;
	}

	return NO_ERROR;
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
			output->set_string_value(str_val);
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
			return ErrorManager::error(__HERE__, ER_CAST_UNEXPECTED);
			break;
		}

		break;

	case DB_FLOAT:
		fl_val = this->float_value();

		switch (type) {
		case DB_INTEGER:
			int_val = (INT32)fl_val;
			if (fabs(fl_val - int_val) > MACHINE_ERROR)
				return ErrorManager::error(__HERE__, ER_VALUE_CAST_IMPOSSIBLE);
			output->set_int_value(int_val);
			return NO_ERROR;
			break;
		case DB_FLOAT:
			output->set_float_value(fl_val);
			return NO_ERROR;
			break;
		case DB_STRING:
			str_val = std::to_string(fl_val);
			output->set_string_value(str_val);
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
			return ErrorManager::error(__HERE__, ER_CAST_UNEXPECTED);
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
				return ErrorManager::error(__HERE__, ER_VALUE_CAST_IMPOSSIBLE);
			}
			// Check if the string was containg nothing else after the converted int
			if (str_val.substr(after) != "")
				return ErrorManager::error(__HERE__, ER_VALUE_CAST_IMPOSSIBLE);

			output->set_int_value(int_val);
			return NO_ERROR;
			break;
		case DB_FLOAT:
			// Try to convert from string to float
			try {
				fl_val = std::stof(str_val, &after);
			}
			catch (const std::exception &e) {
				return ErrorManager::error(__HERE__, ER_VALUE_CAST_IMPOSSIBLE);
			}
			// Check if the string was containg nothing else after the converted float
			if (str_val.substr(after) != "")
				return ErrorManager::error(__HERE__, ER_VALUE_CAST_IMPOSSIBLE);

			output->set_float_value(fl_val);
			return NO_ERROR;
			break;
		case DB_STRING:
			output->set_string_value(str_val);
			return NO_ERROR;
			break;
		case DB_BOOLEAN:
			STRING_TO_LOWER(str_val);
			if (str_val == "true") {
				output->set_bool_value(true);
				return NO_ERROR;
			}

			if (str_val == "false") {
				output->set_bool_value(false);
				return NO_ERROR;
			}

			// Check if the string is an integer value that can be therefore converted to bool
			conv_ok = true;
			try {
				int_val = std::stoi(str_val, &after);
			}
			catch (const std::exception &e) {
				conv_ok = false;
			}
			// Check if the string was containg nothing else after the converted int
			if (str_val.substr(after) == "" && conv_ok) {
				b_val = (int_val == 0) ? false : true;
				output->set_bool_value(b_val);
				return NO_ERROR;
			}

			// Check if the string is a float value that can be therefore converted to bool
			conv_ok = true;
			try {
				fl_val = std::stof(str_val, &after);
			}
			catch (const std::exception &e) {
				conv_ok = false;
			}
			// Check is the string was containg nothing else after the converted float
			if (str_val.substr(after) == "" && conv_ok) {
				b_val = (abs(fl_val) < MACHINE_ERROR) ? false : true;
				output->set_bool_value(b_val);
				return NO_ERROR;
			}

			// No conversion from string to bool was possible
			return ErrorManager::error(__HERE__, ER_VALUE_CAST_IMPOSSIBLE);
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
				return ErrorManager::error(__HERE__, ER_VALUE_CAST_IMPOSSIBLE);
			}
			// Check if the string was containg nothing else after the converted float
			if (str_val.substr(after) != "")
				return ErrorManager::error(__HERE__, ER_VALUE_CAST_IMPOSSIBLE);

			output->set_float_value(fl_val);
			return NO_ERROR;
			break;
		case DB_ANY:
			(*output).set_string_value(str_val);
			return NO_ERROR;
			break;
		default:
			return ErrorManager::error(__HERE__, ER_CAST_UNEXPECTED);
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
			if (b_val)
				output->set_string_value("true");
			else
				output->set_string_value("false");
			return NO_ERROR;
			break;
		case DB_BOOLEAN:
			output->set_bool_value(b_val);
			return NO_ERROR;
		case DB_NUMERIC:
			return ErrorManager::error(__HERE__, ER_VALUE_CAST_IMPOSSIBLE);
			break;
		case DB_ANY:
			output->set_bool_value(b_val);
			return NO_ERROR;
			break;
		default:
			return ErrorManager::error(__HERE__, ER_CAST_UNEXPECTED);
			break;
		}

		break;

	default:
		return ErrorManager::error(__HERE__, ER_CAST_UNEXPECTED);
		break;
	}

	return NO_ERROR;
}