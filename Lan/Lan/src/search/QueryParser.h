#ifndef _Lan_search_QueryParser_
#define _Lan_search_QueryParser_
#include <vector>
#include <string>
#include "Query.h"
using namespace std;

typedef basic_string<char>::size_type S_T; 
static const S_T npos = -1; 

class QueryParser 
{
public:
	Query parse(string querystring);
	////trimָʾ�Ƿ����մ���Ĭ��Ϊ������tok����Ϊ�������ַ�
	vector<string> tokenize(const string& src, string tok,bool trim=false, string null_subst="");

};
#endif




