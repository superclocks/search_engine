#ifndef _Lan_index_FieldInfos_
#define _Lan_index_FieldInfos_
#include "Directory.h"
#include "Document.h"
#include "Field.h"
#include "VoidMap.h"
#include "VoidList.h"
#include "Equators.h"

namespace Lan
{namespace index{


class FieldInfo
{
public:
	const char* name;  //域的名称
	bool isIndexed;    //该域是否被索引
	const int number;  //该域的域号
	bool storeTermVector;             //是否存储术语向量
	bool storeOffsetWithTermVector;       //是否存储术语向量的偏移量
	bool storePositionWithTermVector; //是否存储术语向量的位置信息
	bool omitNorms;                   //是否存储与索引域相关的正规化文档信息

	FieldInfo(const char* fieldName,const bool isIndexed,const int fieldNumber,const bool storeTermVector,
		const bool storeOffsetWithVector, const bool storePositionWithTermVector,const bool omitNorms);
	~FieldInfo();
};

class FieldInfos/*:public LanBase*/
{
private:
	typedef Lan::util::CLHashMap<const char*, FieldInfo*,
		Lan::util::Compare::TChar,Lan::util::Equals::TChar> defByName; //按照<键，值>的形式存储域的信息FieldInfo
	defByName byName;
	Lan::util::CLArrayList<FieldInfo*,Lan::util::Deletor::Object<FieldInfo> > byNumber; //将域的信息FieldInfo直接存入
public:
	enum
	{
		Is_Indexed=0x1,
		Store_TermVector = 0x2,
		Store_Positions_With_TermVector = 0x4,
		Store_Offset_With_TermVector = 0x8,
		Omit_Norms = 0x10
	};

	FieldInfos();
	~FieldInfos();

	FieldInfos(Lan::store::Directory* d, const char* name);
	int fieldNumber(const char* fieldName) const;     //通过域的名称获取域的号
	FieldInfo* fieldInfo(const char* fieldName)const; //通过域名获得域
	const char* fieldName(const int fieldNumber)const;//通过域号获得域名称
	FieldInfo* fieldInfo(const int fieldNumber)const;//通过域号获得域
	int size() const;
	bool hasVectors() const;
	void add(const Lan::document::Document* doc); //为一个文档添加域的信息
	void add(FieldInfos* other); //从另一个域的信息集合FieldInfos中合并信息
	/*如果域不存在，就把域加入。如果域存在，检查域的isIndexed项是否与所设定的相同，如果不相同
	将其设置为已经设定的项，对TermVector也有相同的处理*/
	void add(const char* name, const bool isIndexed, const bool storeTermVector=false,
	          bool storePositionWithTermVector=false, bool storeOffsetWithTermVector=false, bool omitNorms=false);
	
	void add(const char** names, const bool isIndexed, const bool storeTermVector=false,
              bool storePositionWithTermVector=false, bool storeOffsetWithTermVector=false, bool omitNorms=false);

	void write(Lan::store::Directory* d, const char* name) const;
	void write(Lan::store::IndexOutput* output) const;

private:
	//void read(Lan::store::IndexInput* input);
	void addInternal( const char* name,const bool isIndexed, const bool storeTermVector,
		const bool storePositionWithTermVector, const bool storeOffsetWithTermVector, const bool omitNorms);

};

}}


#endif