
#ifndef _Lan_util_SubInPutStream_
#define _Lan_util_SubInPutStream_

#include "StreamBase.h"

namespace jstreams {

template<class T>
class SubInputStream : public StreamBase<T> {
private:
    const __int64 offset;
    StreamBase<T> *input;
public:
    SubInputStream(StreamBase<T> *input, __int64 size=-1);
    int read(const T*& start, int min, int max);
    __int64 reset(__int64 newpos);
    __int64 skip(__int64 ntoskip);
};
template<class T>
SubInputStream<T>::SubInputStream(StreamBase<T> *i, __int64 length)
        : offset(i->getPosition()), input(i) {
    assert(length >= -1);
//    printf("substream offset: %lli\n", offset);
    StreamBase<T>::size = length;
}

template<class T>
int SubInputStream<T>::read(const T*& start, int min, int max) {
    if (StreamBase<T>::size != -1) {
        const __int64 left = StreamBase<T>::size - StreamBase<T>::position;
        if (left == 0) {
            return -1;
        }
        // restrict the amount of data that can be read
        if (max <= 0 || max > left) {
            max = (int)left;
        }
        if (min > max) min = max;
        if (left < min) min = (int)left;
    }
    int nread = input->read(start, min, max);
    if (nread < -1) {
        fprintf(stderr, "substream too short.\n");
        StreamBase<T>::status = Error;
        StreamBase<T>::error = input->getError();
    } else if (nread < min) {
        if (StreamBase<T>::size == -1) {
            StreamBase<T>::status = Eof;
            if (nread > 0) {
                StreamBase<T>::position += nread;
                StreamBase<T>::size = StreamBase<T>::position;
            }
        } else {
//            fprintf(stderr, "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! nread %i min %i max %i size %lli\n", nread, min, max, size);
//            fprintf(stderr, "pos %lli parentpos %lli\n", position, input->getPosition());
//            fprintf(stderr, "status: %i error: %s\n", input->getStatus(), input->getError());
            // we expected data but didn't get enough so that's an error
            StreamBase<T>::status = Error;
            StreamBase<T>::error = "Premature end of stream\n";
            nread = -2;
        }
    } else {
        StreamBase<T>::position += nread;
        if (StreamBase<T>::position == StreamBase<T>::size) {
            StreamBase<T>::status = Eof;
        }
    }
    return nread;
}

template<class T>
__int64 SubInputStream<T>::reset(__int64 newpos) {
//    fprintf(stderr, "subreset pos: %lli newpos: %lli offset: %lli\n", position,
//        newpos, offset);
    StreamBase<T>::position = input->reset(newpos + offset);
    if (StreamBase<T>::position < offset) {
        printf("###########\n");
        StreamBase<T>::status = Error;
        StreamBase<T>::error = input->getError();
    } else {
        StreamBase<T>::position -= offset;
        StreamBase<T>::status = input->getStatus();
    }
    return StreamBase<T>::position;
}

template<class T>
__int64 SubInputStream<T>::skip(__int64 ntoskip) {
//    printf("subskip pos: %lli ntoskip: %lli offset: %lli\n", position, ntoskip, offset);
    if (StreamBase<T>::size == StreamBase<T>::position) {
        StreamBase<T>::status = Eof;
        return -1;
    }
    if (StreamBase<T>::size != -1) {
        const __int64 left = StreamBase<T>::size - StreamBase<T>::position;
        // restrict the amount of data that can be skipped
        if (ntoskip > left) {
            ntoskip = left;
        }
    }
    __int64 skipped = input->skip(ntoskip);
    if (input->getStatus() == Error) {
        StreamBase<T>::status = Error;
        StreamBase<T>::error = input->getError();
    } else {
        StreamBase<T>::position += skipped;
        if (StreamBase<T>::position == StreamBase<T>::size) {
            StreamBase<T>::status = Eof;
        }
    }
    return skipped;
}

} //end namespace jstreams

#endif
