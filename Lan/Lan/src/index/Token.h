#ifndef _Lan_index_Token_
#define _Lan_index_Token_
#include <string>
using namespace std;

namespace Lan
{
	namespace index
	{
class Token 
{
private:
    string term;
public:
	Token(string term); 
	void setterm(string term);
	string getterm();
};
	}
}
#endif