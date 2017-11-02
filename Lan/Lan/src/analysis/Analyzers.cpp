#include "Analyzers.h"
#include "StringBuffer.h"
namespace Lan
{
	namespace analysis
	{
//CharTokenizer���ʵ��
CharTokenizer::CharTokenizer(Lan::util::Reader* in):
	Tokenizer(in),
	offset(0),
	bufferIndex(0),
	dataLen(0),
	ioBuffer(NULL)
{
	buffer[0]=0;
}
char CharTokenizer::normalize(const char c)const
{
	return c;
}
bool CharTokenizer::next(Token* token){
	int length = 0;
	int start = offset;
	while (true) {
		char c;
		offset++;
		if (bufferIndex >= dataLen) {
			dataLen = input->read(ioBuffer, 1024);
			if (dataLen == -1)
				dataLen = 0;
			bufferIndex = 0;
		}
		if (dataLen <= 0 ) {
			if (length > 0)
				break;
			else
				return false;
		}else
			c = ioBuffer[bufferIndex++];
		if (isTokenChar(c)) {                       // if it's a token TCHAR

			if (length == 0)			  // start of token
				start = offset-1;

			buffer[length++] = normalize(c);          // buffer it, normalized

			if (length == 255)		  // buffer overflow!
				break;

		} else if (length > 0)			  // at non-Letter w/ chars
			break;					  // return 'em

	}
	buffer[length]=0;
	token->set( buffer, start, start+length);
	return true;
}
//LetterTokenizer���ʵ��
bool LetterTokenizer::isTokenChar(const char c) const {
	return isalpha((unsigned char)c)!=0;
}
//LowerCaseTokenizer��ʵ��
char LowerCaseTokenizer::normalize(const char chr) const {
	return tolower((unsigned char)chr);
}
//LowerCaseFilter���ʵ��
bool LowerCaseFilter::next(Token* t)
{
	if(!input->next(t))
	{
		return false;
	}
	_strlwr(t->_termText); //ת��ΪСд
	return true;
}
TokenStream* SimpleAnalyzer::tokenStream(const char* fieldName,Lan::util::Reader* reader)
{
	return new LowerCaseTokenizer(reader);
}
//StopFilter���ʵ��
StopFilter::StopFilter(TokenStream* in, bool deleteTokenStream, const char** stopWords):
	TokenFilter(in, deleteTokenStream),
	table(new Lan::util::CLSetList<const char*>(false))
{
	fillStopTable(table,stopWords);
}

void StopFilter::fillStopTable(Lan::util::CLSetList<const char*>* stopTable,
								  const char** stopWords) {
	for (int i = 0; stopWords[i]!=NULL; i++)
		stopTable->insert(stopWords[i]);
}

bool StopFilter::next(Token* token)
{
	while(input->next(token))
	{
		if(table->find(token->_termText)==table->end())
		{
			return true;
		}
	}
	return false;
}



	}
}




