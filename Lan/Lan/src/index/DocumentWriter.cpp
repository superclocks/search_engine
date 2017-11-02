#include "DocumentWriter.h"
#include "FieldInfos.h"
#include "IndexWriter.h"
#include "FieldsWriter.h"
#include "Term.h"
#include "TermInfo.h"

namespace Lan
{namespace index{
//Posting的实现
DocumentWriter::Posting::Posting(Term* t, const int position, TermVectorOffsetInfo* offset)
{
//Func - Constructor
//Pre  - t contains a valid reference to a Term
//Post - Instance has been created
	freq = 1;
	
	//term = _CL_POINTER(t);
	term = (t==NULL?NULL:t);
	positions.values = (int*)malloc(sizeof(int));
	positions.values[0] = position;
	positions.length = 1;
	
	if ( offset != NULL ){
		this->offsets.values = (TermVectorOffsetInfo*)malloc(sizeof(TermVectorOffsetInfo));
		this->offsets.values[0] = *offset;
		this->offsets.length = 1;
	}
}
DocumentWriter::Posting::~Posting(){
//Func - Destructor
//Pre  - true
//Post - The instance has been destroyed

	free(this->positions.values);
	if ( this->offsets.values != NULL )
		free(this->offsets.values);
	//_CLDECDELETE(this->term);
	
}

//DocumentWriter的实现
DocumentWriter::DocumentWriter(Lan::store::Directory* d, Lan::analysis::Analyzer* a, IndexWriter* writer):
	analyzer(a),
	directory(d),
	maxFieldLength(writer->getMaxFieldLength()),
	fieldInfos(NULL),
	fieldLengths(NULL),
	/*similarity(writer->getSimilarity()),
	termIndexInterval( writer->getTermIndexInterval() ),*/
	fieldPositions(NULL),
	fieldBoosts(NULL),
	termBuffer(new Term)
{
 
//CND_PRECONDITION(((maxFieldLength > 0) || (maxFieldLength == IndexWriter::FIELD_TRUNC_POLICY__WARN)),
// "mfl is 0 or smaller than IndexWriter::FIELD_TRUNC_POLICY__WARN")
// 
   fieldInfos     = NULL;
   fieldLengths   = NULL;

}
DocumentWriter::~DocumentWriter(){
//Func - Destructor
//Pre  - true
//Post - The instance has been destroyed
	clearPostingTable();
	//_CLDELETE( fieldInfos );
	if(fieldInfos!=NULL)
	{
		delete fieldInfos;
		fieldInfos=NULL;
	}
	//_CLDELETE_ARRAY(fieldLengths);
	if(fieldLengths!=NULL)
	{
		delete[] fieldLengths;
		fieldLengths = NULL;
	}
	//_CLDELETE_ARRAY(fieldPositions);
	if(fieldPositions!=NULL)
	{
		delete[] fieldPositions;
		fieldPositions = NULL;
	}
	//_CLDELETE_ARRAY(fieldBoosts);
	if(fieldBoosts!=NULL)
	{
		delete[] fieldBoosts;
		fieldBoosts = NULL;
	}
	//_CLDELETE_ARRAY(fieldOffsets);
	if(fieldOffsets!=NULL)
	{
		delete[] fieldOffsets;
		fieldOffsets = NULL;
	}

	//_CLDECDELETE(termBuffer);
}
void DocumentWriter::clearPostingTable(){
	PostingTableType::iterator itr = postingTable.begin();
	while ( itr != postingTable.end() ){
		//_CLDELETE(itr->second);
		if(itr->second!=NULL)
		{
		delete itr->second;
		itr->second=NULL;
		}
		//_CLLDECDELETE(itr->first);
		if(itr->first!=NULL)
		{
			delete itr->first;
		}

		++itr;
	}
	postingTable.clear();
}
void DocumentWriter::addDocument(const char* segment, Document* doc)
{
	//========完成了域的元数据信息文件fnm，存储域的信息文件fdt，域的索引文件fdx的创建并向其中写入信息=========
	//CND_PRECONDITION(fieldInfos==NULL, "fieldInfos!=NULL");
	fieldInfos = new FieldInfos();
	fieldInfos->add(doc); //将doc中的域信息添加到域的信息链中

	const char* buf=Lan::util::Misc::segmentname(segment,".fnm"); //构造域的元数据信息文件名称
	fieldInfos->write(directory,buf); //将域的元数据信息写入到directory中
	//_CLDELETE_CaARRAY(buf);
	if(buf!=NULL)
	{
		delete[] buf;
		buf=NULL;
	}
	FieldsWriter fieldsWriter(directory,segment,fieldInfos); //新建存储域的数据文件.fdt,域的索引文件.fdx
	try
	{
		fieldsWriter.addDocument(doc);//存储域的数据文件.fdt,域的索引文件.fdx
	}
	catch(...)
	{
		fieldsWriter.close(); 
		throw; 
	}
	//=========================================================================================================
	clearPostingTable(); //清空倒排表
	unsigned int size = fieldInfos->size();
	fieldLengths=new int[size];
	fieldPositions = new int[size];
	fieldOffsets = new int[size];
	memset(fieldPositions,0,sizeof(int) * size);
	
	int fbl=fieldInfos->size();
	double fbd = doc->getBoost();
	fieldBoosts = new double[fbl];
	{
		for(int i=0;i<fbl;i++)
			fieldBoosts[i]=fbd;
	}
	{
		for(int i=0;i<fieldInfos->size();i++)
			fieldLengths[i]=0;
	}
	fieldsWriter.close();
	invertDocument(doc); //完成倒排文档
	//=============用快速排序对倒排表进行排序==============
	Posting** postings = NULL;
	int postingsLength = 0;
	sortPostingTable(postings,postingsLength);
	//=====================================================

}
void DocumentWriter::sortPostingTable(Posting**& arrays, int& arraySize)
{
	arraySize = postingTable.size();
	arrays = new Posting*[arraySize];
	PostingTableType::iterator postings = postingTable.begin();
	int i = 0;
	while(postings != postingTable.end())
	{
		arrays[i] = (Posting*)postings->second;
		postings++ ;
		i++;
	}
	quickSort(arrays,0,i-1);
}
void DocumentWriter::invertDocument(const Document* doc)
{
	DocumentFieldEnumeration* fields=doc->fields();
	try
	{
	while(fields->hasMoreElements())
	{
		Field* field = (Field*)fields->nextElement();
		const char* fieldName=field->name();
		const int fieldNumber = fieldInfos->fieldNumber(fieldName);
		int length = fieldLengths[fieldNumber];     // length of field
		int position = fieldPositions[fieldNumber]; // position in field
		if (length>0) 
		{
		    position+=analyzer->getPositionIncrementGap(fieldName);
		}
		int offset = fieldOffsets[fieldNumber];       // offset field
		if(field->isIndexed())
		{
			if(field->isTokenized())  //原始的代码为!field->isTokenized()
			{
			}
			else
			{
				Lan::util::Reader* reader;
				bool delReader = false;
				if(field->readerValue()!=NULL)
				{
					reader = field->readerValue();
				}
				else if(field->stringValue()!=NULL)
				{
					reader =new Lan::util::StringReader(field->stringValue(),strlen(field->stringValue()),false);
					delReader = true;
				}
				else
				{
					printf("field must have either String or Reader value");
					assert(0);
				}
				try
				{
					Lan::analysis::TokenStream* stream = analyzer->tokenStream(fieldName,reader);
					try
					{
						Lan::analysis::Token t;
						int lastTokenEndOffset = -1;
						while(stream->next(&t))
						{
							position += t.getPositionIncrement()-1;
							if(field->isStoreOffsetWithTermVector())
							{

							}
							else
							{
								addPosition(fieldName,t.termText(),position++,NULL);
							}
							lastTokenEndOffset = t.endOffset();
							length++;
							if(maxFieldLength!=IndexWriter::FIELD_TRUNC_POLICY__WARN)
							{
								if(length > maxFieldLength)
									break;
							}
							else if(length >IndexWriter::DEFAULT_MAX_FIELD_LENGTH)
							{
								 const char* errMsgBase = "Indexing a huge number of tokens from a single"
			                    " field (\"%s\", in this case) can cause CLucene"
			                    " to use memory excessively."
			                    "  By default, CLucene will accept only %s tokens"
			                    " tokens from a single field before forcing the"
			                    " client programmer to specify a threshold at"
			                    " which to truncate the token stream."
			                    "  You should set this threshold via"
								" IndexReader::maxFieldLength (set to LUCENE_INT32_MAX"
			                    " to disable truncation, or a value to specify maximum number of fields.";
								
								 char defaultMaxAsChar[34];
								 _i64toa(IndexWriter::DEFAULT_MAX_FIELD_LENGTH,defaultMaxAsChar,10);
								 int errMsgLen = strlen(errMsgBase) + strlen(fieldName) + strlen(defaultMaxAsChar);
								 char* errMsg =new char[errMsgLen+1];
								 _snprintf(errMsg, errMsgLen,errMsgBase, fieldName, defaultMaxAsChar);
								//_CLTHROWT_DEL(CL_ERR_Runtime,errMsg);
							}
						}

						if(lastTokenEndOffset != -1)
							offset += lastTokenEndOffset + 1;
					}
					catch(...)
					{
						stream->close();
						if(stream!=NULL)
						{
							delete stream;
							stream = NULL;
						}
						throw;
					}
					stream->close();
					if(stream!=NULL)
					{
						delete stream;
						stream = NULL;
					}
				}
				catch(...)
				{
					if(delReader)
					{
						if(reader!=NULL)
						{
							delete reader;
							reader = NULL;
						}
					}
					throw;
				}
				if(delReader)
				{
					if(reader!=NULL)
					{
						delete reader;
						reader = NULL;
					}
				}
			}

			fieldLengths[fieldNumber] = length;
			fieldPositions[fieldNumber] = position;
			fieldBoosts[fieldNumber] *= field->getBoost();
			fieldOffsets[fieldNumber] = offset;
		}
	}
	}
	catch(...)
	{
		if(fields!=NULL)
		{
			delete fields;
			fields = NULL;
		}
		throw;
	}
	if(fields!=NULL)
	{
		delete fields;
		fields = NULL;
	}
}
void DocumentWriter::addPosition(const char* field,
                                     const char* text,
                                     const int position, 
                                     TermVectorOffsetInfo* offset)
{
	termBuffer->set(field,text,false);
	Posting* ti = postingTable.get(termBuffer);
	if(ti != NULL)
	{
		int freq = ti->freq;
		if(ti->positions.length == freq)
		{
			ti->positions.length = freq*2;
			ti->positions.values=(int*)realloc(ti->positions.values,ti->positions.length*sizeof(int));
		}
		ti->positions.values[freq] = position;
		if(offset != NULL)
		{
			if(ti->offsets.length == freq)
			{
				ti->offsets.length = freq*2;
				ti->offsets.values=(TermVectorOffsetInfo*)realloc(ti->offsets.values, ti->offsets.length * sizeof(TermVectorOffsetInfo));
			}
			ti->offsets[freq] = *offset;
		}
		ti->freq = freq + 1;
	}
	else
	{
		Term* term = new Term( field, text, false);
		postingTable.put(term, new Posting(term, position, offset));
	}
}
void DocumentWriter::quickSort(Posting**& postings, const int lo, const int hi) {
	if(lo >= hi)
		return;

	int mid = (lo + hi) / 2;

	if(postings[lo]->term->compareTo(postings[mid]->term) > 0) {
		 Posting* tmp = postings[lo];
		postings[lo] = postings[mid];
		postings[mid] = tmp;
	}

	if(postings[mid]->term->compareTo(postings[hi]->term) > 0) {
		Posting* tmp = postings[mid];
		postings[mid] = postings[hi];
		postings[hi] = tmp;
	      
		if(postings[lo]->term->compareTo(postings[mid]->term) > 0) {
			Posting* tmp2 = postings[lo];
			postings[lo] = postings[mid];
			postings[mid] = tmp2;
		}
	}

	int left = lo + 1;
	int right = hi - 1;

	if (left >= right)
		return; 

	const Term* partition = postings[mid]->term; //not kept, so no need to finalize
    
	for( ;; ) {
		while(postings[right]->term->compareTo(partition) > 0)
		--right;
	      
		while(left < right && postings[left]->term->compareTo(partition) <= 0)
			++left;
		      
		if(left < right) {
			Posting* tmp = postings[left];
			postings[left] = postings[right];
			postings[right] = tmp;
			--right;
		} else {
			break;
		}
	}

	quickSort(postings, lo, left);
	quickSort(postings, left + 1, hi);
}

void DocumentWriter::writePostings(Posting** postings, const int postingsLength, const char* segment)
{
	IndexOutput* freq = NULL;
	IndexOutput* prox = NULL;

}

}}
