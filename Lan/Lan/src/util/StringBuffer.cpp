#include "StringBuffer.h"



namespace Lan
{
	namespace util
	{
StringBuffer::StringBuffer()
{
	bufferLength = 32;
	len = 0;
	//buffer =
	bufferOwner = true;
}
StringBuffer::StringBuffer(char* buf, int maxlen, const bool consumeBuffer)
{
	buffer = buf;
	bufferLength = maxlen;
	bufferOwner = !consumeBuffer;
	len = 0;
}
StringBuffer::StringBuffer(const int initSize)
{
	bufferLength = initSize + 1;
	len = 0;
	//buffer = _CL_NEWARRAY(TCHAR,bufferLength);
	bufferOwner = true;
}
StringBuffer::StringBuffer(const char* value)
{
}
StringBuffer::~StringBuffer()
{

}
void StringBuffer::clear()
{

}
void StringBuffer::appendChar(const char character)
{

}
void StringBuffer::append(const char* value)
{

}

	}
}

