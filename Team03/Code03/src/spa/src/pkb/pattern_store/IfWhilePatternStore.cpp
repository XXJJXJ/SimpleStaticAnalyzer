#include "IfWhilePatternStore.h"

void IfWhilePatternStore::add(shared_ptr<Statement> stmt, const string& var) {

}
vector<shared_ptr<Entity>> IfWhilePatternStore::getPattern(string& targetVar) {
    return {};
}

void IfWhilePatternStore::clear() {
    matches.clear();
}

 IfWhilePatternStore::~IfWhilePatternStore() {
    clear();
 }