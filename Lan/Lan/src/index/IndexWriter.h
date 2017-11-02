#ifndef _Lan_index_IndexWriter_
#define _Lan_index_IndexWriter_
#include <vector>
#include <algorithm>
#include <string>
#include <stdlib.h>
#include "Directory.h"
#include "Document.h"
#include "Analyzers.h"
#include "TransactionalRAMDirectory.h"
#include "AnalysisHeader.h"
#include "FSDirectory.h"
#include "SegmentInfos.h"

using namespace std;

namespace Lan
{namespace index{

class IndexWriter 
{
private:
	bool isOpen;
	Lan::analysis::Analyzer* analyzer;
	Lan::store::Directory* directory;
	IndexWriter* writer;

	bool closeDir;
	bool useCompoundFile;
	Lan::store::TransactionalRAMDirectory* ramDirectory;
	void _IndexWriter(const bool create);
	void _finalize();


	
	int getSegmentsCounter(){ return segmentInfos->counter; }
	int maxFieldLength;
	int mergeFactor;
	int minMergeDocs;
	int maxMergeDocs;
	int termIndexInterval;

	__int64 writeLockTimeout;
	__int64 commitLockTimeout;
public:
	Lan::index::SegmentInfos* segmentInfos;
	~IndexWriter();
	enum { DEFAULT_MAX_FIELD_LENGTH = 10000 };
	enum { FIELD_TRUNC_POLICY__WARN = -1 };
	int getMaxFieldLength() const { return maxFieldLength; }
	void setMaxFieldLength(int val){ maxFieldLength = val; }

	enum { DEFAULT_MAX_BUFFERED_DOCS = 10 };

	void setMaxBufferedDocs(int val){ minMergeDocs = val; }
	int getMaxBufferedDocs(){ return minMergeDocs; }

	enum { WRITE_LOCK_TIMEOUT = 1000 };

	void setWriteLockTimeout(__int64 writeLockTimeout) { this->writeLockTimeout = writeLockTimeout; }
	__int64 getWriteLockTimeout() { return writeLockTimeout; }
	enum { COMMIT_LOCK_TIMEOUT = 10000 };

	void setCommitLockTimeout(__int64 commitLockTimeout) { this->commitLockTimeout = commitLockTimeout; }

	__int64 getCommitLockTimeout() { return commitLockTimeout; }

	static const char* WRITE_LOCK_NAME;
	static const char* COMMIT_LOCK_NAME;
	enum{ DEFAULT_MERGE_FACTOR = 10 };

	int getMergeFactor() const{ return mergeFactor; }
	void setMergeFactor(int val){ mergeFactor = val; }
	enum{ DEFAULT_TERM_INDEX_INTERVAL = 128 };

	void setTermIndexInterval(int interval) { termIndexInterval = interval; }
	int getTermIndexInterval() { return termIndexInterval; }

	int getMinMergeDocs() const{ return minMergeDocs; }
	void setMinMergeDocs(int val){ minMergeDocs = val; }
	enum{DEFAULT_MAX_MERGE_DOCS = 0x7FFFFFFFL};

	int getMaxMergeDocs() const{ return maxMergeDocs; }
	void setMaxMergeDocs(int val){ maxMergeDocs = val; }

	IndexWriter(const char* path, Lan::analysis::Analyzer* a, const bool create, const bool closeDir=true);
	IndexWriter(Lan::store::Directory* d, Lan::analysis::Analyzer* a, const bool create, const bool closeDir=false);
	
	void close();
	int docCount();

	void addDocument(Lan::document::Document* doc,Lan::analysis::Analyzer* analyzer = NULL);
	void optimize();
	void addIndexes(Lan::store::Directory** dirs);
	//void addIndexes(IndexReader** readers);
	Lan::store::Directory* getDirectory() { return directory; }
	bool getUseCompoundFile() { return useCompoundFile; }
	void setUseCompoundFile(bool value) { useCompoundFile = value; }
	
	
	//SegmentInfos* segmentInfos;
	

	char* newSegmentName();
};



}}
#endif