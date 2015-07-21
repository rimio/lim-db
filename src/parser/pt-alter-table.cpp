#include "parser\pt-alter-table.hpp"

PTAlterTableRoot::~PTAlterTableRoot () {
}

std::string PTAlterTableRoot::Print () {
	return std::string ("ALTER TABLE");
}

ErrorCode PTAlterTableRoot::Compile () {
	return NO_ERROR;
}

ErrorCode PTAlterTableRoot::Execute () {
	return NO_ERROR;
}