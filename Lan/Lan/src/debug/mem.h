#ifndef _Lan_debug_mem_
#define _Lan_debug_mem_

template<typename T>
class Array
{
public:
	T* values;
	unsigned int length;
	void deleteAll()
	{
		for(unsigned int i=0;i<length;i++)
		{
			if(values[i]!=NULL)
			{
				delete values[i];
				values[i]=NULL;
			}
		}
		if(values!=NULL)
		{
			delete[] values;
			values=NULL;
		}
	}
	void deleteArray()
	{
		if(values!=NULL)
		{
			delete[] values;
			values=NULL;
		}
	}
	Array(){
		values = NULL;
		length = 0;
	}
	Array(T* values, size_t length){
		this->values = values;
		this->length = length;
	}
	Array(size_t length){
		this->values = _CL_NEWARRAY(T,length);
		this->length = length;
	}
	~Array(){}

	const T operator[](size_t _Pos) const
	{
		if (length <= _Pos){
			//_CLTHROWA(CL_ERR_IllegalArgument,"vector subscript out of range");
			printf("vector subscript out of range");
		}
		return (*(values + _Pos));
	}
	T operator[](size_t _Pos)
	{
		if (length <= _Pos){
			//_CLTHROWA(CL_ERR_IllegalArgument,"vector subscript out of range");
			printf("vector subscript out of range");
		}
		return (*(values + _Pos));
	}


};


#endif