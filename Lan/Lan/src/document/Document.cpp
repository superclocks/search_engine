#include "Document.h"
//DocumentFieldEnumeration类的实现
namespace Lan
{
	namespace document
	{
DocumentFieldEnumeration::DocumentFieldList::DocumentFieldList(Field* f,DocumentFieldList* n)
{
	assert(f);
	field=f;
	next=n;
}
DocumentFieldEnumeration::DocumentFieldList::~DocumentFieldList()
{
	if(!field)
	{
		return;
	}
	DocumentFieldList* cur = next;
	while(cur != NULL)
	{
		DocumentFieldList* temp = cur->next;
		cur->next = NULL;
		if(cur != NULL)
		{
			delete cur;
			cur = NULL;
		}
		cur = temp;
	}
	if(field != NULL)
	{
		delete field;
		field = NULL;
	}
}
DocumentFieldEnumeration::DocumentFieldEnumeration(const DocumentFieldList* fl)
{
	fields = fl;
}
DocumentFieldEnumeration::~DocumentFieldEnumeration()
{

}
bool DocumentFieldEnumeration::hasMoreElements() const
{
	if(fields==NULL)
	{ 
		return false;
	}
	else
	{
		return true;
	}
	//return fields==NULL ? false : true;
}
Field* DocumentFieldEnumeration::nextElement()
{
	Field* result = NULL;
	if(fields)
	{
		result = fields->field;
		fields=fields->next;
	}
	return result;
}
//Document类的实现
Document::Document()
{
	boost = 1.0f;
	fieldList = NULL;
}
Document::~Document()
{
	boost=1.0f;
	if(fieldList!=NULL)
	{
		delete fieldList;
	}
	fieldList=NULL;
}

string Document::getContent()
{
	return content;
}
void Document::setContent(string content)
{
	this->content=content;
}
string Document::getTitle()
{
	return title;
}
void Document::setTitle(string title)
{
	this->title=title;
}

void Document::add(Field& field)
{
	fieldList=new DocumentFieldEnumeration::DocumentFieldList(&field,fieldList);
}

DocumentFieldEnumeration* Document::fields() const
{
	return new DocumentFieldEnumeration(fieldList);
}
double Document::getBoost() const
{
	return boost;
}

}}