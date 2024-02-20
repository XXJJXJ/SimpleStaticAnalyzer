//// ai-gen start(gpt, 1, e)
//// prompt: https://chat.openai.com/share/8e7dd4d8-d866-4a69-a89a-abf14f589fa0
//#include "SynonymValues.h"
//#include "common/Entity.h"
//#include <algorithm>
//
//
//void SynonymValues::addValue(const std::shared_ptr<Entity>& value) {
//    values.push_back(value);
//}
//
//const std::vector<std::shared_ptr<Entity>>& SynonymValues::getValues() const {
//    return values;
//}
//
//
//// ai-gen end
//
//vector<string> SynonymValues::toStringList() const {
//    vector<string> result;
//    result.reserve(values.size());
//for (const auto& value : values) {
//        result.push_back(value->getName());
//    }
//    return result;
//}
//
//// ai-gen start(gpt, 0, e)
//// prompt: https://chat.openai.com/share/dc4fa5ec-550d-4bf8-b28d-2d6a9d8bf4a2
//bool SynonymValues::operator==(const SynonymValues &rhs) const {
//    // First, check if the synonyms are different
//    if (synonym != rhs.synonym) {
//        return false;
//    }
//
//    // No need to sort the original vectors if they are of different sizes
//    if (values.size() != rhs.values.size()) {
//        return false;
//    }
//
//    // Sort a copy of the vectors based on the names of the entities
//    auto sortedValues = values; // Make a copy to sort
//    auto sortedRhsValues = rhs.values; // Make a copy to sort
//
//    std::sort(sortedValues.begin(), sortedValues.end(),
//              [](const std::shared_ptr<Entity>& a, const std::shared_ptr<Entity>& b) {
//                  return a->getName() < b->getName();
//              });
//
//    std::sort(sortedRhsValues.begin(), sortedRhsValues.end(),
//              [](const std::shared_ptr<Entity>& a, const std::shared_ptr<Entity>& b) {
//                  return a->getName() < b->getName();
//              });
//
//    // Now that both are sorted, compare element by element
//    for (size_t i = 0; i < sortedValues.size(); ++i) {
//        if (!(sortedValues[i]->getName() == sortedRhsValues[i]->getName())) {
//            return false;
//        }
//    }
//    return true;
//}
//// ai-gen end
