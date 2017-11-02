#ifndef _Lan_store_TransactionalRAMDirectory_
#define _Lan_store_TransactionalRAMDirectory_
#include "RAMDirectory.h"
#include "VoidList.h"
namespace Lan
{namespace store{

class TransactionalRAMDirectory:public RAMDirectory
{
private:
	typedef Lan::util::CLSet<const char* , void* ,Lan::util::Compare::Char> FilenameSet;
	FilenameSet filesToRemoveOnAbort;

	typedef Lan::util::CLSet<const char* ,Lan::store::RAMFile* , Lan::util::Compare::Char,Lan::util::Deletor::acArray,Lan::util::Deletor::Object<RAMFile>> TransFileMap;
	TransFileMap filesToRestoreOnAbort;

	bool transOpen;
	void transResolved();
	bool archiveOrigFileIfNecessary(const char* name);
    void unarchiveOrigFile(const char* name);
protected:
	bool doDeleteFile(const char* name);
public:
	TransactionalRAMDirectory();
	virtual ~TransactionalRAMDirectory();

	void transStart();
	void transAbort();
	void renameFile(const char* from, const char* to);
	IndexOutput* createOutput(const char* name);
	void close();
};


}}




#endif