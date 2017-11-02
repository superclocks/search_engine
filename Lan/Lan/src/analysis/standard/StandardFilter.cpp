#include "StandardFilter.h"


namespace Lan
{
	namespace analysis
	{
		namespace standard
		{
StandardFilter::StandardFilter(TokenStream* in, bool deleteTokenStream):
		TokenFilter(in, deleteTokenStream)
{
}
StandardFilter::~StandardFilter()
{
}
bool StandardFilter::next(Token* t)
{
	if(!input->next(t))
	{
		return false;
	}
	char* text = t->_termText;
	const int textLength = t->termTextLength();
	const char* type = t->type();
	char str[]="'s";
	if(type == tokenImage[APOSTROPHE] &&
		(textLength >= 2 && strcmp(text + textLength - 2, "'s")==0))
	{
		text[textLength - 2]=0;
		t->resetTermTextLen();
		return true;
	}
	else if(type == tokenImage[ACRONYM])
	{
		int j = 0;
		for(int i = 0; i < textLength; i++)
		{
			if(text[i] != '.')
			{
				text[j++]=text[i];
			}
		}
		text[j]=0;
		return true;
	}
}

		}
	}
}

