#include "StatementNumberValidator.h"

StatementNumberValidator::StatementNumberValidator(int expectedNumber)
        : expectedNumber(expectedNumber) {}

bool StatementNumberValidator::validate(const std::shared_ptr<Entity>& entity) const {
    auto statement = std::dynamic_pointer_cast<Statement>(entity);
    return statement != nullptr && statement->getStatementNumber() == expectedNumber;
}
