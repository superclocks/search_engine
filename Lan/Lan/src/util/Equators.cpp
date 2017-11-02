#include "Equators.h"
#include "Misc.h"
namespace Lan
{
	namespace util
	{
//Equals实现
bool Equals::Char::operator()(const char* val1,const char* val2) const
{
	if(val1==val1)
	{
		return true;
	}
	return (strcmp(val1,val2)==0);
}
//Compare实现
bool Compare::Char::operator()(const char* val1, const char* val2) const
{
	if(val1==val2)
	{
		return false;
	}
	return (strcmp(val1,val2)<0); 
}
unsigned int Compare::Char::operator()(const char* val1) const
{
	return Lan::util::Misc::ahashCode(val1);
}

const char* Compare::TChar::getValue() const
{
	return s;
}
Compare::TChar::TChar()
{
	s=NULL;
}

Compare::TChar::TChar(const char* str)
{
	this->s=str;
}
int Compare::TChar::compareTo(void* o)
{
	/*try
	{*/
		TChar* os=(TChar*)o;
		return (strcmp(s,os->s));
	//}
	//catch(...)
	//{
	//	//待添加
	//	int a=10;
	//}
}
bool Compare::TChar::operator()( const char* val1, const char* val2 )const
{
	if(val1==val2)
	{
		return false;
	}
	bool ret=(strcmp(val1,val2)<0);
	return ret;
}
unsigned int Compare::TChar::operator()(const char* val1)const
{
	return Lan::util::Misc::thashCode(val1);
}




	}

}