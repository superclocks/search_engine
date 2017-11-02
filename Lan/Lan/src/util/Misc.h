#ifndef _Lan_util_Misc_
#define _Lan_util_Misc_
#include <string>
using namespace std;

namespace Lan
{namespace util{

class Misc
{
public:
	static unsigned __int64 currentTimeMillis();
	static unsigned int ahashCode(const char* str);
	static unsigned int ahashCode(const char* str, unsigned int len);
	static char* segmentname(const char* segment, const char* ext, const int x=-1 );
#define thashCode ahashCode
};



}}




#endif