#ifndef STATEMENT_NODE_HPP_
#define STATEMENT_NODE_HPP_

#include "parser/parser-node.hpp"
#include "parser/identifier-node.hpp"

//
// Statement types
//
typedef enum
{
	PT_STATEMENT_SELECT,
	PT_STATEMENT_INSERT,
	PT_STATEMENT_DELETE,
	PT_STATEMENT_UPDATE,
	PT_STATEMENT_CREATE_TABLE,
	PT_STATEMENT_CREATE_INDEX,
	PT_STATEMENT_DROP_TABLE,
	PT_STATEMENT_DROP_INDEX
} StatementType;

//
// Base class for all statement nodes
//
class StatementNode : public ParserNode
{
private:
protected:
	// Hidden constructor
	StatementNode () { };

public:
	// Implementation of pure virtual functions
	virtual ParserNodeType getNodeType () const { return PT_STATEMENT; };
	
	// Returns the statement type
	virtual StatementType getStatementType () const = 0;
};

// ------------------ Data Manipulation Language Statements ------------------ //

//
// SELECT statement node
//
class SelectStatementNode : public StatementNode
{
private:
protected:
	// The select list
	TypedParserNode *list_;

	// The FROM part
	TableIdentifierNode *from_;

	// Hidden default constructor
	SelectStatementNode () { };

public:
	// Constructor
	SelectStatementNode (TypedParserNode *list, TableIdentifierNode *from) : list_ (list), from_ (from) { };

	// Implementation of pure virtual functions
	virtual std::string toString () { return "SELECT"; };
	virtual std::string print ();
	virtual StatementType getStatementType () const { return PT_STATEMENT_SELECT; };
};

//
// INSERT statement node
//
class InsertStatementNode : public StatementNode
{
private:
protected:
	// Table to insert into
	TableIdentifierNode *table_;

	// Values to insert into table
	TypedParserNode *values_;

	// Hidden constructor
	InsertStatementNode () { };

public:
	InsertStatementNode (TableIdentifierNode *table, TypedParserNode *values) : table_ (table), values_ (values) { };

	// Implementation of pure virtual functions
	virtual std::string toString () { return "INSERT"; };
	virtual std::string print ();
	virtual StatementType getStatementType () const { return PT_STATEMENT_INSERT; };
};

//
// DELETE statement node
//
class DeleteStatementNode : public StatementNode
{
private:
protected:
public:
	// Implementation of pure virtual functions
	virtual std::string toString () { return "DELETE"; };
	virtual std::string print ();
	virtual StatementType getStatementType () const { return PT_STATEMENT_DELETE; };
};

//
// UPDATE statement node
//
class UpdateStatementNode : public StatementNode
{
private:
protected:
public:
	// Implementation of pure virtual functions
	virtual std::string toString () { return "UPDATE"; };
	virtual std::string print ();
	virtual StatementType getStatementType () const { return PT_STATEMENT_UPDATE; };
};

// ------------------- Data Definition Language Statements ------------------- //

//
// CREATE TABLE statement node
//
class CreateTableStatementNode : public StatementNode
{
private:
protected:
	// Table identifier for new table
	TableIdentifierNode *table_;

	// Column definition
	ColumnIdentifierNode *definition_;

	// Hidden constructor
	CreateTableStatementNode () { };
public:
	CreateTableStatementNode (TableIdentifierNode *table, ColumnIdentifierNode *def) : table_ (table), definition_ (def) { };

	// Implementation of pure virtual functions
	virtual std::string toString () { return "CREATE TABLE"; };
	virtual std::string print ();
	virtual StatementType getStatementType () const { return PT_STATEMENT_CREATE_TABLE; };

	bool compile();
	bool execute();
};

//
// CREATE INDEX statement node
//
class CreateIndexStatementNode : public StatementNode
{
private:
protected:
public:
	// Implementation of pure virtual functions
	virtual std::string toString () { return "CREATE INDEX"; };
	virtual std::string print ();
	virtual StatementType getStatementType () const { return PT_STATEMENT_CREATE_INDEX; };
};

//
// DROP TABLE statement node
//
class DropTableStatementNode : public StatementNode
{
private:
protected:
	// Table identifier
	TableIdentifierNode *table_;

	// Hidden constructor
	DropTableStatementNode () { };

public:
	DropTableStatementNode (TableIdentifierNode *table) : table_ (table) { };

	// Implementation of pure virtual functions
	virtual std::string toString () { return "DROP TABLE"; };
	virtual std::string print ();
	virtual StatementType getStatementType () const { return PT_STATEMENT_DROP_TABLE; };
};

//
// DROP INDEX statement node
//
class DropIndexStatementNode : public StatementNode
{
private:
protected:
public:
	// Implementation of pure virtual functions
	virtual std::string toString () { return "DROP INDEX"; };
	virtual std::string print ();
	virtual StatementType getStatementType () const { return PT_STATEMENT_DROP_INDEX; };
};

#endif