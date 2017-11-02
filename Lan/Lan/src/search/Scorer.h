#ifndef _Lan_search_Scorer_
#define _Lan_search_Scorer_
#include <vector>
#include <map>
#include <math.h>
#include <string>
#include "Posting.h"
#include "IndexReader.h"
#include "TermScorer.h"
#include "DocScorePair.h"
#include "TermScorer.h"
#include "Collector.h"

using namespace std;

class Scorer 
{
private:
	IndexReader reader;
	double queryVectorLength;
	vector<TermScorer> termscorers;
	Collector collector;
public:
	Scorer();
	Scorer(vector<TermScorer> tslist, IndexReader reader);
	void calculateQueryVectorLength();
    double idf(int docFreq, int numDocs);
	//DocScorePair getNextDocAndScore();
	Collector getDocAndScoreSet();
};

#endif


