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

	virtual void writeByte(const unsigned char b)=0; //写入一个byte
	virtual void writeBytes(const unsigned char* b,const int length) =0; //写入byte数组
	void writeInt(const int i); //写入四位byte的int数据
	void writeVInt(const int vi); //写入一个变长的VInt数据类型，它可能包含多个byte
	void writeLong(const __int64 i); //写入八位byte的long数据
	void writeVLong(const __int64 vi); //写入变长的long型数据
	void writeString(const char* s,const int length); //写入字符串
	void writeChars(const char* s,const int start,const int length); //写入一系类UTF-8编码的字符串
	virtual void close()=0;
	virtual __int64 getFilePointer() const =0; //返回文件中的当前位置
	virtual void seek(const __int64 pos)=0; //设置文件中的当前位置
	virtual __int64 length() = 0; //文件中的byte长度
	virtual void flush() = 0; //将缓冲区中的数据写入磁盘
};

class BufferedIndexOutput:public IndexOutput
{
public:
	//LUCENE_STATIC_CONSTANT(int32_t, BUFFER_SIZE=LUCENE_STREAM_BUFFER_SIZE);
	enum { Buffer_Size=Lan_Stream_Buffer_Size };
private:
	unsigned char* buffer;
	__int64 bufferStart;        //缓冲区文件中的位置
	int bufferPosition;     //缓冲区中的位置
public:
	BufferedIndexOutput();
	virtual ~BufferedIndexOutput();
	virtual void writeByte(const unsigned char b); //写入一个byte
	virtual void writeBytes(const unsigned char* b,const int length); //写入byte数组
	void close();
	__int64 getFilePointer() const; //返回文件中的当前位置
	virtual void seek(const __int64 pos); //设置文件中的当前位置
	virtual __int64 length() = 0; //文件中的byte长度
	virtual void flush(); //将缓冲区中的数据写入磁盘 
protected:
	virtual void flushBuffer(const unsigned char* b,const int len)=0; //在output的当前位置写入bytes
};




}}




#endif