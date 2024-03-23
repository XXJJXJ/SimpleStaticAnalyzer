#ifndef SPA_QUERYTOKENIZER_H
#define SPA_QUERYTOKENIZER_H

#include <string>
#include <vector>

class QueryTokenizer {
public:
    QueryTokenizer();
    ~QueryTokenizer();

    static std::vector<std::string> tokenize(const std::string& query);

private:
    static std::vector<std::string> getTokens(const std::string& query);
    static std::vector<std::string> collapseTokens(const std::vector<std::string>& query);
    static bool isPunctuation(char c);
};


#endif //SPA_QUERYTOKENIZER_H