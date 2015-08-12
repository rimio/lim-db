#include "parser\expression\parser-expression-compare.hpp"

#include <cassert>

#include "metadata\database-value.hpp"
#include "parser\parser-value.hpp"

#define MACHINE_ERROR 0.0000001

ParserExpressionCompare::ParserExpressionCompare (
		std::vector<ParserNode*>* arguments,
		CompareOperators compare_op) {
	assert (arguments != NULL);
	assert (arguments->size () == 2);

	arguments_ = arguments;
	op_ = compare_op;
}

ErrorCode ParserExpressionCompare::TypeCheckPre(TypeCheckArg* arg, bool* stop_walk) {
	for (auto arg : *(this->arguments())) {
		arg->set_expected_type(DB_ANY);
	}
	return NO_ERROR;
}

ErrorCode ParserExpressionCompare::ConstantFoldPost() {
	ErrorCode er = NO_ERROR;

	// Get arguments
	std::vector<ParserNode*> children;
	this->GetChildren(&children);

	auto *left_child = children.at(0);
	auto *right_child = children.at(1);

	bool result;

	switch (this->op()) {
	case EQ:
		result = (left_child->computed_value() == right_child->computed_value()) ? true : false;
		break;
	case NOT_EQ:
		result = (left_child->computed_value() == right_child->computed_value()) ? false : true;
		break;
	case LT:
		result = (left_child->computed_value() < right_child->computed_value()) ? true : false;
		break;
	case LT_EQ:
		result = (left_child->computed_value() <= right_child->computed_value()) ? true : false;
		break;
	case GT:
		result = (left_child->computed_value() > right_child->computed_value()) ? true : false;
		break;
	case GT_EQ:
		result = (left_child->computed_value() >= right_child->computed_value()) ? true : false;
		break;
	default:
		break;
	}

	this->set_computed_value((*(new DatabaseValue(result))));

	if (this->computed_value().get_type() != this->ExpectedType()){
		auto aux = this->computed_value();
		er = aux.Cast(this->ExpectedType());
		if (er != NO_ERROR)
			return er;
		this->set_computed_value(aux);
	}

	return er;
}