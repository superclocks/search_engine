#include "AnalysisHeader.h"

namespace Lan
{namespace analysis{

const char* Token::defaultType="word";
Token::Token():_startOffset(0),_endOffset(0),_type(defaultType),positionIncrement(1)
{
	_termTextLen=0;
	_termText = NULL;
	bufferTextLen = 0;
}
Token::~Token()
{

}
Token::Token(const char* text, const int start, const int end, const char* typ):
	_startOffset (start),
	_endOffset (end),
	_type ( typ ),
	positionIncrement (1)
{
    _termTextLen = 0;
#ifndef LUCENE_TOKEN_WORD_LENGTH
    _termText = NULL;
	bufferTextLen = 0;
#else
    _termText[0] = 0; //make sure null terminated
	bufferTextLen = LUCENE_TOKEN_WORD_LENGTH+1;
#endif
	//setText(text);
}
void Token::set(const char* text, const int start, const int end, const char* typ){
	_startOffset = start;
	_endOffset   = end;
	_type        = typ;
	positionIncrement = 1;
	setText(text);
}
unsigned int Token::termTextLength()
{
	if(_termTextLen == -1)
	{
		_termTextLen = strlen(_termText);
	}
	return _termTextLen;
}
void Token::resetTermTextLen()
{
	_termTextLen = -1;
	growBuffer(_termTextLen+1);
}
void Token::setText(const char* text)
{
	_termTextLen=strlen(text);
	growBuffer(_termTextLen+1);
	strncpy(_termText,text,_termTextLen+1);
	_termText[_termTextLen] = 0;
}
const char* Token::termText() const
{
	return (const char*) _termText;
}
void Token::growBuffer(unsigned int size)
{
	if(bufferTextLen >= size)
	{
		return;
	}
	if(_termText == NULL)
	{
		_termText = (char*)malloc(size * sizeof(char));
	}
	else
	{
		_termText = (char*)realloc(_termText, size * sizeof(char));
	}
	bufferTextLen = size;
}
void Token::setPositionIncrement(int posIncr) 
{
	if (posIncr < 0) {
		//_CLTHROWA(CL_ERR_IllegalArgument,"positionIncrement must be >= 0");
		printf("positionIncrement must be >= 0");
	}
	positionIncrement = posIncr;
}

int Token::getPositionIncrement() const 
{ 
	return positionIncrement; 
}
int Analyzer::getPositionIncrementGap(const char* fieldName)
{
	return 0;
}

TokenFilter::TokenFilter(TokenStream* in, bool deleteTS):
	input(in),
	deleteTokenStream(deleteTS)
{
}
TokenFilter::~TokenFilter(){
	close();
}

// Close the input TokenStream.
void TokenFilter::close() {
    if ( input != NULL ){
		//input->close();
        if ( deleteTokenStream )
			if(input!=NULL)
			{
				delete input;
				input=NULL;
			}
			//_CLDELETE( input );
    }
    input = NULL;
}
Tokenizer::Tokenizer()
{
	input=NULL;
}
Tokenizer::Tokenizer(Lan::util::Reader* _input)
	:input(_input)
{

}
Tokenizer::~Tokenizer()
{

}
void Tokenizer::close()
{
	if(input!=NULL)
	{
		// ? delete input;
		input = NULL;
	}
}





analyzer::analyzer()
{

}
int analyzer::getPositionIncrementGap(const string fieldName)
{
	return 0;
}
	}
}