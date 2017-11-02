
#ifndef _Lan_analysis_standard_StandardTokenizerConstants_
#define _Lan_analysis_standard_StandardTokenizerConstants_
namespace Lan
{
	namespace analysis
	{
		namespace standard
		{
  enum TokenTypes {
    _EOF,
    UNKNOWN,
    ALPHANUM,
    APOSTROPHE,
    ACRONYM,
    COMPANY,
    EMAIL,
    HOST,
    NUM,
    CJK
  };
  extern const char** tokenImage;

		
		}
	}
}
#endif
