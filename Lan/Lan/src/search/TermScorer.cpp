//#include "TermScorer.h"
//
//Posting TermScorer::getCurPosting()
//{
//    return cur;
//}
// 
//string TermScorer::getTerm() 
//{
//    return term;
//}
//
//void TermScorer::setTerm(string term)
//{
//    this->term = term;
//}
//
//int TermScorer::getDocFreq() 
//{
//    return docFreq;
//}
//
//void TermScorer::setDocFreq(int docFreq)
//{
//    this->docFreq = docFreq;
//}
//
////vector<Posting>::iterator TermScorer::getPostIter()
////{
////    return postIter;
////}
//
////void TermScorer::setPostIter(vector<Posting>::iterator postIter) 
////{
////    this->postIter = postIter;
////}
//
//TermScorer::TermScorer(string term, int docFreq,vector<Posting> postlist) 
//{
//    this->term = term;
//    this->docFreq = docFreq;
//	this->postlist=postlist;
//}
//TermScorer::TermScorer()
//{
//
//}
////void TermScorer::setIterator()
////{
////	this->postIter=this->postlist.begin();
////}
////TermScorer::TermScorer(const TermScorer& termscorer)
////{
////	this->cur=termscorer.cur;
////	this->docFreq=termscorer.docFreq;
////	this->postlist=termscorer.postlist;
////	this->term=termscorer.term;
////	 
////	int offset;
////	offset=termscorer.postIter-termscorer.postlist.begin();
////	this->postIter=this->postlist.begin()+offset;
////}
//
//vector<Posting> TermScorer::getPostList()
//{
//	return postlist;
//}