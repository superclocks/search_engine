//#include "Scorer.h"
//
//Scorer::Scorer()
//{
//	queryVectorLength = 0;
//}
//Scorer::Scorer(vector<TermScorer> tslist, IndexReader reader) 
//{
//    termscorers = tslist;
//    this->reader = reader;
//    calculateQueryVectorLength();
//}
//
//void Scorer::calculateQueryVectorLength() 
//{
//    double sumofidfs = 0;
//	for (unsigned int i=0;i<termscorers.size();i++) 
//	{
//		TermScorer ts=termscorers[i];
//		int df = ts.getDocFreq();
//		double idf1 = idf(df, reader.numDocs());
//		sumofidfs += idf1 * idf1;
//    }
//    queryVectorLength = (double) (1 / sqrt(sumofidfs));
//}
//
//double Scorer::idf(int docFreq, int numDocs) 
//{
//    return (double) (log(numDocs / (double) (docFreq + 1)) + 1.0);
//}
//Collector Scorer::getDocAndScoreSet() 
//{
//	/*vector<DocScorePair> docpair;*/
//    vector<TermScorer> withthesamedocid;
//    int maxDocID = -1;
//	vector<vector<Posting>> allpostlist;
//	vector<vector<Posting>::iterator> iters;
//	for (unsigned int i=0;i<termscorers.size();i++) 
//	{
//		TermScorer ts=termscorers[i];
//		vector<Posting> ele_postlist=ts.getPostList();
//		allpostlist.push_back(ele_postlist);
//		iters.push_back(allpostlist[i].begin());
//	}
//	vector<Posting> postwithsamedocid;
//	bool stop=false;
//	while(true)
//	{
//		if(stop==true)
//		{
//			break;
//		}
//		for(unsigned int i=0;i<allpostlist.size();i++)
//		{
//			Posting post;
//			if(iters[i]==allpostlist[i].end())
//			{
//				stop=true;
//				break;
//			}
//			if (iters[i]->getDocid() < maxDocID) 
//			{
//				while (iters[i]!=allpostlist[i].end())
//				{
//					iters[i]++;
//					if(iters[i]->getDocid() >= maxDocID)
//					{
//						post=*(iters[i]);
//						break;
//					}
//				}
//			}
//			else
//			{
//				post=*iters[i];
//			}
//			int docid = iters[i]->getDocid();
//			if (docid > maxDocID) 
//			{
//				maxDocID = docid;
//				postwithsamedocid.clear();
//				postwithsamedocid.push_back(post);
//			}
//			else
//			{
//				postwithsamedocid.push_back(post);
//			}
//			if (postwithsamedocid.size() == termscorers.size()) 
//			{
//				// calculate the score
//				double score = 0;
//				vector<Posting>::iterator iter;
//				Posting cur;
//				for (unsigned int j=0;j<postwithsamedocid.size();j++) 
//				{
//					TermScorer t= termscorers[j];
//					cur =postwithsamedocid[j];
//					score += cur.getFreq() * idf(t.getDocFreq(), reader.numDocs()) * idf(t.getDocFreq(), reader.numDocs());
//					iters[j]++;			
//				}
//				withthesamedocid.clear();
//				score = score * queryVectorLength;
//				collector.collect(DocScorePair(docid, score));
//			}
//		}
//	}
//
//	collector.sort();
//	return collector;
//}
