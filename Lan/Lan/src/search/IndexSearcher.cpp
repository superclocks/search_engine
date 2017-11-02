//#include "IndexSearcher.h"
//
//IndexSearcher::IndexSearcher(IndexReader reader) 
//{
//    this->reader = reader;
//}
//
//Collector IndexSearcher::search(Query query) 
//{
//    Scorer scorer = query.getScorer(reader);
//
//	return scorer.getDocAndScoreSet();
//
//}