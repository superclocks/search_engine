#include "TermVector.h"
#include "StringBuffer.h"
#include "TermVector.h"


using namespace Lan::util;
namespace Lan
{namespace index{

Array<TermVectorOffsetInfo> TermVectorOffsetInfo::EMPTY_OFFSET_INFO;

TermVectorOffsetInfo::TermVectorOffsetInfo()
{
	startOffset = 0;
	endOffset = 0;
}
TermVectorOffsetInfo::~TermVectorOffsetInfo() {}

TermVectorOffsetInfo::TermVectorOffsetInfo(int startOffset, int endOffset) {
	this->endOffset = endOffset;
	this->startOffset = startOffset;
}

int TermVectorOffsetInfo::getEndOffset() const{
	return endOffset;
}

void TermVectorOffsetInfo::setEndOffset(int endOffset) {
	this->endOffset = endOffset;
}

int TermVectorOffsetInfo::getStartOffset() const{
	return startOffset;
}

void TermVectorOffsetInfo::setStartOffset(int startOffset) {
	this->startOffset = startOffset;
}

bool TermVectorOffsetInfo::equals(TermVectorOffsetInfo* termVectorOffsetInfo) {
	if (this == termVectorOffsetInfo) 
		return true;

	if (endOffset != termVectorOffsetInfo->endOffset) return false;
	if (startOffset != termVectorOffsetInfo->startOffset) return false;

	return true;
}

size_t TermVectorOffsetInfo::hashCode() const{
	size_t result;
	result = startOffset;
	result = 29 * result + endOffset;
	return result;
}


}}