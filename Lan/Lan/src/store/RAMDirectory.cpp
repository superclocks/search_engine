#include "RAMDirectory.h"
#include "Directory.h"
#include "IndexOutput.h"
#include "CompilerMsvc.h"

using namespace Lan::util;
namespace Lan
{namespace store{
//RAMFile实现
RAMFile::RAMFile()
{
	length=0;
	lastModified=Lan::util::Misc::currentTimeMillis();
}
RAMFile::~RAMFile()
{

}
//RAMIndexOutput类的实现
RAMIndexOutput::RAMIndexOutput():file(new RAMFile())
{
	pointer = 0;
	deleteFile = true;
}
RAMIndexOutput::RAMIndexOutput(RAMFile* f):file(f)
{
	pointer = 0;
	deleteFile = false;
}
RAMIndexOutput::~RAMIndexOutput()
{
	if(deleteFile)
	{
		if(file!=NULL)
		{
			delete file;
			file = NULL;
		}
	}
	else
	{
		file = NULL;
	}
}
void RAMIndexOutput::writeTo(IndexOutput* out)
{
	flush();
	__int64 end = file->length;
	__int64 pos = 0;
	int p = 0;
	while(pos<end)
	{
		int length = Lan::store::BufferedIndexOutput::Buffer_Size;
		__int64 nextPos = pos + length;
		if(nextPos > end)
		{
			length = (int)(end - pos);
		}
		out->writeBytes((unsigned char*)file->buffers[p++],length);
		pos = nextPos;
	}
}
void RAMIndexOutput::reset()
{
	seek(_ILONGLONG(0));
	file->length = _ILONGLONG(0);
}
void RAMIndexOutput::flushBuffer(const unsigned char* src, const int len)
{
	unsigned char* b = NULL;
	int bufferPos = 0;
	while(bufferPos != len)
	{
		int bufferNumber = pointer/Lan::store::BufferedIndexOutput::Buffer_Size;
		int bufferOffset = pointer%Lan::store::BufferedIndexOutput::Buffer_Size;
		int bytesInBuffer = Lan::store::BufferedIndexOutput::Buffer_Size - bufferOffset;
		int remainInSrcBuffer = len - bufferPos;
		int bytesToCopy = bytesInBuffer >= remainInSrcBuffer ? remainInSrcBuffer : bytesInBuffer;
		if(bufferNumber == file->buffers.size())
		{
			b=new unsigned char[Lan::store::BufferedIndexOutput::Buffer_Size];
			file->buffers.push_back(b);
		}
		else
		{
			b=file->buffers[bufferNumber];
		}
		memcpy(b+bufferOffset,src+bufferPos,bytesToCopy*sizeof(unsigned char));
		bufferPos += bytesToCopy;
		pointer += bytesToCopy;
	}
	if (pointer > file->length)
      file->length = pointer;

    file->lastModified = Misc::currentTimeMillis();
}
void RAMIndexOutput::close() 
{
    BufferedIndexOutput::close();
}

  /** Random-at methods */
  void RAMIndexOutput::seek(const __int64 pos)
  {
    BufferedIndexOutput::seek(pos);
    pointer = (int)pos;
  }
  __int64 RAMIndexOutput::length()
  {
    return file->length;
  }

//RAMDirectory实现
RAMDirectory::RAMDirectory():Directory(),files(true,true)
{

}
RAMDirectory::~RAMDirectory()
{
}
void RAMDirectory::list(vector<string>* names) const
{
	//SCOPED_LOCK_MUTEX(files_mutex);

	FileMap::const_iterator itr = files.begin();
    while (itr != files.end())
	{
        names->push_back(itr->first);
        ++itr;
    }
}
void RAMDirectory::renameFile(const char* from, const char* to) 
{
	//SCOPED_LOCK_MUTEX(files_mutex);
	FileMap::iterator itr = files.find(from);

    /* DSR:CL_BUG_LEAK:
    ** If a file named $to already existed, its old value was leaked.
    ** My inclination would be to prevent this implicit deletion with an
    ** exception, but it happens routinely in CLucene's internals (e.g., during
    ** IndexWriter.addIndexes with the file named 'segments'). */
    if (files.exists(to)) {
      files.remove(to);
    }
	if ( itr == files.end() ){
		char tmp[1024];
		_snprintf(tmp,1024,"cannot rename %s, file does not exist",from);
		//_CLTHROWT(CL_ERR_IO,tmp);
	}
	//CND_PRECONDITION(itr != files.end(), "itr==files.end()")
	if(itr==files.end())
	{
		printf("itr==files.end()");
		assert(0);
	}
	RAMFile* file = itr->second;
    files.removeitr(itr,false,true);
	//
	 size_t len = strlen(to);
    char* ret = new char[len+1];
    strncpy(ret,to,len+1);
	//
    files.put(ret, file);
}

IndexOutput* RAMDirectory::createOutput(const char* name)
{
	//SCOPED_LOCK_MUTEX(files_mutex);
	const char* n=files.getKey(name);
	if(n!=NULL)
	{
		RAMFile* rf = files.get(name);
		if(rf!=NULL)
		{
			delete rf;
			rf=NULL;
		}
	}
	else
	{
		//n = STRDUP_AtoA(name);
		int len=strlen(name);
		char* ret=new char[len];
		strncpy(ret,name,len+1);
		n=ret;
	}
	RAMFile* file = new RAMFile();
	file->filename=n;
	files[n]=file;
	return new RAMIndexOutput(file);
}

bool RAMDirectory::doDeleteFile(const char* name)
{
	//SCOPED_LOCK_MUTEX(files_mutex);
    files.remove(name);
    return true;
}
bool RAMDirectory::fileExists(const char* name)const
{
	//SCOPED_LOCK_MUTEX(files_mutex);
	return files.exists(name);
}

void RAMDirectory::close()
{
	//SCOPED_LOCK_MUTEX(files_mutex);
	files.clear();
}

}}
