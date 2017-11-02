#include "PostingList.h"
namespace Lan
{
	namespace document
	{
PostingList::PostingList(string term, int docFreq)
{
	this->term=term;
	this->docFreq=docFreq;
}

void PostingList::incrDocFreq()
{
	docFreq++;
}
void PostingList::addPosting(Posting p)
{
	postings.push_back(p);
}
int PostingList::getDocFreq()
{
	return docFreq;
}
vector<Posting>::iterator PostingList::getPostingIter()
{
	return postings.begin();
}
vector<Posting> PostingList::getPosting()
{
	return postings;
}


	}
}