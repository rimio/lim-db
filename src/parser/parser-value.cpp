#include "parser-value.hpp"
#include "base\error-manager.hpp"

ErrorCode ParserValue::TypeCheckPre(TypeCheckArg* arg, bool* stop_walk) {
	return NO_ERROR;
}

ErrorCode ParserValue::ConstantFoldPost() {
	if (this->value()->is_null()) {
		this->set_computed_value(DatabaseValue());
		return NO_ERROR; 
	}

	ErrorCode er = NO_ERROR;
	DatabaseValue value;
	er = this->value()->Cast(this->ExpectedType(), (&value));
	if (er == NO_ERROR) {
		this->set_computed_value(value);
	}
	return er;
}

