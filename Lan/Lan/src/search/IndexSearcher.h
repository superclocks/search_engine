#ifndef _Lan_search_IndexSearcher_
#define _Lan_search_IndexSearcher_

#include "IndexReader.h"
#include "Query.h"
#include "Collector.h"
#include "DocScorePair.h"

using namespace std;

class IndexSearcher 
{
private:
	IndexReader reader;

public:
	IndexSearcher(IndexReader reader);
	Collector search(Query query);
};
#endif




