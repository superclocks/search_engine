
#include "Misc.h"
#include "VoidMap.h"
#include "Equators.h"
#include "LanBase.h"
bool _Lan_disable_debuglogging = true;
bool _Lan_run_objectcheck = false;
int _Lan_counter_break = -1;

using namespace Lan::util;

namespace Lan
{namespace debug{

int _instance_counter = 0;
struct _file
{
	int refcount;
	char* value;
};//用于名称计数的结构体
struct _pointers
{
	_file* file;
	int initline;
	int initnumber;
};//用于文件名指针引用的结构体

typedef Lan::util::CLSet<const char*, _file*, Compare::Char,Deletor::Dummy,Deletor::Void<_file>> defFile;
typedef Lan::util::CLSet<LanBase*,_pointers*,Compare::Void<LanBase>,Deletor::Dummy,Deletor::Void<_pointers> > defPointer;
typedef Lan::util::CLSet<const void*,_pointers*,Compare::Void<const void>,Deletor::Dummy,Deletor::Void<_pointers> > defVoid;

defFile LanBase_Files(false,true);
defPointer LanBase_Pointers(false,true);
defVoid LanBase_Voids(false,true);

char _files_trim_string[260];
int _files_trim_start = -1;

_file* get_file(const char* file)
{
	if(_files_trim_start == -1)
	{
		_files_trim_start = strlen(__FILE__) - 21;
		strcpy(_files_trim_string,__FILE__);
		_files_trim_string[_files_trim_start] = 0;
	}
	if ( strncmp(file,_files_trim_string,_files_trim_start) == 0 ){
		//this file should be within the same directory area as we found lucenebase.cpp
		//to be, lets trim the start
		file+=_files_trim_start;
	}

   //now return an existing files structure (with refcount++) or create a new one
   defFile::iterator itr = LanBase_Files.find((const char*)file);
   if ( itr != LanBase_Files.end() ){
      _file* bf = itr->second;
      bf->refcount++;
      return bf;
   }else{
      _file* ref = new _file;
      ref->value = new char[strlen(file)+1]; //cannot use _CL_NEWARRAY otherwise recursion
	  strcpy(ref->value,file);

      ref->refcount = 1;
	  LanBase_Files.insert(pair<const char*,_file*>(ref->value,ref));
	  return ref;
   }
}



}}