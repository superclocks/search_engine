#ifndef _Lan_index_TermVector_
#define _Lan_index_TermVector_
#include "FieldInfos.h"
#include "mem.h"

namespace Lan
{namespace index{


struct TermVectorOffsetInfo
{
	int startOffset;
    int endOffset;
public:
	static Array<TermVectorOffsetInfo> EMPTY_OFFSET_INFO;
    TermVectorOffsetInfo();
    ~TermVectorOffsetInfo();
    TermVectorOffsetInfo(int startOffset, int endOffset);
    int getEndOffset() const;
    void setEndOffset(int endOffset);
    int getStartOffset() const;
    void setStartOffset(int startOffset);
    bool equals(TermVectorOffsetInfo* o);
    unsigned int hashCode() const;
};


}}
#endif