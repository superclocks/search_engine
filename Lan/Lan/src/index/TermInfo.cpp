#include "TermInfo.h"

namespace Lan
{namespace index{

TermInfo::TermInfo()
{			
	docFreq     = 0;
	freqPointer = 0;
	proxPointer = 0;
	skipOffset = 0;
}
TermInfo::~TermInfo()
{
}
TermInfo::TermInfo(const int df, const __int64 fp, const __int64 pp)
{
    freqPointer = fp;
    proxPointer = pp;
	docFreq     = df;
    skipOffset = 0;
}
TermInfo::TermInfo(const TermInfo* ti) {
  /*CND_PRECONDITION(ti->docFreq     >= 0, "ti->docFreq contains negative number");
    CND_PRECONDITION(ti->freqPointer >= 0, "ti->freqPointer contains negative number");
    CND_PRECONDITION(ti->proxPointer >= 0, "ti->proxPointer contains negative number");*/

	docFreq     = ti->docFreq;
	freqPointer = ti->freqPointer;
	proxPointer = ti->proxPointer;
	skipOffset  = ti->skipOffset;
}

void TermInfo::set(const int df, const __int64 fp, const __int64 pp, int so) 
{
    /*CND_PRECONDITION(df >= 0, "df contains negative number");
    CND_PRECONDITION(fp >= 0, "fp contains negative number");
    CND_PRECONDITION(pp >= 0, "pp contains negative number");*/

	docFreq     = df;
	freqPointer = fp;
	proxPointer = pp;
    skipOffset  = so;
}

void TermInfo::set(const TermInfo* ti) 
{

  /*  CND_PRECONDITION(ti->docFreq     >= 0, "ti->docFreq contains negative number");
    CND_PRECONDITION(ti->freqPointer >= 0, "ti->freqPointer contains negative number");
    CND_PRECONDITION(ti->proxPointer >= 0, "ti->proxPointer contains negative number");*/

	docFreq     = ti->docFreq;
	freqPointer = ti->freqPointer;
	proxPointer = ti->proxPointer;
    skipOffset =  ti->skipOffset;
}

}}