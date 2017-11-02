
#include "StandardTokenizer.h"
namespace Lan
{
	namespace analysis
	{
		namespace standard
		{
const char* tokenImageArray[] = {
    ("<EOF>"),
    ("<UNKNOWN>"),
    ("<ALPHANUM>"),
    ("<APOSTROPHE>"),
    ("<ACRONYM>"),
    ("<COMPANY>"),
    ("<EMAIL>"),
    ("<HOST>"),
    ("<NUM>"),
    ("<CJK>")
  };
const char** tokenImage = tokenImageArray;
 #define EOS           (ch==-1 || rd->Eos())
 #define SPACE         (_istspace((TCHAR)ch) != 0)
 #define ALPHA         (_istalpha((TCHAR)ch) != 0)
 #define ALNUM         (_istalnum(ch) != 0)
 #define DIGIT         (_istdigit(ch) != 0)
 #define UNDERSCORE    (ch == '_')

 #define _CJK			(  (ch>=0x3040 && ch<=0x318f) || \
  						   (ch>=0x3300 && ch<=0x337f) || \
  						   (ch>=0x3400 && ch<=0x3d2d) || \
  						   (ch>=0x4e00 && ch<=0x9fff) || \
  						   (ch>=0xf900 && ch<=0xfaff) || \
  						   (ch>=0xac00 && ch<=0xd7af) ) 

StandardTokenizer::StandardTokenizer(Lan::util::Reader* reader):
		rd(new Lan::util::FastCharStream(reader)),
    rdPos(-1),
    tokenStart(-1)
{

}
inline bool StandardTokenizer::setToken(Token* t, Lan::util::StringBuffer* sb, TokenTypes tokenCode)
{
	//其它内容待添加
	return true;
}

bool StandardTokenizer::ReadCJK(const char prev, Token* t) {
    t->growBuffer(255+1);//make sure token can hold the next word
	Lan::util::StringBuffer str(t->_termText,t->bufferLength(),true); //use stringbuffer to read data onto the termText
	if ( str.len < 255 ){
		str.appendChar(prev);
		int ch = prev;

		//CONSUME_CJK;
	}
	return setToken(t,&str,Lan::analysis::standard::CJK);
  } 
bool StandardTokenizer::next(Token* t)
{
	int ch=0;
	while (!(ch==-1 || rd->Eos())) 
	{
      ch = readChar();

	  if ( ch == 0 || ch == -1 )
	  {
		continue;
	  } 
	  else if (isspace((unsigned char)(char)ch) != 0) //如果ch为空则继续
	  {
        continue;
      } 
	  else if ((isalpha((unsigned char)(char)ch) != 0) || ch == '_') //如果ch为字母或者ch为'_'执行如下操作
	  {
        tokenStart = rdPos;
        return ReadAlphaNum(ch,t);
      } 
	  else if ((isdigit((unsigned char)(char)ch) != 0) || ch == '-' || ch == '.')  //如果ch为十进制小数，或者ch为'-',或者ch为‘.’时执行如下操作
	  {
        tokenStart = rdPos;
        /* ReadNumber returns NULL if it fails to extract a valid number; in
        ** that case, we just continue. */
        if (ReadNumber(NULL, ch,t))
          return true;
	  } 
	  else if ( _CJK )
	  {
      	if ( ReadCJK(ch,t) )
      		return true;
      }
    }
    return false;
}
StandardTokenizer::~StandardTokenizer()
{
	if(rd!=NULL)
	{
		delete rd;
		rd=NULL;
	}
}
bool StandardTokenizer::ReadNumber(const char* previousNumber, const char prev,Token* t)
{
	return true;
}
bool StandardTokenizer::ReadAlphaNum(const char prev, Token* t)
{
	t->growBuffer(255+1);
	Lan::util::StringBuffer str(t->_termText,t->bufferLength(),true);
	if(str.len< 255)
	{
		str.appendChar(prev);
		int ch = prev;
		while (true) 
		{ 
			ch = readChar(); 
			if (ch==-1 || (!(isalnum((unsigned char)ch)!=0 || ch=='_') || str.len >= 255)) 
			{ 
				break;
			}
			str.appendChar(ch);
		}
		return true;
		if(!(ch==-1 || rd->Eos()) && str.len < 255-1)
		{
			switch(ch)
			{
			case '.':
				str.appendChar('.');
				//return ReadDotted(
			}
		}
	}
	
}
int StandardTokenizer::readChar()
{
	rdPos++;
	return rd->GetNext();
}
		}
	}
}
