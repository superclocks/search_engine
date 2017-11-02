#include "Misc.h"
#include <time.h>
#include <sys/timeb.h>

namespace Lan
{namespace util{

unsigned __int64 Misc::currentTimeMillis()
{
	struct _timeb tstruct;
	_ftime(&tstruct);
	return (((unsigned __int64) tstruct.time) * 1000) + tstruct.millitm;
}

unsigned int Misc::ahashCode(const char* str)
{
	unsigned int hashCode=0;
	while(*str!=0)
	{
		hashCode=hashCode*31+*str++;
	}
	return hashCode;
}
unsigned int Misc::ahashCode(const char* str, unsigned int len)
{
	unsigned int hashCode = 0;
	for(unsigned int i=0;i<len;i++)
		hashCode = hashCode *31 + *str++;
	return hashCode;
}
char* Misc::segmentname(const char* segment, const char* ext, const int x)
{
	//CND_PRECONDITION(ext != NULL, "ext is NULL");
	char* buf = new char[260];
	if(x==-1)
	{
		_snprintf(buf,260,"%s%s", segment,ext );
	}
	else
	{
		_snprintf(buf,260,"%s%s%d", segment,ext,x );
	}
	return buf;
}


}}