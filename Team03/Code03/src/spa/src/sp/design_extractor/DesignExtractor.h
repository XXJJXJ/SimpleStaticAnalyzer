#include <memory>

#include "common/Program.h"
#include "EntityExtractor.h"
#include "AbstractionExtractor.h"
#include "CfgExtractor.h"
#include "pkb/PopulatePKB.h"

class DesignExtractor {
 public:
  DesignExtractor(shared_ptr<Populator> pkb);
  void extractDesign(shared_ptr<Program> program);

 private:
  shared_ptr<Populator> pkbPopulator;
  void extractNextRelation(shared_ptr<Cfg>);
  void nodeTraversalHelper(shared_ptr<CfgNode> currNode,
                           vector<shared_ptr<CfgNode>> visited,
                           shared_ptr<Statement> prevNodeStatement);
};