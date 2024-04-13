#ifndef SPA_QUERYTOKENIZER_H
#define SPA_QUERYTOKENIZER_H

#include <string>
#include <vector>

class QueryTokenizer {
public:
    QueryTokenizer();
    ~QueryTokenizer();

    static std::vector<std::string> tokenize(const std::string &query);
    static std::vector<std::string> collapseTokens(const std::vector<std::string> &query);

private:
    static std::vector<std::string> getTokens(const std::string &query);
    static bool isPunctuation(char c);
    static void handleWithinQuotes(
        std::string &t,
        std::string &currToken,
        std::vector<std::string> &collapsedTokens,
        bool &isWithinQuotes,
        bool &isPrevSyn);
    static void handleWithinWildcard(
        std::string &t,
        std::string &currToken,
        std::vector<std::string> &collapsedTokens,
        bool &isWithinWildcard,
        bool &isPrevSyn);
    static void handleNormalToken(
        std::string &t,
        std::string &currToken,
        std::vector<std::string> &collapsedTokens,
        bool &isWithinQuotes,
        bool &isWithinWildcard);
    static void handleCollapsingTokens(std::string &t, std::string &currToken, bool &isPrevSyn);

};

#endif //SPA_QUERYTOKENIZER_H