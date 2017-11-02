#include "FieldsWriter.h"
#include "VoidMap.h"
#include "Reader.h"
#include "Misc.h"
#include "Directory.h"
#include "IndexOutput.h"
#include "Document.h"
#include "Field.h"
#include "FieldInfos.h"

using namespace Lan::store;
using namespace Lan::util;
using namespace Lan::document;

namespace Lan
{namespace index{

FieldsWriter::FieldsWriter(Directory* d, const char* segment, FieldInfos* fn):
fieldInfos(fn)
{
	if(segment==NULL)
	{
		printf("segment is NULL");
		assert(0);
	}
	const char* buf = Misc::segmentname(segment,".fdt");
	fieldsStream = d->createOutput(buf);
	if(buf!=NULL)
	{
		delete[] buf;
		buf = NULL;
	}
	buf = Misc::segmentname(segment, ".fdx");
	indexStream = d->createOutput(buf);
	if(buf!=NULL)
	{
		delete[] buf;
		buf = NULL;
	}
	//CND_CONDITION(indexStream != NULL,"indexStream is NULL");
}
FieldsWriter::~FieldsWriter()
{
	close();
}
void FieldsWriter::close()
{
	if(fieldsStream)
	{
		fieldsStream->close();
		if(fieldsStream!=NULL)
		{
			delete fieldsStream;
			fieldsStream = NULL;
		}
	}
	if(indexStream)
	{
		indexStream->close();
		if(indexStream!=NULL)
		{
			delete indexStream;
			indexStream=NULL;
		}
	}
}
void FieldsWriter::addDocument(Document* doc)
{
	/*CND_PRECONDITION(indexStream != NULL,"indexStream is NULL");
	CND_PRECONDITION(fieldsStream != NULL,"fieldsStream is NULL");*/
	indexStream->writeLong(fieldsStream->getFilePointer());

	int storedCount = 0;
	DocumentFieldEnumeration* fields = doc->fields();
	while(fields->hasMoreElements())
	{
		Field* field = fields->nextElement();
		if(field->isStored())
			storedCount++;
	}
	//_CLDELETE(fields);
	if(fields!=NULL)
	{
		delete fields;
		fields=NULL;
	}
	fieldsStream->writeVInt(storedCount);

	fields = doc->fields();
	while(fields->hasMoreElements())
	{
		Field* field=fields->nextElement();
		if(field->isStored())
		{
			fieldsStream->writeVInt(fieldInfos->fieldNumber(field->name()));

			unsigned char bits = 0;
			if(field->isTokenized())
				bits |= FieldsWriter::Field_Is_Tokenized;
			if(field->isBinary())
				bits |= FieldsWriter::Field_Is_Binary;
			if(field->isCompressed())
				bits |= FieldsWriter::Field_Is_Compressed;
			fieldsStream->writeByte(bits);
			if(field->isCompressed())
			{
				//_CLTHROWA(CL_ERR_Runtime, "CLucene does not directly support compressed fields. Write a compressed byte array instead");
			}
			else
			{
				if(field->isBinary())
				{
					jstreams::StreamBase<char>* stream = field->streamValue();
					const char* sd;
					int rl=stream->read(sd,10000000,0);
					if(rl<0)
					{
						fieldsStream->writeVInt(0);
					}
					else
					{
						fieldsStream->writeVInt(rl);
						fieldsStream->writeBytes((unsigned char*)sd,rl);
					}
				}
				else if(field->stringValue() == NULL)
				{
					//CND_PRECONDITION(!field->isIndexed(), "Cannot store reader if it is indexed too")
					Reader* r = field->readerValue();
	
					//read the entire string
					const char* rv;
					__int64 rl = r->read(rv, 0x7FFFFFFFL);
					if ( rl > 0x7FFFFFFFL )
						//_CLTHROWA(CL_ERR_Runtime,"Field length too long");
						printf("Field length too long");
					else if ( rl < 0 )
						rl = 0;

					fieldsStream->writeString( rv, (int)rl);
				}
				else if(field->stringValue() != NULL)
				{
					fieldsStream->writeString(field->stringValue(),strlen(field->stringValue()));
				}
				else
				{
					//_CLTHROWA(CL_ERR_Runtime, "No values are set for the field");
					printf("No values are set for the field");
				}
			}
		}
	}
	if(fields!=NULL)
	{
		delete fields;
		fields=NULL;
	}
}


}}