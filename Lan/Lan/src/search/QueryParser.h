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
	////trim指示是否保留空串，默认为保留。tok可以为任意多个字符
	vector<string> tokenize(const string& src, string tok,bool trim=false, string null_subst="");

};
#endif




