#ifndef IDENTIFIER_NODE_HPP_
#define IDENTIFIER_NODE_HPP_

#include "parser/parser-node.hpp"

//
// Identifier node types
//
typedef enum
{
	PT_IDENTIFIER_TABLE,
	PT_IDENTIFIER_COLUMN,
	PT_IDENTIFIER_INDEX
} IdentifierType;

//
// Base identifier node
//
class IdentifierNode : public virtual ParserNode
{
private:
protected:
	// The identifier name
	std::string name_;

	// Hidden constructors
	IdentifierNode () { };
	IdentifierNode (std::string name) : name_ (name) { };

public:
	// Implementation of pure virtual functions
	virtual ParserNodeType getNodeType () const { return PT_IDENTIFIER; };
	virtual std::string print () { return toString (); };

	// Returns the identifier type
	virtual IdentifierType getIdentifierType () const = 0;
};

//
// Table identifier node
//
class TableIdentifierNode : public IdentifierNode
{
private:
protected:
	// Hidden default constructor
	TableIdentifierNode () { };

public:
	// Constructor
	TableIdentifierNode (std::string name) : IdentifierNode (name) { };

	// Implementation of pure virtual functions
	virtual std::string toString () { return name_; };
	virtual IdentifierType getIdentifierType () const { return PT_IDENTIFIER_TABLE; };
};

//
// Column identifier node
//
class ColumnIdentifierNode : public IdentifierNode, public virtual TypedParserNode
{
private:
protected:
	// Identifier's data type
	DataType data_type_;

	// The identifier's table
	std::string table_;

	// Hidden default constructor
	ColumnIdentifierNode () { };

public:
	// Ambiguous constructor
	ColumnIdentifierNode (std::string name) : IdentifierNode (name), table_ (""), data_type_ (DB_UNKNOWN) { };

	// Exact constructor
	ColumnIdentifierNode (std::string table, std::string name) : IdentifierNode (name), table_ (table), data_type_ (DB_UNKNOWN) { };

	// Implementation of pure virtual functions
	virtual std::string toString () { return table_ + "." + name_; };
	virtual IdentifierType getIdentifierType () const { return PT_IDENTIFIER_COLUMN; };
	virtual DataType getDataType () const { return data_type_; };
	//ColumnIdentifierNode getNext() { return *dynamic_cast< ColumnIdentifierNode*>(next_) ; }
	
	// Setter for data type
	void setDataType (DataType data_type) { data_type_ = data_type; };
};

//
// Index identifier node
//
class IndexIdentifierNode : public IdentifierNode
{
private:
protected:
	// The identifier's table
	std::string table_;

	// Hidden default constructor
	IndexIdentifierNode () { };

public:
	// Ambiguous constructor
	IndexIdentifierNode (std::string name) : IdentifierNode (name), table_ ("") { };

	// Exact constructor
	IndexIdentifierNode (std::string table, std::string name) : IdentifierNode (name), table_ (table) { };

	// Implementation of pure virtual functions
	virtual std::string toString () { return table_ + "." + name_; };
	virtual IdentifierType getIdentifierType () const { return PT_IDENTIFIER_INDEX; };
};

#endif