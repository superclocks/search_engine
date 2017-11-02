#ifndef _Lan_util_StringReader_
#define _Lan_util_StringReader_
#include "StreamBase.h"

namespace jstreams
{
template <class T>
class StringReader:public StreamBase<T>
{
private:
	__int64 markpt;
	T* data;
	bool dataowner;
	StringReader(const StringReader<T>&);
	void operator=(const StringReader<T>&);
public:
	StringReader(const T* value, int length=-1, bool copy=true);
	~StringReader();
	int read(const T*& start, int min, int max);
    __int64 skip(__int64 ntoskip);
    __int64 reset(__int64 pos);
};
typedef StringReader<char> StringInputStream;

template <class T>
StringReader<T>::StringReader(const T* value, int length, bool copy)
        : markpt(0), dataowner(copy) {
    if (length < 0) {
        length = 0;
        while (value[length] != '\0') {
            length++;
        }
    }
    StreamBase<T>::size = length;
    if (copy) {
        data = new T[length+1];
        size_t s = (unsigned int)(length*sizeof(T));
        memcpy(data, value, s);
        data[length] = 0;
    } else {
        // casting away const is ok, because we don't write anyway
        data = (T*)value;
    }
}
template <class T>
StringReader<T>::~StringReader() {
    if (dataowner) {
        delete [] data;
    }
}
template <class T>
int
StringReader<T>::read(const T*& start, int min, int max) {
    __int64 left = StreamBase<T>::size - StreamBase<T>::position;
    if (left == 0) {
        StreamBase<T>::status = Eof;
        return -1;
    }
    if (min < 0) min = 0;
    int nread = (int)((max > left || max < 1) ?left :max); //nread是需要读取的字符个数
    start = data + StreamBase<T>::position; //使start指针指向新的位置
    StreamBase<T>::position += nread; //更新位置指针
    if (StreamBase<T>::position == StreamBase<T>::size) //如果字符串的位置指针和它的大小相等，则字符串读取结束
	{
        StreamBase<T>::status = Eof;
    }
    return nread;
}
template <class T>
__int64
StringReader<T>::skip(__int64 ntoskip) {
    const T* start;
    return read(start, ntoskip, ntoskip);
}
template <class T>
__int64
StringReader<T>::reset(__int64 newpos) {
    if (newpos < 0) {
        StreamBase<T>::status = Ok;
        StreamBase<T>::position = 0;
    } else if (newpos < StreamBase<T>::size) {
        StreamBase<T>::status = Ok;
        StreamBase<T>::position = newpos;
    } else {
        StreamBase<T>::position = StreamBase<T>::size;
        StreamBase<T>::status = Eof;
    }
    return StreamBase<T>::position;
}
}



#endif