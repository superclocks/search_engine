#include "FieldInfos.h"
#include "TransactionalRAMDirectory.h"

using namespace Lan::store;
using namespace Lan::document;
using namespace Lan::util;
namespace Lan
{namespace index{


//域的信息类FieldInfo实现
FieldInfo::FieldInfo(	const char* _fieldName,
						const bool _isIndexed,
						const int _fieldNumber,
						const bool _storeTermVector,
						const bool _storeOffsetWithTermVector,
						const bool _storePositionWithTermVector,
						const bool _omitNorms):
	name(_fieldName),isIndexed(_isIndexed),number(_fieldNumber),
	storeTermVector(_storeTermVector),
	storeOffsetWithTermVector(_storeOffsetWithTermVector),
	storePositionWithTermVector(_storeTermVector),
	omitNorms(_omitNorms)
{}
FieldInfo::~FieldInfo(){
	//CL_NS(util)::CLStringIntern::unintern(name);
}
//域的信息容器的实现
FieldInfos::FieldInfos():
	byName(false,false),byNumber(true)
{
}
FieldInfos::~FieldInfos()
{
	byName.clear();
	byNumber.clear();
}
FieldInfos::FieldInfos(Lan::store::Directory* d, const char* name):
byName(false,false),byNumber(true)
{
	/*IndexInput* input = d->openInput(name);
	try {	
		read(input);
	} _CLFINALLY (
	    input->close();
	    _CLDELETE(input);
	);*/
}
void FieldInfos::add(const Lan::document::Document* doc)
{
	DocumentFieldEnumeration* fields = doc->fields(); //该对象中含有DocumentFieldList成员变量，该变量存储了域的链表信息
	Field* field;
	while(fields->hasMoreElements())
	{
		field = fields->nextElement();
		add(field->name(),field->isIndexed(),field->isTermVectorStored());
	}
	if(fields!=NULL)
	{
		delete fields;
		fields=NULL;
	}
}

void FieldInfos::add( const char* name, const bool isIndexed, const bool storeTermVector,
		bool storePositionWithTermVector, bool storeOffsetWithTermVector, bool omitNorms) 
{
	FieldInfo* fi = fieldInfo(name);
	if (fi == NULL) {
		addInternal(name, isIndexed, storeTermVector, 
			storePositionWithTermVector, 
			storeOffsetWithTermVector, omitNorms);
	} else {
		if (fi->isIndexed != isIndexed) {
			fi->isIndexed = true;                      // once indexed, always index
		}
		if (fi->storeTermVector != storeTermVector) {
			fi->storeTermVector = true;                // once vector, always vector
		}
		if (fi->storePositionWithTermVector != storePositionWithTermVector) {
	        fi->storePositionWithTermVector = true;                // once vector, always vector
	    }
	    if (fi->storeOffsetWithTermVector != storeOffsetWithTermVector) {
	        fi->storeOffsetWithTermVector = true;                // once vector, always vector
	    }
	    if (fi->omitNorms != omitNorms) {
	        fi->omitNorms = false;                // once norms are stored, always store
	    }
	}
}
void FieldInfos::add(const char** names,const bool isIndexed, const bool storeTermVectors,
              bool storePositionWithTermVector, bool storeOffsetWithTermVector, bool omitNorms) {
  int i=0;      
  while ( names[i] != NULL ){
     add(names[i], isIndexed, storeTermVectors, storePositionWithTermVector, 
		 storeOffsetWithTermVector, omitNorms);
	 ++i;
  }
}
void FieldInfos::write(Lan::store::Directory* d, const char* name) const
{
	IndexOutput* output = d->createOutput(name);
	try
	{
		write(output);
	}
	catch(...)
	{ 
		output->close();
		if(output!=NULL)
		{
			delete output;
			output = NULL;
		}
		throw;
	}
	output->close();
	if(output!=NULL)
	{
		delete output;
		output = NULL;
	}
}
void FieldInfos::write(Lan::store::IndexOutput* output)const
{
	output->writeVInt(size());
	FieldInfo* fi;
	unsigned char bits;
	for(int i=0; i<size();++i)
	{
		fi=fieldInfo(i);
		bits = 0x0;
 		if (fi->isIndexed) bits |= Is_Indexed;
 		if (fi->storeTermVector) bits |= Store_TermVector;
 		if (fi->storePositionWithTermVector) bits |= Store_Positions_With_TermVector;
 		if (fi->storeOffsetWithTermVector) bits |= Store_Offset_With_TermVector;
 		if (fi->omitNorms) bits |= Omit_Norms;

	    output->writeString(fi->name,strlen(fi->name));
	    output->writeByte(bits);
	}

}
int FieldInfos::fieldNumber(const char* fieldName) const
{
	FieldInfo* fi = fieldInfo(fieldName);
	return (fi!=NULL) ? fi->number : -1;
}
FieldInfo* FieldInfos::fieldInfo(const char* fieldName) const {
	FieldInfo* ret = byName.get(fieldName);
	return ret;
}
const char* FieldInfos::fieldName(const int fieldNumber)const 
{
	FieldInfo* fi = fieldInfo(fieldNumber);
	return (fi==NULL)? (""):fi->name;
}
FieldInfo* FieldInfos::fieldInfo(const int fieldNumber) const
{
	if(fieldNumber<0 || (unsigned int)fieldNumber >= byNumber.size())
		return NULL;
	return byNumber[fieldNumber];
}
int FieldInfos::size() const
{
	return byNumber.size();
}
void FieldInfos::addInternal( const char* name, const bool isIndexed, const bool storeTermVector,
		bool storePositionWithTermVector, bool storeOffsetWithTermVector, bool omitNorms) 
{
	FieldInfo* fi = new FieldInfo(name, isIndexed, byNumber.size(), storeTermVector, 
		storePositionWithTermVector, storeOffsetWithTermVector, omitNorms);
	byNumber.push_back(fi);
	byName.put( fi->name, fi);
}

}}