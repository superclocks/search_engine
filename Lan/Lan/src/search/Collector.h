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
	unsigned int count; //计数器
public:
	Collector();
	void collect(DocScorePair p);
	DocScorePair getDocScorePair();
	void quick_sort(int l,int t); //对queue进行从大到小排序
	void sort();
	bool hasNext(); //如果queue中还有元素则返回true，否则返回false
};
#endif



