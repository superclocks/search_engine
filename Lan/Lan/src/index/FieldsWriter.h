#ifndef _Lan_index_FieldsWriter_
#define _Lan_index_FieldsWriter_
#include <assert.h>
#include "VoidMap.h"
#include "Directory.h"
#include "IndexOutput.h"
#include "Document.h"
#include "Field.h"
#include "FieldInfos.h"

namespace Lan
{namespace index{

class FieldsWriter
{
private:
	FieldInfos* fieldInfos;
	Lan::store::IndexOutput* fieldsStream;
	Lan::store::IndexOutput* indexStream;

public:
	enum { Field_Is_Tokenized = 0x1 };
	enum { Field_Is_Binary = 0x2 };
	enum { Field_Is_Compressed = 0x4 };

	FieldsWriter(Lan::store::Directory* d,const char* segment,FieldInfos* fn);
	~FieldsWriter();
	void close();
	void addDocument(Lan::document::Document* doc);
};

}}


#endif