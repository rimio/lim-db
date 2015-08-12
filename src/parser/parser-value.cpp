#include "parser-value.hpp"
#include "base\error-manager.hpp"

ErrorCode ParserValue::TypeCheckPre(TypeCheckArg* arg, bool* stop_walk) {
	return NO_ERROR;
}

ErrorCode ParserValue::ConstantFoldPost() {
	ErrorCode er = NO_ERROR;
	DatabaseValue value;
	auto aux = this->value();
	er = aux->Cast(this->ExpectedType(), (&value));
	if (er == NO_ERROR)
		this->set_computed_value(value);
	return er;
}

