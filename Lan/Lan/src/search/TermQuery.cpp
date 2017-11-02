//#include "TermQuery.h"
//TermQuery::TermQuery() 
//{
//}
//TermQuery::TermQuery(string t) 
//{
//	this->term = t;
//}
//TermScorer TermQuery::getScorer(IndexReader reader) 
//{
//    PostingList plist = reader.getPostingList(term);
//    int docFreq = plist.getDocFreq();
//	vector<Posting>::iterator iter = plist.getPostingIter();
//	TermScorer termscorer(term,docFreq,plist.getPosting());
//    return termscorer;
//}

