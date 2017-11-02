#ifndef _Lan_index_TermInfo_
#define _Lan_index_TermInfo_
namespace Lan
{namespace index{

class TermInfo
{
public:
	int docFreq;
	__int64 freqPointer;
	__int64 proxPointer; //此词的位置信息在位置信息文件中的偏移量

	int skipOffset;    //此词的倒排表的跳跃表在倒排表文件.frq中的偏移量

    TermInfo();

	TermInfo(const int df, const __int64 fp, const __int64 pp);
	TermInfo(const TermInfo* ti);

	~TermInfo();
	void set(const int docFreq, const __int64 freqPointer, const __int64 proxPointer, int skipOffset);

	void set(const TermInfo* ti);
};


}}
#endif