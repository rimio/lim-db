#include "parser/parser-node.hpp"
#include "metadata/int-database-value.hpp"
#include "metadata/bool-database-value.hpp"
#include "metadata/float-database-value.hpp"
#include "metadata/string-database-value.hpp"
#include "base/error-manager.hpp"
#include "base/generic-operations.hpp"
#include <stdexcept>

#define MACHINE_ERROR 0.0000001

ParserNode::ParserNode ()
{
	location_.begin.initialize(nullptr, 0, 0);
	location_.end.initialize(nullptr, 0, 0);
}

ParserNode::~ParserNode ()
{
}

// Walker on parse tree. It has a pre-walk function and post-walk function.
// Pre-walk function is called before advancing to node members.
// Post-walk function is called after advanced to node members.
// Walk can be halted with stop_walk argument.
template <class ArgPre, class ArgPost>
ErrorCode ParserNode::ParserWalk (ErrorCode (ParserNode::*pre_func) (ArgPre*, bool*), ArgPre* pre_arg,
								  ErrorCode (ParserNode::*post_func) (ArgPost*, bool*), ArgPost* post_arg) {
	bool stop_walk = false;
	return ParserWalkInternal (pre_func, pre_arg, post_func, post_arg, &stop_walk);
}

ErrorCode ParserNode::ParserWalk (ErrorCode (ParserNode::*pre_func) (void),
								  ErrorCode (ParserNode::*post_func) (void)) {
	return ParserWalkInternal (pre_func, post_func);
}

template <class ArgPre, class ArgPost>
ErrorCode ParserNode::ParserWalkInternal (ErrorCode (ParserNode::*pre_func) (ArgPre*, bool*), ArgPre* pre_arg,
										  ErrorCode (ParserNode::*post_func) (ArgPost*, bool*), ArgPost* post_arg,
										  bool* stop_walk) {
	ErrorCode error_code = NO_ERROR;
	std::vector<ParserNode *> children;

	error_code = (this->*pre_func) (pre_arg, stop_walk);
	if (error_code != NO_ERROR || *stop_walk)
		return error_code;

	GetChildren (&children);
	for (auto child = children.begin (); child != children.end (); ++child) {
		error_code = (*child)->ParserWalkInternal (pre_func, pre_arg, post_func, post_arg, stop_walk);
		if (error_code != NO_ERROR || *stop_walk)
			return error_code;
	}

	return (this->*post_func) (post_arg, stop_walk);
}

ErrorCode ParserNode::ParserWalkInternal (ErrorCode (ParserNode::*pre_func) (),
										  ErrorCode (ParserNode::*post_func) ()) {
	ErrorCode error_code = NO_ERROR;
	std::vector<ParserNode *> children;

	error_code = (this->*pre_func) ();
	if (error_code != NO_ERROR)
		return error_code;

	GetChildren (&children);
	for (auto child = children.begin (); child != children.end (); ++child) {
		error_code = (*child)->ParserWalkInternal (pre_func, post_func);
		if (error_code != NO_ERROR)
			return error_code;
	}

	return (this->*post_func) ();
}

ErrorCode ParserNode::NameResolve() {
	NameResolveArg arg;

	return ParserWalk(&ParserNode::NameResolvePre, &arg, &ParserNode::NameResolvePost, &arg);
}

ErrorCode ParserNode::TypeCheck() {
	TypeCheckArg arg;

	return ParserWalk(&ParserNode::TypeCheckPre, &arg, &ParserNode::TypeCheckPost, &arg);
}

