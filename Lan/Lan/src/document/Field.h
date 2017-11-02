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
	const char* _name;  //��������"path","content"��
	char* _stringValue; //���еı��������
	Lan::util::Reader* _readerValue;
	jstreams::StreamBase<char>* _streamValue;

	int config;
	double boost;
	bool omitNorms;
public:
	enum Store //�Ƿ�洢�����ö��
	{
		Store_Yes=1,      //�洢����
		Store_No=2,       //���洢����
		Store_Compress=4  //��ѹ������ʽ�洢������ڴ��ĵ��Ͷ����������Ǻ����õ�
	};
	enum Index            //�������������ʽ
	{
		Index_No=16,          //����������������Ȼ�޷����������򣬵��û�����ͨ������"stored"����ʸ��������
		Index_Tokenized=32,   //���������������Ƚ��зִʲ�����һЩ�߼��ķ���
		Index_UnTokenized=64, //�����������������Ը�����зִʴ���
		Index_NoNorms=128     //���������������ǲ��Ը���ִʣ�Ҳ���洢norms��Ϣ
	};
	enum TermVector       //���ƴ�����
	{
		TermVector_No=256,            //���洢������
		TermVector_Yes=512,           //�洢ÿƪ�ĵ��Ĵ�����
		TermVector_With_Positions=1024, //�洢�������Լ�λ����Ϣ
		TermVector_With_Offsets=2048   //�洢���������ִ�ʱ��ƫ������Ϣ
	};

	Field(const char* name,const char* value,int configs); //���캯����name=������value=������ݣ�configs=ö�ٿ�����Ϣ
	~Field(); //��������

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