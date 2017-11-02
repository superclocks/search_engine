#ifndef _Lan_analysis_analyzer_
#define _Lan_analysis_analyzer_
#include "Document.h"
#include "Token.h"
#include "AnalysisHeader.h"
#include "Reader.h"
#include "VoidList.h"

#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using namespace Lan::index;
using namespace Lan::document;
namespace Lan
{
	namespace analysis
	{
class CharTokenizer:public Tokenizer
{
	int offset, bufferIndex, dataLen;
	char buffer[255+1];
	const char* ioBuffer;
protected:
	virtual bool isTokenChar(const char c) const=0;
	virtual char normalize(const char c) const;
public:
	CharTokenizer(Lan::util::Reader* in);
	virtual ~CharTokenizer(){}
	bool next(Token* token);
};

class LetterTokenizer:public CharTokenizer {
public:
	// Construct a new LetterTokenizer. 
	LetterTokenizer(Lan::util::Reader* in):
	CharTokenizer(in) {}

    ~LetterTokenizer(){}
protected:
    /** Collects only characters which satisfy _istalpha.*/
	bool isTokenChar(const char c) const;
};
class LowerCaseTokenizer:public LetterTokenizer {
public:
	/** Construct a new LowerCaseTokenizer. */
	LowerCaseTokenizer(Lan::util::Reader* in):
	LetterTokenizer(in) {}

    ~LowerCaseTokenizer(){}
protected:
	/** Collects only characters which satisfy _totlower. */
	char normalize(const char chr) const;
};
//
class SimpleAnalyzer:public Analyzer
{
public:
	TokenStream* tokenStream(const char* fieldName,Lan::util::Reader* reader);
	~SimpleAnalyzer(){}
};
/*一下定义的类都继承TokenFilter,
而TokenFilter则继承抽象基类TokenStream
所有下面的类用于构成分词链对分词进行处理
*/
class LowerCaseFilter:public TokenFilter //将单词转化为小写
{
public:
	LowerCaseFilter(TokenStream* in, bool deleteTokenStream):
	  TokenFilter(in,deleteTokenStream){}
	~LowerCaseFilter(){}
	bool next(Token* token); //重要的分词函数
};

class StopFilter:public TokenFilter   //过滤停词
{
private:
	Lan::util::CLSetList<const char*>* table;
public:
	StopFilter(TokenStream* in, bool deleteTokenStream, const char** stopWords);
	StopFilter(TokenStream* in, bool deleteTokenStream, Lan::util::CLSetList<const char*>* stopTable):
	TokenFilter(in,deleteTokenStream),table(stopTable){}
	~StopFilter(){}
	static void fillStopTable(Lan::util::CLSetList<const char*>* stopTable, const char** stopWords);

	bool next(Token* token);
};





	}
}
#endif
