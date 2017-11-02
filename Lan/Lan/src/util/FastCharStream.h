
#ifndef _Lan_util_FastCharStream_
#define _Lan_util_FastCharStream_

#include "Reader.h"
namespace Lan
{
	namespace util
	{

	/** Ported implementation of the FastCharStream class. */
	class FastCharStream/*:LUCENE_BASE*/
	{
		static const int maxRewindSize;
		int pos;
		int rewindPos;
		__int64 resetPos;
		int col;
		int line;
		// read character from stream return false on error
		void readChar(char &);	
	public:
		Reader* input;

		/// Initializes a new instance of the FastCharStream class LUCENE_EXPORT.
		FastCharStream(Reader* reader);
		~FastCharStream();
		
		/// Returns the next TCHAR from the stream.
		int GetNext();

		void UnGet();
		
		/// Returns the current top TCHAR from the input stream without removing it.
		int Peek();
		
		
		/// Returns <b>True</b> if the end of stream was reached.
		bool Eos() const;

		/// Gets the current column.
		int Column() const;

		/// Gets the current line.
		int Line() const;
	};



	}
}
#endif
