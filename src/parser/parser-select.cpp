#include "parser\parser-select.hpp"
#include "base\generic-operations.hpp"

//
// PTSelectNode
//

ParserSelect::~ParserSelect () {
	// delete select list
	if (list_ != nullptr && list_ != NULL)
		vector_clear_and_delete (*list_);

	if (list_ != nullptr && list_ != NULL)
		delete list_;

	// delete from
	if (from_ != nullptr && list_ != NULL)
		delete from_;
}

std::string ParserSelect::ToString () {
	std::string to_string = std::string ("SELECT ");

	bool first_item = true;
	if (list_ != nullptr) {
		for (auto item = list_->begin (); item != list_->end (); ++item) {
			if (!first_item) {
				to_string += ", ";
			}
			first_item = false;

			to_string += (*item)->ToString ();
		}
	}

	to_string += "FROM ";
	to_string += from_->ToString ();

	return to_string;
}

void ParserSelect::GetChildren (std::vector<ParserNode *>* children) {
	// Add select list
	for (auto item = list_->begin (); item != list_->end (); ++item) {
		children->push_back (*item);
	}

	// Add from_
	children->push_back (from_);
}

//
// PTSelectRoot
//

ParserSelectStatement::ParserSelectStatement (std::vector<ParserNode *>* list,
											  ParserTable* from, yy::location loc) {

	list_ = list;
	from_ = from;

	setLocation (loc);
}

ErrorCode ParserSelectStatement::Compile () {
	return NO_ERROR;
}

ErrorCode ParserSelectStatement::Prepare () {
	return NO_ERROR;
}

ErrorCode ParserSelectStatement::Execute () {
	return NO_ERROR;
}

std::string ParserSelectStatement::Print () {
	return ToString ();
}