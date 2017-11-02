/*------------------------------------------------------------------------------
* Copyright (C) 2003-2006 Ben van Klinken and the CLucene Team
* 
* Distributable under the terms of either the Apache License (Version 2.0) or 
* the GNU Lesser General Public License, as specified in the COPYING file.
------------------------------------------------------------------------------*/
//#include "CLucene/StdHeader.h"
#include "Reader.h"
namespace Lan
{
	namespace util
	{

StringReader::StringReader ( const char* value ):
  Reader(NULL,true){
	  reader = new jstreams::StringReader<char>(value);
}
StringReader::StringReader ( const char* value, const int length ):
  Reader(NULL,true){
	  reader = new jstreams::StringReader<char>(value,length);
}
StringReader::StringReader ( const char* value, const int length, bool copyData ):
  Reader(NULL,true){
	  reader = new jstreams::StringReader<char>(value,length, copyData);
}
StringReader::~StringReader(){
}


FileReader::FileReader ( const char* path, const char* enc,
						 const int cachelen, const int /*cachebuff*/ ):
	Reader(NULL, true)
{
	this->input = new jstreams::FileInputStream(path, cachelen);
	this->reader = new SimpleInputStreamReader(this->input,enc); //(this is a jstream object)
}

FileReader::~FileReader (){
    if (input) 
		delete input;
}
int FileReader::read(const char*& start, int _min, int _max) {
    return reader->read(start, _min, _max);
}
__int64 FileReader::mark(int readlimit) {
    return reader->mark(readlimit);
}
__int64 FileReader::reset(__int64 newpos) {
    return reader->reset(newpos);
}



SimpleInputStreamReader::SimpleInputStreamReader(jstreams::StreamBase<char> *i, const char* enc)
{
    finishedDecoding = false;
    input = i;
    charbuf.setSize(262);

	if ( strcmp(enc,"ASCII")==0 )
		encoding = ASCII;
#ifdef _UCS2
	else if ( strcmp(enc,"UTF-8")==0 )
		encoding = UTF8;
	else if ( strcmp(enc,"UCS-2LE")==0 )
		encoding = UCS2_LE;
#endif
	else
		//_CLTHROWA(CL_ERR_IllegalArgument,"Unsupported encoding, use jstreams iconv based instead");
		printf("Unsupported encoding, use jstreams iconv based instead");
	mark(262);
    charsLeft = 0;
}
SimpleInputStreamReader::~SimpleInputStreamReader(){
	input = NULL;
}
int SimpleInputStreamReader::decode(char* start, int space){
	// decode from charbuf
    const char *inbuf = charbuf.readPos;
    const char *inbufend = charbuf.readPos + charbuf.avail;
    char *outbuf = start;
	const char *outbufend = outbuf + space;

	if ( encoding == ASCII ){
		while ( outbuf<outbufend && inbuf<inbufend ){
			*outbuf = *inbuf;
			outbuf++;
			inbuf++;
		}
		
#ifdef _UCS2
	}
	else if ( encoding == UCS2_LE ){
		while ( outbuf<outbufend && (inbuf+1)<inbufend ){
			uint8_t c1 = *inbuf;
			uint8_t c2 = *(inbuf+1);
			unsigned short c = c1 | (c2<<8);
			
			#ifdef _UCS2
				*outbuf = c;
			#else
				*outbuf = LUCENE_OOR_CHAR(c);
			#endif
			outbuf++;
			inbuf+=2;
		}

	}else if ( encoding == UTF8 ){
		while ( outbuf<outbufend && inbuf<inbufend ){
			size_t utflen = lucene_utf8charlen(inbuf);
			if ( utflen==0 ){
				error = "Invalid multibyte sequence.";
				status = jstreams::Error;
				return -1;
			}else if ( inbuf+utflen > inbufend ){
				break; //character incomplete
			}else{
				size_t rd = lucene_utf8towc(outbuf,inbuf,inbufend-inbuf);
				if ( rd == 0 ){
					error = "Invalid multibyte sequence.";
					status = jstreams::Error;
					return -1;
				}else{
					inbuf+=rd;
					outbuf++;
				}
			}
		}
#endif //_UCS2
	}else
		//_CLTHROWA(CL_ERR_Runtime,"Unexpected encoding");
		printf("Unexpected encoding");
	if ( outbuf < outbufend ) { 
		//we had enough room to convert the entire input
		if ( inbuf < inbufend ) {
			// last character is incomplete
			// move from inbuf to the end to the start of
			// the buffer
			memmove(charbuf.start, inbuf, inbufend-inbuf);
			charbuf.readPos = charbuf.start;
			charbuf.avail = inbufend-inbuf;
		} else if ( outbuf < outbufend ) { //input sequence was completely converted
			charbuf.readPos = charbuf.start;
			charbuf.avail = 0;
			if (input == NULL) {
				finishedDecoding = true;
			}
		}
	} else {
        charbuf.readPos += charbuf.avail - (inbufend-inbuf);
        charbuf.avail = inbufend-inbuf;
	}
    return outbuf-start;
}

int SimpleInputStreamReader::fillBuffer(char* start, int space) {
    // fill up charbuf
    if (input && charbuf.readPos == charbuf.start) {
        const char *begin;
        int numRead;
        numRead = input->read(begin, 1, charbuf.size - charbuf.avail);
        //printf("filled up charbuf\n");
        if (numRead < -1) {
            error = input->getError();
            status = jstreams::Error;
            input = 0;
            return numRead;
        }
        if (numRead < 1) {
            // signal end of input buffer
            input = 0;
            if (charbuf.avail) {
                error = "stream ends on incomplete character";
                status = jstreams::Error;
            }
            return -1;
        }
        // copy data into other buffer
        memmove( charbuf.start + charbuf.avail, begin, numRead * sizeof(char));
        charbuf.avail = numRead + charbuf.avail;
    }
    // decode
    int n = decode(start, space);
    //printf("decoded %i\n", n);
    return n;
}

	}
}