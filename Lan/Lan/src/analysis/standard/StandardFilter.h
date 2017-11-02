/*------------------------------------------------------------------------------
* Copyright (C) 2003-2006 Ben van Klinken and the CLucene Team
* 
* Distributable under the terms of either the Apache License (Version 2.0) or 
* the GNU Lesser General Public License, as specified in the COPYING file.
------------------------------------------------------------------------------*/
#ifndef _Lan_analysis_standard_StandardFilter_
#define _Lan_analysis_standard_StandardFilter_

#include "AnalysisHeader.h"
#include "Analyzers.h"
#include "StandardTokenizerConstants.h"
//#include "StringBuffer.h"


namespace Lan
{
	namespace analysis
	{
		namespace standard
		{
	/** Normalizes tokens extracted with {@link StandardTokenizer}. */
	class StandardFilter: public TokenFilter{
	public:
		// Construct filtering <i>in</i>. 
		StandardFilter(TokenStream* in, bool deleteTokenStream);

		~StandardFilter();

		
	  /** Returns the next token in the stream, or NULL at EOS.
	  * <p>Removes <tt>'s</tt> from the end of words.
	  * <p>Removes dots from acronyms.
	  */
		bool next(Token* token);
	};
		}
	}
}
#endif
