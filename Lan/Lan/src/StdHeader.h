
#ifndef lucene_stdheader_h
#define lucene_stdheader_h


	#define L_NS_DEF(sub) namespace Lan{ namespace sub{
	#define L_NS_DEF2(sub,sub2) namespace lucene{ namespace sub{ namespace sub2 {

	#define L_NS_END }}
	#define L_NS_END2 }}}

	#define L_NS_USE(sub) using namespace lucene::sub;
	#define L_NS_USE2(sub,sub2) using namespace lucene::sub::sub2;

	#define L_NS(sub) lucene::sub
	#define L_NS2(sub,sub2) lucene::sub::sub2

#endif // STDHEADER_H
