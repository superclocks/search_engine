#ifndef _Lan_store_IndexOutput_
#define _Lan_store_IndexOutput_
#include <stdio.h>
#include <assert.h>
#include <string>
#include "LConfig.h"

namespace Lan
{namespace store{
class IndexOutput
{
private:
	bool isclosed;
public:
	IndexOutput();
	virtual ~IndexOutput();

	virtual void writeByte(const unsigned char b)=0; //д��һ��byte
	virtual void writeBytes(const unsigned char* b,const int length) =0; //д��byte����
	void writeInt(const int i); //д����λbyte��int����
	void writeVInt(const int vi); //д��һ���䳤��VInt�������ͣ������ܰ������byte
	void writeLong(const __int64 i); //д���λbyte��long����
	void writeVLong(const __int64 vi); //д��䳤��long������
	void writeString(const char* s,const int length); //д���ַ���
	void writeChars(const char* s,const int start,const int length); //д��һϵ��UTF-8������ַ���
	virtual void close()=0;
	virtual __int64 getFilePointer() const =0; //�����ļ��еĵ�ǰλ��
	virtual void seek(const __int64 pos)=0; //�����ļ��еĵ�ǰλ��
	virtual __int64 length() = 0; //�ļ��е�byte����
	virtual void flush() = 0; //���������е�����д�����
};

class BufferedIndexOutput:public IndexOutput
{
public:
	//LUCENE_STATIC_CONSTANT(int32_t, BUFFER_SIZE=LUCENE_STREAM_BUFFER_SIZE);
	enum { Buffer_Size=Lan_Stream_Buffer_Size };
private:
	unsigned char* buffer;
	__int64 bufferStart;        //�������ļ��е�λ��
	int bufferPosition;     //�������е�λ��
public:
	BufferedIndexOutput();
	virtual ~BufferedIndexOutput();
	virtual void writeByte(const unsigned char b); //д��һ��byte
	virtual void writeBytes(const unsigned char* b,const int length); //д��byte����
	void close();
	__int64 getFilePointer() const; //�����ļ��еĵ�ǰλ��
	virtual void seek(const __int64 pos); //�����ļ��еĵ�ǰλ��
	virtual __int64 length() = 0; //�ļ��е�byte����
	virtual void flush(); //���������е�����д����� 
protected:
	virtual void flushBuffer(const unsigned char* b,const int len)=0; //��output�ĵ�ǰλ��д��bytes
};




}}




#endif