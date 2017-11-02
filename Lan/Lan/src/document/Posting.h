#ifndef _Lan_document_Posting_
#define _Lan_document_Posting_
namespace Lan
{
	namespace document
	{
class Posting 
{
private:
	int docid;
	int freq;
public:
	Posting(int docid, int termfreq);
	Posting();
	int getDocid();
	void setDocid(int docid);
	int getFreq();
	void setFreq(int freq);
	
};
	}
}
#endif