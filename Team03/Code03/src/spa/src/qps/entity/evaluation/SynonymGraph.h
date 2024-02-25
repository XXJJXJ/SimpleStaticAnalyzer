// ai-gen start (gpt, 1, e)
// prompt: https://chat.openai.com/share/7b6dae68-063a-4ce8-9fd0-bd2ac43f9fe4
#ifndef SYNONYMGRAPH_H
#define SYNONYMGRAPH_H

#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include "qps/entity/query/Query.h"

class SynonymGraph {
public:
    SynonymGraph(const std::vector<std::shared_ptr<Predicate>>& predicates);
    std::vector<SynonymPtrSet> groupSynonyms();

private:
    void addEdge(const std::shared_ptr<Synonym>& u, const std::shared_ptr<Synonym>& v);
    void DFS(std::shared_ptr<Synonym> v, SynonymPtrSet & component);

    std::vector<std::shared_ptr<Predicate>> predicates;
    std::unordered_map<std::shared_ptr<Synonym>, std::vector<std::shared_ptr<Synonym>>, SynonymPtrHash, SynonymPtrEqual> adjList;
    std::unordered_set<std::shared_ptr<Synonym>> visited;
};

#endif // SYNONYMGRAPH_H
// ai-gen end