/*
* Created by ZHENGTAO JIANG on 8/2/24.
*/

#ifndef SPA_QUERYFACADE_H
#define SPA_QUERYFACADE_H
#include <string>

class QueryFacade {
public:
	// Arguments: user query string
	// Returns: results string
	std::string evaluateQuery(std::string query);
};


#endif //SPA_QUERYFACADE_H