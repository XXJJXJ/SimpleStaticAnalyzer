#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "common/Procedure.h"
#include "EntityStoreInterface.h"

class ProcedureStore : public EntityStoreInterface<Procedure> {
 private:
  unordered_map<string, shared_ptr<Procedure>> nameToProcMap;
  vector<shared_ptr<Procedure>> allProcedures;
 public:
  bool add(shared_ptr<Procedure> procedure) override;
  vector<shared_ptr<Procedure>> getAll() override;
  shared_ptr<Procedure> get(const string &name) override;
  void clear() override;
  ~ProcedureStore();
};