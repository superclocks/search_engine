#ifndef _Lan_store_RAMDirectory_
#define _Lan_store_RAMDirectory_
#include <string>
#include "Directory.h"
#include "VoidMap.h"
#include "Misc.h"
#include "Equators.h"
#include "VoidList.h"
#include "IndexOutput.h"
using namespace std;


namespace Lan
{namespace store{
class RAMFile
{
public:
	Lan::util::CLVector<unsigned char*,Lan::util::Deletor::Array<unsigned char> > buffers;
	__int64 length;
	unsigned __int64 lastModified;
	const char* filename;
	RAMFile();
	~RAMFile();
};
//RAMIndexOutput类向缓冲区写入信息
class RAMIndexOutput:public BufferedIndexOutput
{
protected:
	RAMFile* file;
	int pointer;
	bool deleteFile;
	void flushBuffer(const unsigned char* src,const int length);
public:
	RAMIndexOutput(RAMFile* f);
	RAMIndexOutput();
	virtual ~RAMIndexOutput();
	virtual void close();
	virtual void seek(const __int64 pos);
	__int64 length();
	void reset();
	void writeTo(IndexOutput* output);
};

class RAMDirectory:public Directory
{
typedef Lan::util::CLHashMap<const char*,RAMFile*,
		Lan::util::Compare::Char,Lan::util::Equals::Char,
		Lan::util::Deletor::acArray,Lan::util::Deletor::Object<RAMFile>> FileMap;

protected:
	virtual bool doDeleteFile(const char* name);
	void _copyFromDir(Directory* dir,bool closeDir);
	FileMap files;
public:
	void list(vector<string>* name)const;

	RAMDirectory();
	virtual ~RAMDirectory();
	RAMDirectory(Directory* dir);
	RAMDirectory(const char* dir);
	bool fileExists(const char* name)const;
	//__int64 fileModified(const char* name)const;
	//__int64 fileLength(const char* name)const;

	virtual void renameFile(const char* from, const char* to);
	virtual IndexOutput* createOutput(const char* name);

	virtual void close();

};


}}

#endif