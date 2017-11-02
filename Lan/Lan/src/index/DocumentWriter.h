#ifndef _Lan_index_DocumentWriter_
#define _Lan_index_DocumentWriter_
#include "Analyzers.h"
#include "Directory.h"
#include "VoidMap.h"
#include "IndexWriter.h"
#include "Term.h"
#include "AnalysisHeader.h"
#include "Field.h"
#include "StringReader.h"
#include "FieldInfos.h"
#include "Misc.h"
#include "mem.h"
#include "TermVector.h"
#include "LanBase.h"

namespace Lan
{namespace index
{
class DocumentWriter{
public:
	class Posting
	{
	public:
		Term* term;
		int freq;
		Array<int> positions;
		Array<TermVectorOffsetInfo> offsets;
		Posting(Term* t,const int position, TermVectorOffsetInfo* offset);
		~Posting();
	};

private:
	Lan::analysis::Analyzer* analyzer;
	Lan::store::Directory* directory;
	FieldInfos* fieldInfos;
	const int maxFieldLength;
	//Similarity* similarity;
	int termIndexInterval;

	//Keys代表Terms，values代表Postings
	//在文档被索引之前，将其放到缓冲区中
	typedef Lan::util::CLHashtable< Term* , Posting* ,Term::Compare, Term::Equals > PostingTableType;
	PostingTableType postingTable;
	int* fieldLengths; //array
	int* fieldPositions; //array
	int* fieldOffsets; //array
	double* fieldBoosts; //array

	Term* termBuffer;

public:
	DocumentWriter(Lan::store::Directory* d, Lan::analysis::Analyzer* a, /*Similarity*　similarity,*/ const int maxFieldLength);
	DocumentWriter(Lan::store::Directory* directory, Lan::analysis::Analyzer* analyzer, IndexWriter* writer);
	~DocumentWriter();

	void addDocument(const char* segment,Document* doc);

private:
	void invertDocument(const Document* doc);
	void addPosition(const char* field, const char* text, const int position, TermVectorOffsetInfo* offset);
	void sortPostingTable(Posting**& arrays, int& arraySize);

	static void quickSort(Posting**& postings, const int lo, const int hi);

	void writePostings(Posting** postings, const int postingsLength, const char* segment);

	void writeNorms(const char* segment);

	void clearPostingTable();

};



}}
#endif