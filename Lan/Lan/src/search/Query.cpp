//#include "Query.h"
//
//Query::Query(vector<TermQuery> termqueries) 
//{
//      this->termqueries = termqueries;
//}
//
//Scorer Query::getScorer(IndexReader reader)
//{
//        vector<TermScorer> tslist;
//		tslist.clear();
//        for(unsigned int i=0;i<termqueries.size();i++)
//		{
//			TermQuery tq=termqueries[i];
//            TermScorer ts = tq.getScorer(reader);
//			tslist.push_back(ts);
//        }
//        return Scorer(tslist, reader);
//}
