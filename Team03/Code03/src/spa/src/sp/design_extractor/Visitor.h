#pragma once
#include <memory>

class PrintStatement;
class ReadStatement;
class Program;
class Procedure;
class Statement;
class Expression;
class Variable;

using namespace std;

class Visitor {
public:
	void visitProgram(shared_ptr<Program> program);
	virtual void visitProcedure(shared_ptr<Procedure> procedure) = 0;
	virtual void visitVariable(shared_ptr<Variable> variable) = 0;
	virtual void visitPrintStatement(shared_ptr<PrintStatement> print_statement) = 0;
	virtual void visitReadStatement(shared_ptr<ReadStatement> read_statement) = 0;
	void visitExpression(shared_ptr<Expression> expression);
};