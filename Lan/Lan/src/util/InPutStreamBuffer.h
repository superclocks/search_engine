
#ifndef _Lan_util_InPutStreamBuffer_
#define _Lan_util_InPutStreamBuffer_

#include <cstdlib>

namespace jstreams {

template <class T>
class InputStreamBuffer {
private:
public:
    T* start;
    int size;
    T* readPos;
    int avail;

    InputStreamBuffer();
    ~InputStreamBuffer();
    void setSize(int size);
    int read(const T*& start, int max=0);

     int makeSpace(int needed);
};

template <class T>
InputStreamBuffer<T>::InputStreamBuffer() {
    readPos = start = 0;
    size = avail = 0;
}
template <class T>
InputStreamBuffer<T>::~InputStreamBuffer() {
    free(start);
}
template <class T>
void
InputStreamBuffer<T>::setSize(int size) {
    // store pointer information
    int offset = (int)(readPos - start);

	// allocate memory in the buffer
    if ( start == 0 )
		start = (T*)malloc(size*sizeof(T));
	else
		start = (T*)realloc(start, size*sizeof(T));
    this->size = size;

    // restore pointer information
    readPos = start + offset;
}
template <class T>
int
InputStreamBuffer<T>::makeSpace(int needed) {
    // determine how much space is available for writing
    int space = size - ((int)(readPos - start)) - avail;
    if (space >= needed) {
        // there's enough space
        return space;
    }

    if (avail) {
        if (readPos != start) {
//            printf("moving\n");
            // move data to the start of the buffer
            memmove(start, readPos, avail*sizeof(T));
            space += (int)(readPos - start);
            readPos = start;
        }
    } else {
        // we may start writing at the start of the buffer
        readPos = start;
        space = size;
    }
    if (space >= needed) {
        // there's enough space now
        return space;
    }

    // still not enough space, we have to allocate more
//    printf("resize %i %i %i %i %i\n", avail, needed, space, size + needed - space, size);
    setSize(size + needed - space);
    return needed;
}
template <class T>
int
InputStreamBuffer<T>::read(const T*& start, int max) {
    start = readPos;
    if (max <= 0 || max > avail) {
        max = avail;
    }
    readPos += max;
    avail -= max;
    return max;
}

} // end namespace jstreams

#endif
