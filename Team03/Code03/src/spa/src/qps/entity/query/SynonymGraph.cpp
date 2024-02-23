#include "SynonymGraph.h"
#include <stack>

SynonymGraph::SynonymGraph(const std::vector<std::shared_ptr<Predicate>>& predicates) : predicates(predicates) {
    for (const auto& predicate : predicates) {
        auto synonyms = predicate->getSynonyms();
        for (size_t i = 0; i < synonyms.size(); ++i) {
            for (size_t j = i + 1; j < synonyms.size(); ++j) {
                addEdge(synonyms[i], synonyms[j]);
                addEdge(synonyms[j], synonyms[i]);
            }
        }
    }
}

void SynonymGraph::addEdge(const std::shared_ptr<Synonym>& u, const std::shared_ptr<Synonym>& v) {
    adjList[u].push_back(v);
}

std::vector<std::unordered_set<std::shared_ptr<Synonym>>> SynonymGraph::groupPredicates() {
    std::vector<std::unordered_set<std::shared_ptr<Synonym>>> groups;
    for (const auto& pair : adjList) {
        if (visited.find(pair.first) == visited.end()) {
            std::unordered_set<std::shared_ptr<Synonym>> component;
            DFS(pair.first, component);
            groups.push_back(component);
        }
    }
    return groups;
}

void SynonymGraph::DFS(std::shared_ptr<Synonym> v, std::unordered_set<std::shared_ptr<Synonym>>& component) {
    visited.insert(v);
    component.insert(v);
    for (auto& adjSynonym : adjList[v]) {
        if (visited.find(adjSynonym) == visited.end()) {
            DFS(adjSynonym, component);
        }
    }
}

