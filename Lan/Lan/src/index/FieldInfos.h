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
	const char* name;  //�������
	bool isIndexed;    //�����Ƿ�����
	const int number;  //��������
	bool storeTermVector;             //�Ƿ�洢��������
	bool storeOffsetWithTermVector;       //�Ƿ�洢����������ƫ����
	bool storePositionWithTermVector; //�Ƿ�洢����������λ����Ϣ
	bool omitNorms;                   //�Ƿ�洢����������ص����滯�ĵ���Ϣ

	FieldInfo(const char* fieldName,const bool isIndexed,const int fieldNumber,const bool storeTermVector,
		const bool storeOffsetWithVector, const bool storePositionWithTermVector,const bool omitNorms);
	~FieldInfo();
};

class FieldInfos/*:public LanBase*/
{
private:
	typedef Lan::util::CLHashMap<const char*, FieldInfo*,
		Lan::util::Compare::TChar,Lan::util::Equals::TChar> defByName; //����<����ֵ>����ʽ�洢�����ϢFieldInfo
	defByName byName;
	Lan::util::CLArrayList<FieldInfo*,Lan::util::Deletor::Object<FieldInfo> > byNumber; //�������ϢFieldInfoֱ�Ӵ���
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
	int fieldNumber(const char* fieldName) const;     //ͨ��������ƻ�ȡ��ĺ�
	FieldInfo* fieldInfo(const char* fieldName)const; //ͨ�����������
	const char* fieldName(const int fieldNumber)const;//ͨ����Ż��������
	FieldInfo* fieldInfo(const int fieldNumber)const;//ͨ����Ż����
	int size() const;
	bool hasVectors() const;
	void add(const Lan::document::Document* doc); //Ϊһ���ĵ���������Ϣ
	void add(FieldInfos* other); //����һ�������Ϣ����FieldInfos�кϲ���Ϣ
	/*����򲻴��ڣ��Ͱ�����롣�������ڣ�������isIndexed���Ƿ������趨����ͬ���������ͬ
	��������Ϊ�Ѿ��趨�����TermVectorҲ����ͬ�Ĵ���*/
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