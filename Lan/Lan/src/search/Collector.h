#ifndef _Lan_search_Collector_
#define _Lan_search_Collector_
#include <vector>
#include "DocScorePair.h"
using namespace std;

class Collector 
{
private:
	vector<DocScorePair> queue;
	vector<DocScorePair>::iterator iter;
	unsigned int count; //������
public:
	Collector();
	void collect(DocScorePair p);
	DocScorePair getDocScorePair();
	void quick_sort(int l,int t); //��queue���дӴ�С����
	void sort();
	bool hasNext(); //���queue�л���Ԫ���򷵻�true�����򷵻�false
};
#endif



