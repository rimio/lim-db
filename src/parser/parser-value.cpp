#include "parser-value.hpp"
#include "base\error-manager.hpp"

ErrorCode ParserValue::TypeCheckPre(TypeCheckArg* arg, bool* stop_walk) {
	set_expected_type(value_->get_type());
	
	return NO_ERROR;
}

ErrorCode ParserValue::Compute(DataType expected_type, ParserNode* *value) {
	ErrorCode er = NO_ERROR;
	if (expected_type != DB_ANY) {
		DatabaseValue* val = ((ParserValue*)(*value))->value();
		er = Convert(((ParserValue*)(*value))->value()->get_type(), expected_type, &val);
		if (er == NO_ERROR)
			((ParserValue*)(*value))->set_value(val);
	}
	return er;
}
