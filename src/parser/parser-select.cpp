#include "parser\parser-select.hpp"
#include "base\generic-operations.hpp"

//
// PTSelectNode
//

ParserSelect::~ParserSelect () {
	// delete select list
	vector_clear_and_delete (*list_);
	delete list_;

	// delete from
	delete from_;
}

std::string ParserSelect::ToString () {
	std::string to_string = std::string ("SELECT ");

	bool first_item = true;
	for (auto item = list_->begin (); item != list_->end (); ++item) {
		if (!first_item) {
			to_string += ", ";
		}
		first_item = false;

		to_string += (*item)->ToString ();
	}

	to_string += "FROM ";
	to_string += from_->ToString ();

	return to_string;
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