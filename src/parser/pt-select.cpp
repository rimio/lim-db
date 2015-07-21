#include "parser\pt-select.hpp"
#include "base\generic-operations.hpp"

//
// PTSelectNode
//

PTSelectNode::~PTSelectNode () {
	// delete select list
	vector_clear_and_delete (*list_);
	delete list_;

	// delete from
	delete from_;
}

std::string PTSelectNode::ToString () {
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

PTSelectRoot::PTSelectRoot (std::vector<ParserNode *>* list,
							PTTableNode* from, yy::location loc) {

	list_ = list;
	from_ = from;

	setLocation (loc);
}

ErrorCode PTSelectRoot::Compile () {
	return NO_ERROR;
}

ErrorCode PTSelectRoot::Prepare () {
	return NO_ERROR;
}

ErrorCode PTSelectRoot::Execute () {
	return NO_ERROR;
}

std::string PTSelectRoot::Print () {
	return ToString ();
}