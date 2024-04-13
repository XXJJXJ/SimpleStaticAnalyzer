#pragma once
#include <memory>

class PrintStatement;
class ReadStatement;
class Program;
class Procedure;
class Statement;
class Expression;
class Variable;
class Constant;
class ArithmeticOperation;
class ConditionalOperation;
class RelationalOperation;
class AssignStatement;
class IfStatement;
class WhileStatement;
class CallStatement;

using namespace std;

class Visitor {
 public:
  void visitProgram(shared_ptr<Program> program);
  void visitExpression(shared_ptr<Expression> expression);
  virtual void visitProcedure(shared_ptr<Procedure> procedure) = 0;
  virtual void visitConstant(shared_ptr<Constant> constant) = 0;
  virtual void visitVariable(shared_ptr<Variable> variable) = 0;
  virtual void visitPrintStatement(shared_ptr<PrintStatement> printStatement) = 0;
  virtual void visitReadStatement(shared_ptr<ReadStatement> readStatement) = 0;
  virtual void visitArithmeticOperation(shared_ptr<ArithmeticOperation> arithmeticOperation) = 0;
  virtual void visitAssignStatement(shared_ptr<AssignStatement> assignStatement) = 0;
  virtual void visitConditionalOperation(shared_ptr<ConditionalOperation> conditionalOperation) = 0;
  virtual void visitRelationalOperation(shared_ptr<RelationalOperation> relationalOperation) = 0;
  virtual void visitIfStatement(shared_ptr<IfStatement> ifStatement) = 0;
  virtual void visitWhileStatement(shared_ptr<WhileStatement> whileStatement) = 0;
  virtual void visitCallStatement(shared_ptr<CallStatement> callStatement) = 0;
};