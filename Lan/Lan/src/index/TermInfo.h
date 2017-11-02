#ifndef _Lan_index_TermInfo_
#define _Lan_index_TermInfo_
namespace Lan
{namespace index{

class TermInfo
{
public:
	int docFreq;
	__int64 freqPointer;
	__int64 proxPointer; //�˴ʵ�λ����Ϣ��λ����Ϣ�ļ��е�ƫ����

	int skipOffset;    //�˴ʵĵ��ű����Ծ���ڵ��ű��ļ�.frq�е�ƫ����

    TermInfo();

	TermInfo(const int df, const __int64 fp, const __int64 pp);
	TermInfo(const TermInfo* ti);

	~TermInfo();
	void set(const int docFreq, const __int64 freqPointer, const __int64 proxPointer, int skipOffset);

	void set(const TermInfo* ti);
};


}}
#endif