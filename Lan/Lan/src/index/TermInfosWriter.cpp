#include "TermInfosWriter.h"
#include "Directory.h"
#include "Misc.h"
#include "FieldInfos.h"
#include "Term.h"
#include "TermInfo.h"
#include "IndexWriter.h"

using namespace Lan::util;
using namespace Lan::store;

namespace Lan
{namespace index{
TermInfosWriter::TermInfosWriter(Directory* directory,const char* segment,FieldInfos* fis,int interval):
fieldInfos(fis)
{
	 //CND_PRECONDITION(segment != NULL, "segment is NULL");
	if(segment==NULL)
		printf("segment is NULL");
	//Initialize instance
     initialise(directory,segment,interval, false);

	other = new TermInfosWriter(directory, segment,fieldInfos, interval, true);

	//CND_CONDITION(other != NULL, "other is NULL");
	if(segment==NULL)
		printf("other is NULL");

	other->other = this;
} 
TermInfosWriter::TermInfosWriter(Directory* directory, const char* segment, FieldInfos* fis, int interval, bool isIndex):
	    fieldInfos(fis)
{
	//CND_PRECONDITION(segment != NULL, "segment is NULL");
	if(segment==NULL)
		printf("segment is NULL");
    initialise(directory,segment,interval,isIndex);
}
void TermInfosWriter::initialise(Directory* directory, const char* segment, int interval, bool IsIndex)
{
	lastTerm = new Term;

	//CND_CONDITION(lastTerm != NULL, "Could not allocate memory for lastTerm");
	if(lastTerm==NULL)
		printf("Could not allocate memory for lastTerm");
    
	lastTi  = new TermInfo();

    //CND_CONDITION(lastTi != NULL, "Could not allocate memory for lastTi");
	if(lastTi==NULL)
		printf("Could not allocate memory for lastTi");
	lastIndexPointer = 0;
	size             = 0;
	isIndex          = IsIndex;
	indexInterval = interval;
	skipInterval = Lan_Default_TermDocs_Skip_Interval;

	const char* buf = Misc::segmentname(segment, (isIndex ? ".tii" : ".tis"));
	output = directory->createOutput( buf );
	//_CLDELETE_CaARRAY(buf);
	if(buf!=NULL)
	{
		delete[] buf;
		buf=NULL;
	}
	output->writeInt(FORMAT);                      // write format
	output->writeLong(0);                          // leave space for size
	output->writeInt(indexInterval);// write indexInterval
	output->writeInt(skipInterval); // write skipInterval

        //Set other to NULL by Default
    other = NULL;
}
TermInfosWriter::~TermInfosWriter()
{
	close();
}
void TermInfosWriter::add(Term* term,const TermInfo* ti)
{
	if(!(isIndex || (!isIndex && term->compareTo(lastTerm)>0)))
		printf("term out of order");
	if(!(ti->freqPointer >= lastTi->freqPointer))
		printf("freqPointer out of order");
	if(!(ti->proxPointer >= lastTi->proxPointer))
		printf("proxPointer out of order");
	if(!isIndex && size%indexInterval==0)
	{
		other->add(lastTerm,lastTi);
	}
	writeTerm(term);
	output->writeVInt(ti->docFreq);
	output->writeVLong(ti->freqPointer - lastTi->freqPointer);
	output->writeVLong(ti->proxPointer - lastTi->proxPointer);
	if(ti->docFreq>=skipInterval)
	{
		output->writeVInt(ti->skipOffset);
	}
	if (isIndex)
	{
		output->writeVLong(other->output->getFilePointer() - lastIndexPointer);
		lastIndexPointer = other->output->getFilePointer(); // write pointer
	}

	lastTi->set(ti);
	size++;
}

void TermInfosWriter::close() {
    //Func - Closes the TermInfosWriter
	//Pre  - true
	//Post - The TermInfosWriter has been closed
    
		if (output){
			//write size at start
		    output->seek(4);          // write size after format
		    output->writeLong(size);
		    output->close();
		   //_CLDELETE(output);
		   if(output!=NULL)
		   {
			   delete output;
			   output = NULL;
		   }


		   if (!isIndex){
			   if(other){
			      other->close();
			      //_CLDELETE( other );
				  if(other!=NULL)
					{
						delete other;
						other = NULL;
					}
			      }
		      }
              _CLDECDELETE(lastTerm);

		      //_CLDELETE(lastTi);
				if(lastTi!=NULL)
				{
					delete lastTi;
					lastTi = NULL;
				}
		   }
	}

	void TermInfosWriter::writeTerm(Term* term) {
	    int start = Misc::stringDifference(lastTerm->text(),lastTerm->textLength(), 
			term->text(),term->textLength());
		int length = term->textLength() - start;
	 
		output->writeVInt(start);			  // write shared prefix length
		output->writeVInt(length);			  // write delta length
		output->writeChars(term->text(), start, length);  // write delta chars

		int fieldnum = fieldInfos->fieldNumber(term->field());
		CND_PRECONDITION(fieldnum>=-1&&fieldnum<fieldInfos->size(),"Fieldnum is out of range");
		output->writeVInt(fieldnum); // write field num

		if ( lastTerm->__cl_refcount == 1 ){
			lastTerm->set(term,term->text());
		}else{
			_CLDECDELETE(lastTerm);
			lastTerm = _CL_POINTER(term);
		}
	}




}}