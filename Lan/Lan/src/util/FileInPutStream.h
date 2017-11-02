
#ifndef _Lan_util_FileInPutStream_
#define _Lan_util_FileInPutStream_

#include "BufferedStream.h"

namespace jstreams {

class FileInputStream : public BufferedInputStream<char> {
private:
    FILE *file;
    std::string filepath;

public:
    static const int defaultBufferSize;
    FileInputStream(const char *filepath, int buffersize=defaultBufferSize);
    ~FileInputStream();
    int fillBuffer(char* start, int space);
};

} // end namespace jstreams

#endif

