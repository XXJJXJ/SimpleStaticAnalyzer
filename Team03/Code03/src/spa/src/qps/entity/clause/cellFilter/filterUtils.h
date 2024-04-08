
#ifndef SPA_FILTERUTILS_H
#define SPA_FILTERUTILS_H

#include <memory>
#include "CellFilter.h"
#include "qps/entity/clause/attribute/Ref.h"
#include "qps/entity/clause/PredicateUtils.h"
#include "AttributeFilter.h"
#include "IdentifierFilter.h"
#include "StatementNumberFilter.h"
#include "SynonymFilter.h"
#include "WildcardFilter.h"

std::shared_ptr<CellFilter> getFilterForStatementRef(const StatementRef& stmtRef);
std::shared_ptr<CellFilter> getFilterForEntityRef(const EntityRef& entRef);
std::shared_ptr<CellFilter> getFilterForProcAndStmtRef(const ProcAndStmtRef& procAndStmtRef);
std::shared_ptr<CellFilter> getFilterForRef(const Ref& ref);

#endif //SPA_FILTERUTILS_H

