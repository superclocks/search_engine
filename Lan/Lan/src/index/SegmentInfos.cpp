#include "SegmentInfos.h"
#include "Directory.h"
#include "VoidMap.h"
#include "Misc.h"
using namespace Lan::store;
using namespace Lan::util;
namespace Lan
{namespace index{
//SegmentInfo类的实现
SegmentInfo::SegmentInfo(const char* Name, const int DocCount, Lan::store::Directory* Dir): 
	docCount(DocCount),dir(Dir)
{
	//STRCPY_AtoA(name,Name,CL_MAX_NAME);
		strncpy(name,Name,260);
}
  
SegmentInfo::~SegmentInfo()
{
}

//SegmentInfos类的实现
SegmentInfos::SegmentInfos(bool deleteMembers) :
      infos(deleteMembers){
  
      counter = 0;
      version = Misc::currentTimeMillis();
  }

SegmentInfos::~SegmentInfos()
{
   infos.clear();
}
  
SegmentInfo* SegmentInfos::info(int i) 
{
	//CND_PRECONDITION(i >= 0, "i contains negative number");
	if(i<0)
	{
		printf("i contains negative number");
		assert(0);
	}
	//Get the i-th SegmentInfo instance
    SegmentInfo *ret = infos[i];
    //Condition check to see if the i-th SegmentInfo has been retrieved
    //CND_CONDITION(ret != NULL,"No SegmentInfo instance found");
	if(ret==NULL)
	{
		printf("No SegmentInfo instance found");
		assert(0);
	}
    return ret;
}

void SegmentInfos::clearto(unsigned int _min)
{
	if (infos.size()>_min) 
	{ // Make sure we actually need to remove
		segmentInfosType::iterator itr,bitr=infos.begin()+_min,eitr=infos.end();
		for(itr=bitr;itr!=eitr;++itr)
		{
				//_CLLDELETE((*itr));
				if((*itr)!=NULL)
				{
					delete *itr;
				}
		}
		infos.erase(bitr,eitr);
	}
}
void SegmentInfos::add(SegmentInfo* info)
{
	infos.push_back(info);
}
int SegmentInfos::size() const
{
	return infos.size();
}

  //void SegmentInfos::read(Directory* directory){
  ////Func - Reads segments file that resides in directory. 
  ////Pre  - directory contains a valid reference
  ////Post - The segments file has been read and for each segment found
  ////       a SegmentsInfo intance has been created and stored.

	 // //Open an IndexInput to the segments file
  //    IndexInput* input = directory->openInput("segments");
	 // //Check if input is valid
	 // if (input){
  //      try {
  //          int32_t format = input->readInt();

  //          if(format < 0){     // file contains explicit format info
  //             // check that it is a format we can understand
  //             if (format < FORMAT){
  //                TCHAR err[30];
  //                _sntprintf(err,30,_T("Unknown format version: %d"),format);
  //                _CLTHROWT(CL_ERR_Runtime,err);
  //             }
  //             version = input->readLong(); // read version
  //             counter = input->readInt(); // read counter
  //          }
  //          else{     // file is in old format without explicit format info
  //             counter = format;
  //          }

  //          //Temporary variable for storing the name of the segment
  //          TCHAR tname[CL_MAX_PATH];
  //          char aname[CL_MAX_PATH];
  //          SegmentInfo* si  = NULL;

  //          //read segmentInfos
  //          for (int32_t i = input->readInt(); i > 0; --i){ 
  //              // read the name of the segment
  //              input->readString(tname, CL_MAX_PATH); 
		//		STRCPY_TtoA(aname,tname,CL_MAX_PATH);

  //              //Instantiate a new SegmentInfo Instance
  //              si = _CLNEW SegmentInfo(aname, input->readInt(),directory);

  //              //Condition check to see if si points to an instance
  //              CND_CONDITION(si != NULL, "Memory allocation for si failed")	;

  //              //store SegmentInfo si
  //              infos.push_back(si);
  //           } 

  //          if(format >= 0){ // in old format the version number may be at the end of the file
  //             if (input->getFilePointer() >= input->length())
  //                version = Misc::currentTimeMillis(); // old file format without version number
  //             else
  //                version = input->readLong(); // read version
  //          }
  //      } _CLFINALLY(
  //          //destroy the inputStream input. The destructor of IndexInput will 
		//    //also close the Inputstream input
  //          _CLDELETE( input );
  //          );
	 // }
  //}

  void SegmentInfos::write(Directory* directory){
  //Func - Writes a new segments file based upon the SegmentInfo instances it manages
  //Pre  - directory is a valid reference to a Directory
  //Post - The new segment has been written to disk
    
	  //Open an IndexOutput to the segments file
	  IndexOutput* output = directory->createOutput("segments.new");
	   //Check if output is valid
	  if (output){
          try {
		   output->writeInt(FORMAT); // write FORMAT
           output->writeLong(++version); // every write changes the index
           output->writeInt(counter); //Write the counter

			  //Write the number of SegmentInfo Instances
			  //which is equal to the number of segments in directory as
			  //each SegmentInfo manages a single segment
			  output->writeInt(infos.size());			  

			  SegmentInfo *si = NULL;

			  //temporary value for wide segment name
			  char tname[260];

			  //Iterate through all the SegmentInfo instances
           for (unsigned int i = 0; i < infos.size(); ++i) {
				  //Retrieve the SegmentInfo
               si = info(i);
               //Condition check to see if si has been retrieved
               //CND_CONDITION(si != NULL,"No SegmentInfo instance found");
			   if(si==NULL)
			   {
				   printf("No SegmentInfo instance found");
				   assert(0);
			   }
				  //Write the name of the current segment
              //STRCPY_AtoT(tname,si->name,CL_MAX_PATH);
			   strncpy(tname,si->name,260);
			output->writeString(tname,strlen(tname));

				  //Write the number of documents in the segment 
              output->writeInt(si->docCount);
           }
         }/* _CLFINALLY(
              output->close();
              _CLDELETE( output );
         );*/
		  catch(...)
		  { 
			 output->close();
              //_CLDELETE( output );
			  if(output!=NULL)
			  {
				  delete output;
				  output = NULL;
			  }
			  throw; 
		  }
		output->close(); 
		if(output!=NULL)
		{
			delete output;
			output = NULL;
		}
			 

          // install new segment info
          directory->renameFile("segments.new","segments");
	  }
  }

  
//__int64 SegmentInfos::readCurrentVersion(Directory* directory)
//{
//    IndexInput* input = directory->openInput("segments");
//    int32_t format = 0;
//    int64_t version = 0;
//    try {
//      format = input->readInt();
//      if(format < 0){
//         if(format < FORMAT){
//            TCHAR err[30];
//            _sntprintf(err,30,_T("Unknown format version: %d"),format);
//            _CLTHROWT(CL_ERR_Runtime,err);
//         }
//         version = input->readLong(); // read version
//       }
//     }
//     _CLFINALLY( input->close(); _CLDELETE(input); );
//     
//     if(format < 0)
//      return version;
//
//    // We cannot be sure about the format of the file.
//    // Therefore we have to read the whole file and cannot simply seek to the version entry.
//    SegmentInfos* sis = _CLNEW SegmentInfos();
//    sis->read(directory);
//    version = sis->getVersion();
//    _CLDELETE(sis);
//    return version;
//}


}}

