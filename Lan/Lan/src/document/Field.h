#ifndef _Lan_document_Field__
#define _Lan_document_Field__
#include <assert.h>
#include <string>
#include "Reader.h"
#include "StreamBase.h"

using namespace std;
namespace Lan
{namespace document{


class Field
{
private:
	const char* _name;  //域的类别，如"path","content"等
	char* _stringValue; //域中的保存的内容
	Lan::util::Reader* _readerValue;
	jstreams::StreamBase<char>* _streamValue;

	int config;
	double boost;
	bool omitNorms;
public:
	enum Store //是否存储此域的枚举
	{
		Store_Yes=1,      //存储此域
		Store_No=2,       //不存储此域
		Store_Compress=4  //以压缩的形式存储域，这对于大文档和二进制数据是很有用的
	};
	enum Index            //控制域的索引方式
	{
		Index_No=16,          //不对域建立索引，虽然无法搜索到该域，但用户可以通过它的"stored"项访问该域的内容
		Index_Tokenized=32,   //对域建立索引，首先进行分词并进行一些高级的分析
		Index_UnTokenized=64, //对域建立索引，但不对该域进行分词处理
		Index_NoNorms=128     //对域建立索引，但是不对该域分词，也不存储norms信息
	};
	enum TermVector       //控制词向量
	{
		TermVector_No=256,            //不存储词向量
		TermVector_Yes=512,           //存储每篇文档的词向量
		TermVector_With_Positions=1024, //存储词向量以及位置信息
		TermVector_With_Offsets=2048   //存储词向量及分词时的偏移量信息
	};

	Field(const char* name,const char* value,int configs); //构造函数，name=域的类别，value=域的内容，configs=枚举控制信息
	~Field(); //析构函数

	const char* name();

	char* stringValue(); 
	Lan::util::Reader* readerValue();
	jstreams::StreamBase<char>* streamValue();
	bool isStored();
	bool isIndexed();
	bool isTokenized();
	bool isCompressed();
	void setConfig(int termVector);
	bool isTermVectorStored();
	bool isStoreOffsetWithTermVector();
	bool isStorePositionWithTermVector();
	double getBoost();
	void setBoost(double value);
	bool isBinary();
	bool getOmitNorms();
	void setOmitNorms(bool omitNorms);
	char* toString();
};
	
}}
#endif