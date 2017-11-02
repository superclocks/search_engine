#ifndef _Lan_util_StringIntern_
#define _Lan_util_StringIntern_
#include "VoidMap.h"
#include "Equators.h"

namespace Lan
{namespace util{


typedef Lan::util::CLHashMap<const char*, int,Lan::util::Compare::TChar,Lan::util::Equals::TChar,Lan::util::Deletor::tcArray,Lan::util::Deletor::DummyInt32> __wcsintrntype;
typedef Lan::util::CLHashMap<const char*, int,Lan::util::Compare::Char,Lan::util::Equals::Char,Lan::util::Deletor::acArray, Lan::util::Deletor::DummyInt32 > __strintrntype;

class CLStringIntern
{
	static __wcsintrntype stringPool;
	static __strintrntype stringaPool;
	//STATIC_DEFINE_MUTEX(THIS_LOCK)
public:
	static const char* intern(const char* str,char* file,int line);
	static bool unintern(const char* str);
};


}}

#endif