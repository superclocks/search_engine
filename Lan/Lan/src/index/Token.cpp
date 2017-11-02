#include "Token.h"
namespace Lan
{
	namespace index
	{
Token::Token(string term)
{
    this->term = term;
}
string Token::getterm()
{
	return term;
}
void Token::setterm(string term)
{
	this->term=term;
}

	}
}
