#ifndef _Lan_search_Query_
#define _Lan_search_Query_
#include <vector>

#include "IndexReader.h"
#include "TermQuery.h"
#include "Scorer.h"
using namespace std;
class Query 
{
private:
    vector<TermQuery> termqueries;
    
public:
	Query(vector<TermQuery> termqueries);
    Scorer getScorer(IndexReader reader);
};

#endif



