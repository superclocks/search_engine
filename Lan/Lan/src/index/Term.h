#ifndef _Lan_index_Term_
#define _Lan_index_Term_
#include <string>
#include "StringIntern.h"
#include "Equators.h"
#include "Misc.h"

using namespace std;
namespace Lan
{namespace index{

class Term
{
private:
	unsigned int cachedHashCode;
	const char* _field;
	char* _text;
	unsigned int textLenBuf;
	unsigned int textLen;
	bool internF;

public:
	Term(const Term* fieldTerm, const char* txt);
	Term();
	Term(const char* fld, const char* txt, bool internField);
	Term(const char* fld, const char* txt);
	~Term();

	const char* field() const;
	const char* text() const;
	inline void set(const char* fld, const char* txt)
	{
				set(fld,txt,true);
	}

	void set(const Term* term, const char* txt);
	void set(const char* fld, const char* txt, const bool internField);
	int compareTo(const Term* other) const;
	bool equals(const Term* other) const;
	unsigned int textLength() const
	{
		return textLen;
	}

	char* toString() const;
	unsigned int hashCode();

	class Equals:public binary_function<const Term*,const Term*,bool>
	{
	public:
		bool operator()( const Term* val1, const Term* val2 ) const
		{
				return val1->equals(val2);
		}
	};
	
	class Compare:/*LUCENE_BASE,*/ public Lan::util::Compare::_base //<Term*>
	{
	public:
		bool operator()( Term* t1, Term* t2 ) const
		{
			return ( t1->compareTo(t2) < 0 );
		}
		size_t operator()( Term* t ) const
		{
			return t->hashCode();
		}
	};
};

}}
#endif