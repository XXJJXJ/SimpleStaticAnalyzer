#ifndef SYNONYMGRAPH_H
#define SYNONYMGRAPH_H

#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include "Query.h"

class SynonymGraph {
public:
    SynonymGraph(const std::vector<std::shared_ptr<Predicate>>& predicates);
    std::vector<std::unordered_set<std::shared_ptr<Synonym>>> groupPredicates();

private:
    void addEdge(const std::shared_ptr<Synonym>& u, const std::shared_ptr<Synonym>& v);
    void DFS(std::shared_ptr<Synonym> v, std::unordered_set<std::shared_ptr<Synonym>>& component);

    std::vector<std::shared_ptr<Predicate>> predicates;
    std::unordered_map<std::shared_ptr<Synonym>, std::vector<std::shared_ptr<Synonym>>, std::hash<std::shared_ptr<Synonym>>, std::equal_to<>> adjList;
    std::unordered_set<std::shared_ptr<Synonym>> visited;
};

#endif // SYNONYMGRAPH_H
