#ifndef SPA_QUERYTOKENIZER_H
#define SPA_QUERYTOKENIZER_H

#include <string>
#include <vector>

class QueryTokenizer {
public:
    QueryTokenizer();
    ~QueryTokenizer();

    std::vector<std::vector<std::vector<std::string>>> tokenize(const std::string& query);

private:
    bool isPunctuation(char c);
    std::vector<std::vector<std::vector<std::string>>> splitTokens(const std::vector<std::string>& tokens);
};


#endif //SPA_QUERYTOKENIZER_H