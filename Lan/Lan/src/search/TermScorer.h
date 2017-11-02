#ifndef _Lan_search_TermScorer_
#define _Lan_search_TermScorer_
#include "Posting.h"
#include <string>
#include <vector>
using namespace std;
using namespace Lan::document;
class TermScorer 
{
private:
	string term;
	int docFreq;
	Posting cur;
	vector<Posting> postlist;

public:
	TermScorer();
	TermScorer(string term, int docFreq,vector<Posting> postlist);
	//TermScorer(const TermScorer& termscorer);
	Posting getCurPosting();  
	/*bool hasNext();
	Posting next();*/
	//Posting skipTo(int docid);
	string getTerm();
	void setTerm(string term);
	int getDocFreq();
	void setDocFreq(int docFreq);
	/*vector<Posting>::iterator getPostIter();
	void setPostIter(vector<Posting>::iterator postIter);*/
	vector<Posting> getPostList();
	//void setIterator();

};
#endif
