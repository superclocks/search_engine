#ifndef _Lan_store_Directory_
#define _Lan_store_Directory_
#include <string>
#include <vector>
#include "IndexOutput.h"
using namespace std;

namespace Lan
{namespace store{

class Directory /*LUCENE_REFBASE*/
{
protected:
	Directory(){}
	virtual bool doDeleteFile(const char* name) = 0;

public:
	virtual ~Directory(){}
	char** list() const
	{
    	vector<string> names;
    		
    	list(&names);
    
		unsigned int size = names.size();
		char** rets=new char*[size+1]; //= _CL_NEWARRAY(char*,size+1);
		for ( size_t i=0;i<size;i++ )
		{
			unsigned int len=strlen(names[i].c_str());
			char* ret = new char[len+1];
			strncpy(ret,names[i].c_str(),len+1);
			rets[i] = ret; // STRDUP_AtoA(names[i].c_str());
		}
		rets[size]=NULL;
		return rets;	
	}
	virtual void list(vector<string>* name) const = 0;

	//virtual void fileExists(const char* name) const = 0;

	//virtual __int64 fileModefied(const char* name) const = 0;

	//virtual __int64 fileLength(const char* name) const = 0;
	virtual void renameFile(const char* from, const char* to) = 0;
	virtual Lan::store::IndexOutput* createOutput(const char* name) = 0;

	virtual void close() = 0;


};

}}

#endif