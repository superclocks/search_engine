#ifndef _Lan_analysis_standard_StandardAnalyzer_
#define _Lan_analysis_standard_StandardAnalyzer_
#include "VoidMap.h"
#include "Reader.h"
#include "AnalysisHeader.h"
#include "Analyzers.h"
#include "VoidList.h"
#include "StandardFilter.h"
#include "StandardTokenizer.h"

namespace Lan
{
	namespace analysis
	{
		namespace standard
		{
class StandardAnalyzer:public Analyzer
{
private:
	Lan::util::CLSetList<const char*> stopSet;
public:
	StandardAnalyzer();
	StandardAnalyzer(const char** stopWords);
	~StandardAnalyzer();
	TokenStream* tokenStream(const char* fieldName, Lan::util::Reader* reader);
};
		}
	}
}




#endif