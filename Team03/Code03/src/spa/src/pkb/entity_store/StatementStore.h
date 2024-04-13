#pragma once

#include <unordered_map>

#include "common/statement/Statement.h"
#include "common/statement/AssignStatement.h"
#include "common/statement/CallStatement.h"
#include "common/statement/IfStatement.h"
#include "common/statement/ReadStatement.h"
#include "common/statement/PrintStatement.h"
#include "common/statement/WhileStatement.h"

class StatementStore {
 private:
  unordered_map<int, shared_ptr<Statement>> lineToStatementMap;

  unordered_map<int, shared_ptr<AssignStatement>> lineToAssignStatementMap;
  unordered_map<int, shared_ptr<ReadStatement>> lineToReadStatementMap;
  unordered_map<int, shared_ptr<PrintStatement>> lineToPrintStatementMap;
  unordered_map<int, shared_ptr<WhileStatement>> lineToWhileStatementMap;
  unordered_map<int, shared_ptr<IfStatement>> lineToIfStatementMap;
  unordered_map<int, shared_ptr<CallStatement>> lineToCallStatementMap;

  vector<shared_ptr<Statement>> allStatementsCache;
  vector<shared_ptr<AssignStatement>> assignStatementsCache;
  vector<shared_ptr<CallStatement>> callStatementsCache;
  vector<shared_ptr<ReadStatement>> readStatementsCache;
  vector<shared_ptr<PrintStatement>> printStatementsCache;
  vector<shared_ptr<WhileStatement>> whileStatementsCache;
  vector<shared_ptr<IfStatement>> ifStatementsCache;

  bool add(shared_ptr<Statement> stmt);
 public:
  StatementStore();
  vector<shared_ptr<Statement>> getAll();

  bool addPrint(shared_ptr<PrintStatement> stmt);
  vector<shared_ptr<PrintStatement>> getAllPrint();

  bool addRead(shared_ptr<ReadStatement> stmt);
  vector<shared_ptr<ReadStatement>> getAllRead();

  bool addAssign(shared_ptr<AssignStatement> stmt);
  vector<shared_ptr<AssignStatement>> getAllAssign();

  bool addIf(shared_ptr<IfStatement> stmt);
  vector<shared_ptr<IfStatement>> getAllIf();

  bool addWhile(shared_ptr<WhileStatement> stmt);
  vector<shared_ptr<WhileStatement>> getAllWhile();

  bool addCall(shared_ptr<CallStatement> stmt);
  vector<shared_ptr<CallStatement>> getAllCall();

  void clear();
  ~StatementStore();
};