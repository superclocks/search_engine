#include "Field.h"
namespace Lan
{namespace document{

Field::Field(const char* name,const char* value,int config)
{
	if(name==NULL)
	{
		printf("Name is Null");
		assert(0);
	}
	if(value==NULL)
	{
		printf("value is NULL");
	}

	//_name        = CLStringIntern::intern( Name  CL_FILELINE);
	//_stringValue = stringDuplicate( Value );
	int len=strlen(name);
	char* name_new=new char[len+1];
	strncpy(name_new,name,len+1);
	_name=name_new;

	len=strlen(value);
	_stringValue=new char[len+1];
	strncpy(_stringValue,value,len+1);

	_readerValue = NULL;
	_streamValue = NULL;
	boost=1.0f;
	omitNorms=false;
	setConfig(config);
}
Field::~Field()
{

}

void Field::setConfig(int x)
{
	int newConfig=0;

	//set storage settings
	if ( (x & Store_Yes) || (x & Store_Compress) ){
		newConfig |= Store_Yes;
		if ( x & Store_Compress )
			newConfig |= Store_Compress;
	}else
		newConfig |= Store_No;

	if ( (x & Index_No)==0 ){
		bool index=false;

		if ( x & Index_NoNorms ){
			newConfig |= Index_NoNorms;
			index = true;
		}

		if ( x & Index_Tokenized && x & Index_UnTokenized )
		{
			//_CLTHROWA(CL_ERR_IllegalArgument,"it doesn't make sense to have an untokenised and tokenised field");
			printf("it doesn't make sense to have an untokenised and tokenised field");
			assert(false);
		}	
		if ( x & Index_Tokenized ){
			newConfig |= Index_Tokenized;
			index = true;
		}
		if ( x & Index_UnTokenized ){
			newConfig |= Index_UnTokenized;
			index = true;
		}
		if ( !index )
			newConfig |= Index_No;
	}else
		newConfig |= Index_No;

	if ( newConfig & Index_No && newConfig & Store_No )
	{
		//_CLTHROWA(CL_ERR_IllegalArgument,"it doesn't make sense to have a field that is neither indexed nor stored");
		printf("it doesn't make sense to have a field that is neither indexed nor stored");
		assert(false);
	}
	//set termvector settings
	if ( (x & TermVector_No) == 0 ){
		bool termVector=false;
		if ( x & TermVector_Yes ){
			termVector=true;
		}
		if ( x & TermVector_With_Offsets ){
			newConfig |= TermVector_With_Offsets;
			termVector=true;
		}
		if ( x & TermVector_With_Positions ){
			newConfig |= TermVector_With_Positions;
			termVector=true;
		}
		if ( termVector ){
			if ( newConfig & Index_No )
			{
				//_CLTHROWA(CL_ERR_IllegalArgument,"cannot store a term vector for fields that are not indexed.");
				printf("cannot store a term vector for fields that are not indexed.");
				assert(false);
			}
				

			newConfig |= TermVector_Yes;
		}else
			newConfig |= TermVector_No;
	}else
		newConfig |= TermVector_No;

	config = newConfig;
}
const char* Field::name(){ return _name; }
char* Field::stringValue(){ return _stringValue; }
Lan::util::Reader* Field::readerValue(){ return _readerValue; }
jstreams::StreamBase<char>* Field::streamValue() { return _streamValue; }
bool Field::isStored() { return (config & Store_Yes)!=0; }
bool Field::isIndexed() 	{ return (config & Index_Tokenized)!=0 || (config & Index_UnTokenized)!=0; }
bool Field::isTokenized() 	{ return (config & Index_Tokenized) != 0; }
bool Field::isCompressed() 	{ return (config & Store_Compress) != 0; }
bool Field::isBinary() 	{ return _streamValue!=NULL; }

bool Field::isTermVectorStored() { return (config & TermVector_Yes) != 0; }
bool	Field::isStoreOffsetWithTermVector() { return (config & TermVector_Yes) != 0 && (config & TermVector_With_Offsets) != 0; }
bool	Field::isStorePositionWithTermVector() { return (config & TermVector_Yes) != 0 && (config & TermVector_With_Positions) != 0; }

bool Field::getOmitNorms() { return omitNorms; }
void Field::setOmitNorms(bool omitNorms) { this->omitNorms=omitNorms; }

void Field::setBoost(double boost) { this->boost = boost; }
double Field::getBoost() { return boost; }


}}