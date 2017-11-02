#ifndef _Lan_index_SegmentInfos_
#define _Lan_index_SegmentInfos_
#include "VoidList.h"
#include "Directory.h"
namespace Lan
{namespace index{

class SegmentInfo
{
private:
	Lan::store::Directory* dir; //存储段
public:
	Lan::store::Directory* getDir() const {return dir;} //获得存储段信息
	char name[260];
	const int docCount;
	SegmentInfo(const char* Name, const int DocCount, Lan::store::Directory* Dir);
	~SegmentInfo();
};
typedef Lan::util::CLVector<SegmentInfo*,Lan::util::Deletor::Object<SegmentInfo> > segmentInfosType;
class SegmentInfos/*: LUCENE_BASE */
{
	/** The file format version, a negative number. */
	/* Works since counter, the old 1st entry, is always >= 0 */
	//LUCENE_STATIC_CONSTANT(int32_t,FORMAT=-1);
	enum { FORMAT=-1 };
	/**
	* counts how often the index has been changed by adding or deleting docs.
	* starting with the current time in milliseconds forces to create unique version numbers.
	*/
	__int64 version;

	segmentInfosType infos;
		
    int counter;  // used to name new segments
	friend class IndexWriter; //allow IndexWriter to use counter
public:
    SegmentInfos(bool deleteMembers=true);
    ~SegmentInfos();

		
	//delete and clears objects 'from' from to 'to'
	void clearto(size_t to);
		
	//count of segment infos
	int size() const;
	//add a segment info
	void add(SegmentInfo* info);
	//Returns a reference to the i-th SegmentInfo in the list.
	SegmentInfo* info(int i);
		
	/**
	* version number when this SegmentInfos was generated.
	*/
	__int64 getVersion() { return version; }
		
	static __int64 readCurrentVersion(Lan::store::Directory* directory);

	//Reads segments file that resides in directory
	//void read(Lan::store::Directory* directory);

	//Writes a new segments file based upon the SegmentInfo instances it manages
    void write(Lan::store::Directory* directory);
};

}}




#endif