#ifndef _Lan_util_Equators_
#define _Lan_util_Equators_
#include <string>
#include <functional>
#include <xstddef>
#include <stdlib.h>
using namespace std; 
namespace Lan
{namespace util{

class Equals
{
public:
	class Char:public binary_function<const char*,const char*,bool>
	{
	public:
		bool operator()(const char* val1, const char* val2)const;
	};
	class TChar:public Char
	{
	};
};

class Comparable
{
public:
	virtual ~Comparable(){}
	virtual int compareTo(void* o) = 0;
};

class Deletor
{
public:
	template<typename _kt>
	class Array
	{
	public:
		static void doDelete(_kt* arr)
		{
			//_CLDELETE_LARRAY(arr);
			if(arr!=NULL)
				delete[] arr;
			arr=NULL;
		}
	};
	class tcArray
	{
	public:
		static void doDelete(const char* arr)
		{
			//_CLDELETE_CARRAY(arr);
			if(arr!=NULL)
				delete[] arr;
			arr=NULL;
		}
	};
	class acArray
	{
	public:
		static void doDelete(const char* arr)
		{
			//_CLDELETE_CaARRAY(arr);
			if(arr!=NULL)
				delete[] arr;
			arr=NULL;
		}
	};
	class Dummy
	{
	public:
		static void doDelete(const void* nothing)
		{

		}
	};
	
	class DummyInt32
	{
	public:
		static void doDelete(const int nothing)
		{
		}
	};
	

	template<typename _kt>
	class Object
	{
	public:
		static void doDelete(_kt* obj)
		{
			if(obj!=NULL)
			{
				delete obj;
				obj = NULL;
			}
		}
	};
	template<typename _kt>
	class Void
	{
	public:
		static void doDelete(_kt* obj)
		{
			if(obj != NULL)
			{
				delete obj;
				obj = NULL;
			}
		}
	};
};

class Compare
{
public:
	//======
	class _base
	{
	public:
		enum
		{
			bucket_size=4,
			min_buckets=8,
		};
		_base()
		{
		}
	};
	//======
	class Char:public _base
	{
	public:
		bool operator() (const char* val1,const char* val2) const;
		unsigned operator()(const char* val1) const;
	};
	//======
	class TChar:public _base,public Comparable
	{
		const char* s;
	public:
		const char* getValue() const;
		TChar();
		TChar(const char* str);
		int compareTo(void* o);
		bool operator()(const char* val1,const char* val2)const;
		unsigned int operator()(const char* val1)const;

	};
	//======
	template<typename _cl>
	class Void:public _base //<const void*,const void*,bool>
	{
	public:
		int compareTo(_cl* o)
		{
		if ( this == o )
			return o;
		else
			return this > o ? 1 : -1;
		}
		bool operator()( _cl* t1, _cl* t2 ) const
		{
			return t1 > t2 ? true : false;
		}
		size_t operator()( _cl* t ) const
		{
			return (size_t)t;
		}
	};
};




}}
#endif