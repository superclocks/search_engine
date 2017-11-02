#include <fstream>
#include <string>
#include <vector>
#include <assert.h>
using namespace std;
typedef basic_string<char>::size_type S_T; 
static const S_T npos = -1; 

////trim指示是否保留空串，默认为保留。tok可以为任意多个字符
vector<string> tokenize(const string& src, string tok,           
                       bool trim=false, string null_subst="") 
{ 
   if( src.empty() || tok.empty() ) 
       throw "tokenize: empty string\0"; 
       
    vector<string> v; 
    S_T pre_index = 0, index = 0, len = 0; 
    while( (index = src.find_first_of(tok, pre_index)) !=npos ) 
    { 
        if( (len = index-pre_index)!=0 ) 
            v.push_back(src.substr(pre_index, len)); 
        else if(trim==false) 
            v.push_back(null_subst); 
        pre_index = index+1; 
    } 
    string endstr = src.substr(pre_index); 
    if( trim==false ) v.push_back( endstr.empty()?null_subst:endstr ); 
    else if( !endstr.empty() ) 
        v.push_back(endstr); 
    return v; 
} 

void quick_sort(int s[], int l, int r)
{
    if (l < r)
    {
        //Swap(s[l], s[(l + r) / 2]); //将中间的这个数和第一个数交换 参见注1
        int i = l, j = r, x = s[l];
        while (i < j)
        {
            while(i < j && s[j] >= x) // 从右向左找第一个小于x的数
                j--;  
            if(i < j) 
				s[i++] = s[j];
            while(i < j && s[i] < x) // 从左向右找第一个大于等于x的数
				i++;  
			if(i < j) 
				s[j--] = s[i];
        }
        s[i] = x;
        quick_sort(s, l, i - 1); // 递归调用 
        quick_sort(s, i + 1, r);
    }
}


void main(int argv,char**argc)
{
	string *str=new string[2];

	char* p="DFS";
	char* pp;
	pp=p;
	assert(pp);
	int a[10]={10,9,8,7,6,5,4,3,2,1};
	quick_sort(a,0,9);
	vector<string>::iterator iter;
	vector<string> aaa;
	aaa.push_back("dsfa");
	aaa.push_back("fadfa");
	iter=aaa.begin();
	//iter->n_Getpnext();
 	/*ifstream t("aa.txt");
	string str;
	t.seekg(0,ios::end);
	str.reserve(t.tellg());
	t.seekg(0,ios::beg);
	str.assign((std::istreambuf_iterator<char>(t)),
            std::istreambuf_iterator<char>());

	string a="adad ddf      fdaf dfafd";

	vector<string> res=tokenize(a," ",true);*/
}