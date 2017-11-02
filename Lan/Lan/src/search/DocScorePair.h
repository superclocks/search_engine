#ifndef _Lan_search_DocScorePair_
#define _Lan_search_DocScorePair_
class DocScorePair 
{
private:
	int docid;
	double score;

public:
	DocScorePair();
	DocScorePair(int docid, double score);
	int getDocid();
	void setDocid(int docid);
	double getScore();
	void setScore(double score);
};
#endif



