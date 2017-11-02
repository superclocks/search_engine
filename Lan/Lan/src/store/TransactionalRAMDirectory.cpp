#include "TransactionalRAMDirectory.h"

using namespace Lan::util;

namespace Lan
{namespace store{

TransactionalRAMDirectory::TransactionalRAMDirectory():
RAMDirectory(),filesToRestoreOnAbort(true,true)
{
	transOpen = false;
}
TransactionalRAMDirectory::~TransactionalRAMDirectory()
{
}
bool TransactionalRAMDirectory::archiveOrigFileIfNecessary(const char* name)
{
	if(fileExists(name) && filesToRemoveOnAbort.find(name) == filesToRemoveOnAbort.end())
	{
		const char* origName = files.getKey(name);
		RAMFile* origFile = files.get(name);
		files.remove(name, true, true);
		filesToRestoreOnAbort.put(origName,origFile);
		if(fileExists(name))
		{
			printf("File should not exist immediately after archival.");
			assert(0);
		}
		return true;
	}
	return false;
}
bool TransactionalRAMDirectory::doDeleteFile(const char* name)
{
	return true;
}
void TransactionalRAMDirectory::transStart()
{
	/* if (transOpen) {
      _CLTHROWA(CL_ERR_RAMTransaction,"Must resolve previous transaction before starting another.");
    }

    CND_CONDITION(filesToRemoveOnAbort.size() == 0,
        "filesToRemoveOnAbort should have been cleared by either its"
        " constructor or transResolved."
      );
    CND_CONDITION(filesToRestoreOnAbort.size() == 0,
        "filesToRestoreOnAbort should have been cleared by either its"
        " constructor or transResolved."
      );*/

    transOpen = true;
}
void TransactionalRAMDirectory::renameFile(const char* from, const char* to) {
   
    if (transOpen) {
      //_CLTHROWA(CL_ERR_RAMTransaction,"TransactionalRAMDirectory disallows renameFile during a transaction.");
    }
    RAMDirectory::renameFile(from, to);
  }
IndexOutput* TransactionalRAMDirectory::createOutput(const char* name)
{
	if(!transOpen)
	{
		return RAMDirectory::createOutput(name);
	}
	bool wasOriginalAndWasArchived = archiveOrigFileIfNecessary(name);
	try
	{
		IndexOutput* ret = RAMDirectory::createOutput(name);
		filesToRemoveOnAbort.put(files.getKey(name),NULL);
		return ret;
	}
	catch(...)
	{
		/*if (wasOriginalAndWasArchived) 
		{
			unarchiveOrigFile(name);
		}
		throw;*/
	}
}
void TransactionalRAMDirectory::close()
{
	if(transOpen)
	{
		transAbort();
	}
	RAMDirectory::close();
}
void TransactionalRAMDirectory::transAbort()
{
	if (!transOpen) 
	{
      //_CLTHROWA(CL_ERR_RAMTransaction,"There is no open transaction.");
		printf("There is no open transaction.");
	}
}

}}