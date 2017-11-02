#include "IndexWriter.h"
#include "DocumentWriter.h"

using namespace Lan::store;
using namespace Lan::util;
using namespace Lan::analysis;
using namespace Lan::index;
using namespace Lan::document;
namespace Lan
{namespace index{

char* IndexWriter::newSegmentName()
{
	char buf[9];
	_i64toa(segmentInfos->counter++,buf,36);
	int rlen= strlen(buf)+2;
	char* ret=new char[rlen];
	strcpy_s(ret,rlen,"_");
	strncpy(ret+1,buf,rlen-1);
	return ret;
}
void IndexWriter::addDocument(Lan::document::Document* doc,Lan::analysis::Analyzer* analyzer)
{
	//CND_PRECONDITION(ramDirectory != NULL,"ramDirectory is NULL");
	if(ramDirectory==NULL)
	{
		printf("ramDirectory is NULL");
		assert(0);
	}
	if ( analyzer == NULL )
		analyzer = this->analyzer;

	ramDirectory->transStart();
	try {
		char* segmentName = newSegmentName();
	//	CND_CONDITION(segmentName != NULL, "segmentName is NULL");
	//	try {
	//		//Create the DocumentWriter using a ramDirectory and analyzer
	//		// supplied by the IndexWriter (this).
			DocumentWriter* dw = new DocumentWriter(
				ramDirectory, analyzer, this );
	//		CND_CONDITION(dw != NULL, "dw is NULL");
			if(dw==NULL)
			{
				printf("dw is NULL");
			}
	//		try {
	//			//Add the client-supplied document to the new segment.
				dw->addDocument(segmentName, doc);
	//		} _CLFINALLY(
	//			_CLDELETE(dw);
	//		);

	//		//Create a new SegmentInfo instance about this new segment.
	//		SegmentInfo* si = _CLNEW SegmentInfo(segmentName, 1, ramDirectory);
	//		CND_CONDITION(si != NULL, "Si is NULL");

	//		{
	//			SCOPED_LOCK_MUTEX(THIS_LOCK)

 //  				//Add the info object for this particular segment to the list
 //  				// of all segmentInfos->
 //  				segmentInfos->add(si);
	//   			
 //         		//Check to see if the segments must be merged
 //         		maybeMergeSegments();
	//		}
	//	} _CLFINALLY(
	//		_CLDELETE_CaARRAY(segmentName);
	//	);
	//	
	} catch (...) {
	//	ramDirectory->transAbort();
	//	throw;
	}
	//ramDirectory->transCommit();
}


//ÐÂµÄÌí¼Ó
IndexWriter::IndexWriter(const char* path, Lan::analysis::Analyzer* a, const bool create, const bool _closeDir):
	directory( FSDirectory::getDirectory(path, create)),
	analyzer(a),
	segmentInfos (new SegmentInfos),
	closeDir(_closeDir)
{
	if(path==NULL)
	{
		printf("path is NULL");
		assert(0);
	}
	_IndexWriter(create);
}

void IndexWriter::_IndexWriter(const bool create)
{
	//similarity = CL_NS(search)::Similarity::getDefault();
	useCompoundFile = true;
	/*if ( directory->getDirectoryType() == RAMDirectory::DirectoryType() )
	    useCompoundFile = false;*/

	//Create a ramDirectory
	ramDirectory = new TransactionalRAMDirectory;

	//CND_CONDITION(ramDirectory != NULL,"ramDirectory is NULL");
	if(ramDirectory==NULL)
	{
		printf("ramDirectory is NULL");
	}

	//Initialize the writeLock to
	//writeLock  = NULL;
	
	//initialise the settings...
	maxFieldLength = DEFAULT_MAX_FIELD_LENGTH;
	mergeFactor = DEFAULT_MERGE_FACTOR;
	maxMergeDocs = DEFAULT_MAX_MERGE_DOCS;
	writeLockTimeout = WRITE_LOCK_TIMEOUT;
	commitLockTimeout = COMMIT_LOCK_TIMEOUT;
	minMergeDocs = DEFAULT_MAX_BUFFERED_DOCS;
	termIndexInterval = DEFAULT_TERM_INDEX_INTERVAL;

	//Create a new lock using the name "write.lock"
	//LuceneLock* newLock = directory->makeLock(IndexWriter::WRITE_LOCK_NAME);

	//Condition check to see if newLock has been allocated properly
	//CND_CONDITION(newLock != NULL, "No memory could be allocated for LuceneLock newLock");

	//Try to obtain a write lock
	//if (!newLock->obtain(writeLockTimeout)){
	//	//Write lock could not be obtained so delete it
	//	_CLDELETE(newLock);
	//	//Reset the instance
	//	_finalize();
	//	//throw an exception because no writelock could be created or obtained
	//	_CLTHROWA(CL_ERR_IO, "Index locked for write or no write access." );
	//}

	//The Write Lock has been obtained so save it for later use
	//this->writeLock = newLock;

	//Create a new lock using the name "commit.lock"
	//LuceneLock* lock = directory->makeLock(IndexWriter::COMMIT_LOCK_NAME);

	//Condition check to see if lock has been allocated properly
	//CND_CONDITION(lock != NULL, "No memory could be allocated for LuceneLock lock");

	//LockWith2 with ( lock,commitLockTimeout,this, NULL, create );
	//{
	//	SCOPED_LOCK_MUTEX(directory->THIS_LOCK) // in- & inter-process sync
	//	with.run();
	//}

	////Release the commit lock
	//_CLDELETE(lock);

   isOpen = true;

}




}}