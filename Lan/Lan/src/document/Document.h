#ifndef _Lan_document_Document_
#define _Lan_document_Document_

#include <string>
#include "Field.h"

using namespace std;
namespace Lan
{namespace document{

class DocumentFieldEnumeration
{
	class DocumentFieldList
	{
	public:
		DocumentFieldList(Field* f,DocumentFieldList* n);
		~DocumentFieldList();
		Field* field;
		DocumentFieldList* next;
	};
	friend class Document;

private:
	const DocumentFieldList* fields;
public:
	DocumentFieldEnumeration(const DocumentFieldList* fl);
	~DocumentFieldEnumeration();
	bool hasMoreElements() const;
	Field* nextElement();

};
class Document 
{
private:
	string content;
	string title;

public:
    string getContent();
	void setContent(string content);
	string getTitle();
	void setTitle(string title);
//ÐÂµÄÌí¼Ó
private:
	DocumentFieldEnumeration::DocumentFieldList* fieldList;
	double boost;
public:
	Document();
	~Document();
	void add(Field& feild);
	DocumentFieldEnumeration* fields() const;
	double getBoost() const;
};

}}
#endif