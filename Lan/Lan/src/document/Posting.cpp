#include "Posting.h"
namespace Lan
{
	namespace document
	{
int Posting::getDocid()
{
	return docid;
}
void Posting::setDocid(int docid)
{
	this->docid = docid;
}
int Posting::getFreq()
{
	return freq;
}
void Posting::setFreq(int freq)
{
	this->freq = freq;
}
Posting::Posting(int docid, int termfreq)
{
	this->docid = docid;
    this->freq = termfreq;
}
Posting::Posting()
{

}

	}
}