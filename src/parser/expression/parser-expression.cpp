#include "parser\expression\parser-expression.hpp"

ParserExpression::ParserExpression (std::vector<ParserNode*>* arguments) {
	arguments_ = arguments;
}

ParserExpression::~ParserExpression () {
	if (arguments_ != NULL) {
		delete arguments_;
	}
}

void ParserExpression::GetChildren (std::vector<ParserNode*>* children) {
	if (arguments_ != NULL) {
		for (auto argp = arguments_->begin (); argp != arguments_->end ();
			 ++argp) {
			children->push_back (*argp);
		}
	}
}