ErrorCode ParserNode::Convert(DataType from, DataType to, DatabaseValue* *val) {
	INT32 int_val;
	float fl_val;
	std::string str_val;
	bool b_val;
	
	// Needs to be freed if val gets a new instance
	auto holder = (*val);

	switch(from) {
	case DB_INTEGER:
		int_val = (*(IntDatabaseValue*)(*val)).get_value();
	
		switch (to) {
		case DB_INTEGER:
			return NO_ERROR;
			break;
		case DB_FLOAT:
			fl_val = (float)int_val;
			(*val) = new FloatDatabaseValue(fl_val);
			delete holder;
			return NO_ERROR;
			break;
		case DB_STRING:
			str_val = std::to_string(int_val);
			(*val) = new StringDatabaseValue(str_val);
			delete holder;
			return NO_ERROR;
			break;
		case DB_BOOLEAN:
			b_val = (int_val == 0) ? false : true;
			(*val) = new BoolDatabaseValue(b_val);
			delete holder;
			return NO_ERROR;
			break;
		default:
			return NO_ERROR;
			break;
		}

		break;

	case DB_FLOAT:
		fl_val = (*(FloatDatabaseValue*)(*val)).get_value();

		switch (to) {
		case DB_INTEGER:
			int_val = (INT32)fl_val;
			if (fabs(fl_val - int_val) > MACHINE_ERROR)
				return ErrorManager::error(__HERE__, ER_COLUMN_AND_VALUE_TYPE_MISMATCH);
			(*val) = new IntDatabaseValue(int_val);
			delete holder;
			return NO_ERROR;
			break;
		case DB_FLOAT:
			return NO_ERROR;
			break;
		case DB_STRING:
			str_val = std::to_string(fl_val);
			(*val) = new StringDatabaseValue(str_val);
			delete holder;
			return NO_ERROR;
			break;
		case DB_BOOLEAN:
			b_val = (abs(fl_val) < MACHINE_ERROR) ? false : true;
			(*val) = new BoolDatabaseValue(b_val);
			delete holder;
			return NO_ERROR;
			break;
		default:
			return NO_ERROR;
			break;
		}

		break;
	
	case DB_STRING:
		str_val = (*(StringDatabaseValue*)(*val)).get_value();
		std::string::size_type after; 
		bool conv_ok;

		switch (to) {
		case DB_INTEGER:
			// Try to convert from string to int 
			try {
				int_val = std::stoi(str_val,&after);
			}
			catch (const std::exception &e) {
				return ErrorManager::error(__HERE__, ER_COLUMN_AND_VALUE_TYPE_MISMATCH);
			}
			// Check if the string was containg nothing else after the converted int
			if (str_val.substr(after) != "")
				return ErrorManager::error(__HERE__, ER_COLUMN_AND_VALUE_TYPE_MISMATCH);
			
			(*val) = new IntDatabaseValue(int_val);
			delete holder;
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

			(*val) = new FloatDatabaseValue(fl_val);
			delete holder;
			return NO_ERROR;
			break;
		case DB_STRING:
			return NO_ERROR;
			break;
		case DB_BOOLEAN:
			STRING_TO_LOWER(str_val);
			if (str_val == "true") {
				(*val) = new BoolDatabaseValue(true);
				delete holder;
				return NO_ERROR;
			}
			
			if (str_val == "false") {
				(*val) = new BoolDatabaseValue(false);
				delete holder;
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
				(*val) = new BoolDatabaseValue(b_val);
				delete holder;
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
				(*val) = new BoolDatabaseValue(b_val);
				delete holder;
				return NO_ERROR;
			}

			// No conversion from string to bool was possible
			return ErrorManager::error(__HERE__, ER_COLUMN_AND_VALUE_TYPE_MISMATCH);
			break;
		default:
			bool conv_ok;
			return NO_ERROR;
			break;
		}

		break;

	case DB_BOOLEAN:
		b_val = (*(BoolDatabaseValue*)(*val)).get_value();

		switch (to) {
		case DB_INTEGER:
			if (b_val)
				(*val) = new IntDatabaseValue(1);
			else
				(*val) = new IntDatabaseValue(0);
			delete holder;
			return NO_ERROR;
			break;
		case DB_FLOAT:
			if (b_val)
				(*val) = new FloatDatabaseValue(1.0);
			else
				(*val) = new FloatDatabaseValue(0.0);
			delete holder;
			return NO_ERROR;
			break;
		case DB_STRING:
			if (b_val)
				(*val) = new StringDatabaseValue("true");
			else
				(*val) = new StringDatabaseValue("false");
			delete holder;
			return NO_ERROR;
			break;
		case DB_BOOLEAN:
			return NO_ERROR;
			break;
		default:
			return NO_ERROR;
			break;
		}

		break;

	default:
		return NO_ERROR;
		break;
	}

	return NO_ERROR;
}