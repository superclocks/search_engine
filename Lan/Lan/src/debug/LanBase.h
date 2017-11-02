#ifndef _lucene_debug_LanBase_
#define _lucene_debug_LanBase_
namespace Lan
{namespace debug
{class LanBase{
public:
	static void* operator new (unsigned int size);
	static void operator delete (void* p);
	int __cl_initnum;

	static void* operator new (unsigned int size, char const * file, int line);
	static void operator delete (void* p, char const* file, int line);

	static void* __cl_voidpadd(void* data, const char* file, int line, size_t size);
	static void __cl_voidpremove(const void* data, const char* file, int line);
	static void __cl_unregister(const void* obj); 

	static int __cl_GetUnclosedObjectsCount(); 
	static const char* __cl_GetUnclosedObject(int item); 
	static char* __cl_GetUnclosedObjects(); 
	static void __cl_PrintUnclosedObjects();
  
  	
  	static void __cl_ClearMemory();



	int __cl_refcount;
	LanBase(){
		__cl_refcount=1;
	}
	inline int __cl_getref(){
		return __cl_refcount;
	}
	inline int __cl_addref(){
		__cl_refcount++;
		return __cl_refcount;
	}
	inline int __cl_decref(){
		__cl_refcount--;
		return __cl_refcount;
	}
    virtual ~LanBase(){};

};
class LanVoidBase{
	public:
	
		int dummy__see_mem_h_for_details; 
        virtual ~LanVoidBase(){};
};
	

}}



#endif