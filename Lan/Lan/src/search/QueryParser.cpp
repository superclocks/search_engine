//#include "QueryParser.h"
//
//Query QueryParser::parse(string querystring)
//{
//    vector<string> qs = tokenize(querystring," ",true);
//    vector<TermQuery> termqueries;
//	for(unsigned int i=0;i<qs.size();i++)
//	{
//		string q=qs[i];
//		termqueries.push_back(TermQuery(q));
//    }
//    return Query(termqueries);    
//}
//
//vector<string> QueryParser::tokenize(const string& src, string tok,bool trim, string null_subst) 
//{ 
//	if( src.empty() || tok.empty() ) 
//	{
//		throw "tokenize: empty string\0"; 
//	}
//    vector<string> v; 
//    S_T pre_index = 0, index = 0, len = 0; 
//    while( (index = src.find_first_of(tok, pre_index)) !=npos ) 
//    { 
//        if( (len = index-pre_index)!=0 ) 
//            v.push_back(src.substr(pre_index, len)); 
//        else if(trim==false) 
//            v.push_back(null_subst); 
//        pre_index = index+1; 
//    } 
//    string endstr = src.substr(pre_index); 
//    if( trim==false ) v.push_back( endstr.empty()?null_subst:endstr ); 
//    else if( !endstr.empty() ) 
//        v.push_back(endstr); 
//    return v; 
//} 
//
//
