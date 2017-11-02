#ifndef _Lan_index_TermInfosWriter_
#define _Lan_index_TermInfosWriter_
#include "Directory.h"
#include "FieldInfos.h"
#include "TermInfo.h"
#include "Term.h"

namespace Lan
{namespace index{
class TermInfosWriter
{
private:
	FieldInfos* fieldInfos;
	Lan::store::IndexOutput* output;
	Term* lastTerm;
	TermInfo* lastTi;
	__int64 size;
	__int64 lastIndexPointer;
	bool isIndex;
	TermInfosWriter* other;

	TermInfosWriter(Lan::store::Directory* directory,const char* segment,FieldInfos* fis, int interval,bool isIndex);
public:
	enum { FORMAT=-2 };
	int indexInterval;
	int skipInterval;
	TermInfosWriter(Lan::store::Directory* ditrectory,const char* segment, FieldInfos* fis, int interval);
	~TermInfosWriter();
	void add(Term* term,const TermInfo* ti);
	void close();
private:
	void initialise(Lan::store::Directory* directory, const char* segment,int interval, bool IsIndex);
	void writeTerm(Term* term);
};


}}



#endif