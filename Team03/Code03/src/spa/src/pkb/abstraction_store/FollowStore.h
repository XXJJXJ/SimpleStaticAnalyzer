#pragma once

#include <unordered_map>
#include "common/statement/Statement.h"
#include "StmtStmtStore.h"

class FollowStore : public StmtStmtStore {
 public:
  bool checkValidity(shared_ptr<Statement> follower, shared_ptr<Statement> followed) override;
  ~FollowStore();
};