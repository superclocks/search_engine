#ifndef _Lan_search_TermQuery_
#define _Lan_search_TermQuery_
#include "PostingList.h"
#include "Posting.h"
#include "IndexReader.h"
#include "TermScorer.h"

#include <string>
using namespace std;

class TermQuery 
{
private:
    string term;

public:
	TermQuery();
	TermQuery(string t);
    TermScorer getScorer(IndexReader reader);
};
#endif



