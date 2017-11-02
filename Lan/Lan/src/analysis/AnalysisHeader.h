#ifndef _Lan_analysis_AnalysisHeader_
#define _Lan_analysis_AnalysisHeader_

#include <string>
#include <vector>

#include "Reader.h"

using namespace std;

namespace Lan
{
	namespace analysis
	{


class Token
{
private:
	int _startOffset;
	int _endOffset;
	const char* _type;
	int positionIncrement;
	unsigned int bufferTextLen;

public:
	char* _termText;

	int _termTextLen;
	static const char* defaultType;

	Token();
	~Token();

	Token(const char* text, const int start, const int end, const char* typ=defaultType);
	void set(const char* text, const int start,const int end, const char* typ=defaultType);
	unsigned int bufferLength(){return bufferTextLen;}
	void growBuffer(unsigned int size);
	const char* termText() const;
	unsigned int termTextLength();
	const char* type() const { return _type; }
	void resetTermTextLen();
	void setText(const char* txt);
	
	int startOffset() const { return _startOffset; }
	void setStartOffset(int val){ _startOffset = val; }

	int endOffset() const { return _endOffset; }
	void setEndOffset(int val){ _endOffset = val; }

	void setPositionIncrement(int posIncr);
	int getPositionIncrement() const;

};

class TokenStream
{
public:
	virtual bool next(Token* token)=0;
	virtual ~TokenStream(){};
	virtual void close() = 0;

};

class Analyzer
{
public:
	virtual TokenStream* tokenStream(const char* fieldName,Lan::util::Reader* reader) = 0;
	virtual ~Analyzer(){}
	virtual int getPositionIncrementGap(const char* fieldName);
};



class Tokenizer:public TokenStream
{
protected:
	Lan::util::Reader* input;
public:
	Tokenizer();
	Tokenizer(Lan::util::Reader* _input);
	virtual void close();
	virtual ~Tokenizer();

};

class TokenFilter:public TokenStream
{
protected:
	TokenStream* input;
	bool deleteTokenStream;
	TokenFilter(TokenStream* in,bool deleteTS = false);
	virtual ~TokenFilter();
public:
	void close();
};

class analyzer
{
public:
	//virtual TokenStream* tokenStream();
	analyzer();
	virtual ~analyzer(){};

	virtual int getPositionIncrementGap(const string fieldName);
};
	}
}



#endif