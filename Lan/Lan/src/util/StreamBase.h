
#ifndef _Lan_util_StreamBase_
#define _Lan_util_StreamBase_

#include <string>

//#define INT32MAX 0x7FFFFFFFL

namespace jstreams {

enum StreamStatus { Ok, Eof, Error };
/*
为读取多种不同文件格式的基类
该类用统一方式访问数据流资源
*/

template <class T>
class StreamBase {
protected:
    __int64 size;     //输入字符串的大小（字符个数）
    __int64 position; //读取的当前的字符个数
    std::string error;
    StreamStatus status; //字符串是否结束状态
public:
    StreamBase() :size(-1), position(0), status(Ok){ }
    virtual ~StreamBase(){}
    //返回最后的出错信息，如果没有错误则返回空字符
    const char* getError() const { return error.c_str(); }
    StreamStatus getStatus() const { return status; }
    //获取流中的当前位置，从这个函数返回的参数可以重新设置流
    __int64 getPosition() const { return position; }
   //获得流的大小，如果当前的流未知大小，则返回-1，如果已到达流的结尾则流的大小依然是可知的
    __int64 getSize() const { return size; }
    //从流中读出字符
	//start 
	//min 从流中读出的字符个数
	//max 从流中读出的最大字符个数
	//返回参数 从流中读出的字符个数，如果已读到字符最后则返回-1，如果错误产生则返回-2
    virtual int read(const T*& start, int min, int max) = 0;
   
    virtual __int64 skip(__int64 ntoskip);
   
    virtual __int64 reset(__int64 pos) = 0;
    __int64 mark(int readlimit) {
        __int64 p = getPosition();
        const T* ptr;
        read(ptr, readlimit, -1);
        return reset(p);
    }
};
#define SKIPSTEP 1024
template <class T>
__int64
StreamBase<T>::skip(__int64 ntoskip) {
    const T *begin;
    int nread;
    __int64 skipped = 0;
    while (ntoskip) {
        int step = (int)((ntoskip > SKIPSTEP) ?SKIPSTEP :ntoskip);
        nread = read(begin, 1, step);
        if (nread < -1 ) {
            // an error occurred
            return nread;
        } else if (nread < 1) {
            ntoskip = 0;
        } else {
            skipped += nread;
            ntoskip -= nread;
        }
    }
    return skipped;
}

} // end namespace jstreams

#endif
