#include "FSDirectory.h"
#include "Misc.h"
#include "Equators.h"
#include <assert.h>
using namespace Lan::util;
namespace Lan
{namespace store{

static Lan::util::CLHashMap<const char*, FSDirectory*, Lan::util::Compare::Char,Lan::util::Equals::Char> DIRECTORIES(false,false);
FSDirectory::FSDirectory(const char* path,const bool createDir)/*:
	Directory()*/
	 /*refCount(0),
   useMMap(false)*/
{
	//_fullpath(directory,path,260);

}
bool FSDirectory::doDeleteFile(const char* name)
{
	return true;
}

FSDirectory* FSDirectory::getDirectory(const char* file, const bool _create)
{
	FSDirectory* dir=NULL;
	if(!file || !*file)
	{
		printf("Invalid directory");
		assert(0);
	}
	dir =DIRECTORIES.get(file);
	if(dir==NULL)
	{
		dir=new FSDirectory(file,_create);
	}
	return dir;
}

void FSDirectory::list(vector<string>* name)const
{

}
void FSDirectory::priv_getFN(char* buffer, const char* name) const
{
      buffer[0] = 0;
      strcpy(buffer,directory);
      strcat(buffer, "\\" );
      strcat(buffer,name);
}

void FSDirectory::renameFile(const char* from, const char* to)
{
	//CND_PRECONDITION(directory[0]!=0,"directory is not open");
 //   SCOPED_LOCK_MUTEX(THIS_LOCK)
 //   char old[CL_MAX_DIR];
 //   priv_getFN(old, from);

 //   char nu[CL_MAX_DIR];
 //   priv_getFN(nu, to);

 //   /* This is not atomic.  If the program crashes between the call to
 //   delete() and the call to renameTo() then we're screwed, but I've
 //   been unable to figure out how else to do this... */

 //   if ( Misc::dir_Exists(nu) ){
 //     //we run this sequence of unlinking an arbitary 100 times
 //     //on some platforms (namely windows), there can be a
 //     //delay between unlink and dir_exists==false          
 //     while ( true ){
 //         if( _unlink(nu) != 0 ){
 //   	    char* err = _CL_NEWARRAY(char,16+strlen(to)+1); //16: len of "couldn't delete "
 //   		strcpy(err,"couldn't delete ");
 //   		strcat(err,to);
 //           _CLTHROWA_DEL(CL_ERR_IO, err );
 //         }
 //         //we can wait until the dir_Exists() returns false
 //         //after the success run of unlink()
 //         int i=0;
 //         while ( Misc::dir_Exists(nu) && i < 100 ){
 //           if ( ++i > 50 ) //if it still doesn't show up, then we do some sleeping for the last 50ms
 //             _LUCENE_SLEEP(1);
 //         }
 //         if ( !Misc::dir_Exists(nu) )
 //           break; //keep trying to unlink until the file is gone, or the unlink fails.
 //     }
 //   }
 //   if ( _rename(old,nu) != 0 ){
 //      //todo: jlucene has some extra rename code - if the rename fails, it copies
 //      //the whole file to the new file... might want to implement that if renaming
 //      //fails on some platforms
 //       char buffer[20+CL_MAX_PATH+CL_MAX_PATH];
 //       strcpy(buffer,"couldn't rename ");
 //       strcat(buffer,from);
 //       strcat(buffer," to ");
 //       strcat(buffer,nu);
 //     _CLTHROWA(CL_ERR_IO, buffer );
 //   }
}
IndexOutput* FSDirectory::createOutput(const char* name)
{
	if(directory[0]==0)
	{
		printf("directory is not open");
		assert(0);
	}
	char fl[260];
	priv_getFN(fl,name);
	/*if ( Misc::dir_Exists(fl) ){
		if ( _unlink(fl) != 0 ){
			char tmp[1024];
			strcpy(tmp, "Cannot overwrite: ");
			strcat(tmp, name);
			_CLTHROWA(CL_ERR_IO, tmp);
		}
	}*/
	IndexOutput* in;
	return in;
}
void FSDirectory::close()
{

}
	
}}