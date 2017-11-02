#ifndef _Lan_store_FSDirectory_
#define _Lan_store_FSDirectory_
#include "Directory.h"
#include "VoidMap.h"
#include <string>
#include <assert.h>
#include <stdlib.h>
using namespace std;
using namespace Lan::store;
namespace Lan
{
	namespace store
	{
class FSDirectory:public Directory
{
private:
	char directory[260];
	void priv_getFN(char* buffer, const char* name)const;
protected:
	FSDirectory(const char* path,const bool createDir);
	bool doDeleteFile(const char* name);
public:
	static FSDirectory* getDirectory(const char* file, const bool create);

	void list(vector<string>* name) const;
	void renameFile(const char* from, const char* to);
	IndexOutput* createOutput(const char* name);
	void close();
};
	}

}




#endif