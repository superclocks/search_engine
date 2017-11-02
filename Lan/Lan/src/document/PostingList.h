#ifndef _Lan_document_PostingList_
#define _Lan_document_PostingList_
#include "Posting.h"
#include <string>
#include <vector>
using namespace std;
namespace Lan
{
	namespace document
	{
class PostingList 
{
private:
	string term;
	int docFreq;
	vector<Posting> postings;
public:
	PostingList(string term, int docFreq);
	void incrDocFreq();
	void addPosting(Posting p);
	int getDocFreq();
	vector<Posting>::iterator getPostingIter();
	vector<Posting> getPosting();
};
	}
}
#endif
