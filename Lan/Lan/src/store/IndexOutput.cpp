#include "IndexOutput.h"
namespace Lan
{namespace store{

IndexOutput::IndexOutput()
{
}
IndexOutput::~IndexOutput()
{
}
BufferedIndexOutput::BufferedIndexOutput()
{
	//buffer = _CL_NEWARRAY(uint8_t, BUFFER_SIZE );
	buffer=new unsigned char[1024];
	bufferStart=0;
	bufferPosition=0;
}
BufferedIndexOutput::~BufferedIndexOutput()
{
	if(buffer!=NULL)
	{
		close();
	}
}

void BufferedIndexOutput::close()
{
	flush();
	//_CLDELETE_ARRAY( buffer );
	if(buffer!= NULL)
	{
		delete[] buffer;
		buffer=NULL;
	}
	bufferStart=0;
	bufferPosition=0;
}
void BufferedIndexOutput::writeByte(const unsigned char b)
{
	//CND_PRECONDITION(buffer!=NULL,"IndexOutput is closed")
	if(buffer==NULL)
	{
		printf("IndexOutput is closed");
		assert(0);
	}
	if(bufferPosition>=Lan_Stream_Buffer_Size)
	{
		flush();
	}
	buffer[bufferPosition++]=b;
}
void BufferedIndexOutput::writeBytes(const unsigned char* b,const int length)
{
	if(length<0)
	{
		printf("IO Argument Error. Value must be a positive value.");
		assert(0);
	}
	int bytesLeft=Lan_Stream_Buffer_Size-bufferPosition;
	if(bytesLeft>=length)
	{
		memcpy(buffer+bufferPosition,b,length);
		bufferPosition+=length;
		if(Lan_Stream_Buffer_Size-bufferPosition==0)
			flush();
	}
	else
	{
		if(length>Lan_Stream_Buffer_Size)
		{
			if(bufferPosition>0)
				flush();
			flushBuffer(b,length);
			bufferStart+=length;
		}
		else
		{
			__int64 pos=0;
			int pieceLength;
			while(pos<length)
			{
				if(length-pos<bytesLeft)
					pieceLength=length-pos;
				else
					pieceLength=bytesLeft;
				memcpy(buffer + bufferPosition, b + pos, pieceLength);
				pos += pieceLength;
				bufferPosition += pieceLength;
				// if the buffer is full, flush it
				bytesLeft = Lan_Stream_Buffer_Size - bufferPosition;
				if (bytesLeft == 0) 
				{
					  flush();
					  bytesLeft = Lan_Stream_Buffer_Size;
				}
			}
		}
	}
}
void IndexOutput::writeInt(const int i)
{
	writeByte((unsigned char)(i >> 24));
	writeByte((unsigned char)(i >> 16));
	writeByte((unsigned char)(i >> 8));
	writeByte((unsigned char) i );
}
void IndexOutput::writeVInt(const int vi)
{
	unsigned int i = vi;
	while((i & ~0x7F) != 0)
	{
		writeByte((unsigned char)((i & 0x7f) | 0x80));
		i >>= 7; //doing unsigned shift
	}
	 writeByte( (unsigned char)i );
}

void IndexOutput::writeLong(const __int64 i)
{
    writeInt((int) (i >> 32));
    writeInt((int) i);
}
void IndexOutput::writeVLong(const __int64 vi) 
{
	__int64 i = vi;
    while ((i & ~0x7F) != 0) {
      writeByte((unsigned char)((i & 0x7f) | 0x80));
      i >>= 7; //doing unsigned shift
    }
    writeByte((unsigned char)i);
}
void IndexOutput::writeString(const char* s, const int length )
{
    writeVInt(length);
    writeChars(s, 0, length);
}
void IndexOutput::writeChars(const char* s, const int start, const int length){
    if ( length < 0 || start < 0 )
	{
      //_CLTHROWA(CL_ERR_IllegalArgument, "IO Argument Error. Value must be a positive value.");
	  printf("IO Argument Error. Value must be a positive value.");
		assert(0);
	}

    const int end = start + length;
    for (int i = start; i < end; ++i) {
        const int code = (int)s[i];
        if (code >= 0x01 && code <= 0x7F)
			writeByte((unsigned char)code);
        else if (((code >= 0x80) && (code <= 0x7FF)) || code == 0) {
			writeByte((unsigned char)(0xC0 | (code >> 6)));
			writeByte((unsigned char)(0x80 | (code & 0x3F)));
        } else {
			writeByte((unsigned char)(0xE0 | (((unsigned int)code) >> 12))); //unsigned shift
			writeByte((unsigned char)(0x80 | ((code >> 6) & 0x3F)));
			writeByte((unsigned char)(0x80 | (code & 0x3F)));
        }
    }
  }

__int64 BufferedIndexOutput::getFilePointer() const{
    return bufferStart + bufferPosition;
  }

  void BufferedIndexOutput::seek(const __int64 pos) {
    flush();
    bufferStart = pos;
  }

  void BufferedIndexOutput::flush() {
    flushBuffer(buffer, bufferPosition);
    bufferStart += bufferPosition;
    bufferPosition = 0;
  }

}}