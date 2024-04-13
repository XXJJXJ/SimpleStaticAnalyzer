#include "WildcardFilter.h"

bool WildcardFilter::passFilter(const std::shared_ptr<Entity> &entity) const {
    return entity != nullptr;
}
