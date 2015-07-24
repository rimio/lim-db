#ifndef PARSER_ROOT_HPP_
#define PARSER_ROOT_HPP_

#include "base\error-codes.hpp"

class ParserRoot {
public:
	virtual ~ParserRoot () {}

	virtual ErrorCode Process() final;
	virtual std::string Print() = 0;

protected:
	ParserRoot () {}

	virtual ErrorCode Compile() = 0;
	virtual ErrorCode Prepare() = 0;
	virtual ErrorCode Execute() = 0;
};

#endif // PARSER_ROOT_HPP_