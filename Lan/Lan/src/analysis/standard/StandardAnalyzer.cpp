#include "StandardAnalyzer.h"
namespace Lan
{
	namespace analysis
	{
		namespace standard
		{

StandardAnalyzer::StandardAnalyzer():stopSet(false)
{
	////StopFilter::
}

TokenStream* StandardAnalyzer::tokenStream(const char* fieldName, Lan::util::Reader* reader)
{
	TokenStream* ret = new StandardTokenizer(reader);
	ret = new StandardFilter(ret, true);
	ret = new LowerCaseFilter(ret, true);
	ret = new StopFilter(ret, true, &stopSet);
	return ret;
}
StandardAnalyzer::~StandardAnalyzer()
{

}
		}
	}
}