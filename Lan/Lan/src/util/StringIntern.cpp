#include "StringIntern.h"

namespace Lan
{namespace util{

__wcsintrntype::iterator wblank;
bool blanksinitd=false;
__wcsintrntype CLStringIntern::stringPool(true);
__strintrntype CLStringIntern::stringaPool(true);
//DEFINE_MUTEX(CLStringIntern::THIS_LOCK)

bool CLStringIntern::unintern(const char* str)
{
		if ( str == NULL )
			return false;
		if ( str[0] == 0 )
			return false;

		//SCOPED_LOCK_MUTEX(THIS_LOCK)

		__wcsintrntype::iterator itr = stringPool.find(str);
		if ( itr != stringPool.end() ){
			if ( (itr->second) == 1 ){
				stringPool.removeitr(itr);
				return true;
			}else
				(itr->second)--;
		}
		return false;
}

const char* CLStringIntern::intern(const char* str ,char* file,int line){
		if ( str == NULL )
			return NULL;
		if ( str[0] == 0 )
			return "";

		//SCOPED_LOCK_MUTEX(THIS_LOCK)

		__wcsintrntype::iterator itr = stringPool.find(str);
		if ( itr==stringPool.end() ){
//#ifdef _UCS2
//			TCHAR* ret = lucenewcsdup(str CL_FILELINEREF);
//#else
			//char* ret = lucenestrdup(str CL_FILELINEREF);
			 size_t len = strlen(str);
			char* ret = new char[len+1];
			strncpy(ret,str,len+1);
			
//#endif
			stringPool[ret]= 1;
			return ret;
		}
		else
		{
			(itr->second)++;
			return itr->first;
		}
	}

}}