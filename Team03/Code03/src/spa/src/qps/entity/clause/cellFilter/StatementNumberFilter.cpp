#include "StatementNumberFilter.h"

StatementNumberFilter::StatementNumberFilter(int expectedNumber) : expectedNumber(expectedNumber) {}

bool StatementNumberFilter::passFilter(const std::shared_ptr<Entity> &entity) const {
    auto statement = std::dynamic_pointer_cast<Statement>(entity);
    return statement != nullptr && statement->getStatementNumber() == expectedNumber;
}
