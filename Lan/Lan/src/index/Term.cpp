#include "Term.h"
#include "StringIntern.h"
using namespace Lan::util;
namespace Lan
{namespace index{

Term::Term()
{
	_field="";
	internF = false;
	cachedHashCode = 0;
	textLen = 0;
	_text = "";
	textLenBuf = 0;
	textLen = 0;
}
Term::Term(const char* fld,const char* txt, bool internField)
{
	_field = "";
	internF = false;
	textLen = 0;
	/*#ifdef LUCENE_TERM_TEXT_LENGTH
		_text[0]=0;
	#else*/
		_text = "";
		textLenBuf = 0;
	//#endif

    set(fld,txt,internField);
}
Term::Term(const Term* fieldTerm, const char* txt){
	_field = "";
	internF = false;
	textLen = 0;
	/*#ifdef LUCENE_TERM_TEXT_LENGTH
		_text[0]=0;
	#else*/
		_text = "";
		textLenBuf = 0;
	//#endif

    set(fieldTerm,txt);
}
Term::Term(const char* fld, const char* txt){
	_field = "";
	internF = false;
	textLen = 0;
	/*#ifdef LUCENE_TERM_TEXT_LENGTH
		_text[0]=0;
	#else*/
		_text = "";
		textLenBuf = 0;
	//#endif

    set(fld,txt);
}
Term::~Term(){

	if ( internF )
		CLStringIntern::unintern(_field);
	_field = NULL;

#ifndef LUCENE_TERM_TEXT_LENGTH
	//Deletetext if it is the owner
	if ( _text != "")
	{
		//_CLDELETE_CARRAY( _text );
		if(_text!=NULL)
		{
			delete[] _text;
			_text = NULL;
		}
	}
#endif
}
const char* Term::field() const 
{
    return _field;
}

const char* Term::text() const 
{
    return _text;
}

void Term::set(const Term* term, const char* txt){
	set(term->field(),txt,false);
}

void Term::set(const char* fld, const char* txt,const bool internField)
{
	const char* oldField = _field;
	cachedHashCode = 0;
    textLen = strlen(txt);
	if ( _text && textLen > textLenBuf){
		if ( _text != "" )
		{
			//_CLDELETE_ARRAY( _text );
			if(_text!=NULL)
			{
				delete[] _text;
				_text=NULL;
			}
		}
		else
			_text = NULL;
		textLenBuf = 0;
	}

	if ( _text=="" )
		_text = "";
	else if ( _text==NULL ){
		if ( txt[0] == 0 ){
			//if the string is blank and we aren't re-using the buffer...
			_text = "";
		}else{
			//duplicate the text
			//_text  = stringDuplicate(txt);
			 size_t len = strlen(txt);
			char* ret = new char[len+1];
			strncpy(ret,txt,len+1);
			_text=ret;
			textLenBuf = textLen;
		}
	}else{
		//re-use the buffer
		strcpy(_text,txt);
	}


    //Set Term Field
	if ( internField )
		_field = CLStringIntern::intern(fld  ,__FILE__,__LINE__);
	else
		_field = fld;

	//unintern old field after interning new one, 
	if ( internF )
		CLStringIntern::unintern(oldField);
	internF = internField;
		    
    //CND_PRECONDITION(_tcscmp(fld, _field)==0,"field not equal");
}

/** Compares two terms, returning true iff they have the same
  field and text. */
bool Term::equals(const Term* other) const{
   if ( cachedHashCode != 0 && other->cachedHashCode != 0 &&
		other->cachedHashCode != cachedHashCode )
		return false;

  if ( _field==other->_field ){
     //this can be quicker than using compareTo, because checks
     //field length first
	  if ( textLen == other->textLen ){
		  return (strcmp(_text,other->_text)==0);
	  }else
        return false;
  }else
     return false;
}

unsigned int Term::hashCode(){
	if ( cachedHashCode == 0 )
		cachedHashCode = Misc::thashCode(_field) + Misc::thashCode(_text,textLen);
	return cachedHashCode;
}

int Term::compareTo(const Term* other) const
{
	if(_field == other->_field)
	{
		return strcmp(_text,other->_text);
	}
	else
	{
		return strcmp(_field,other->_field);
	}
}



}}
