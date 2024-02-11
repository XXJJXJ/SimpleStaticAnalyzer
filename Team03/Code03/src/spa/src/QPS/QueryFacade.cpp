/*
* Created by ZHENGTAO JIANG on 8/2/24.w
*
* Users submit queries to the QPS using the evaluateQuery() method,
* Returns a string response with requested data:
* Statement Numbers e.g 1,3,5,6
* Variables e.g a,b,c,v
*/

#include "QueryFacade.h"
#include "QueryParser.h"
#include "QueryValidator.h"

std::string QueryFacade::evaluateQuery(std::string query) {
	QueryValidator qv;

	return qv.validateQuery(query);
}