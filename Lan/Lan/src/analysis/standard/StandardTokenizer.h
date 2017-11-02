
#ifndef _Lan_analysis_standard_StandardTokenizer_
#define _Lan_analysis_standard_StandardTokenizer_
#include <tchar.h>
#include <string>

#include "AnalysisHeader.h"
#include "Analyzers.h"
#include "StandardTokenizerConstants.h"
#include "StringBuffer.h"
#include "FastCharStream.h"
#include "Reader.h"
using namespace std;
namespace Lan
{
	namespace analysis
	{
		namespace standard
		{

  class StandardTokenizer: public Tokenizer {
  private:
    int rdPos;
    int tokenStart;

    // Advance by one character, incrementing rdPos and returning the character.
    int readChar();
    // Retreat by one character, decrementing rdPos.
    void unReadChar();

    // createToken centralizes token creation for auditing purposes.
	//Token* createToken(CL_NS(util)::StringBuffer* sb, TokenTypes tokenCode);
    inline bool setToken(Token* t, Lan::util::StringBuffer* sb, TokenTypes tokenCode);

    //bool ReadDotted(Lan::util::StringBuffer* str, TokenTypes forcedType,Token* t);

  public:
	Lan::util::FastCharStream* rd;

    // Constructs a tokenizer for this Reader.
    StandardTokenizer(Lan::util::Reader* reader);

    ~StandardTokenizer();

    /** Returns the next token in the stream, or false at end-of-stream.
    * The returned token's type is set to an element of
    * StandardTokenizerConstants::tokenImage. */
    bool next(Token* token);

    // Reads for number like "1"/"1234.567", or IP address like "192.168.1.2".
    bool ReadNumber(const char* previousNumber, const char prev, Token* t);

    bool ReadAlphaNum(const char prev, Token* t);

    //// Reads for apostrophe-containing word.
    //bool ReadApostrophe(CL_NS(util)::StringBuffer* str, Token* t);

    //// Reads for something@... it may be a COMPANY name or a EMAIL address
    //bool ReadAt(CL_NS(util)::StringBuffer* str, Token* t);

    //// Reads for COMPANY name like AT&T.
    //bool ReadCompany(CL_NS(util)::StringBuffer* str, Token* t);
    //
    //// Reads CJK characters
    bool ReadCJK(const char prev, Token* t);
  };

		}
	}
}
#endif
