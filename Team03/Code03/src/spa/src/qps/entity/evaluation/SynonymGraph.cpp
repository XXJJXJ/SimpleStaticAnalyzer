#include "SynonymGraph.h"
#include <stack>

// ai-gen start (gpt, 1, e)
// prompt: https://chat.openai.com/share/7b6dae68-063a-4ce8-9fd0-bd2ac43f9fe4
SynonymGraph::SynonymGraph(
    const std::vector<std::shared_ptr<Predicate>> &predicates, const std::vector<shared_ptr<Synonym>> &declaredSynonyms)
    : predicates(predicates) {
    // add self loop for each synonym
    for (const auto &synonym : declaredSynonyms) {
        addEdge(synonym, synonym);
    }
    for (const auto &predicate : predicates) {
        auto synonyms = predicate->getSynonyms();
        for (size_t i = 0; i < synonyms.size(); ++i) {
            for (size_t j = i + 1; j < synonyms.size(); ++j) {
                addEdge(synonyms[i], synonyms[j]);
                addEdge(synonyms[j], synonyms[i]);
            }
        }
    }
}

void SynonymGraph::addEdge(const std::shared_ptr<Synonym> &u, const std::shared_ptr<Synonym> &v) {
    adjList[u].push_back(v);
}

std::vector<SynonymPtrSet> SynonymGraph::groupSynonyms() {
    std::vector<SynonymPtrSet> groups;
    for (const auto &pair : adjList) {
        if (visited.find(pair.first) == visited.end()) {
            SynonymPtrSet component;
            DFS(pair.first, component);
            groups.push_back(component);
        }
    }
    return groups;
}

void SynonymGraph::DFS(std::shared_ptr<Synonym> v, SynonymPtrSet &component) {
    visited.insert(v);
    component.insert(v);
    for (auto &adjSynonym : adjList[v]) {
        if (visited.find(adjSynonym) == visited.end()) {
            DFS(adjSynonym, component);
        }
    }
}
// ai-gen end