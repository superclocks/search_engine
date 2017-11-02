#ifndef _Lan_util_BufferedStream_
#define _Lan_util_BufferedStream_
#include "StreamBase.h"
#include "InPutStreamBuffer.h"
#include <cassert>


namespace jstreams
{
template <class T>
class BufferedInputStream : public StreamBase<T> {
private:
    bool finishedWritingToBuffer;
    InputStreamBuffer<T> buffer;

    void writeToBuffer(int minsize);
    int read_(const T*& start, int min, int max);
protected:
    /**
     * This function must be implemented by the subclasses.
     * It should write a maximum of @p space characters at the buffer
     * position pointed to by @p start. If no more data is avaiable due to
     * end of file, -1 should be returned. If an error occurs, the status
     * should be set to Error, an error message should be set and the function
     * must return -1.
     **/
    virtual int fillBuffer(T* start, int space) = 0;
    // this function might be useful if you want to reuse a bufferedstream
    void resetBuffer() {printf("implement 'resetBuffer'\n");}
    BufferedInputStream<T>();
public:
    int read(const T*& start, int min, int max);
    __int64 reset(__int64);
    virtual __int64 skip(__int64 ntoskip);
};

template <class T>
BufferedInputStream<T>::BufferedInputStream() {
    finishedWritingToBuffer = false;
}

template <class T>
void
BufferedInputStream<T>::writeToBuffer(int ntoread) {
    int missing = ntoread - buffer.avail;
    int nwritten = 0;
    while (missing > 0 && nwritten >= 0) {
        int space;
        space = buffer.makeSpace(missing);
        T* start = buffer.readPos + buffer.avail;
        nwritten = fillBuffer(start, space);
        assert(StreamBase<T>::status != Eof);
        if (nwritten > 0) {
            buffer.avail += nwritten;
            missing = ntoread - buffer.avail;
        }
    }
    if (nwritten < 0) {
        finishedWritingToBuffer = true;
    }
}
template <class T>
int
BufferedInputStream<T>::read(const T*& start, int min, int max) {
    if (StreamBase<T>::status == Error) return -2;
    if (StreamBase<T>::status == Eof) return -1;

    // do we need to read data into the buffer?
    if (!finishedWritingToBuffer && min > buffer.avail) {
        // do we have enough space in the buffer?
        writeToBuffer(min);
        if (StreamBase<T>::status == Error) return -2;
    }

    int nread = buffer.read(start, max);

    BufferedInputStream<T>::position += nread;
    if (BufferedInputStream<T>::position > BufferedInputStream<T>::size
        && BufferedInputStream<T>::size > 0) {
        // error: we read more than was specified in size
        // this is an error because all dependent code might have been labouring
        // under a misapprehension
        BufferedInputStream<T>::status = Error;
        BufferedInputStream<T>::error = "Stream is longer than specified.";
        nread = -2;
    } else if (BufferedInputStream<T>::status == Ok && buffer.avail == 0
            && finishedWritingToBuffer) {
        BufferedInputStream<T>::status = Eof;
        if (BufferedInputStream<T>::size == -1) {
            BufferedInputStream<T>::size = BufferedInputStream<T>::position;
        }
        // save one call to read() by already returning -1 if no data is there
        if (nread == 0) nread = -1;
    }
    return nread;
}
template <class T>
__int64
BufferedInputStream<T>::reset(__int64 newpos) {
    if (StreamBase<T>::status == Error) return -2;
    // check to see if we have this position
    __int64 d = BufferedInputStream<T>::position - newpos;
    if (buffer.readPos - d >= buffer.start && -d < buffer.avail) {
        BufferedInputStream<T>::position -= d;
        buffer.avail += (int)d;
        buffer.readPos -= d;
        StreamBase<T>::status = Ok;
    }
    return StreamBase<T>::position;
}
template <class T>
__int64
BufferedInputStream<T>::skip(__int64 ntoskip) {
    const T *begin;
    int nread;
    __int64 skipped = 0;
    while (ntoskip) {
        int step = (int)((ntoskip > buffer.size) ?buffer.size :ntoskip);
        nread = read(begin, 1, step);
        if (nread <= 0) {
            return skipped;
        }
        ntoskip -= nread;
        skipped += nread;
    }
    return skipped;
}
}





#endif