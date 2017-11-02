
#ifndef _Lan_util_StreamBase_
#define _Lan_util_StreamBase_

#include <string>

//#define INT32MAX 0x7FFFFFFFL

namespace jstreams {

enum StreamStatus { Ok, Eof, Error };
/*
Ϊ��ȡ���ֲ�ͬ�ļ���ʽ�Ļ���
������ͳһ��ʽ������������Դ
*/

template <class T>
class StreamBase {
protected:
    __int64 size;     //�����ַ����Ĵ�С���ַ�������
    __int64 position; //��ȡ�ĵ�ǰ���ַ�����
    std::string error;
    StreamStatus status; //�ַ����Ƿ����״̬
public:
    StreamBase() :size(-1), position(0), status(Ok){ }
    virtual ~StreamBase(){}
    //�������ĳ�����Ϣ�����û�д����򷵻ؿ��ַ�
    const char* getError() const { return error.c_str(); }
    StreamStatus getStatus() const { return status; }
    //��ȡ���еĵ�ǰλ�ã�������������صĲ�����������������
    __int64 getPosition() const { return position; }
   //������Ĵ�С�������ǰ����δ֪��С���򷵻�-1������ѵ������Ľ�β�����Ĵ�С��Ȼ�ǿ�֪��
    __int64 getSize() const { return size; }
    //�����ж����ַ�
	//start 
	//min �����ж������ַ�����
	//max �����ж���������ַ�����
	//���ز��� �����ж������ַ�����������Ѷ����ַ�����򷵻�-1�������������򷵻�-2
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
