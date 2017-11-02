#ifndef _Lan_util_Reader_
#define _Lan_util_Reader_
#include "StreamBase.h"
#include "StringReader.h"
#include "BufferedStream.h"
#include "FileInPutStream.h"

namespace Lan
{
	namespace util
	{
class Reader
{
typedef jstreams::StreamBase<char> jsReader;
public:
	bool deleteReader;
	jsReader* reader;
	Reader(jsReader* reader, bool deleteReader)
	{
		this->reader=reader;
		this->deleteReader=deleteReader;
	}
	virtual ~Reader()
	{
		if(deleteReader)
		{
			delete reader;
		}
		reader=NULL;
	}
	inline int read()
	{
		const char* b;
		int nread = reader->read(b,1,1);
		if(nread<-1)
		{
			//_CLTHROWA(CL_ERR_IO,reader->getError() );
			printf(reader->getError());
		}
		else if(nread==-1)
		{
			return -1;
		}
		else
		{
			return b[0];
		}
	}

	inline int read(const char*& start){
		int nread = reader->read(start,1,0);
		if ( nread < -1 ) //if not eof
			//_CLTHROWA(CL_ERR_IO,reader->getError());
			printf(reader->getError());
		else
			return nread;
	}
	inline int read(const char*& start, int len){
		int nread = reader->read(start, len, len);
		if ( nread < -1 ) //if not eof
			//_CLTHROWA(CL_ERR_IO,reader->getError());
			printf(reader->getError());
		else
			return nread;
	}
	inline __int64 skip(__int64 ntoskip){
		__int64 skipped = reader->skip(ntoskip);
		if ( skipped < 0 ) 
			//_CLTHROWA(CL_ERR_IO,reader->getError());
			printf(reader->getError());
		else
			return skipped;
	}
	inline __int64 mark(int readAheadlimit){
		__int64 pos = reader->mark(readAheadlimit);
		if ( pos < 0 )
			//_CLTHROWA(CL_ERR_IO,reader->getError());
			printf(reader->getError());
		else
			return pos;
	}
	__int64 reset(__int64 pos){
		__int64 r = reader->reset(pos);
		if ( r < 0 )
			//_CLTHROWA(CL_ERR_IO,reader->getError());
			printf(reader->getError());
		else
			return r;
	}
};

class StringReader: public Reader{
public:
	StringReader ( const char* value );
    StringReader ( const char* value, const int length );
    StringReader ( const char* value, const int length, bool copyData );
	~StringReader();
};

/** A very simple inputstreamreader implementation. For a
* more complete InputStreamReader, use the jstreams version
* located in the contrib package
*/
class SimpleInputStreamReader: public jstreams::BufferedInputStream<char>{
    int decode(char* start, int space);
	int encoding;
	enum{
		ASCII=1,
		UTF8=2,
		UCS2_LE=3
	};
    bool finishedDecoding;
    jstreams::StreamBase<char>* input;
    int charsLeft;

    jstreams::InputStreamBuffer<char> charbuf;
    int fillBuffer(char* start, int space);
public:
	SimpleInputStreamReader(jstreams::StreamBase<char> *i, const char* encoding);
	~SimpleInputStreamReader();
};

/**
* A helper class which constructs a FileReader with a specified
* simple encodings, or a given inputstreamreader
*/
class FileReader: public Reader{
	jstreams::FileInputStream* input;
public:
	FileReader ( const char* path, const char* enc,
        const int cachelen = 13,
        const int cachebuff = 14 ); //todo: optimise these cache values
	~FileReader ();

    int read(const char*& start, int _min, int _max);
    __int64 mark(int readlimit);
    __int64 reset(__int64);
};
	}
}




#endif