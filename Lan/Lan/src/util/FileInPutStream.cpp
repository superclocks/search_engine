
//#include "jstreamsconfig.h"
#include "FileInPutStream.h"
#include <cerrno>
#include <cstring>
namespace jstreams {

const int FileInputStream::defaultBufferSize = 1048576;
FileInputStream::FileInputStream(const char *filepath, int buffersize) {
    // try to open the file for reading
    file = fopen(filepath, "rb");
    this->filepath = filepath;
    if (file == 0) {
        // handle error
        error = "Could not read file '";
        error += filepath;
        error += "': ";
        error += strerror(errno);
        status = Error;
        return;
    }
    // determine file size. if the stream is not seekable, the size will be -1
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // if the file has size 0, make sure that it's really empty
    // this is useful for filesystems like /proc that report files as size 0
    // for files that do contain content
    if (size == 0) {
        char dummy[1];
        size_t n = fread(dummy, 1, 1, file);
        if (n == 1) {
            size = -1;
            fseek(file, 0, SEEK_SET);
        } else {
            fclose(file);
            file = 0;
            return;
        }
    }

    // allocate memory in the buffer
    int bufsize = (size <= buffersize) ?size+1 :buffersize;
    mark(bufsize);
}
FileInputStream::~FileInputStream() {
    if (file) {
        if (fclose(file)) {
            // handle error
            error = "Could not close file '" + filepath + "'.";
        }
    }
}
int
FileInputStream::fillBuffer(char* start, int space) {
    if (file == 0) return -1;
    // read into the buffer
    int nwritten = fread(start, 1, space, file);
    // check the file stream status
    if (ferror(file)) {
        error = "Could not read from file '" + filepath + "'.";
        fclose(file);
        file = 0;
        status = Error;
        return -1;
    }
    if (feof(file)) {
        fclose(file);
        file = 0;
    }
    return nwritten;
}
}
